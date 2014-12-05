//
//  Container.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/5/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Container.h"

Container::Container()
{}

Container::Container(XMLParse *xml, xml_node<> *rootNode)
{
    printf("Calling the Container Constructor\n");
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
        cout << node << "\n";
        if(node == "name")
            name = pNode->value();
        else if(node == "description")
            description = pNode->value();
        else if(node == "accept")
            accept.push_back(pNode->value());
        else if(node == "item")
            items.push_back(pNode->value());
        else if(node == "status")
            status = pNode->value();
        
        pNode = pNode->next_sibling();
    }
}

string Container::getName()
{
    return name;
}