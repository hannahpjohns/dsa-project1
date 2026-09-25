#include <iostream>
#include <string>
#include <sstream>
#include "Tree.h"

using namespace std;

int main(){
	cout << "START" << endl;
	Tree tree;
	int n;
	cin >> n;
	cin.ignore();

	for (int i = 0; i < n; i++) {
		string line;
		getline(cin, line);
		stringstream ss(line);
		string word;
		ss >> word;

		if (word == "insert") {
			size_t quote1 = line.find('"');
			size_t quote2 = line.find('"', quote1 + 1);
			string name = line.substr(quote1 + 1, quote2 - quote1 - 1);
			int id = stoi(line.substr(quote2 + 1));
			if (tree.insert(id, name)) {
				cout << "successful" << endl;
			}
			else cout << "not successful" << endl;
		}
		else if (word == "remove") {
			int id;
			ss >> id;
			if(tree.remove(id)) {
				cout << "successful" << endl;
			}
			else cout << "not successful" << endl;
		}
		else if (word == "print") {
			if (line.find('"') != string::npos) {
				size_t quote1 = line.find('"');
				size_t quote2 = line.find('"', quote1 + 1);
				tree.searchName(line.substr(quote1 + 1, quote2 - quote1 - 1));
			}
			else {
				int id;
				ss >> id;
				tree.searchId(id);
			}
		}
		else if (word == "printLevelcount") {
			tree.printLevelcount();
		}
		else if (word == "printInorder") {
			tree.printInorder();
		}
		else if (word == "printPreorder") {
			tree.printPreorder();
		}
		else if (word == "printPostorder") {
			tree.printPostorder();
		}
		else if (word == "removeInorder") {
			int num;
			ss >> num;
			if (tree.removeInorder(num)) {
				cout << "successful" << endl;
			} else {
				cout << "not successful" << endl;
			}
		}
	}

	return 0;
}
