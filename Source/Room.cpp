//
//  Room.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Room.h"

Room::Room()
{
    inRoom = 0;
}

Room::Room(XMLParse *xml, xml_node<> *rootNode)
{
//    borders.insert(make_pair("north", ""));
//    borders.insert(make_pair("south", ""));
//    borders.insert(make_pair("east", ""));
//    borders.insert(make_pair("west", ""));
    
    inRoom = 0;
//    printf("Calling the Room Constructor\n");
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        string node = pNode->name();
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
            //Border b;
            xml_node<> *cNode = pNode->first_node();
            string bName, d;
            while(cNode != 0)
            {
                string n = cNode->name();
                if(n == "direction")
                {
                    d = cNode->value();
                }
                else if(n == "name")
                {
                    bName = cNode->value();
                }
            
                cNode = cNode->next_sibling();
            }
            //Adding Pair
            borders.insert(make_pair(d,bName));
        }
        else if(node == "trigger")
        {
            Trigger T(pNode);
            triggers.push_back(T);
        }
        pNode = pNode->next_sibling();
    }
}

//Copy Constructor
//Room::Room(const Room &r)
//{
//    name = r.name;
//    description = r.description;
//}

//Get the name of the room
string Room::getName()
{
    return name;
}

//Check if the player is in the room
bool Room::getInRoom()
{
    return inRoom;
}

//Print the description of the room when the player first enters the room
void Room::printDescription()
{
    if(!inRoom)
    {
        cout << description << "\n";
        inRoom = 1;
    }
}

int Room::containerInRoom(string s)
{
    for(int location = 0; location < containers.size(); location++)
    {
        if(containers.at(location) == s)
            return location;
    }
    return -1;
}

//Check if the item is in the room and return the location of the item if it is
int Room::itemInRoom(string s)
{
    for(int location = 0; location < items.size(); location++)
    {
        if(items.at(location) == s)
            return location;
    }
    return -1;
}

//Add an item to the room's inventory
void Room::addItem(string s)
{
    items.push_back(s);
}

//Remove an item from the room's inventory
void Room::delItem(string s)
{
    int location = itemInRoom(s);
    if(location != -1)
        items.erase(items.begin()+location);
}

//Print all the items in the room
void Room::printItems()
{
    for(int l = 0; l < items.size(); l++)
    {
        cout << items.at(l) << " ";
    }
    cout << "\n";
}

//Checks if the player can go in a certain direction
string Room::roomInDirection(string dir)
{
    string retval = "";
    auto it = borders.find(dir);
    if(it != borders.end())
    {
        retval = it->second;
    }
    return retval;
}

void Room::addTriggers(vector<Trigger *> * t)
{
    for(int counter = 0; counter < triggers.size(); counter++)
    {
        t->push_back(&triggers.at(counter));
    }
}

vector<string> Room::getContainers()
{
    return containers;
}

vector<string> Room::getCreatures()
{
    return creatures;
}

int Room::creatureInRoom(string n)
{
    for(int counter = 0; counter < creatures.size(); counter++)
    {
        if(creatures.at(counter) == n)
            return counter;
    }
    return -1;
}

void Room::setStatus(string s)
{
    status = s;
}

string Room::getType()
{
    return type;
}

void Room::delCreature(string s)
{
    if(creatureInRoom(s)!=-1)
        creatures.erase(creatures.begin() + creatureInRoom(s));
}

void Room::delContainer(string s)
{
    if(containerInRoom(s) != -1)
        containers.erase(containers.begin() + containerInRoom(s));
}
