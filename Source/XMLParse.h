//
//  XMLParse.h
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//


#ifndef zork_clone_XMLParse_h
#define zork_clone_XMLParse_h

#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class XMLParse
{
public:
    XMLParse();
    XMLParse(istream &ifile);
    xml_node<> * getRootNode() const;
    xml_document<> getDocument() const;
    void printChildNodes(xml_node<> *);
    void iterateNodes(xml_node<> *);

private:
    xml_document<> xmlDocument;
    xml_node<> *rootNode;
};

#endif
