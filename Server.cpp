
#include "Server.h"

Server::Server(int port)throw (const char*) {
    //tcp communication with ipv4 addresses.
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0)
        throw("Socket Failed");
    stop_server
}

void Server::start(ClientHandler& ch)throw(const char*){
}

void Server::stop(){
    t->join(); // do not delete this!
}

Server::~Server() {
}

