
#include <csignal>
#include <signal.h>
#include "Server.h"

Server::Server(int port)throw (const char*) {
    //tcp communication with ipv4 addresses.
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(this->server_socket < 0)
        throw("Socket Failed");
    this->stop_server = false;
    this->my_addr.sin_family = AF_INET;
    this->my_addr.sin_port = htons(port);
    this->my_addr.sin_addr.s_addr = INADDR_ANY;
    this->client_size = sizeof(my_addr);
    if(bind(server_socket, (sockaddr*)&my_addr, this->client_size)<0){
        throw("bind failed");
    }
}
void sig_handler(int signum){

    printf("Inside handler function\n");
}
void Server::start(ClientHandler& ch)throw(const char*){
    //create a new thread with this pointer and the client handler for it to deal with clients.
    this->t = new thread([&ch, this](){
        //set the maximum number of clients to 3.
        if(listen(server_socket, 3)<0){
            throw("listen failed");
        }
        signal(SIGALRM , sig_handler);
        while(!stop_server){
            //maybe set time out to this accept, if the condition was true but there is no other client actually.
            alarm(10);
            int client_ID = accept(this->server_socket,(sockaddr*)&this->my_addr, &this->client_size);
            if(client_ID>0){
                ch.handle(client_ID);
            } else{
                throw("accept failed");
            }
            alarm(0);
            close(client_ID);
        }
        //close the server socket when finished with all clients- stop listening in this port.
        close(server_socket);
    });
}

void Server::stop(){
    this->stop_server = true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

