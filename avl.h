
#pragma once
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct node {
	int key;
	node* left;
	node* right;
	int height;
	node(int k):key(k),left(nullptr),right(nullptr),height(1){}
};

class AVL {
	node* root;
public:

	AVL():root(nullptr){}

	//INorder

	void Inorder(node* n) {
		if (n != nullptr) {
			preorder(n->left);
			cout << n->key << " ";
			preorder(n->right);
		}
	}

	//preorder

	void preorder(node* n) {
		if (n != nullptr) {
			cout << n->key << " ";
			preorder(n->left);
			preorder(n->right);
		}
	}

	//func for checking 2 BSTs ,are they identical or not
	bool isIdentical(node* root1, node* root2) {
		if (root1 == nullptr && root2 == nullptr)return 1;
		else if (root1 == nullptr || root2 == nullptr)return 0;
		else {
			return root1->key == root2->key 
				&& isIdentical(root1->left, root2->left) 
				&& isIdentical(root1->right, root2->right);

		}
	}
	
	//utility height func

	int height(node* n) {
		if (n == nullptr)return 0;
		return n->height;
	}

	//right rotation -> tree is left-side heavy 

	node* rightRotation(node* y) {
		node* x = y->left;
		node* T2 = x->right;

		//swap
		x->right = y;
		y->left = T2;

		y->height = 1 + max(height(y->left), height(y->right));
		x->height = 1 + max(height(x->left), height(x->right));

		return x;
	}

	//left rotation -> tree is right-side heavy

	node* leftRotation(node* y) {
		node* x = y->right;
		node* T2 = x->left;

		//swap
		x->left = y;
		y->right = T2;

		y->height = 1 + max(height(y->left), height(y->right));
		x->height = 1 + max(height(x->left), height(x->right));

		return x;
	}

	//balance factor - utility

	int getBal(node* n) {
		if (n == nullptr)return 0;
		return height(n->left) - height(n->right);
	}  

	//insertion

	node* insert(node* n, int k) {
		if (n == nullptr) return new node(k);

		if (k < n->key)n->left = insert(n->left, k);
		else if (k > n->key)n->right = insert(n->right, k);
		else { return n; }// no same data

		//update height
		n->height = 1 + max(height(n->left), height(n->right));

		//get balance factor
		int balance = getBal(n);

		//LL->RR
		if (balance > 1 && k < n->left->key) return rightRotation(n);

		//Left Right
		if (balance > 1 && k > n->left->key) {
			n->left = leftRotation(n->left);
			return rightRotation(n);
		}

		//RR->LR
		if (balance < -1 && k > n->right->key)return leftRotation(n);

		//Right Left
		if (balance < -1 && k < n->right->key) {
			n->right = rightRotation(n->right);
			return leftRotation(n);
		}

		return n;
	}

	//deletion

	node* getIS(node* root) {
		while (root != nullptr && root->left != nullptr) {
			root = root->left;
		}
		return root;
	}

	node* deleteNode(node* n, int k) {
		if (n == nullptr)return n;

		if (k < n->key) {
			n->left=deleteNode(n->left, k);
		 }
		else if (k > n->key) {
			n->right = deleteNode(n->right, k);
		}

		//key is found
		else {
			if (n->left == nullptr) {
				node* temp = n->right;
				delete n;
				return temp;
			}
			else if (n->right == nullptr) {
				node* temp = n->left;
				delete n;
				return temp;
			}
			else {
				node* IS = getIS(n->right);

				n->key = IS->key;

				n->right = deleteNode(n->right, IS->key);
			}
		}

		//if the tree had only 1 node
		if(n==nullptr){
			return n;
		}

		//update height
		n->height = 1 + max(height(n->left), height(n->right));
		
		//check balance factor
		int balance = getBal(n);

		//left left case
		if (balance > 1 && getBal(n->left) >= 0) {
			return rightRotation(n);
		}

		//left right case
		if (balance > 1 && getBal(n->left) < 0) {
			n->left = leftRotation(n->left);
			return rightRotation(n);
		}

		//right right case
		if (balance < -1 && getBal(n->right) <= 0) {
			return leftRotation(n);
		}

		//right left case
		if (balance < -1 && getBal(n->right)>0) {
			n->right = rightRotation(n->right);
			return leftRotation(n);
		}

		return n;
	}
	
};
