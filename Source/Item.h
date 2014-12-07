//
//  Item.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <string>
#include <vector>
#include "XMLParse.h"

using namespace std;

#ifndef zork_clone_Item_h
#define zork_clone_Item_h

struct TurnOn
{
    string turnOnPrint;
    string action;
};

class Item
{
public:
    Item();
    Item(XMLParse *, xml_node<> *);
    
    string getName();
    string getWriting();
    bool getCanTurnOn();
    void setCanTurnOn(bool b);
    string getAction();
    string getTurnOnPrint();
    void setStatus(string s);
    
private:
    string name;
    string description;
    string status;
    string writing;
    TurnOn turnon;
    bool canTurnOn;
    //bool turnon;
    //vector<Trigger> triggers;
};

#endif
