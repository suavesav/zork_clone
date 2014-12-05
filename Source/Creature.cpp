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
    printf("Calling the Creature Constructor\n");
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
        cout << node << "\n";
        if(node == "name")
            name = pNode->value();
        else if(node == "description")
            description = pNode->value();
        else if(node == "vulnerability")
            vulnerability.push_back(pNode->value());
        pNode = pNode->next_sibling();
    }
}

string Creature::getName()
{
    return name;
}