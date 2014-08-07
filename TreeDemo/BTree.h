//
//  BTree.h
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#ifndef __TreeDemo__BTree__
#define __TreeDemo__BTree__

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "BNode.h"

/**
 Structure of B-tree.
 */
class BTree {
private:
    /**
     Root of the tree.
     */
    BNode *root;
    
    /**
     Prints Graphviz representation to file.
     @param stream
            Stream of the target file.
     */
    void printToFile(ofstream &stream);
    
public:
    /**
     Empty tree constructor.
     */
    BTree();
    
    /**
     Filled tree constructor.
     @param root
            Node to set as the root.
     */
    BTree(BNode *root) : root(root) { }
    
    /**
     Default destructor.
     */
    ~BTree();
    
    /**
     Creates visualization of the current state of the tree using Graphviz.
     @param path
            Where to save the PDF with visualization.
     @param dot
            Path to the Graphviz dot utility.
     */
    void visualize(string path, string dot);
};

#endif /* defined(__TreeDemo__BTree__) */
