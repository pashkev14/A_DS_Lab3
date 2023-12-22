#include <chrono>
#include <fstream>

#include "BST.h"
#include "RB.h"
#include "AVL.h"

using namespace std::chrono;

/*
auto start = high_resolution_clock::now();
input your function here
auto stop = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(stop - start);
*/

int rb_height(rb_node* root) {
	if (root == nullptr) {
		return -1;
	}
	return std::max(rb_height(root->left), rb_height(root->right)) + 1;
}


int main() {
	std::ifstream file("nums1000000.txt");
	int tmp;
	avl_node* root = nullptr;
	for (int i = 1; i <= 1000000; ++i) {
		file >> tmp;
		if (i % 20000 == 0) {
			root = insert(root, tmp);
			std::cout << root->height << "\n";
		}
		else {
			root = insert(root, tmp);
		}
	}
	return 0;
}