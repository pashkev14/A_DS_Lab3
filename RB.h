#pragma once

#include <iostream>

struct rb_node {

	int key;
	char color;
	rb_node* left;
	rb_node* right;
	rb_node* parent;

	rb_node(int);

	rb_node* uncle();

	rb_node* sibling();

	bool is_left();

	bool has_red_child();

	void move_down(rb_node* new_parent);

};

struct rb_tree {
	
	rb_node* root;

	rb_tree();

	rb_node* search(int val);

	rb_node* successor(rb_node* node);

	void swap_colors(rb_node* u, rb_node* v);

	void swap_values(rb_node* u, rb_node* v);

	void preorder_traversal(rb_node* node);

	void postorder_traversal(rb_node* node);

	void inorder_traversal(rb_node* node);

	void preorder();

	void postorder();

	void inorder();

	void rotate_left(rb_node* node);

	void rotate_right(rb_node* node);

	void fix_double_red(rb_node* node);

	void fix_double_black(rb_node* node);

	rb_node* replace_node(rb_node* node);

	void insert(int val);

	void remove_node(rb_node* node);

	void remove(int val);

};