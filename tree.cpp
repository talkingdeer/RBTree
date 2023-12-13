#include "tree.h"

void RBTree::initializeNULLNode(NodePtr node, NodePtr parent) {
	node->data = 0;
	node->parent = parent;
	node->left = nullptr;
	node->right = nullptr;
	node->color = 0;
}
	
void RBTree::preOrderHelper(NodePtr node) {
	if (node != TNULL) {
		cout<<node->data<<" ";
		preOrderHelper(node->left);
		preOrderHelper(node->right);
	} 
}
	
void RBTree::inOrderHelper(NodePtr node) {
	if (node != TNULL) {
		inOrderHelper(node->left);
		cout<<node->data<<" ";
		inOrderHelper(node->right);
	} 
}

void RBTree::postOrderHelper(NodePtr node) {
	if (node != TNULL) {
		postOrderHelper(node->left);
		postOrderHelper(node->right);
		cout<<node->data<<" ";
	} 
}

NodePtr RBTree::searchTreeHelper(NodePtr node, int key) {
	if (node == TNULL || key == node->data) {
		return node;
	}
	if (key < node->data) {
		return searchTreeHelper(node->left, key);
	} 
	return searchTreeHelper(node->right, key);
}

void RBTree::fixDelete(NodePtr x) {
	NodePtr s;
	while (x != root && x->color == 0) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if (s->color == 1) {
				s->color = 0;
				x->parent->color = 1;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->color == 0 && s->right->color == 0) {
				s->color = 1;
				x = x->parent;
			} else {
				if (s->right->color == 0) {
					s->left->color = 0;
					s->color = 1;
					rightRotate(s);
					s = x->parent->right;
				} 
				s->color = x->parent->color;
				x->parent->color = 0;
				s->right->color = 0;
				leftRotate(x->parent);
				x = root;
			}
		} else {
			s = x->parent->left;
			if (s->color == 1) {
				s->color = 0;
				x->parent->color = 1;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->right->color == 0 && s->right->color == 0) {
				s->color = 1;
				x = x->parent;
			} else {
				if (s->left->color == 0) {
					s->right->color = 0;
					s->color = 1;
					leftRotate(s);
					s = x->parent->left;
				} 
				s->color = x->parent->color;
				x->parent->color = 0;
				s->left->color = 0;
				rightRotate(x->parent);
				x = root;
			}
		} 
	}
	x->color = 0;
}

void RBTree::rbTransplant(NodePtr u, NodePtr v){
	if (u->parent == nullptr) {
		root = v;
	} else if (u == u->parent->left){
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RBTree::deleteNodeHelper(NodePtr node, int key) {
	NodePtr z = TNULL;
	NodePtr x, y;
	while (node != TNULL){
		if (node->data == key) {
			z = node;
		}

		if (node->data <= key) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	if (z == TNULL) {
		cout<<"Couldn't find key in the tree"<<endl;
		return;
	} 

	y = z;
	int y_original_color = y->color;
	if (z->left == TNULL) {
		x = z->right;
		rbTransplant(z, z->right);
	} else if (z->right == TNULL) {
		x = z->left;
		rbTransplant(z, z->left);
	} else {
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		} else {
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (y_original_color == 0){
		fixDelete(x);
	}
}

void RBTree::fixInsert(NodePtr k){
	NodePtr u;
	while (k->parent->color == 1) {
		if (k->parent == k->parent->parent->right) {
			u = k->parent->parent->left;
			if (u->color == 1) {
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			} else {
				if (k == k->parent->left) {
					k = k->parent;
					rightRotate(k);
				}
				k->parent->color = 0;
				k->parent->parent->color = 1;
				leftRotate(k->parent->parent);
			}
		} else {
			u = k->parent->parent->right;

			if (u->color == 1) {
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;	
			} else {
				if (k == k->parent->right) {
					k = k->parent;
					leftRotate(k);
				}
				k->parent->color = 0;
				k->parent->parent->color = 1;
				rightRotate(k->parent->parent);
			}
		}
		if (k == root) {
			break;
		}
	}
	root->color = 0;
}

void RBTree::printHelper(NodePtr root, string indent, bool last) {
	if (root != TNULL) {
	   cout<<indent;
	   if (last) {
		  cout<<"R----";
		  indent += "     ";
	   } else {
		  cout<<"L----";
		  indent += "|    ";
	   }
		
	   string sColor = root->color?"RED":"BLACK";
	   cout<<root->data<<"("<<sColor<<")"<<endl;
	   printHelper(root->left, indent, false);
	   printHelper(root->right, indent, true);
	}
}

RBTree::RBTree() {
	TNULL = new Node;
	TNULL->color = 0;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	root = TNULL;
}

void RBTree::clear(NodePtr node) {
	if (node != TNULL) {
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

RBTree::~RBTree() {		// проблема с утечками памяти была из-за деструктора
	clear(root);
	delete TNULL;
}

NodePtr RBTree::minimum(NodePtr node) {
	while (node->left != TNULL) {
		node = node->left;
	}
	return node;
}

NodePtr RBTree::maximum(NodePtr node) {
	while (node->right != TNULL) {
		node = node->right;
	}
	return node;
}

NodePtr RBTree::successor(NodePtr x) {
	if (x->right != TNULL) {
		return minimum(x->right);
	}
	NodePtr y = x->parent;
	while (y != TNULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

NodePtr RBTree::predecessor(NodePtr x) {
	if (x->left != TNULL) {
		return maximum(x->left);
	}
	NodePtr y = x->parent;
	while (y != TNULL && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

void RBTree::leftRotate(NodePtr x) {
	NodePtr y = x->right;
	x->right = y->left;
	if (y->left != TNULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RBTree::rightRotate(NodePtr x) {
	NodePtr y = x->left;
	x->left = y->right;
	if (y->right != TNULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

void RBTree::insert(int key) {
	if(this->searchTree(key) == TNULL){
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}
		if (node->parent == nullptr){
			node->color = 0;
			return;
		}
		if (node->parent->parent == nullptr) {
			return;
		}
		fixInsert(node);
	}
}

int maxDepth(NodePtr node)
{
    if (node == NULL)
        return 0;
    else {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void RBTree::printDepth(){
	cout << "Depth of the tree is " << maxDepth(root) << endl;
	
}