//
//  Game.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/6/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "Game.h"

Game::Game()
{}

Game::Game(Map m)
{
//    cout << "Calling the Game constructor\n";
    map = m;
    Player P;
    player = P;
    player.setCurrRoom(map.getFirstRoom());
    gameOver = 0;
}

void Game::gameLoop()
{
    bool triggered = 0;
    int success = 0;
    string command;
    room = &map.rooms.find(player.getCurrRoom())->second;
    
    while(!gameOver)
    {
        if(player.getCurrRoom() != room->getName())
            room = &map.rooms.find(player.getCurrRoom())->second;
        room->printDescription();
        
        checkTriggers();
        triggered = parseTrigger("");
        getline(cin, command);
        checkTriggers();
        success = parseInput(command);
        success = 0;
    }
}

int Game::parseInput(string command)
{
    bool triggered = 0;
    int success = 1;
    string word1, word2, word3, word4;
    stringstream(command) >> word1 >> word2 >> word3 >> word4;
    triggered = parseTrigger(word1);
    
    //cout << "Triggered: " << triggered << "\n";
    
    if(!triggered)
    {
        if(word1 == "n" || word1 == "s" ||word1 == "e" ||word1 == "w")
        {
            if(word1 == "n")
                word1 = "north";
            else if(word1 == "s")
                word1 = "south";
            else if(word1 == "e")
                word1 = "east";
            else if(word1 == "w")
                word1 = "west";
            
            string inThatDirection =room->roomInDirection(word1);
//            cout << room->getName() << "\n";
            if(inThatDirection != "Can't go that way")
                player.setCurrRoom(inThatDirection);
            else
                cout << inThatDirection << "\n";
        }
        else if(word1 == "i")
        {
            player.showInventory();
        }
        else if(word1 == "take")
        {
            //room->printItems();
            if(room->itemInRoom(word2) != -1)
            {
                player.addInventory(word2);
                room->delItem(word2);
                cout << "Item " << word2 << " added to inventory.\n";
            }
            else
            {
                bool gotItem = 0;
                for(auto it = map.containers.begin(); it != map.containers.end(); it++)
                {
                    Container *c = &it->second;
                    if(c->itemInContainer(word2) != -1)
                    {
                        player.addInventory(word2);
                        c->delItem(word2);
                        cout << "Item " << word2 << " added to inventory.\n";
                        gotItem = 1;
                    }
                }
                if(!gotItem)
                    cout << "No such item in room or containers\n";
            }
        }
        else if(command == "open exit")
        {
            if(room->getType() == "exit")
            {
                gameOver = 1;
                success = 1;
                cout << "Game Over\n";
            }
            else
            {
                cout << "Not at exit...keep looking.\n";
            }
        }
        else if(word1 == "open")
        {
            if(room->containerInRoom(word2) != -1)
            {
                Container *c = &map.containers.find(word2)->second;
                if(c->getStatus() == "" || c->getStatus() == "unlocked")
                    c->printItems();
            }
            else
            {
                cout << "Error\n";
            }
        }
        else if(word1 == "read")
        {
            if(player.findItem(word2) != -1)
            {
                string wr = map.readItem(word2);
                if(wr != "")
                    cout << wr << "\n";
                else
                    cout << "Nothing written." << "\n";
            }
            else
                cout << "No such item in your inventory.\n";
        }
        else if(word1 == "drop")
        {
            if(player.findItem(word2) != -1)
            {
                player.delInventory(word2);
                room->addItem(word2);
                cout << word2 << " dropped.\n";
            }
            else
                cout << "Error \n";
        }
        else if(word1 == "put")
        {
            if(player.findItem(word2) != -1)
            {
                if(room->containerInRoom(word4) != -1)
                {
                    bool putted = map.putItemInContainer(word2, word4);
//                    Container c = map.containers.find(word2)->second;
//                    c.addItem(word2);
                    if(putted)
                        player.delInventory(word2);
                }
                else
                {
                    cout << "Error" << "\n";
                }
            }
            else
            {
                cout << "Error\n";
            }
        }
        else if(word1 == "turn" && word2 == "on")
        {
            if(player.findItem(word3) != -1)
            {
                Item *i = &map.items.find(word3)->second;
                if(i->getCanTurnOn())
                {
                    string iword1, iword2, iword3, iword4;
                    stringstream(i->getAction()) >> iword1 >> iword2 >> iword3 >> iword4;
                    i->setStatus(iword4);
                    cout << "You activate the " << word3 << "\n";
                    cout << i->getTurnOnPrint() << "\n";
                    i->setCanTurnOn(0);
                    i->setTurnedOn(1);
                }
                else if(i->getTurnedOn())
                {
                    cout << "You activate the " << word3 << "\n";
                    cout << i->getTurnOnPrint() << "\n";
                }
            }
            else
            {
                cout << "Item " << word3 << " not in inventory.";
            }
        }
        else if(word1 == "attack" && word3 == "with")
        {
            bool hit = 0;
            vector<string> actions;
            for(auto it = map.creatures.begin(); it != map.creatures.end(); it++)
            {
                if(it->first == word2 && room->creatureInRoom(word2) != -1)
                {
                    Creature *c = &it->second;
                    if(c->checkVulnerability(word4))
                    {
                        if(player.findItem(word4) != -1)
                        {
                            hit = c->attackWith(&map.items.find(word4)->second);
                            if(hit)
                                actions = c->getAttackAction();
                        }
                    }
                }
            }
            if(hit)
            {
                player.delInventory(word4);
                map.delItem(word4);
                for(int counter = 0; counter <actions.size(); counter++)
                    parseAction(actions.at(counter));
            }
            else if(!hit)
                cout << "Error\n";
        }
        else
        {
            cout << "Error\n";
            success = 0;
        }
    }
    return success;
}

