//
//  BTree.cpp
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#include "BTree.h"

BTree::BTree() {
    // if there's no root, let's make one
    root = new BNode();
}

BTree::~BTree(){
    // delete tree means to delete root
    delete root;
}

void BTree::printToFile(ofstream &stream) {
    // print header
    stream << "digraph btree {" << endl;
    stream << "    node [shape=plaintext, height=.1, fontname=\"Arial\"];" << endl;
    
    // print the actual tree
    root->printSubtree(stream);
    
    // mind the brace
    stream << "}" << endl;
}

void BTree::visualize(string path, string dot) {
    // create temp file
    char *tmpname = strdup("/tmp/dotXXXXXX");
    mkstemp(tmpname);
    ofstream f(tmpname);
    
    // write to temp file
    printToFile(f);
    
    // run dot on temp file
    string command = dot + " -Tpdf " + string(tmpname) + " -o " + path + " > /dev/null 2> /dev/null";
    system(command.c_str());
    
    // delete temp file
    unlink(tmpname);
}

