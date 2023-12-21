#pragma once

#include <iostream>

struct avl_node {

	int key;
	int height;
	avl_node* left;
	avl_node* right;

	avl_node(int);

};

int max(int a, int b);

int height(avl_node* node);

int balance(avl_node* node);

void preorder_traversal(avl_node* node);

void postorder_traversal(avl_node* node);

void inorder_traversal(avl_node* node);

avl_node* successor(avl_node* node);

avl_node* rotate_left(avl_node* node);

avl_node* rotate_right(avl_node* node);

avl_node* insert(avl_node* root, int val);
 
avl_node* remove(avl_node* root, int val);