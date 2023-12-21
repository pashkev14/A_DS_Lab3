#include "RB.h"

rb_node::rb_node(int val) {
	key = val;
	color = 'R';
	left = right = parent = nullptr;
}

rb_node* rb_node::uncle() {
	if (parent == nullptr || parent->parent == nullptr) {
		return nullptr;
	}
	if (parent->is_left()) {
		return parent->parent->right;
	}
	else {
		return parent->parent->left;
	}
}

rb_node* rb_node::sibling() {
	if (parent == nullptr) {
		return nullptr;
	}
	if (is_left()) {
		return parent->right;
	}
	else {
		return parent->left;
	}
}

bool rb_node::is_left() {
	return this == parent->left;
}

bool rb_node::has_red_child() {
	return ((left != nullptr && left->color == 'R') || (right != nullptr && right->color == 'R'));
}

void rb_node::move_down(rb_node* new_parent) {
	if (parent != nullptr) {
		if (is_left()) {
			parent->left = new_parent;
		}
		else {
			parent->right = new_parent;
		}
	}
	new_parent->parent = parent;
	parent = new_parent;
}

rb_tree::rb_tree() {
	root = nullptr;
}

rb_node* rb_tree::search(int val) {
	rb_node* tmp = root;
	while (tmp != nullptr) {
		if (val < tmp->key) {
			if (tmp->left == nullptr)
				break;
			else
				tmp = tmp->left;
		}
		else if (val == tmp->key) {
			break;
		}
		else {
			if (tmp->right == nullptr)
				break;
			else
				tmp = tmp->right;
		}
	}
	return tmp;
}

rb_node* rb_tree::successor(rb_node* node) {
	rb_node* tmp = node;
	while (tmp->left != nullptr) {
		tmp = tmp->left;
	}
	return tmp;
}

void rb_tree::swap_colors(rb_node* u, rb_node* v) {
	char tmp;
	tmp = u->color;
	u->color = v->color;
	v->color = tmp;
}

void rb_tree::swap_values(rb_node* u, rb_node* v) {
	int tmp;
	tmp = u->key;
	u->key = v->key;
	v->key = tmp;
}

void rb_tree::preorder_traversal(rb_node* node) {
	if (node != nullptr) {
		std::cout << node->key << node->color << " ";
		preorder_traversal(node->left);
		preorder_traversal(node->right);
	}
}

void rb_tree::postorder_traversal(rb_node* node) {
	if (node != nullptr) {
		postorder_traversal(node->left);
		postorder_traversal(node->right);
		std::cout << node->key << node->color << " ";
	}
}

void rb_tree::inorder_traversal(rb_node* node) {
	if (node != nullptr) {
		inorder_traversal(node->left);
		std::cout << node->key << node->color << " ";
		inorder_traversal(node->right);
	}
}

void rb_tree::preorder() {
	preorder_traversal(root);
}

void rb_tree::postorder() {
	postorder_traversal(root);
}

void rb_tree::inorder() {
	inorder_traversal(root);
}

void rb_tree::rotate_left(rb_node* node) {
	rb_node* new_parent = node->right;
	if (node == root) {
		root = new_parent;
	}
	node->move_down(new_parent);
	node->right = new_parent->left;
	if (new_parent->left != nullptr) {
		new_parent->left->parent = node;
	}
	new_parent->left = node;
}

void rb_tree::rotate_right(rb_node* node) {
	rb_node* new_parent = node->left;
	if (node == root) {
		root = new_parent;
	}
	node->move_down(new_parent);
	node->left = new_parent->right;
	if (new_parent->right != nullptr) {
		new_parent->right->parent = node;
	}
	new_parent->right = node;
}

