#include "connection.h"

connection::connection()
{
    //default constructor not used
}

connection::connection(int mySocket, int &server_fd, struct sockaddr_in &address) {
    this->mySocket = mySocket;
    this->server_fd = server_fd;
    this->address = address;
}

std::string connection::listen() {
    char buffer[1024] = { 0 };

    std::cout << "listening for Client command\n";
    read(mySocket, buffer, 1024);
    std::cout << "Recieved: " << buffer << std::endl;
    return std::string(buffer);
}

std::string connection::sendRPC(std::string RPC, bool bRead)
{
    char reply[1024] = { 0 };

    send(mySocket, RPC.c_str(), RPC.size() + 1, 0);

    if (bRead) {
        read(mySocket, reply, 1024);
    }

    return std::string(reply);
}

void connection::setSocket(int newSocket) {
    this->mySocket = newSocket;
}

int connection::getSocket() {
    return mySocket;
}

void connection::setThreadNum(int num) {
    this->threadNum = num;
}

int connection::getThreadNum() {
    return threadNum;
}

void connection::end() {
    std::string disc = "Connection Terminated";

    std::cout << "closing connection\n";
    send(mySocket, disc.c_str(), disc.size()+1, 0);
    delete this;
}

void connection::closeSocket() {
    close(mySocket);
}
