//
//  BNode.h
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#ifndef __TreeDemo__BNode__
#define __TreeDemo__BNode__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 A node of a B-tree.
 */
class BNode {
private:
    /**
     Indentifier of the node.
     */
    long identifier;
    
    /**
     Global node identifier for Graphviz labeling purposes.
     */
    static long masterIdentifier;
    
public:
    /**
     Number of cells in the node.
     */
    static const int size = 3;
    
    /**
     Default value.
     */
    static const int empty = -9999;
    
    /**
     Constructs new node with default (empty) values.
     */
    BNode();
    
    /**
     Recursive post-order destructor.
     */
    ~BNode();
    
    /**
     Values of the node.
     */
    int values[size];
    
    /**
     Pointers to another nodes.
     */
    BNode *pointers[size + 1];
    
    /**
     Colors of cells in the Graphviz visualization
     */
    string vizcolors[size];
    
    /**
     Prints subtree of the node into a Graphviz file.
     @param stream
            Output stream.
     */
    void printSubtree(ofstream &stream);
};

#endif /* defined(__TreeDemo__BNode__) */
