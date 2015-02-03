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

  std::string function_name;
  getline(ss, function_name);

  // suivant le cas, bloquer le verrou en mode WRITE ou en mode READ
  if (change_data)
    pthread_rwlock_wrlock(&lock);  // bloque en mode WRITE
  else
    pthread_rwlock_rdlock(&lock);  // bloque en mode READ
  
  
  // executer la commande et calculer la reponse

  std::map<string, FunctionManager>::iterator it = 
       functions.find(function_name);
  if (it != functions.end()){
    try {
        FunctionManager ptr = it->second;
        response = (this->*ptr)(ss);
    } catch (const runtime_error & e) {
        response = e.what(); 
    }
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

string TCPServer::create_photo (stringstream & ss) {
    manager.create_photo(ss);
    return "Your photo was created";
}

string TCPServer::create_video (stringstream & ss) {
    manager.create_video(ss);
    return "Your video was created";
}

string TCPServer::create_film (stringstream & ss) {
    manager.create_film(ss);
    return "Your film was created";
}

string TCPServer::create_group (stringstream & ss) {
    return "Not implemented yet";
}

string TCPServer::remove_multimedia (stringstream & ss) {
    std::string name;
    getline(ss, name);
    manager.remove_multimedia(name);
    return "Multimedia file removed";
}

string TCPServer::remove_group (stringstream & ss) {
    std::string name;
    getline(ss, name);
    manager.remove_group(name);
    return "Group removed";
}

string TCPServer::search_multimedia (stringstream & ss) {
    std::string name;
    getline(ss, name);
    return manager.search_multimedia(name);
}

string TCPServer::search_group (stringstream & ss) {
    std::string name;
    getline(ss, name);
    return manager.search_group(name);
}

string TCPServer::play (stringstream & ss) {
    std::string name;
    getline(ss,name);
    manager.play(name);
    return "Playing...";
}
