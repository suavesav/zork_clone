//
//  Item.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <string>
#include <vector>
#include "XMLParse.h"

using namespace std;

#ifndef zork_clone_Item_h
#define zork_clone_Item_h

class Item
{
public:
    Item();
    Item(XMLParse *, xml_node<> *);
    
    string getName();
    string getWriting();
    
private:
    string name;
    string description;
    string status;
    string writing;
    //bool turnon;
    //vector<Trigger> triggers;
};

#endif
