//
//  RBTree.cpp
//  TreeDemo
//
//  Created by Petr Mánek on 29.04.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#include "RBTree.h"

RBTree::RBTree() {
    // we begin with empty root and static leaf
    nil = new RBNode();
    root = nil;
}

RBTree::~RBTree() {
    if (root) {
        // we delete tree, tree deletes root
        delete root;
        delete nil;
    }
}

void RBTree::add(int a) {
    if (find(a)) {
        // inserting duplicate value
        return;
    }
    
    // find place for the new node
    RBNode *traverse = root;
    RBNode *parent = nil;
    
    while (traverse != nil) {
        parent = traverse;
        
        // traverse like an ordinary binary tree
        if (a < traverse->value) {
            traverse = traverse->left;
        } else {
            traverse = traverse->right;
        }
    }
    
    if (parent != nil) {
        // insert node as leaf
        RBNode *inserted = new RBNode(nil, parent, RBNode::red, a);
        if (a < parent->value) {
            parent->left = inserted;
        } else {
            parent->right = inserted;
        }
        
        // restore RB properties of the tree
        addRebalance(inserted);
    } else {
        // insert node as root
        root = new RBNode(nil, nil, RBNode::black, a);
    }
}

void RBTree::rotateLeft(RBNode *node) {
    RBNode *temp;
    temp = node->right;
    node->right = temp->left;
    temp->left->parent = node;
    temp->parent = node->parent;
    
    if (node->parent == nil) {
        root = temp;
    } else if (node == node->parent->left) {
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }
    
    temp->left = node;
    node->parent = temp;
}

void RBTree::rotateRight(RBNode *node) {
    RBNode *temp;
    temp = node->left;
    node->left = temp->right;
    temp->right->parent = node;
    temp->parent = node->parent;
    
    if (node->parent == nil) {
        root = temp;
    } else if (node == node->parent->right) {
        node->parent->right = temp;
    } else {
        node->parent->left = temp;
    }
    
    temp->right = node;
    node->parent = temp;
}

void RBTree::addRebalance(RBNode *node) {
    while (node->parent != nil && node->parent->parent && node->parent->color == RBNode::red) {
        if (node->parent == node->parent->parent->left) {
            // parent is left son
            RBNode *granduncle = node->parent->parent->right;
            
            if (granduncle->color == RBNode::red) {
                // case 1
                node->parent->color = RBNode::black;
                granduncle->color = RBNode::black;
                node->parent->parent->color = RBNode::red;
                node = node->parent->parent;
            } else if (granduncle->color == RBNode::black) {
                // case 2
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                
                // case 3
                node->parent->color = RBNode::black;
                node->parent->parent->color = RBNode::red;
                rotateRight(node->parent->parent);
            }
        } else {
            // parent is right son
            RBNode *granduncle = node->parent->parent->left;
            
            if (granduncle->color == RBNode::red) {
                // case 1
                node->parent->color = RBNode::black;
                granduncle->color = RBNode::black;
                node->parent->parent->color = RBNode::red;
                node = node->parent->parent;
            } else {
                // case 2
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                
                // case 3
                node->parent->color = RBNode::black;
                node->parent->parent->color = RBNode::red;
                rotateLeft(node->parent->parent);
            }
        }
    }
    
    root->color = RBNode::black;
}

RBNode *RBTree::findNode(int a) {
    RBNode *traverse = root;
    
    while (traverse != nil) {
        // traverse like an ordinary binary tree
        if (a < traverse->value) {
            traverse = traverse->left;
        } else if (a > traverse->value) {
            traverse = traverse->right;
        } else {
            return traverse;
        }
    }
    
    // nil = not found
    return nil;
}

bool RBTree::find(int a) {
    // let's try to find the node
    return findNode(a) != nil;
}

RBNode *RBTree::successor(RBNode *node) {
    if (node->right != nil) {
        RBNode *traverse = node->right;
        
        // find leftmost element in the right subtree
        while (traverse->left != nil) {
            traverse = traverse->left;
        }
        
        return traverse;
    } else {
        RBNode *parent = node->parent;
        RBNode *traverse = node;
        
        while (parent != nil && traverse == parent->right) {
            traverse = parent;
            parent = parent->parent;
        }
        
        return parent;
    }
}

