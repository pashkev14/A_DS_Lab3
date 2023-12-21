#include "AVL.h"

avl_node::avl_node(int val) {
	key = val;
	height = 1;
	left = right = nullptr;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(avl_node* node) {
	if (node == nullptr) {
		return 0;
	}
	return node->height;
}

int balance(avl_node* node) {
	if (node == nullptr) {
		return 0;
	}
	return height(node->left) - height(node->right);
}

void preorder_traversal(avl_node* node) {
	if (node != nullptr) {
		std::cout << node->key << "|" << balance(node) << " ";
		preorder_traversal(node->left);
		preorder_traversal(node->right);
	}
}

void postorder_traversal(avl_node* node) {
	if (node != nullptr) {
		postorder_traversal(node->left);
		postorder_traversal(node->right);
		std::cout << node->key << "|" << balance(node) << " ";
	}
}

void inorder_traversal(avl_node* node) {
	if (node != nullptr) {
		inorder_traversal(node->left);
		std::cout << node->key << "|" << balance(node) << " ";
		inorder_traversal(node->right);
	}
}

avl_node* successor(avl_node* node) {
	avl_node* cur = node->right;
	while (cur->left != nullptr) {
		cur = cur->left;
	}
	return cur;
}

avl_node* rotate_left(avl_node* node) {
	avl_node* x = node->right;
	avl_node* y = x->left;
	x->left = node;
	node->right = y;
	node->height = max(height(node->left), height(node->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

avl_node* rotate_right(avl_node* node) {
	avl_node* x = node->left;
	avl_node* y = x->right;
	x->right = node;
	node->left = y;
	node->height = max(height(node->left), height(node->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

avl_node* insert(avl_node* root, int val) {
	if (root == nullptr) {
		return new avl_node(val);
	}
	if (val < root->key) {
		root->left = insert(root->left, val);
	}
	else if (val > root->key) {
		root->right = insert(root->right, val);
	}
	else {
		return root;
	}
	root->height = 1 + max(height(root->left), height(root->right));
	int bal = balance(root);
	if (bal > 1 && val < root->left->key) {
		return rotate_right(root);
	}
	if (bal < -1 && val > root->right->key) {
		return rotate_left(root);
	}
	if (bal > 1 && val > root->left->key) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}
	if (bal < -1 && val < root->right->key) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}

avl_node* remove(avl_node* root, int val) {
	if (root == nullptr) {
		return root;
	}
	if (val < root->key) {
		root->left = remove(root->left, val);
	}
	else if (val > root->key) {
		root->right = remove(root->right, val);
	}
	else {
		if ((root->left == nullptr) || (root->right == nullptr)) {
			avl_node* tmp = (root->left != nullptr ? root->left : root->right);
			if (tmp == nullptr) {
				tmp = root;
				root = nullptr;
			}
			else {
				*root = *tmp;
			}
			delete tmp;
		}
		else {
			avl_node* tmp = successor(root);
			root->key = tmp->key;
			root->right = remove(root->right, tmp->key);
		}
	}
	if (root == nullptr) {
		return root;
	}
	root->height = 1 + max(height(root->left), height(root->right));
	int bal = balance(root);
	if (bal > 1 && balance(root->left) >= 0) {
		return rotate_right(root);
	}
	if (bal > 1 && balance(root->left) < 0) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}
	if (bal < -1 && balance(root->right) <= 0) {
		return rotate_left(root);
	}
	if (bal < -1 && balance(root->right) > 0) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}