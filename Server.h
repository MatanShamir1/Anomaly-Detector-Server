/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <pthread.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include <iostream>
#include <istream>
#include <unistd.h>
#include "CLI.h"


using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){
        SocketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    int server_socket;
    thread* t; // the thread to run the start() method in
    bool stop_server;
    sockaddr_in my_addr;
    socklen_t client_size;

    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
