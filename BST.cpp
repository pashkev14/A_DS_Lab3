#include "BST.h"

bst_node::bst_node(int val) {
	key = val;
	left = right = nullptr;
}

void preorder_traversal(bst_node* node) {
	if (node != nullptr) {
		std::cout << node->key << " ";
		preorder_traversal(node->left);
		preorder_traversal(node->right);
	}
}

void postorder_traversal(bst_node* node) {
	if (node != nullptr) {
		postorder_traversal(node->left);
		postorder_traversal(node->right);
		std::cout << node->key << " ";
	}
}

void inorder_traversal(bst_node* node) {
	if (node != nullptr) {
		inorder_traversal(node->left);
		std::cout << node->key << " ";
		inorder_traversal(node->right);
	}
}

bst_node* insert(bst_node* root, int val) {
	if (root == nullptr) {
		return new bst_node(val);
	}
	if (val > root->key) {
		root->right = insert(root->right, val);
	}
	else if (val < root->key) {
		root->left = insert(root->left, val);
	}
	return root;
}

bst_node* remove(bst_node* root, int key) {
	if (root == nullptr) {
		return root;
	}
	if (root->key > key) {
		root->left = remove(root->left, key);
		return root;
	}
	else if (root->key < key) {
		root->right = remove(root->right, key);
		return root;
	}
	if (root->left == nullptr) {
		bst_node* tmp = root->right;
		delete root;
		return tmp;
	}
	else if (root->right == NULL) {
		bst_node* tmp = root->left;
		delete root;
		return tmp;
	}
	else {
		bst_node* next_p = root;
		bst_node* next = root->right;
		while (next->left != nullptr) {
			next_p = next;
			next = next->left;
		}
		if (next_p != root)
			next_p->left = next->right;
		else
			next_p->right = next->right;
		root->key = next->key;
		delete next;
		return root;
	}
}