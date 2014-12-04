//
//  obj.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/3/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#ifndef zork_clone_obj_h
#define zork_clone_obj_h
class obj
{
public:
    obj();
    obj(int i);
    
    int getZer();
    
private:
    string name;
    int zer;
};

#endif
