#include "server.h"
#include "game.h"
#include "connection.h"

int main() {
    int server_fd;
    struct sockaddr_in new_address;
    server myServer;

    /*DISCLAIMER: Everything now handles exaclty 1 client.
    * multiclient (even multiple players playing single player)
    * will take more work.
    */

    //start server
    myServer.serverSetup(new_address, server_fd);
    do {
        myServer.createConnection(new_address, server_fd);
    } while(true);

    std::cout << "Shutting down server\n";

    return 1;
}
