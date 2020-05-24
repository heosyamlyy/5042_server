//
// Created by liuyang016 on 5/24/20.
//

#ifndef INC_5042_GAME_H
#define INC_5042_GAME_H
#pragma once
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <string>

class connection;

class game {
public:
    //constructors
    game();
    game(connection *connection);

    //public functions
    void playGame();

private:
    //private data
    connection* myConnection;

    //private functions
};

#endif //INC_5042_GAME_H
