//
//  Trigger.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//


#ifndef zork_clone_Trigger_h
#define zork_clone_Trigger_h

#include <string>
#include "XMLParse.h"

using namespace std;

class XMLParse;

struct TrigCondition
{
    bool has;
    string object;
    string owner;
    string status;
};

class Trigger
{
public:
    Trigger();
    Trigger(xml_node<> *);
    
    TrigCondition getCondition();
    string getTriggerCommand();
    string getAction();
    string getType();
    string getTriggerPrint();
    bool getActivated();
    void setActivated(bool);
    void printTrigger();
    
private:
    bool activated;
    string type;
    string triggerCommand;
    string triggerPrint;
    string action;
    TrigCondition tc;
    
};

#endif
