//
//  TCPServer.h: TCP/IP INET Server.
//  (c) Eric Lecolinet - Telecom ParisTech - 2014.
//  http://www.telecom-paristech.fr/~elc
//

#ifndef __TCPServer__
#define __TCPServer__
#include <pthread.h>
#include "Socket.h"
#include <map>
#include <string>
#include "multimedia_manager.h"

/** TCPServer: TCP/IP INET Server.
 * This class supports TCP/IP AF_INET connections following the IPv4 Internet
 * protocol. Other families, such as AF_INET6 or AF_UNIX are not yet supported.
 */
class TCPServer {
public:
  TCPServer();
  virtual ~TCPServer();
  
  /** starts the main loop of the server on this port.
   * returns 0 for normal termination, a negative value otherwise.
   */
  virtual int run(int port);

protected:
  /** processes a message and returns the response
   * the connection with the client will be closed if false is returned.
   */
  virtual bool processMessage(const std::string& message, std::string& response);

  /// reads messages from a client.
  virtual void readMessages(Socket*);
  
  /// callback function of pthread_create() that calls readMessages().
  static void* startReadMessages(void*);

  /// closes the socket (and the corresponding thread) of a client.
  virtual void closeSocketAndThread(Socket*, const char* msg);

  ServerSocket servsock;
  pthread_rwlock_t lock;
  
private: // disables copy.
  //Return if it modifies program datas.
  //Takes the name of the function, the args (map) and the string to send.
  typedef string (TCPServer::*FunctionManager)(stringstream&);

  MultimediaManager manager;
  TCPServer(const TCPServer&);
  TCPServer& operator=(const TCPServer&);
  //Map to find the corresponding function.
  map<string, FunctionManager> functions;
  //Create photo alias
  string create_photo (stringstream &);
  //Create video alias
  string create_video (stringstream &);
  //Create film alias
  string create_film (stringstream &);
  //create group
  string create_group (stringstream &);
  //remove multimedia alias
  string remove_multimedia (stringstream &);
  //remove group alias
  string remove_group (stringstream &);
  //search multimedia file.
  string search_multimedia (stringstream &);
  //search group file.
  string search_group (stringstream &);
  //play multimedia file
  string play (stringstream &);
};


#endif

