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
//    printf("Calling the Container Constructor\n");
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
//        cout << node << "\n";
        if(node == "name")
            name = pNode->value();
        else if(node == "description")
            description = pNode->value();
        else if(node == "accept")
            accept.push_back(pNode->value());
        else if(node == "item")
//            cout << "Item\n";
            container_items.push_back(pNode->value());
        else if(node == "status")
            status = pNode->value();
        
        pNode = pNode->next_sibling();
    }
}

string Container::getName()
{
    return name;
}

//Check if the item is in the container and return the location of the item if it is
int Container::itemInContainer(string s)
{
    for(int location = 0; location < container_items.size(); location++)
    {
        if(container_items.at(location) == s)
            return location;
    }
    return -1;
}

//Add an item to the container's inventory
void Container::addItem(string s)
{
    container_items.push_back(s);
}

//Remove an item from the container's inventory
void Container::delItem(string s)
{
    int location = itemInContainer(s);
    if(location != -1)
        container_items.erase(container_items.begin()+location);
}

//Print all the items in the container
void Container::printItems()
{
    if(container_items.size() == 0)
        cout << name << "is empty.";
    else
    {
        cout << name << "contains ";
        for(int l = 0; l < container_items.size(); l++)
        {
            if(l != 0)
                cout << ", ";
            cout << container_items.at(l);
        }
    }
    cout << "\n";
}