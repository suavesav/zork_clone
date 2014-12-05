//
//  Map.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <vector>
#include <unordered_map>
#include "Room.h"
#include "Creature.h"
#include "Container.h"
#include "Item.h"
#include "XMLParse.h"


#ifndef zork_clone_Map_h
#define zork_clone_Map_h

class Map
{
public:
    Map();
    Map(XMLParse *);
    
private:
    unordered_map<string, Room> rooms;
    unordered_map<string, Creature> creatures;
    unordered_map<string, Container> containers;
    unordered_map<string, Item> items;
};
#endif
