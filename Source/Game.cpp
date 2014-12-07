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
    room = map.rooms.find(player.getCurrRoom())->second;
    while(!gameOver)
    {
        //cout << player.getCurrRoom();
        
        room.printDescription();
        while(success != 1)
        {
            getline(cin, command);
            success = parseInput(command);
        }
        success = 0;
//        gameOver = 1;
    }
}

int Game::parseInput(string command)
{
    int success = 1;
    string word1, word2, word3, word4;
    stringstream(command) >> word1 >> word2 >> word3 >> word4;
//    success = 0;
    
    if(word1 == "n" || word1 == "s" ||word1 == "e" ||word1 == "w")
    {}
    else if(word1 == "i")
    {
        player.showInventory();
    }
    else if(word1 == "take")
    {
        //room.printItems();
        if(room.itemInRoom(word2) != -1)
        {
            player.addInventory(word2);
            room.delItem(word2);
            cout << "Item " << word2 << " added to inventory.\n";
        }
//        else if(map.containers.find(word2)->second.itemInContainer(word2) != -1)
//        {
//            
//        }
        else
            cout << "Error \n";
    }
    else if(command == "open exit")
    {
        gameOver = 1;
        success = 1;
    }
    else if(word1 == "open")
    {
        if(room.containerInRoom(word2) != -1)
        {
            map.containers.find(word2)->second.printItems();
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
            room.addItem(word2);
            cout << word2 << " dropped.\n";
        }
        else
            cout << "Error \n";
    }
    else if(word1 == "put")
    {}
    else if(word1 == "turn" && word2 == "on")
    {}
    else if(word1 == "attack" && word3 == "with")
    {}
    else
    {
        cout << "Error\n";
        success = 0;
    }
    return success;
}