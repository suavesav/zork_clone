//
//  Player.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#ifndef zork_clone_Player_h
#define zork_clone_Player_h

#include <string>
#include <vector>

class Player
{
public:
    Player();
private:
    int health;
    int maxHealth;
    bool dead;
    //Inventory
    //Position
    string currRoom;
    
}

#endif
