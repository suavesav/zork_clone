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
#include "Item.h"

using namespace std;
#ifndef zork_clone_Creature_h
#define zork_clone_Creature_h

struct attckCondition
{
    string attackObject;
    string attackStatus;
};

struct attack
{
    vector<string> action;
    attckCondition ac;
    string attackPrint;
};

class Creature
{
public:
    Creature();
    Creature(XMLParse *, xml_node<> *);
    
    string getName();
    void addTriggers(vector<Trigger *> *);
    bool checkVulnerability(string weapon);
    bool attackWith(Item *);
    vector<string> getAttackAction();
    
    
private:
    string name;
    string status;
    string description;
    vector<string> vulnerability;
    vector<Trigger> triggers;
    attack atk;
    
    
};

#endif
