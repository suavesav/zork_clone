//
//  XMLParse.cpp
//  zork_clone
//
//  Created by Savinay Nangalia on 12/4/14.
//  Copyright (c) 2014 Savinay Nangalia. All rights reserved.
//

#include "XMLParse.h"

XMLParse::XMLParse()
{}

XMLParse::XMLParse(istream &ifile)
{
    vector<char> buffer((istreambuf_iterator<char>(ifile)), istreambuf_iterator<char>( ));
    
    buffer.push_back('\0');
    xmlDocument.parse<0>(&buffer[0]);
    
    rootNode = xmlDocument.first_node();
}


//Function to return all the nodes under any given root node
void XMLParse::printChildNodes(xml_node<> *rootNode)
{
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        cout << pNode->name() << "\n";
        printChildNodes(pNode);
        pNode = pNode->next_sibling();
    }
}

//Function to iterate through the contents of a node
void XMLParse::iterateNodes(xml_node<> *rootNode)
{
    xml_node<> *pNode = rootNode->first_node();
    while(pNode != 0)
    {
        //cout << pNode->name() << "\n";
        pNode = pNode->next_sibling();
    }
}

//Returns the rootNode of xmlDocument
xml_node<> * XMLParse::getRootNode() const
{
    return rootNode;
}

