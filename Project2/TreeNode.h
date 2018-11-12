#pragma once
#define TREENODEPTR TreeNode *
#define TREENULLPTR NULL
#include <string>
using namespace std;

class TreeNode {
private:
	std::string name;
	std::string title;
public:
	TREENODEPTR rightSibling;//right sibling
	TREENODEPTR leftmostChild;//leftmost chid
	TREENODEPTR parent;
	TreeNode(std::string newTitle, std::string newName);
	
	std::string getName();
	std::string getTitle();
};