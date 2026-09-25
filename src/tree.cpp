#include <iostream>
#include <regex>
#include "tree.h"

using namespace std;

// Node constructor
Tree::Node::Node() {
	id = 00000000;
	name = "";
	left = nullptr;
	right = nullptr;
	height = 1;
	balance = 0;
}

//Node parametirzed constructor
Tree::Node::Node(int id, string name) {
	this->id = id;
	this->name = name;
	left = nullptr;
	right = nullptr;
	height = 1;
	balance = 0;
}

// Node destructor
Tree::Node::~Node() {
	delete left;
	delete right;

}

int Tree::getHeight(Node* element) {
	if (element == nullptr) return 0; // 0 height for non-existent nodes
	return element->height;
}

int Tree::getBalance(Node* element) {
	if (element == nullptr) return 0;
	return element->balance;
}

// Calculates parent height by taking the max height of both children
int Tree::calcHeight(Node *element) {
	 int height = 1 + max(getHeight(element->left), getHeight(element->right));
	return height;
}

int Tree::calcBalance(Node* element) {
	int balance = getHeight(element->left) - getHeight(element->right);
	return balance;
}

// void Tree::Node::setBalance(Node* element) {
//
// }

// void Tree::Node::setHeight(Node* element) {
//
// }

Tree::Tree() {
	root = nullptr;
}

//Paramterized Tree constructor
Tree::Tree(Node* root) {
	this->root = root;
}

Tree::~Tree() {
	delete root;
}

Tree::Node* Tree::insertNode(Node* current, int id, string name) {
	if (current == nullptr) {
		return new Node(id, name);
	}
	if (id < current->id) {
		current->left = insertNode(current->left, id, name); // Recursively compares againt left subtree
	}
	else if (id > current->id) {
		current->right = insertNode(current->right, id, name); // Recursively compares against right subtree
	}
	//rotate
	current->height = calcHeight(current);
	current->balance = calcBalance(current);

	if (current->balance > 1 && getBalance(current->left) >= 0) {
		return leftLeft(current);
	}
	if (current->balance > 1 && getBalance(current->left) < 0) {
		return leftRight(current);
	}
	if (current->balance < -1 && getBalance(current->right) <= 0) {
		return rightRight(current);
	}
	if (current->balance < -1 && getBalance(current->right) > 0) {
		return rightLeft(current);
	}

	return current;
}

Tree::Node* Tree::rightRight(Node* current) {
	Node* temp = current->right;
	current->right = temp->left;
	temp->left = current;

	current->height = calcHeight(current);
	current->balance = calcBalance(current);
	temp->height = calcHeight(temp);
	temp->balance = calcBalance(temp);
	return temp;
}

Tree::Node *Tree::leftLeft(Node *current) {
	Node* temp = current->left;
	current->left = temp->right;
	temp->right = current;

	current->height = calcHeight(current);
	current->balance = calcBalance(current);
	temp->height = calcHeight(temp);
	temp->balance = calcBalance(temp);
	return temp;

}

Tree::Node *Tree::leftRight(Node *current) {
	current->left = rightRight(current->left);
	return leftLeft(current);
}

Tree::Node *Tree::rightLeft(Node *current) {
	current->right = leftLeft(current->right);
	return rightRight(current);
}

Tree::Node* Tree::removeNode(Node* current, int id, bool& removed) {
	if (current == nullptr) return nullptr;
	if (id < current->id) {
		current->left = removeNode(current->left, id, removed);
	}
	else if (id > current->id) {
		current->right = removeNode(current->right, id, removed);
	}
	else {
		removed = true;
		if (current->left == nullptr) {
			Node* child = current->right;
			current->right = nullptr;
			delete current;
			return child;
			}
		if (current->right == nullptr) {
			Node* child = current->left;
			current->left = nullptr;
			delete current;
			return child;
		}
		Node* next = current->right;
		while (next->left != nullptr) {
			next = next->left;
		}
			current->id = next->id;
			current->name = next->name;
			current->right = removeNode(current->right, next->id, removed);

	}
	current->height = calcHeight(current);
	current->balance = calcBalance(current);
	return current;

}

