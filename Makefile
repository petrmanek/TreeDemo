###################################################
#
# Makefile for TreeDemo
#
###################################################

#
# Macros
#

CXX = g++
CFLAGS = -std=gnu++11 -Wall -fexceptions -O3
LNK_OPTIONS = 

SRCDIR = TreeDemo
OBJDIR = build/obj
OUTDIR = build/bin

INSTALL_PREFIX = /usr/local/bin

#
# INCLUDE directories for TreeDemo
#

INCLUDE =

#
# Build TreeDemo
#

build: $(OUTDIR)/TreeDemo

$(OUTDIR)/TreeDemo: before_build \
		$(OBJDIR)/main.o\
		$(OBJDIR)/BNode.o\
		$(OBJDIR)/BTree.o\
		$(OBJDIR)/RBNode.o\
		$(OBJDIR)/RBTree.o
	$(CXX) $(LNK_OPTIONS) \
		$(OBJDIR)/main.o\
		$(OBJDIR)/BNode.o\
		$(OBJDIR)/BTree.o\
		$(OBJDIR)/RBNode.o\
		$(OBJDIR)/RBTree.o\
		-o $(OUTDIR)/TreeDemo

clean: 
		rm \
		$(OBJDIR)/main.o\
		$(OBJDIR)/BNode.o\
		$(OBJDIR)/BTree.o\
		$(OBJDIR)/RBNode.o\
		$(OBJDIR)/RBTree.o\
		$(OUTDIR)/TreeDemo

install: $(OUTDIR)/TreeDemo
		cp $(OUTDIR)/TreeDemo $(INSTALL_PREFIX)/TreeDemo

uninstall:
		rm $(INSTALL_PREFIX)/TreeDemo

#
# Build the parts of TreeDemo
#

# Item # 1 -- main --
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o


# Item # 2 -- BNode --
$(OBJDIR)/BNode.o: $(SRCDIR)/BNode.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)/BNode.cpp -o $(OBJDIR)/BNode.o


# Item # 3 -- BTree --
$(OBJDIR)/BTree.o: $(SRCDIR)/BTree.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)/BTree.cpp -o $(OBJDIR)/BTree.o


# Item # 4 -- RBNode --
$(OBJDIR)/RBNode.o: $(SRCDIR)/RBNode.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)/RBNode.cpp -o $(OBJDIR)/RBNode.o


# Item # 5 -- RBTree --
$(OBJDIR)/RBTree.o: $(SRCDIR)/RBTree.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)/RBTree.cpp -o $(OBJDIR)/RBTree.o

#
# Create necessary folders
#
before_build: 
	[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	[ -d $(OUTDIR) ] || mkdir -p $(OUTDIR)


.PHONY: before_build clean install uninstall build
