//
//  main.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 11/29/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "XMLParse.h"
#include "Map.h"
#include "Game.h"

using namespace std;

//Function Declarations
Map makeMap(ifstream&);
void playGame(Map);

//Main Function
int main(int argc, const char * argv[]) {
    
    //Check if correct number of arguments
    if(argc != 2)
    {
        printf("Wrong number of arguments. \n");
        return 1;
    }

    //generate the filepath
    string filepath("/Users/Sav/XCodeProjects/zork_clone/Resources/Games/");
    filepath.append(argv[1]);
    ifstream ifile(filepath);
    
    //Try opening the file
    if(ifile.is_open())
    {
        Map gameMap = makeMap(ifile);
        playGame(gameMap);
    }
    else
    {
        cout << filepath;
        printf("File does not exist\n");
        return 1;
    }
    return 0;
}

//This Function makes the map for the game
Map makeMap(ifstream& ifile)
{
    XMLParse xml(ifile);
    Map map(&xml);
    return map;
}

//This function plays game from the map
void playGame(Map map)
{
    Game G(map);
    G.gameLoop();
}
