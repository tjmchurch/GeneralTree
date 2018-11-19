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
	long recursiveRead(istream& infile, TREENODEPTR parent);
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
	//big-theta(1)
	//O(1)
	TREENODEPTR getRoot();
	OrgTree();
	OrgTree(OrgTree& rhs);
	//big-theta(1)
	//O(1)
	void addRoot(std::string title, std::string name);
	//big-theta(1)
	//O(1)
	unsigned int getSize();//return total number of employee
	//big-theta(1)
	//O(1)
	TREENODEPTR leftmostChild(TREENODEPTR node);
	//big-theta(1)
	//O(1)
	TREENODEPTR rightSibling(TREENODEPTR node);
	//big-theta(n) where n is the size of the sub tree
	//O(n)
	void printSubTree(TREENODEPTR subTreeRoot);
	//find time complexity
	//big theta(n)
	//O(n)
	TREENODEPTR find(std::string title);	
	//read time complexity
	//average case is on a balanced tree of n nodes with each node having x children
	//big-theta(nlogbaseX(n))
	//O(n^2) worst 
	//worst case happens when you have a root with one child and that node has n-2 children
	bool read(std::string filename);
	//write time complexity
	//O(n)
	//big-theta(n)
	void write(std::string filename);
	//hire time complexity
	//big theta(n)
	//O(n)
	//no children on the parent is time complexity is 1
	//worst time complexity resuts from one root with n-1 children
	void hire(TREENODEPTR parent, std::string newTitle, std::string newName);
	//Fire time complexity
	//big-theta(n)
	//O(n)
	//worst case happens when you search through X nodes and the deleted node has n-X children
	bool fire(std::string formerTitle);
	~OrgTree();
};