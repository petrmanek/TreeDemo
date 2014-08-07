//
//  main.cpp
//  TreeDemo
//
//  Created by Petr Mánek on 10.03.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>
#include "BTree.h"
#include "RBTree.h"

using namespace std;

/**
 Main tree which is modified by the commands.
 */
RBTree tree;

/**
 Path to the dot utility, default value is preset for convenience.
 */
string dot = "/usr/local/bin/dot";

/**
 Trims the string.
 @param str
        Input string
 @return String without whitespaces at the beginning and the end.
 @see trim3 at http://www.codeproject.com/Articles/10880/A-trim-implementation-for-std-string
 */
string& trim(string& str) {
    // some magic
    str.erase(str.begin(), find_if(str.begin(), str.end(),
                                   [](char& ch)->bool { return !isspace(ch); }));
    str.erase(find_if(str.rbegin(), str.rend(),
                      [](char& ch)->bool { return !isspace(ch); }).base(), str.end());
    return str;
}

/**
 Prints the prompt in format: "tree~XXXX$ "
 @param counter
        Counter of commands.
 */
void prompt(int &counter) {
    cout << "tree~" << counter++ << "$ ";
}

/**
 Creates visualization of RB-tree and the corresponding B-tree.
 The files are saved in the current directory and named "tree-XXXX-b.pdf", "tree-XXXX-rb.pdf"
 @param counter
        Counter of commands.
 */
void viz(int counter) {
    // compose names
    string rb = "tree-" + to_string(counter) + "-rb.pdf";
    string b = "tree-" + to_string(counter) + "-b.pdf";
    
    // visualize the trees
    tree.visualize(rb, dot);
    tree.btree().visualize(b, dot);
}

/**
 Prints the help string.
 */
void printhelp() {
    cout << "Syntax: [command] [argument]" << endl;
    cout << "Commands: i (insert), d (delete), f (find), h (help), e or q (exit)" << endl;
    cout << "Every command produces a new tree, which is then visualized and saved into the working directory." << endl;
    cout << "Every visualization has its own numerical identifier, the current one is displayed in the prompt." << endl;
    cout << "May the Force be with you!" << endl;
    cout << endl;
}

/**
 Determines if a file exists.
 @param path
        Path of the file.
 @return true if the file at @c path exists and is readable.
 */
bool fexists(string path) {
    // use the input stream to check for existence
    ifstream ifs(path);
    return ifs.good();
}

/**
 Performs command from the prompt.
 @param line
        Line entered by the user.
 @param counter
        Command counter.
 */
void command(string line, int counter) {
    // normalize input
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    trim(line);
    
    // use the string stream to load data
    stringstream cmd(line);
    char c; cmd >> c;
    
    switch (c) {
        // insert command
        case 'i':
        {
            int arg = -1; cmd >> arg;
            if (arg <= 0) {
                cout << "Positive argument expected. " << endl << endl;
                return;
            }
            
            tree.add(arg);
            viz(counter - 1);
        }
            
            break;
        
        // delete command
        case 'd':
        {
            int arg = -1; cmd >> arg;
            if (arg <= 0) {
                cout << "Positive argument expected. " << endl << endl;
                return;
            }
            
            tree.remove(arg);
            viz(counter);
        }
            
            break;
        
        // find command
        case 'f':
        {
            int arg = -1; cmd >> arg;
            if (arg <= 0) {
                cout << "Positive argument expected. " << endl << endl;
                return;
            }
            
            if (tree.find(arg)) {
                cout << "The tree does contain " << arg << "." << endl;
            } else {
                cout << "The tree does NOT contain " << arg << "." << endl;
            }
        }
            
            break;
            
        // help command
        case 'h':
            printhelp();
            break;
            
        // exit / quit command
        case 'e':
        case 'q':
            exit(0);
            break;
            
        // unknown command fallback
        default:
            cout << "Unknown command \"" << c << "\", type \"h\" for help." << endl << endl;
            break;
    }
}

/**
 The main entry point of the program.
 @param argc
        The number of arguments.
 @param argv
        The values of the arguments.
 @return The exit code.
 */
int main(int argc, const char * argv[])
{
    // print the legal info
    cout << "TreeDemo 0.1" << endl;
    cout << "(c) 2014 Petr Mánek, Charles University in Prague." << endl << endl;
    
    // check for dot
    // check presence in PATH before you ask
    if (system("dot -V > /dev/null 2>&1") == 0) {
        dot = "dot";
    }
    else {
        while (!fexists(dot)) {
            cout << "Dot not found at \"" << dot << "\". Enter a new path, please: ";
            getline(cin, dot);
        }
    }
    
    // initialize interactive mode
    string line;
    int counter = 1;
    prompt(counter);
    
    while (getline(cin, line)) {
        // perform command
        command(line, counter);
        
        // prompt again
        prompt(counter);
    }
    
    return 0;
}

