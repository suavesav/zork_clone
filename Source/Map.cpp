//
//  Map.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Map.h"

Map::Map()
{}

Map::Map(XMLParse *xml)
{
    //Map Constructor
    printf("Calling the Map Constructor\n");
    xml_node<> *pNode = xml->getRootNode()->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
        if(node=="room")
        {
            cout << "Room \n";
            Room room(xml, pNode);
            rooms.insert(make_pair(room.getName(), room));
        }
        else if(node=="container")
        {
            cout << "Container \n";
            Container container(xml, pNode);
            containers.insert(make_pair(container.getName(), container));
        }
        else if(node == "item")
        {
            cout << "Item \n";
            Item item(xml, pNode);
            items.insert(make_pair(item.getName(), item));
        }
        else if(node == "creature")
        {
            cout << "Creature \n";
            Creature creature(xml, pNode);
            creatures.insert(make_pair(creature.getName(), creature));
        }
        pNode = pNode->next_sibling();
    }
}