void Game::checkTriggers()
{
    currentTriggers.clear();
    room->addTriggers(&currentTriggers);
    if(room->getCreatures().size()!=0)
    {
        for(int counter = 0; counter < room->getCreatures().size(); counter++)
        {
            Creature *c = &map.creatures.find(room->getCreatures().at(counter))->second;
            c->addTriggers(&currentTriggers);
        }
    }
    if(room->getContainers().size()!=0)
    {
        for(int counter = 0; counter < room->getContainers().size(); counter++)
        {
            Container *c = &map.containers.find(room->getContainers().at(counter))->second;
            c->addTriggers(&currentTriggers);
        }
    }
    //cout << "size of current triggers: " << currentTriggers.size() << "\n";
}

bool Game::parseTrigger(string command)
{
    bool act = 0;
    //cout << "Parsing trigger\n";
    for(int counter = 0; counter<currentTriggers.size(); counter++)
    {
        Trigger * T = currentTriggers.at(counter);
        if(T->getActivated() && T->getType() == "permanent")
            T->setActivated(0);
        if(T->getActivated() == 0)
        {
            if(T->getTriggerCommand() == "" || T->getTriggerCommand() == command)
            {
                //T.printTrigger();
                //cout << "Owner: " << T.getCondition().owner << "\n";
                if(T->getCondition().owner != "")
                    checkOwner(T);
                else if(T->getCondition().status != "")
                    checkStatus(T);
            }
            act = act || T->getActivated();
        }
    }
    return act;
}

void Game::update(string att, string val)
{
    
}

void Game::checkOwner(Trigger * T)
{
    string obj = T->getCondition().object;
    bool h = T->getCondition().has;
    if(T->getCondition().owner == "inventory")
    {
        //cout << "has found" << h << player.findItem(obj) << "\n";
        if((player.findItem(obj)!=-1 && h) || (player.findItem(obj)==-1 && !h))
        {
            //cout << "Setting activated\n";
            T->setActivated(1);
            if(T->getTriggerPrint() != "")
                cout << T->getTriggerPrint() << "\n";
            if(T->getAction() != "")
                parseAction(T->getAction());
        }
    }
    else if(T->getCondition().owner == room->getName() && ((room->itemInRoom(obj) != -1 && h) || (room->itemInRoom(obj)==-1 && !h)))
    {
        T->setActivated(1);
        if(T->getTriggerPrint() != "")
            cout << T->getTriggerPrint() << "\n";
        if(T->getAction() != "")
            parseAction(T->getAction());
    }
    else
    {
        for(int counter = 0; counter < room->getContainers().size(); counter++)
        {
            if(T->getCondition().owner == room->getContainers().at(counter))
            {
                Container * c = &map.containers.find(room->getContainers().at(counter))->second;
                if((c->itemInContainer(obj)!=-1 && h) || (c->itemInContainer(obj)==-1 && !h))
                {
                    T->setActivated(1);
                    if(T->getTriggerPrint() != "")
                        cout << T->getTriggerPrint() << "\n";
                    if(T->getAction() != "")
                        parseAction(T->getAction());
                }
            }
        }
    }
}

void Game::checkStatus(Trigger * T)
{
    string obj = T->getCondition().object;
    string stat = T->getCondition().status;
    
    //search the entire map for something that matches obj and check to see if its status matches stat
    for(auto it = map.items.begin(); it != map.items.end(); it++)
    {
        if(it->first == obj)
        {
            Item *i = &it->second;
            if(i->getStatus() == stat)
            {
                T->setActivated(1);
                if(T->getTriggerPrint() != "")
                    cout << T->getTriggerPrint() << "\n";
                if(T->getAction() != "")
                    parseAction(T->getAction());
            }
        }
    }
    for(auto it = map.containers.begin(); it!=map.containers.end(); it++)
    {
        if(it->first == obj)
        {
            Container *c = &it->second;
            if(c->getStatus() == stat)
            {
                T->setActivated(1);
                if(T->getTriggerPrint() != "")
                    cout << T->getTriggerPrint() << "\n";
                if(T->getAction() != "")
                    parseAction(T->getAction());
            }
        }
    }
}


void Game::parseAction(string action)
{
//    cout << action << endl;
    string aword1, aword2, aword3, aword4;
    stringstream(action) >> aword1 >> aword2 >> aword3 >> aword4;
    if(aword1 == "Add")
    {
        map.addItem(aword2);
        for(auto it = map.containers.begin(); it != map.containers.end(); it++)
        {
            if(it->first == aword4)
            {
                Container *c = &it->second;
                c->addItem(aword2);
            }
        }
        for(auto it = map.rooms.begin(); it != map.rooms.end(); it++)
        {
            if(it->first == aword4)
            {
                Room *r = &it->second;
                r->addItem(aword2);
            }
        }
        room->printItems();
    }
    else if(aword1 == "Delete")
    {
        room->delCreature(aword2);
        room->delContainer(aword2);
    }
    else if(aword1 == "Update")
    {
        for(auto it = map.containers.begin(); it != map.containers.end(); it++)
        {
            if(it->first == aword2)
            {
                Container *c = &it->second;
                c->setStatus(aword4);
            }
        }
        for(auto it = map.items.begin(); it != map.items.end(); it++)
        {
            if(it->first == aword2)
            {
                Item *i = &it->second;
                i->setStatus(aword4);
            }
        }
        for(auto it = map.rooms.begin(); it != map.rooms.end(); it++)
        {
            if(it->first == aword2)
            {
                Room *r = &it->second;
                r->setStatus(aword4);
            }
        }
    }
}
