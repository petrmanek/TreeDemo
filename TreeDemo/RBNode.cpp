//
//  RBNode.cpp
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#include "RBNode.h"

// we start at zero
long RBNode::masterIdentifier = 0;

RBNode::~RBNode() {
    // delete left, then right... stop at nil
    if (left && left != nil) delete left;
    if (right && right != nil) delete right;
}

void RBNode::printSubtree(ofstream &stream, RBNode *nil) {
    // serialize node
    stream << "node" << identifier << "[label=\"" << value << "\", fillcolor=" << (color == RBNode::red ? "red" : "black") << "];" << endl;
    
    // serialize left son
    if (left != nil) {
        left->printSubtree(stream, nil);
        stream << "\"node" << identifier << "\" -> \"node" << left->identifier << "\"" << endl;
    } else {
        // in case of nil
        stream << "node" << identifier << "left[shape=box, label=\"NIL\", fillcolor=black, fontsize=5, width=.3];" << endl;
        stream << "\"node" << identifier << "\" -> \"node" << identifier << "left\"" << endl;
    }
    
    // serialize right son
    if (right != nil) {
        right->printSubtree(stream, nil);
        stream << "\"node" << identifier << "\" -> \"node" << right->identifier << "\"" << endl;
    } else {
        // in case of nil
        stream << "node" << identifier << "right[shape=box, label=\"NIL\", fillcolor=black, fontsize=5, width=.3];" << endl;
        stream << "\"node" << identifier << "\" -> \"node" << identifier << "right\"" << endl;
    }
}
