//
//  TCPServer.cpp: TCP/IP INET Server.
//  (c) Eric Lecolinet - Telecom ParisTech - 2013.
//  http://www.telecom-paristech.fr/~elc
//

#include <TCPServer.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <multimedia_manager.h>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Hook for TCPServer::startReadMessages() (see TCPServer::run())

struct TCPServerHook {
  TCPServerHook(TCPServer* _server, Socket* _sock)
  : server(_server), sock(_sock) {}
  TCPServer* server;
  Socket* sock;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

TCPServer::TCPServer() : servsock() {
  pthread_rwlock_init(&lock, NULL);
  //Create a new manager
  //TODO Load previous manager
  manager = MultimediaManager();
  functions =
      {{"create_photo",&TCPServer::create_photo},
       {"create_video",&TCPServer::create_video},
       {"create_film",&TCPServer::create_video},
       {"create_group",&TCPServer::create_group},
       {"remove_multimedia",&TCPServer::remove_multimedia},
       {"remove_group",&TCPServer::remove_group},
       {"search_multimedia",&TCPServer::search_multimedia},
       {"search_group",&TCPServer::search_group},
       {"play",&TCPServer::play}};
}

TCPServer::~TCPServer() {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int TCPServer::run(int port)
{
  // lier le ServerSocket a ce port
  int status = servsock.bind(port);
  
  if (status < 0) {
    cerr << "TCPServer: can't bind on port: "<<port<<" status="<<status<< endl;
    return status;  // valeur negative, voir Socket::bind()
  }

  // ignorer le signal SIGPIPE qui avorterait le serveur en cas d'erreur reseau
  servsock.ignoreSigPipe();
  
  while (true) {
    Socket* sock = servsock.accept();

    if (sock == NULL) {
      cerr << "TCPServer: accept() failed" << endl;
      continue;  // continue va a la prochaine iteration de while()
    }

    // lancer la lecture des messages de ce socket dans un thread.
    // pthread_create() cree un thread qui appelle la methode statique
    // startReadMessages() avec un argument de type (void*) qui est en fait
    // un TCPServerHook*. Ceci permet a startReadMessages() d'appeller la
    // methode d'instance readMessages() avec les argument adequats.

    TCPServerHook* hook = new TCPServerHook(this, sock);
    pthread_t tid;
    
    int status = pthread_create(&tid, NULL, startReadMessages, hook);
    if (status < 0)
      cerr << "TCPServer: pthread_create() failed" << endl;
  }
  
  pthread_exit(NULL);
  return 0;  // OK
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// called by pthread_create()

void* TCPServer::startReadMessages(void* _hook)
{
  TCPServerHook* hook = static_cast<TCPServerHook*>(_hook);
  hook->server->readMessages(hook->sock);
  delete hook;
  return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void TCPServer::readMessages(Socket* sock)
{
  SocketBuffer sockbuf(sock);
  
  while (true) {
    std::string message, response;
    
    // lire les données envoyées par le client
    // SocketBuffer::readLine() lit jusqu'au premier '\n' (qui est supprimé)
    ssize_t received = sockbuf.readLine(message);
    
    if (received < 0) {
      closeSocketAndThread(sock, "read error");
      continue;
    }
    
    if (received == 0) {
      closeSocketAndThread(sock, "connection closed by client");
      continue;
    }
    
    // traiter le message et retourner la reponse
    // ferme la connection si la valeur de retour est false
    if (! processMessage(message, response)) {
      closeSocketAndThread(sock, "closing connection with client");
      continue;
    }
    
    // toujours envoyer une reponse au client (sinon il va se bloquer)
    // SocketBuffer::writeLine() envoie tout et rajoute '\n'
    ssize_t sent = sockbuf.writeLine(response);
    
    if (sent < 0) {
      closeSocketAndThread(sock,"write error");
      continue;
    }
    
    if (sent == 0) {
      closeSocketAndThread(sock, "connection closed by client");
      continue;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void TCPServer::closeSocketAndThread(Socket* sock, const char* msg)
{
  cerr << "TCPServer: " << msg << " on socket: "<< sock << endl;
  delete sock;          // detruit le socket (NB: le destr fait sock.close())
  pthread_exit(NULL);   // termine le thread
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Traite le message 'message' et retourne la reponse 'response' ainsi qu'un
// booleen (par return) qui indique si la connection avec le client doit se
// poursuivre (true) ou etre fermée (false).
//
// Cette fonction peut etre executee en parallele par plusieurs threads sauf si
// le verrou 'lock' est bloqué en mode WRITE

bool TCPServer::processMessage(const std::string& message, std::string& response)
{
  // cette variable indique si la commande modifie les donnees du programme
  // par defaut on suppose que oui
  bool change_data = true;

  //String stream
  std::stringstream ss;
  ss << message;
  //arguments first
  std::map<string, std::string> args;
  boost::archive::binary_iarchive iarch(ss);
  iarch >> args;
  std::string function_name;
  std::map<string, string>::const_iterator function_it =
      args.find("function_name");

  if (function_it == args.end()) {
      function_name = "";
  } else {
      function_name = function_it->second;
  }

  // suivant le cas, bloquer le verrou en mode WRITE ou en mode READ
  if (change_data)
    pthread_rwlock_wrlock(&lock);  // bloque en mode WRITE
  else
    pthread_rwlock_rdlock(&lock);  // bloque en mode READ
  
  
  // executer la commande et calculer la reponse

  std::map<string, FunctionManager>::iterator it = 
       functions.find(function_name);
  if (it != functions.end()){
    FunctionManager ptr = it->second;
    response = (this->*ptr)(args);
  }else {
    response = "Unknown function";
  }

  // pour l'instant on se contente de prefixer le message par "OK: "
  cout << "TCPServer: message: " << message << endl;
  // sleep(8);                    // sert uniquement a tester le verrou
  cout << "TCPServer:TCPServer response: " << response << endl;
  
  
  // debloque le verrou (attention ne pas oublier cette ligne !)
  pthread_rwlock_unlock(&lock);

  // retourner false pour fermer la connexion
  return true;
}

string TCPServer::create_photo (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name, it_date, it_path, it_place;
    it_name  = args.find("name");
    it_date  = args.find("date");
    it_path  = args.find("pathname");
    it_place = args.find("place");
    if (it_name  == args.end() 
     && it_date  == args.end()
     && it_path  == args.end()
     && it_place == args.end()) {
        manager.create_photo();
        return "A new default photo was created.";
    } else if (it_name  == args.end()
            || it_date  == args.end()
            || it_path  == args.end()
            || it_place == args.end()) {
        return "A problem appeared when reading arguments";
    } else {
        std::string name  = it_name->second;
	string path  = it_path->second;
	string place = it_place->second;
	unsigned long date = stoul(it_date->second);
	manager.create_photo(name, date, path, place);
	return "Your photo was created";
    }
}

string TCPServer::create_video (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name, it_date, it_path, it_length;
    it_name  = args.find("name");
    it_date  = args.find("date");
    it_path  = args.find("pathname");
    it_length = args.find("length");
    if (it_name  == args.end() 
     && it_date  == args.end()
     && it_path  == args.end()
     && it_length == args.end()) {
        manager.create_video();
        return "A new default video was created.";
    } else if (it_name  == args.end()
            || it_date  == args.end()
            || it_path  == args.end()
            || it_length == args.end()) {
        return "A problem appeared when reading arguments";
    } else {
        std::string name  = it_name->second;
	string path  = it_path->second;
	unsigned int length = stoul(it_length->second);
	unsigned long date = stoul(it_date->second);
	manager.create_video(name, date, path, length);
	return "Your video was created";
    }
}

string TCPServer::create_film (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name, it_date, it_path, it_chapters,
        it_number;
    it_name  = args.find("name");
    it_date  = args.find("date");
    it_path  = args.find("pathname");
    it_chapters  = args.find("chapters");
    it_number    = args.find("number_chapters");
    if (it_name  == args.end() 
     && it_date  == args.end()
     && it_path  == args.end()
     && it_chapters == args.end()
     && it_number   == args.end()) {
        manager.create_film();
        return "A new default video was created.";
    } else if (it_name  == args.end()
            || it_date  == args.end()
            || it_path  == args.end()){
        return "A problem appeared when reading arguments";
    } else {
        std::string name  = it_name->second;
	string path  = it_path->second;
	unsigned long date = stoul(it_date->second);
	if (it_chapters == args.end() && it_number == args.end()) {
	    manager.create_film(name, date, path);
	    return "Your film was created";
	} else if (it_chapters != args.end() && it_number != args.end()) {
            unsigned int number = stoul(it_number->second);
	    unsigned int i = 0;
	    std::stringstream ss;
	    return "Your film was created";
	    ss << it_chapters->second;
	    unsigned int * chapters = new unsigned int[number];
            for (i = 0; i < number; i++) {
                ss >> chapters[i];
            }
	    manager.create_film(name,date,path,chapters,number);
	    delete chapters;
	    return "Your film was created";
	} else {
            return "A problem appeared when reading arguments";
	}
    }
}

string TCPServer::create_group (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name;
    it_name = args.find("name");
    if (it_name == args.end()) {
        manager.create_group();
	return "Default group created";
    } else {
        std::string name = it_name->second;
	manager.remove_group(name);
	return "Group created";
    }
}

string TCPServer::remove_multimedia (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name;
    it_name = args.find("name");
    if (it_name == args.end()) {
        return "A problem appeared when reading arguments";
    } else {
        std::string name = it_name->second;
	manager.remove_multimedia(name);
	return "Multimedia file removed";
    }
}

string TCPServer::remove_group (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name;
    it_name = args.find("name");
    if (it_name == args.end()) {
        return "A problem appeared when reading arguments";
    } else {
        std::string name = it_name->second;
	manager.remove_group(name);
	return "Group removed";
    }
}

string TCPServer::search_multimedia (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name;
    it_name = args.find("name");
    if (it_name == args.end()) {
        return "A problem appeared when reading arguments";
    } else {
        std::string name = it_name->second;
	return manager.search_multimedia(name);
    }
}

string TCPServer::search_group (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name;
    it_name = args.find("name");
    if (it_name == args.end()) {
        return "A problem appeared when reading arguments";
    } else {
        std::string name = it_name->second;
	return manager.search_group(name);
    }
}

string TCPServer::play (const std::map<string,string>& args) {
    std::map<string, std::string>::const_iterator it_name;
    it_name = args.find("name");
    if (it_name == args.end()) {
        return "A problem appeared when reading arguments";
    } else {
        std::string name = it_name->second;
	manager.play(name);
	return "Playing...";
    }
}
