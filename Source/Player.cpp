//
//  Player.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/6/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Player.h"

Player::Player()
{
    health = 100;
    maxHealth = 250;
    dead = 0;
}

//Getters and Setters for Player's current location
string Player::getCurrRoom()
{
    return currRoom;
}

void Player::setCurrRoom(string cr)
{
    currRoom = cr;
}


void Player::addInventory(string i)
{
    inventory.push_back(i);
}

void Player::delInventory(string i)
{
    int location = findItem(i);
    if(location != -1)
        inventory.erase(inventory.begin()+location);
}

int Player::findItem(string s)
{
    for(int counter = 0; counter < inventory.size(); counter++)
    {
        if(inventory.at(counter) == s)
        {
            return counter;
        }
    }
    return -1;
}

void Player::showInventory()
{
    cout << "Inventory: ";
    if(inventory.size() == 0)
    {
        cout << "empty\n";
        return;
    }
    for(int counter = 0; counter < inventory.size(); counter++)
    {
        if(counter > 0)
            cout << ", ";
        cout << inventory.at(counter);
    }
    cout << "\n";
}