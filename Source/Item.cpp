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

Item::Item(XMLParse *xml, xml_node<> *rootNode)
{
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