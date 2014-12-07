//
//  Game.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/6/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "Map.h"
#include "Player.h"
#include "Room.h"

using namespace std;
#ifndef zork_clone_Game_h
#define zork_clone_Game_h


class Game
{
public:
    Game();
    Game(Map);
    void gameLoop();
    int parseInput(string);
    
private:
    Map map;
    Player player;
    bool gameOver;
    Room room;
    
};

#endif
