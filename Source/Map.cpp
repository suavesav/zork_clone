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
//    printf("Calling the Map Constructor\n");
    gotFirstRoom = 0;
    xml_node<> *pNode = xml->getRootNode()->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
        if(node=="room")
        {
//            cout << "Room \n";
            Room room(xml, pNode);
            rooms.insert(make_pair(room.getName(), room));
            if(!gotFirstRoom)
            {
                firstRoom = room.getName();
                gotFirstRoom = 1;
            }
        }
        else if(node=="container")
        {
//            cout << "Container \n";
            Container game_container(xml, pNode);
            containers.insert(make_pair(game_container.getName(), game_container));
        }
        else if(node == "item")
        {
//            cout << "Item \n";
            Item item(xml, pNode);
            items.insert(make_pair(item.getName(), item));
        }
        else if(node == "creature")
        {
//            cout << "Creature \n";
            Creature creature(xml, pNode);
            creatures.insert(make_pair(creature.getName(), creature));
        }
        pNode = pNode->next_sibling();
    }
}

string Map::getFirstRoom()
{
    return firstRoom;
}

//Prints the writing on the item
string Map::readItem(string s)
{
    return items.find(s)->second.getWriting();
}

void Map::addItem(string s)
{
    Item item(s);
    items.insert(make_pair(s, item));
}

void Map::delItem(string s)
{
    items.erase(s);
}