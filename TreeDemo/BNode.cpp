//
//  BNode.cpp
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#include "BNode.h"

// we start at zero
long BNode::masterIdentifier = 0;

BNode::BNode() : identifier(++masterIdentifier) {
    // initialize node with default values
    for (int i = 0; i < size; i++) {
        values[i] = empty;
        vizcolors[i] = "";
        pointers[i] = NULL;
    }
    
    pointers[size] = NULL;
}

BNode::~BNode() {
    // to delete node means to delete its values and its children
    for (int i = 0; i < size + 1; i++) {
        if (pointers[i]) {
            delete pointers[i];
        }
    }
}

void BNode::printSubtree(ofstream &stream) {
    // this is really nasty code for really nice Graphviz appearance
    // you have been warned
    stream << "node" << identifier << "[label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\"><TR>";
    for (int i = 0; i < size; i++) {
        // print pointer cell
        stream << "<TD BGCOLOR=\"gray\" PORT=\"f" << i << "\">  </TD><TD";
        
        // print main cell
        if (vizcolors[i] != "") {
            stream << " BGCOLOR=\"" << vizcolors[i] << "\"";
        }
        
        stream << ">";
        
        if (vizcolors[i] != "") {
            stream << "<FONT COLOR=\"white\">";
        }
        
        // print value of the main cell
        stream << " " << (values[i] == empty ? "–" : to_string(values[i])) << " ";
        
        if (vizcolors[i] != "") {
            stream << "</FONT>";
        }
        
        // we like good syntax
        stream << "</TD>";
    }
    stream << "<TD BGCOLOR=\"gray\" PORT=\"f" << size << "\">  </TD></TR></TABLE>>];" << endl;
    
    // create arrows and boxes for children
    for (int i = 0; i < size + 1; i++) {
        if (!pointers[i]) continue;
        pointers[i]->printSubtree(stream);
        stream << "node" << identifier << ":f" << i << " -> \"node" << pointers[i]->identifier << "\";" << endl;
    }
}