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
#include <iostream>

using namespace std;

class Player
{
public:
    Player();
    void setCurrRoom(string);
    string getCurrRoom();
    
    void addInventory(string);
    void delInventory(string);
    void showInventory();
    int findItem(string);
    
private:
    int health;
    int maxHealth;
    bool dead;
    //Inventory
    vector<string> inventory;
    //Position
    string currRoom;
};

#endif
