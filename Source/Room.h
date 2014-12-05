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
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "XMLParse.h"

using namespace std;

#ifndef zork_clone_Room_h
#define zork_clone_Room_h

struct Border
{
    string name;
    string direction;
};

class Room
{
public:
    Room();
    Room(XMLParse *, xml_node<> *);
    
    string getName();
    
private:
    string name;
    string status;
    string type;
    string description;
    vector<Border> borders;
    vector<string> containers;
    vector<string> items;
    vector<string> creatures;
    //vector<Trigger> triggers;
};

#endif
