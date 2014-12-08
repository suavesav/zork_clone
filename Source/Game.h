//
//  Game.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/6/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//




#ifndef zork_clone_Game_h
#define zork_clone_Game_h

#include <iostream>
#include <string>
#include <sstream>
#include "Map.h"
#include "Player.h"
#include "Room.h"
#include "Trigger.h"

using namespace std;

class Game
{
public:
    Game();
    Game(Map);
    void gameLoop();
    int parseInput(string);
    void checkTriggers();
    void parseTrigger(string);
    void update(string, string);
    void parseAction(string);
    void checkOwner(Trigger T);
    void checkStatus(Trigger T);
    
private:
    Map map;
    Player player;
    bool gameOver;
    Room *room;
    vector<Trigger> currentTriggers;
    
};

#endif