void RBTree::remove(int a) {
    RBNode *del = findNode(a);
    
    if (del == nil) {
        // no node to delete
        return;
    }
    
    RBNode *x, *y;
    if (del->left == nil || del->right == nil) {
        // we can replace the deleted node by one of its descendants
        y = del;
    } else {
        // find successor according to the rules
        y = successor(del);
    }
    
    // remove the node
    if (y->left != nil) {
        x = y->left;
    } else {
        x = y->right;
    }
    
    x->parent = y->parent;
    if (y->parent == nil) {
        root = x;
    } else {
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    }
    
    // if we did the successor thing, copy the value
    if (y != del) {
        del->value = y->value;
    }
    
    // rebalance only if the removed node was black
    if (y->color == RBNode::black) {
        removeRebalance(x);
    }
}

void RBTree::removeRebalance(RBNode *node) {
    while (node != root && node->color == RBNode::black) {
        if (node == node->parent->left) {
            RBNode *temp = node->parent->right;
            
            if (temp->color == RBNode::red) {
                // case 1
                temp->color = RBNode::black;
                node->parent->color = RBNode::red;
                
                rotateLeft(node->parent);
                temp = node->parent->right;
            }
            
            if (temp->left->color == RBNode::black && temp->right->color == RBNode::black) {
                // case 2
                temp->color = RBNode::red;
                node = node->parent;
            } else if (temp->right->color == RBNode::black) {
                // case 3
                temp->left->color = RBNode::black;
                temp->color = RBNode::red;
                
                rotateRight(temp);
                temp = node->parent->right;
            }
            
            temp->color = node->parent->color;
            node->parent->color = RBNode::black;
            temp->right->color = RBNode::black;
            
            rotateLeft(node->parent);
            node = root;
        } else {
            RBNode *temp = node->parent->left;
            
            if (temp->color == RBNode::red) {
                // case 1
                temp->color = RBNode::black;
                node->parent->color = RBNode::red;
                
                rotateRight(node->parent);
                temp = node->parent->left;
            }
            
            if (temp->right->color == RBNode::black && temp->left->color == RBNode::black) {
                // case 2
                temp->color = RBNode::red;
                node = node->parent;
            } else if (temp->left->color == RBNode::black) {
                // case 3
                temp->right->color = RBNode::black;
                temp->color = RBNode::red;
                
                rotateLeft(temp);
                temp = node->parent->left;
            }
            
            temp->color = node->parent->color;
            node->parent->color = RBNode::black;
            temp->left->color = RBNode::black;
            
            rotateRight(node->parent);
            node = root;
        }
    }
    
    node->color = RBNode::black;
}

void RBTree::printToFile(ofstream &stream) {
    // print the header
    stream << "digraph rbtree {" << endl;
    stream << "    node [shape=circle height=.1 fontname=\"Arial\" style=filled, fontcolor=white];" << endl;
    
    // serialize root
    if (root) {
        root->printSubtree(stream, nil);
    }
    
    // remember to close the braces
    stream << "}" << endl;
}

void RBTree::visualize(string path, string dot) {
    // generate a temp file
    char *tmpname = strdup("/tmp/dotXXXXXX");
    mkstemp(tmpname);
    ofstream f(tmpname);
    
    // print into the temp file
    printToFile(f);
    
    // run dot on temp file
    string command = dot + " -Tpdf " + string(tmpname) + " -q -o " + path + " > /dev/null 2> /dev/null";
    system(command.c_str());
    
    // remove the temp file
    unlink(tmpname);
}

BNode *RBTree::fillBTree(RBNode *parent) {
    // we don't want to construct lots of NILs
    if (parent == nil) {
        return nullptr;
    }
    
    // convert current node
    BNode *node = new BNode();
    node->values[1] = parent->value;
    node->vizcolors[1] = parent->color == RBNode::red ? "red" : "black";
    
    // convert left son
    if (parent->left != nil) {
        node->values[0] = parent->left->value;
        node->vizcolors[0] = parent->left->color == RBNode::red ? "red" : "black";
        node->pointers[0] = fillBTree(parent->left->left);
        node->pointers[1] = fillBTree(parent->left->right);
    }
    
    // convert right son
    if (parent->right != nil) {
        node->values[2] = parent->right->value;
        node->vizcolors[2] = parent->right->color == RBNode::red ? "red" : "black";
        node->pointers[2] = fillBTree(parent->right->left);
        node->pointers[3] = fillBTree(parent->right->right);
    }
    
    // return everything together
    return node;
}

BTree RBTree::btree() {
    // use BTree constructor to avoid any nasty private APIs
    return BTree(fillBTree(root));
}