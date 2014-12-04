//
//  obj.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/3/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "obj.h"

obj::obj()
{
    zer = 0;
}

obj::obj(int i)
{
    zer = i;
}

int obj::getZer()
{
    return zer;
}