//
// Created by liuyang016 on 5/24/20.
//

#ifndef INC_5042_CONNECTION_H
#define INC_5042_CONNECTION_H
#pragma once
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include <iostream>

class connection

{
public:
    connection();
    connection(int mySocket, int &server_fd, struct sockaddr_in &address);

    std::string sendRPC(std::string RPC, bool bRead);
    std::string listen();
    void setSocket(int newSocket);
    int getSocket();
    void setThreadNum(int num);
    int getThreadNum();
    void end();
    void closeSocket();

private:
    int threadNum;
    int mySocket;
    int server_fd;
    struct sockaddr_in address;
    int addressLen = sizeof(address);

};


#endif //INC_5042_CONNECTION_H
