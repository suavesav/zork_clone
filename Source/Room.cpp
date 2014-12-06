//
//  Room.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Room.h"

Room::Room()
{}

Room::Room(XMLParse *xml, xml_node<> *rootNode)
{
    printf("Calling the Room Constructor\n");
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
//        cout << node << "\n";
        if(node == "name")
            name = pNode->value();
        else if(node == "description")
            description = pNode->value();
        else if(node == "status")
            status = pNode->value();
        else if(node == "type")
            type = pNode->value();
        else if(node == "container")
            containers.push_back(pNode->value());
        else if(node == "creature")
            creatures.push_back(pNode->value());
        else if(node == "item")
            items.push_back(pNode->value());
        else if(node == "border")
        {
            Border b;
            xml_node<> *cNode = pNode->first_node();
            string n =cNode->name();
            if(n == "direction")
            {
                b.direction = cNode->value();
                b.name = cNode->next_sibling()->value();
            }
            else
            {
                b.name = cNode->value();
                b.direction = cNode->next_sibling()->value();
            }
            borders.push_back(b);
        }
        pNode = pNode->next_sibling();
    }
}

string Room::getName()
{
    return name;
}