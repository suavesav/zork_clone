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
#include "obj.h"
//#include <rapidxml-1.13/rapidxml.hpp>
//#include <rapidxml-1.13/rapidxml_print.hpp>

using namespace std;
//using namespace rapidxml;

void loadGame(ifstream&);
//void printChildren(xml_node<> *);

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
        XMLParse Game(ifile);
    }
    else
    {
        cout << filepath;
        printf("File does not exist\n");
        return 1;
    }
    return 0;
}
