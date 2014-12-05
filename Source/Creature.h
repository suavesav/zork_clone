//
//  Creature.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <string>
#include <vector>
#include "Trigger.h"
#include "XMLParse.h"

using namespace std;
#ifndef zork_clone_Creature_h
#define zork_clone_Creature_h

class Creature
{
public:
    Creature();
    Creature(XMLParse *, xml_node<> *);
    
    string getName();
    
private:
    string name;
    int health;
    string description;
    vector<string> vulnerability;
    //int hit;
    //vector<Trigger> triggers;
    
    
};

#endif
