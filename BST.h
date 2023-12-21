#pragma once

#include <iostream>

struct bst_node {
	int key;
	bst_node* left;
	bst_node* right;

	bst_node(int);
};

void preorder_traversal(bst_node* node);

void postorder_traversal(bst_node* node);

void inorder_traversal(bst_node* node);

bst_node* insert(bst_node* root, int val);

bst_node* remove(bst_node* root, int key);