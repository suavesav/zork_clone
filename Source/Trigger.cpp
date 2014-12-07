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
                    if(strcmp(nextNode->value(), "no"))
                        tc.has=0;
                    else
                        tc.has = 1;
                }
                else if(att == "object")
                {
                    tc.object = pNode->value();
                }
                else if(att == "owner")
                {
                    tc.owner = pNode->value();
                }
                else if(att == "status")
                {
                    tc.status = pNode->value();
                }
                nextNode = nextNode->next_sibling();
            }
        }
        
        pNode = pNode->next_sibling();
    }
}