//
//  Item.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/5/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Item.h"

Item::Item()
{}

Item::Item(string n)
{
    canTurnOn = 0;
    name = n;
}

Item::Item(XMLParse *xml, xml_node<> *rootNode)
{
    turnedOn = 0;
    canTurnOn = 0;
//    printf("Calling the Item Constructor\n");
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
//        cout << node << "\n";
        if(node == "name")
            name = pNode->value();
        else if(node == "description")
            description = pNode->value();
        else if(node == "writing")
            writing = pNode->value();
        else if(node == "status")
            status = pNode->value();
        else if(node == "turnon")
        {
            canTurnOn = 1;
            xml_node<> * nextNode = pNode->first_node();
            while(nextNode != 0)
            {
                string att = nextNode->name();
                if(att == "print")
                {
                    turnon.turnOnPrint = nextNode->value();
                }
                else if(att == "action")
                {
                    turnon.action = nextNode->value();
                }
                nextNode = nextNode->next_sibling();
            }
        }
        
        pNode = pNode->next_sibling();
    }
}

string Item::getName()
{
    return name;
}

string Item::getWriting()
{
    return writing;
}

bool Item::getCanTurnOn()
{
    return canTurnOn;
}

string Item::getAction()
{
    return turnon.action;
}

void Item::setStatus(string s)
{
    status = s;
}

string Item::getTurnOnPrint()
{
    return turnon.turnOnPrint;
}

void Item::setCanTurnOn(bool b)
{
    canTurnOn = b;
}

string Item::getStatus()
{
    return status;
}

void Item::setTurnedOn(bool b)
{
    turnedOn = b;
}

bool Item::getTurnedOn()
{
    return turnedOn;
}