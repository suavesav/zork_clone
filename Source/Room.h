//
//  Room.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#ifndef zork_clone_Room_h
#define zork_clone_Room_h

struct Border
{
    string name;
    int direction;
};

class Room
{
public:
    Room();
    
private:
    string name;
    int status;
    int type;
    string description;
    vector<Border> borders;
    vector<Container> containers;
    vector<Item> items;
    vector<Creature> creatrues;
    vector<Trigger> triggers;
}

#endif