void rb_tree::fix_double_red(rb_node* node) {
	if (node == root) {
		node->color = 'B';
		return;
	}
	rb_node* parent = node->parent, * grandparent = parent->parent, * uncle = node->uncle();
	if (parent->color != 'B') {
		if (uncle != NULL && uncle->color == 'R') {
			parent->color = 'B';
			uncle->color = 'B';
			grandparent->color = 'R';
			fix_double_red(grandparent);
		}
		else {
			if (parent->is_left()) {
				if (node->is_left()) {
					swap_colors(parent, grandparent);
				}
				else {
					rotate_left(parent);
					swap_colors(node, grandparent);
				}
				rotate_right(grandparent);
			}
			else {
				if (node->is_left()) {
					rotate_right(parent);
					swap_colors(node, grandparent);
				}
				else {
					swap_colors(parent, grandparent);
				}
				rotate_left(grandparent);
			}
		}
	}
}

void rb_tree::fix_double_black(rb_node* node) {
	if (node == root) {
		return;
	}
	rb_node* sibling = node->sibling(), * parent = node->parent;
	if (sibling == NULL) {
		fix_double_black(parent);
	}
	else {
		if (sibling->color == 'R') {
			parent->color = 'R';
			sibling->color = 'B';
			if (sibling->is_left()) {
				rotate_right(parent);
			}
			else {
				rotate_left(parent);
			}
			fix_double_black(node);
		}
		else {
			if (sibling->has_red_child()) {
				if (sibling->left != NULL and sibling->left->color == 'R') {
					if (sibling->is_left()) {
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rotate_right(parent);
					}
					else {
						sibling->left->color = parent->color;
						rotate_right(sibling);
						rotate_left(parent);
					}
				}
				else {
					if (sibling->is_left()) {
						sibling->right->color = parent->color;
						rotate_left(sibling);
						rotate_right(parent);
					}
					else {
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						rotate_left(parent);
					}
				}
				parent->color = 'B';
			}
			else {
				sibling->color = 'R';
				if (parent->color == 'B')
					fix_double_black(parent);
				else
					parent->color = 'B';
			}
		}
	}
}

rb_node* rb_tree::replace_node(rb_node* node) {
	if (node->left != nullptr and node->right != nullptr) {
		return successor(node->right);
	}
	if (node->left == nullptr and node->right == nullptr) {
		return nullptr;
	}
	if (node->left != nullptr) {
		return node->left;
	}
	else {
		return node->right;
	}
}

void rb_tree::insert(int val) {
	rb_node* node = new rb_node(val);
	if (root == nullptr) {
		node->color = 'B';
		root = node;
	}
	else {
		rb_node* tmp = search(val);
		if (tmp->key == val) {
			return;
		}
		node->parent = tmp;
		if (val < tmp->key) {
			tmp->left = node;
		}
		else {
			tmp->right = node;
		}
		fix_double_red(node);
	}
}

void rb_tree::remove_node(rb_node* node) {
	rb_node* rep = replace_node(node);
	bool both_black = ((rep == nullptr || rep->color == 'B') && (node->color == 'B'));
	rb_node* parent = node->parent;
	if (rep == nullptr) {
		if (node == root) {
			root = nullptr;
		}
		else {
			if (both_black) {
				fix_double_black(node);
			}
			else {
				if (node->sibling() != nullptr)
					node->sibling()->color = 'R';
			}
			if (node->is_left()) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
		}
		delete node;
		return;
	}
	if (node->left == nullptr || node->right == nullptr) {
		if (node == root) {
			node->key = rep->key;
			node->left = node->right = nullptr;
			delete rep;
		}
		else {
			if (node->is_left()) {
				parent->left = rep;
			}
			else {
				parent->right = rep;
			}
			delete node;
			rep->parent = parent;
			if (both_black) {
				fix_double_black(rep);
			}
			else {
				rep->color = 'B';
			}
		}
		return;
	}
	swap_values(rep, node);
	remove_node(rep);
}

void rb_tree::remove(int val) {
	if (root == nullptr) {
		return;
	}
	rb_node* node = search(val);
	if (node->key != val) {
		return;
	}
	remove_node(node);
}