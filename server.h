//
// Created by liuyang016 on 5/24/20.
//

#ifndef INC_5042_SERVER_H
#define INC_5042_SERVER_H
#pragma once
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <iostream>
#include <iterator> //for spliting
#include <cstring> //for spliting
#include <sstream> //for spliting
#include <signal.h>
#define MAXCONNECTION 500
#define SERVER "SERVER> "

class connection;
class game;

class server {

public:
    server();
    server(int port);

    void serverSetup(struct sockaddr_in &address, int &server_fd); //will we have to re-run this for every new connection?
    void createConnection(struct sockaddr_in &address, int &server_fd);

    void startTask(connection* myConnection);

private:
    //default port if server is instantiated using default constructor
    int PORT = 12105;

    bool bFirstRun = true; //needed only if we have to run serverSetup for each new connection.
    std::vector<std::string> splitBuffer(std::string buffer);
    bool login(int socket); //handles the login RPC to the server before a connection is made (connections handle all reads/sends after they are made)
    bool authenticate(std::string userName, std::string password); //authenticates users

    //pthreads won't accept member functions, so we force it to be a "non-member" function.
    //making this static is apparently bad practice, but we are hacking Object Oriented C++ into old school C threads, so...
    static void *task(void *arg);
};

#endif //INC_5042_SERVER_H
