
#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H

#include <vector>
using namespace std;

class Tree {
	class Node {
	public:
		int id;
		string name;
		Node* left;
		Node* right;
		int height;
		int balance;

		Node();
		Node(int id, string name);
		~Node();

		//void setBalance(Node* element);
		//void setHeight(Node* element);
	};
	Node* root;

	int getHeight(Node* element);
	int getBalance(Node* element);
	int calcHeight(Node* element);
	int calcBalance(Node* element);

	Node* insertNode(Node* current, int id, string name);
	Node* removeNode(Node* current, int id, bool& removed);

	Node* leftLeft(Node* current);
	Node* rightRight(Node* current);
	Node* leftRight(Node* current);
	Node* rightLeft(Node* current);

	Node* searchId(Node* current, int id);
	void searchName(Node* current, string name, vector<int>& names);

	void inOrder(Node* current, vector<string>& names);
	void preOrder(Node* current, vector<string>& names);
	void postOrder(Node* current, vector<string>& names);
	int levelCount(Node* current);

	void getInorderIds(Node* current, vector<int>& ids);


public:
	Tree();
	Tree(Node* root);
	~Tree();

	bool insert(int id, string name);
	bool remove(int id);

	bool searchName(string name);
	bool searchId( int id);

	void printInorder();
	void printPreorder();
	void printPostorder();
	void printLevelcount();

	bool removeInorder(int n);
	bool validId(int id);
	bool validName(string name);

};
#endif //PROJECT1_AVL_H
