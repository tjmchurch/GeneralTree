#pragma once
#define TREENODEPTR TreeNode *
#define TREENULLPTR NULL
#include <string>
#include "TreeNode.h"
#include <fstream>
#include <sstream>
/*
The space complexity of of a tree with N TreeNode is 3TN+2SN
where T is the size of a TREENODEPTR, S is the size
of a string
*/
class OrgTree {
private:
	void print(TREENODEPTR subTreeRoot, int i);
	TREENODEPTR find(std::string title, TREENODEPTR root);
	void setRoot(TREENODEPTR newRoot);
	TREENODEPTR fireFind(std::string title, TREENODEPTR root);
	void clear(TREENODEPTR root);
	TREENODEPTR readHire(TREENODEPTR parent, std::string newTitle, std::string newName);
	void recursiveWrite(TREENODEPTR root, std::ofstream &filename);
	TREENODEPTR copy(TREENODEPTR oldRoot,TREENODEPTR parent);
	unsigned int size = 0;
	TREENODEPTR root;
public:	
	TREENODEPTR getRoot();
	OrgTree();
	OrgTree(OrgTree& rhs);

	void addRoot(std::string title, std::string name);
	unsigned int getSize();//return total number of employee
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	void printSubTree(TREENODEPTR subTreeRoot);
	TREENODEPTR find(std::string title);	
	bool read(std::string filename);
	void write(std::string filename);
	void hire(TREENODEPTR parent, std::string newTitle, std::string newName);
	bool fire(std::string formerTitle);
	~OrgTree();
};