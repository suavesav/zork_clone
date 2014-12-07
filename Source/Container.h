//
//  Container.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <string>
#include <vector>
#include "XMLParse.h"

using namespace std;

#ifndef zork_clone_Container_h
#define zork_clone_Container_h

class Container
{
public:
    Container();
    Container(XMLParse *, xml_node<> *);
    
    string getName();
    int itemInContainer(string);
    void delItem(string);
    void addItem(string);
    void printItems();
    
private:
    string name;
    string status;
    string description;
    vector<string> accept;
    vector<string> container_items;
    //vector<Trigger> triggers;
};

#endif
