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
    int success = 0;
    string command;
    room = &map.rooms.find(player.getCurrRoom())->second;
    
    while(!gameOver)
    {
        if(player.getCurrRoom() != room->getName())
            room = &map.rooms.find(player.getCurrRoom())->second;
        room->printDescription();
        
        checkTriggers();
        getline(cin, command);
        checkTriggers();
        success = parseInput(command);
        success = 0;
    }
}

int Game::parseInput(string command)
{
    int success = 1;
    string word1, word2, word3, word4;
    stringstream(command) >> word1 >> word2 >> word3 >> word4;
//    success = 0;
    
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
        //room.printItems();
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
                if(c->itemInContainer(word2))
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
        gameOver = 1;
        success = 1;
    }
    else if(word1 == "open")
    {
        if(room->containerInRoom(word2) != -1)
        {
            Container *c = &map.containers.find(word2)->second;
            if(c->getStatus() == "" || c->getStatus() == "unlocked")
                c->printItems();
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
                Container *c = &map.containers.find(word2)->second;
                c->addItem(word2);
                player.delInventory(word2);
            }
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
                cout << i->getTurnOnPrint() << "\n";
                i->setCanTurnOn(0);
            }
        }
    }
    else if(word1 == "attack" && word3 == "with")
    {}
    else
    {
        cout << "Error\n";
        success = 0;
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
}

void Game::parseTrigger(string command)
{
    for(int counter = 0; counter<currentTriggers.size(); counter++)
    {
        Trigger T = currentTriggers.at(counter);
        if(T.getActivated() && T.getType() == "Permanent")
            T.setActivated(0);
        if(T.getActivated() == 0)
        {
            if(T.getTriggerCommand() == "" || T.getTriggerCommand() == command)
            {
                
                if(T.getCondition().owner != "")
                    checkOwner(T);
                else if(T.getCondition().status != "")
                    checkStatus(T);
            }
        }
    }
}

void Game::update(string att, string val)
{
    
}

void Game::checkOwner(Trigger T)
{
    if(T.getCondition().owner == "inventory")
    {
        if((player.findItem(T.getCondition().object)!=-1 && T.getCondition().has) || (player.findItem(T.getCondition().object)==-1 && !T.getCondition().has))
        {
            T.setActivated(1);
            if(T.getTriggerPrint() != "")
                cout << T.getTriggerPrint() << "\n";
            if(T.getAction() != "")
                parseAction(T.getAction());
        }
    }
    else if((room->itemInRoom(T.getCondition().object) != -1 &&T.getCondition().has) || (room->itemInRoom(T.getCondition().object)==-1 && !T.getCondition().has))
    {
        T.setActivated(1);
        if(T.getTriggerPrint() != "")
            cout << T.getTriggerPrint() << "\n";
        if(T.getAction() != "")
            parseAction(T.getAction());
    }
    else
    {
        for(int counter = 0; counter < room->getContainers().size(); counter++)
        {
            if(T.getCondition().owner == room->getContainers().at(counter))
            {
                Container * c = &map.containers.find(room->getContainers().at(counter))->second;
                if((c->itemInContainer(T.getCondition().object)!=-1 && T.getCondition().has) || (c->itemInContainer(T.getCondition().object)==-1 && !T.getCondition().has))
                {
                    T.setActivated(1);
                    if(T.getTriggerPrint() != "")
                        cout << T.getTriggerPrint() << "\n";
                    if(T.getAction() != "")
                        parseAction(T.getAction());
                }
            }
        }
    }
}

void Game::checkStatus(Trigger T)
{
//    bool notFound = 1;
//    string obj = T.getCondition().object;
//    string stat = T.getCondition().status;
    
    //search the entire map for something that matches obj and check to see if its status matches stat
//    while(notFound)
//    {
//        for(int counter = 0; counter < map)
//    }
}

void Game::parseAction(string s)
{}
