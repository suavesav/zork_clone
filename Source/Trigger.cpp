//
//  Trigger.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/7/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//
#include "Trigger.h"

Trigger::Trigger()
{}

Trigger::Trigger(xml_node<> * root_node)
{
    activated = 0;
    xml_node<> * pNode = root_node->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
        if(node == "type")
        {
            type = pNode->value();
        }
        else if(node == "command")
        {
            triggerCommand = pNode->value();
        }
        else if(node == "print")
        {
            triggerPrint = pNode->value();
        }
        else if(node == "action")
        {
            action = pNode->value();
        }
        else if (node == "condition")
        {
            xml_node<> * nextNode = pNode->first_node();
            while(nextNode != 0)
            {
                string att = nextNode->name();
                if(att == "has")
                {
                    string val = nextNode->value();
                    //cout << (strcmp(nextNode->value(), "no") ? "match" : "nomatch") << "\n";
                    if(val == "no")
                        tc.has=0;
                    else
                        tc.has = 1;
                }
                else if(att == "object")
                {
                    tc.object = nextNode->value();
                }
                else if(att == "owner")
                {
                    tc.owner = nextNode->value();
                }
                else if(att == "status")
                {
                    tc.status = nextNode->value();
                }
                nextNode = nextNode->next_sibling();
            }
        }
        
        pNode = pNode->next_sibling();
    }
}

TrigCondition Trigger::getCondition()
{
    return tc;
}

string Trigger::getTriggerCommand()
{
    return triggerCommand;
}

string Trigger::getAction()
{
    return action;
}

string Trigger::getType()
{
    return type;
}

string Trigger::getTriggerPrint()
{
    return triggerPrint;
}

bool Trigger::getActivated()
{
    return activated;
}

void Trigger::setActivated(bool b)
{
    activated = b;
}


void Trigger::printTrigger()
{
    cout<< "Command: " << triggerCommand << "\nType: " << type << "\n Condition: \thas " << tc.has << "\n\tobject " << tc.object<< "\n\towner " << tc.owner << "\n\tstatus " << tc.status << "\nAction: " << action<<"\n";
}
//bool Trigger::parseTrigger(Trigger T, string s)
//{
//    activated = 0;
//    if(triggerCommand == "" || triggerCommand == s)
//    {
//        if(tc.owner != "")
//        {
//            checkOwner(T);
//        }
//        else if(tc.status != "")
//        {
//            checkStatus(T);
//        }
//    }
//    return activated;
//}
