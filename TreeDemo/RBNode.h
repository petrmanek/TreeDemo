//
//  RBNode.h
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#ifndef __TreeDemo__RBNode__
#define __TreeDemo__RBNode__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 Color of Red-black tree node.
 */
typedef int color_t;

/**
 A node of a Red-black tree.
 */
class RBNode {
private:
    /**
     Indentifier of the node.
     */
    long identifier;
    
    /**
     Global node identifier for Graphviz labeling purposes.
     */
    static long masterIdentifier;
    
    /**
     Nil node pointer copy.
     */
    RBNode *nil;
    
public:
    /**
     Red color.
     */
    static const color_t red = 0;
    
    /**
     Black color.
     */
    static const color_t black = 1;
    
    /**
     Default value.
     */
    static const int empty = -9999;
    
    /*
     Value of the node.
     */
    int value;
    
    /**
     Color of the node.
     */
    color_t color;
    
    /**
     Left son of the node.
     */
    RBNode *left;
    
    /**
     Right son of the node.
     */
    RBNode *right;
    
    /**
     Parent of the node.
     */
    RBNode *parent;
    
    /**
     Prints subtree of the node into a Graphviz file.
     @param stream
            Output stream.
     @param nil
            Nil node to omit.
     */
    void printSubtree(ofstream &stream, RBNode *nil);
    
    /**
     Constructs new node with default (empty) values.
     */
    RBNode() : identifier(++masterIdentifier), nil(nullptr), value(empty), color(black), left(nullptr), right(nullptr), parent(nullptr) { }
    
    /**
     Constructs new node with preset values.
     @param nil
            Nil node reference, will be set as left and right son.
     @param parent
            Reference to the parent node.
     @param color
            Color of the node.
     @param value
            Value of the node.
     */
    RBNode(RBNode *nil, RBNode *parent, color_t color, int value) : identifier(++masterIdentifier), nil(nil), value(value), color(color), left(nil), right(nil), parent(parent) { }
    
    /**
     Recursive post-order destructor, stops at the Nil node.
     */
    ~RBNode();
};

#endif /* defined(__TreeDemo__RBNode__) */
