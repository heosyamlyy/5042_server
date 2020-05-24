//
// Created by liuyang016 on 5/24/20.
//

#include "game.h"
#include "connection.h"

game::game()
{
    //default constructor
}

game::game(connection *Connection)
{
    //creates a game played via myConnection given by the server/client
    this->myConnection = Connection;
}

void game::playGame() {

    printf("You're playing a game on its own thread! How fun!\n");
    myConnection->sendRPC("You're playing a game on a server! How fun!", false);
    sleep(1);
    printf("You're playing a game on its own thread! How fun!\n");
    myConnection->sendRPC("You're playing a game on a server! How fun!", false);
    sleep(3);
    printf("You're playing a game on its own thread! How fun!\n");
    myConnection->sendRPC("You're playing a game on a server! How fun!", false);
    sleep(2);

    return;
}