bool Tree::insert(int id, string name) {
	if(!validId(id) || !validName(name)) return false;
	if (searchId(root,id) != nullptr) return false;

	root = insertNode(root, id, name);
	return true;
}

bool Tree::remove(int id) {
	bool removed = false;
	root = removeNode(root, id, removed);
	return removed;
}

bool Tree::searchId(int id) {
	Node* res = searchId(root, id);
	if (res == nullptr) {
		cout << "unsuccessful" << endl;
		return false;
	}
	cout << res->name << endl;
	return true;
}

Tree::Node* Tree::searchId(Node* current, int id) {
	if (current == nullptr) return nullptr;
	if (current->id == id) return current;
	if (id < current->id) {
		return searchId(current->left, id);
	}
		return searchId(current->right, id);
};

bool Tree::searchName(string name) {
	vector<int>matches;
	searchName(root, name, matches);
	if (matches.empty()) {
		cout << "unsuccessful" << endl;
		return false;
	}
	for (size_t i =  0; i < matches.size(); i++) {
		cout << matches[i] << endl;
	}
	return true;
}

void Tree::searchName(Node* current, string name, vector<int>& matches) {
	if (current == nullptr) return;
	if (current->name == name) matches.push_back(current->id);
	searchName(current->left, name, matches);
	searchName(current->right, name, matches);
}

void Tree::inOrder(Node* current, vector<string>& names) {
	if (current == nullptr) return; // used in class code as a reference
	inOrder(current->left, names);
	names.push_back(current->name);
	inOrder(current->right, names);
}

void Tree::preOrder(Node* current, vector<string>& names) {
	if (current == nullptr) return; //used in class code as a reference
	names.push_back(current->name);
	preOrder(current->left, names);
	preOrder(current->right, names);
}

void Tree::postOrder(Node* current, vector<string>& names) {
	if (current == nullptr) return; // used in class code as a reference
	postOrder(current->left, names);
	postOrder(current->right, names);
	names.push_back(current->name);
}

int Tree::levelCount(Node* current) {
	if (current == nullptr) return 0;
	return current->height;

}
void Tree::printInorder() {
	vector<string>names;
	inOrder(root, names);
	if (!names.empty()) cout << names[0];
	for (int i = 1; i < int(names.size()); i++) {
		cout << ", " << names[i];
	}
	cout << endl;
}
void Tree::printPreorder() {
	vector<string>names;
	preOrder(root, names);
	if (!names.empty()) cout << names[0];
	for (int i = 1; i < int(names.size()); i++) {
		cout << ", " << names[i];
	}
	cout << endl;
}
void Tree::printPostorder() {
	vector<string>names;
	postOrder(root, names);
	if (!names.empty()) cout << names[0];
	for (int i = 1; i < int(names.size()); i++) {
		cout << ", " << names[i];
	}
	cout << endl;
}

void Tree::printLevelcount() {
	cout << levelCount(root);
}

void Tree::getInorderIds(Node*current, vector<int>& ids) {
	if (current == nullptr) return;
	getInorderIds(current->left, ids);
	ids.push_back(current->id);
	getInorderIds(current->right, ids);
}

bool Tree::removeInorder(int n) {
	vector<int>ids;
	getInorderIds(root, ids);
	if (n <0 || n >= (int)ids.size()) {
		return false;
	}
	return remove(ids[n]);
}

bool Tree::validId(int id) {
	// used onine gdb rescource for starting point
	return regex_match(to_string(id), regex("[0-9]{8}"));
}

bool Tree::validName(string name) {
	//used online gdb resource for starting point
	return regex_match(name, regex("[A-Za-z ]+"));
}



