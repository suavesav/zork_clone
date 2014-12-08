//
//  Creature.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/5/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Creature.h"

Creature::Creature()
{}

Creature::Creature(XMLParse *xml, xml_node<> *rootNode)
{
//    printf("Calling the Creature Constructor\n");
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
//        cout << node << "\n";
        if(node == "name")
            name = pNode->value();
        else if(node == "description")
            description = pNode->value();
        else if(node == "vulnerability")
            vulnerability.push_back(pNode->value());
        else if(node == "attack")
        {
            xml_node<> * nextNode = pNode->first_node();
            while(nextNode != 0)
            {
                string n = nextNode->name();
                if(n == "condition")
                {
                    xml_node<> * nextNextNode = nextNode->first_node();
                    while(nextNextNode != 0)
                    {
                        string nn = nextNextNode->name();
                        if(nn == "status")
                        {
                            atk.ac.attackStatus = nextNextNode->value();
                        }
                        else if (nn == "object")
                        {
                            atk.ac.attackObject = nextNextNode->value();
                        }
                        nextNextNode = nextNextNode->next_sibling();
                    }
                }
                else if(n == "print")
                {
                    atk.attackPrint = nextNode->value();
                }
                else if(n == "action")
                {
                    atk.action.push_back(nextNode->value());
                }
                nextNode = nextNode->next_sibling();
            }
        }
        else if(node == "trigger")
        {
            Trigger T(pNode);
            triggers.push_back(T);
        }
        pNode = pNode->next_sibling();
    }
}

string Creature::getName()
{
    return name;
}

void Creature::addTriggers(vector<Trigger> * t)
{
    for(int counter = 0; counter < triggers.size(); counter++)
    {
        t->push_back(triggers.at(counter));
    }
}

