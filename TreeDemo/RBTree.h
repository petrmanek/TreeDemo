//
//  RBTree.h
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#ifndef __TreeDemo__RBTree__
#define __TreeDemo__RBTree__

#include <iostream>
#include <unistd.h>
#include <fstream>
#include "RBNode.h"
#include "BTree.h"

/**
 Implementation of Red-black trees.
 */
class RBTree {
private:
    /**
     Root of the tree.
     */
    RBNode *root;
    
    /**
     Leaf of the tree.
     */
    RBNode *nil;
    
    /**
     Prints Graphviz representation to file.
     @param stream
            Stream of the target file.
     */
    void printToFile(ofstream &stream);
    
    /**
     Recursively fills the B-tree with data from this tree.
     @param parent
            Subtree of this node will be used.
     @return Subtree of @c parent, in B-tree format.
     */
    BNode *fillBTree(RBNode *parent);
    
    /**
     Traverses through the tree to find an item with the given value.
     @param a
            Value to find.
     @return Node with value @c a or @c nil.
     */
    RBNode *findNode(int a);
    
    /**
     Rotates the subtree of given node in the left direction.
     @param node
            Node determining the subtree.
     */
    void rotateLeft(RBNode *node);
    
    /**
     Rotates the subtree of given node in the right direction.
     @param node
            Node determining the subtree.
     */
    void rotateRight(RBNode *node);
    
    /**
     Restores the Red-black properties of the tree after add operation.
     @param node
            The added node.
     */
    void addRebalance(RBNode *node);
    
    /**
     Restores the Red-black properties of the tree after remove operation.
     @param node
            The removed node.
     */
    void removeRebalance(RBNode *node);
    
    /**
     Finds suitable successor for a node, which is about to be removed.
     @param node
            Node to find successor for.
     @return A successor for @c node.
     */
    RBNode *successor(RBNode *node);
    
public:
    /**
     Empty tree constructor.
     */
    RBTree();
    
    /**
     Default destructor.
     */
    ~RBTree();
    
    /**
     Adds new item into the tree. That is, if the tree doesn't already contain it.
     @param a
            The item to add, positive integer expected.
     */
    void add(int a);
    
    /**
     Searches for item in the tree.
     @param a
            The item to search for, positive integer expected.
     @return true if the tree contains a node with value equal to @c a, otherwise false
     */
    bool find(int a);
    
    /**
     Removes an item from the tree. If the tree doesn't contain this item, nothing happens.
     @param a
            The item to remove, positive integer expected.
     */
    void remove(int a);
    
    /**
     Creates visualization of the current state of the tree using Graphviz.
     @param path
            Where to save the PDF with visualization.
     @param dot
            Path to the Graphviz dot utility.
     */
    void visualize(string path, string dot);
    
    /**
     Constructs a B-tree corresponding to the current state of the tree.
     @return Analogical B-Tree.
     */
    BTree btree();
};

#endif /* defined(__TreeDemo__RBTree__) */
