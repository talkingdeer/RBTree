#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <set>
#include <chrono>
using namespace std;
#include "exception.h"

struct Node {
	int data;
	Node *parent;
	Node *left;
	Node *right;
	int color;
};

typedef Node *NodePtr;

class RBTree {
private:
	
	NodePtr root;
	NodePtr TNULL;
	
	void initializeNULLNode(NodePtr node, NodePtr parent);
	void preOrderHelper(NodePtr node);
	void inOrderHelper(NodePtr node);
	void postOrderHelper(NodePtr node);

	NodePtr searchTreeHelper(NodePtr node, int key);

	void fixDelete(NodePtr x);
	void rbTransplant(NodePtr u, NodePtr v);
	void deleteNodeHelper(NodePtr node, int key);
	void fixInsert(NodePtr k);
	void printHelper(NodePtr root, string indent, bool last);
public:
	RBTree();
	~RBTree();
	void clear(NodePtr node);
	
	void preorder() {
		preOrderHelper(this->root);
	}
	void inorder() {
		inOrderHelper(this->root);
	}
	void postorder() {
		postOrderHelper(this->root);
	}
	
	NodePtr searchTree(int k) {
		return searchTreeHelper(this->root, k);
	}

	NodePtr minimum(NodePtr node);
	NodePtr maximum(NodePtr node);
	NodePtr successor(NodePtr x);
	NodePtr predecessor(NodePtr x);

	void leftRotate(NodePtr x);
	void rightRotate(NodePtr x);
	void insert(int key);
	void printDepth();

	NodePtr getRoot(){
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	void print() {
	    if (root) {
    		printHelper(this->root, "", true);
	    }
	}
};