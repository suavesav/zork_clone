//
//  Room.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//



#ifndef zork_clone_Room_h
#define zork_clone_Room_h

#include <iostream>
#include <string>
#include <vector>
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "XMLParse.h"

using namespace std;

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
//    Room(const Room &room);
    
    string getName();
    bool getInRoom();
    void printDescription();
    int itemInRoom(string);
    int containerInRoom(string);
    void delItem(string);
    void addItem(string);
    void printItems();
    string roomInDirection(string);
    void addTriggers(vector<Trigger *> *);
    vector<string> getContainers();
    vector<string> getCreatures();
    int creatureInRoom(string);
    void setStatus(string);
    string getType();
    
private:
    bool inRoom;
    string name;
    string status;
    string type;
    string description;
    vector<Border> borders;
    vector<string> containers;
    vector<string> items;
    vector<string> creatures;
    vector<Trigger> triggers;
};

#endif
