#include <string>
#include <iostream>
#include "TreeNode.h"
#include "OrgTree.h"
#include <fstream>
//O(1)
void OrgTree::setRoot(TREENODEPTR newRoot) {
	if (root != TREENULLPTR) {
		root->parent = newRoot;
	}
	newRoot->leftmostChild = root;
	root = newRoot;
}
//O(1)
void OrgTree::addRoot(std::string title, std::string name) {
	setRoot(new TreeNode(title, name));
	size++;
}
//O(1)
unsigned int OrgTree::getSize() {
	return size;
}
//O(1)
TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node) {
	return node->leftmostChild;
}
//O(1)
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node) {
	return node->rightSibling;
}
//O(n)
void OrgTree::printSubTree(TREENODEPTR subTreeRoot) {
	if (root == TREENULLPTR) {
		cout << "Empty tree" << endl;
		return;
	}
	std::cout << subTreeRoot->getTitle() << " : " << subTreeRoot->getName() << std::endl;
	print(subTreeRoot->leftmostChild, 1);
}
void OrgTree::print(TREENODEPTR subTreeRoot, int index) {
	for (int i = 0; i < index; i++) {
		std::cout << "\t";
	}
	std::cout << subTreeRoot->getTitle() << " : " << subTreeRoot->getName() << std::endl;
	if (subTreeRoot->leftmostChild != TREENULLPTR) {
		print(subTreeRoot->leftmostChild, index + 1);
	}
	if (subTreeRoot->rightSibling != TREENULLPTR) {
		print(subTreeRoot->rightSibling, index);
	}

}
//O(n)
TREENODEPTR OrgTree::find(std::string title, TREENODEPTR root) {
	if (root == TREENULLPTR) {
		return TREENULLPTR;
	}
	//compares whether equal comapre returns 0 if equal 
	if (!root->getTitle().compare(title)) {
		return root;
	}
	TREENODEPTR tmp = find(title, root->rightSibling);
	if (tmp != TREENULLPTR) {
		return tmp;
	}
	tmp = find(title, root->leftmostChild);	
	return tmp;
	
	
}
//O(n)
TREENODEPTR OrgTree::find(std::string title) {
	return find(title, root);
}
//O(n)
bool OrgTree::read(std::string filename) {		
	std::ifstream infile(filename);
	if (!infile.is_open()){
		infile.close();
		return false;
	}
	clear(getRoot());	
	root = TREENULLPTR;
	std::string line;
	unsigned long counter = 0;
	//write first line 
	if (infile.peek() == ')') // first line should not be
	{
		infile.close();
		return false;
	}
	std::getline(infile, line);
	addRoot(line.substr(0, line.find(",")), line.substr(line.find(",")+1));
	counter++;
	TREENODEPTR current = getRoot();
	while (true) {
		std::getline(infile, line);
			//if the line doesnt have ) make a new treeNode
			if (line.find(')') == std::string::npos) {
				counter++;
				current = readHire(current, line.substr(0, line.find(",")), line.substr(line.find(",")+1));				
			}
			//contains )
			else {
				counter--;
				if (infile.eof()) {
					infile.close();
					if (!counter){						
						return true;
					}
					clear(getRoot());
					root = TREENULLPTR;
					return false;
				}
				std::getline(infile, line);
				if (line.at(0) == ')') {
					counter--;
					current = current->parent;
					if (infile.eof()) {
						if (!counter) {
							infile.close();
							return true;
						}
						clear(getRoot());
						root = TREENULLPTR;
						infile.close();
						return false;
					}
					std::getline(infile, line);
					while (line.at(0) == ')') {
						counter--;
						if (infile.eof()) {
							if (!counter) {
								infile.close();
								return true;
							}
							clear(getRoot());
							root = TREENULLPTR;
							infile.close();
							return false;
							//check for correct file format
						}
						std::getline(infile, line);
						
						current = current->parent;
					}				
				}				
					counter++;
					current = readHire(current->parent, line.substr(0, line.find(",")), line.substr(line.find(",")+1));				
		}
	}
}
//O(n)
void OrgTree::write(std::string filename) {
	std::ofstream ofile(filename);
	recursiveWrite(getRoot(),ofile);
}
void OrgTree::recursiveWrite(TREENODEPTR root, std::ofstream &ofile) {
	if (root == TREENULLPTR){
		return;
	}
	ofile << root->getTitle() << "," << root->getName() << endl;
	recursiveWrite(root->leftmostChild,ofile);
	ofile << ")" << endl;
	recursiveWrite(root->rightSibling, ofile);
}
//hire time complexity
//The average time complexity is n
//big theta(n)
//the worst time complexity is n
//O(n)
//no children on the parent is time complexity is 1
//worst time complexity resuts from one root with n-1 children
void OrgTree::hire(TREENODEPTR parent, std::string newTitle, std::string newName) {
	size++;
	TREENODEPTR tmp = parent;
	//check for no children
	if (tmp->leftmostChild == TREENULLPTR) {
		tmp->leftmostChild = new TreeNode(newTitle, newName);
		tmp->leftmostChild->parent = tmp;
		return;
	}
	//iterate until no right sibling 
	tmp = tmp->leftmostChild;
	while (tmp->rightSibling != TREENULLPTR) {
		tmp = tmp->rightSibling;
	}
	tmp->rightSibling = new TreeNode(newTitle, newName);
	tmp->rightSibling->parent = tmp->parent;
}
//Fire time complexity
//big-theta(n) average case
//O(n) worst 
//worst case happens when you search through X nodes and the deleted node has n-X children
bool OrgTree::fire(std::string formerTitle) {
	//returns 0 if true
	//checks if the root is the one fired
	//root cannot be fired
	if (!formerTitle.compare(getRoot()->getTitle())) {
		return false;
	}
	//returning the parent if the fired person is LMC
	//retruning right sibling if the fired person is not LMC
	TREENODEPTR fNode = fireFind(formerTitle, root);
	//checks for title not being found
	if (fNode == TREENULLPTR) {
		return false;
	}
	size--;
	//checks if the fired person is the LMC of a node
	if (fNode->leftmostChild != TREENULLPTR) {
		if (!formerTitle.compare(fNode->leftmostChild->getTitle())) {
			//node that needs deleted
			TREENODEPTR tmp = fNode->leftmostChild;
			//check if it is a leaf
			if (tmp->leftmostChild == TREENULLPTR) {
				fNode->leftmostChild = tmp->rightSibling;
				delete tmp;
				return true;
			}
			fNode->leftmostChild = tmp->leftmostChild;
			TREENODEPTR iterate = fNode->leftmostChild;
			//iterate until the last child of the deleted node
			while (iterate->rightSibling != TREENULLPTR) {
				iterate->parent = fNode;
				iterate = iterate->rightSibling;
			}
			iterate->parent = fNode;
			//makes the rightMost child of the deleted node->right sibling the deleted nodes right sibling
			iterate->rightSibling = tmp->rightSibling;
			delete tmp;
			return true;
		}
	}
	//fired people is not a LMC
	//fNode->rightSibling contains the fired Person
	TREENODEPTR tmp = fNode->rightSibling;
	//fired person has no child
	if (tmp->leftmostChild == TREENULLPTR) {
		fNode->rightSibling = tmp->rightSibling;
		delete tmp;
		return true;
	}
	fNode->rightSibling = tmp->leftmostChild;
	TREENODEPTR iterate = fNode->rightSibling;
	while (iterate->rightSibling != TREENULLPTR) {
		iterate->parent = fNode->parent;
		iterate = iterate->rightSibling;
	}
	iterate->parent = fNode->parent;
	iterate->rightSibling = tmp->rightSibling;
	delete tmp;
	return true;

}
OrgTree::~OrgTree() {
	clear(getRoot());	
}
//returning the parent if the fired person is LMC
//retruning right sibling if the fired person is not LMC
TREENODEPTR OrgTree::fireFind(std::string title, TREENODEPTR root) {
	if (root == TREENULLPTR) {
		return TREENULLPTR;
	}
	TREENODEPTR tmp;
	if (root->leftmostChild != TREENULLPTR) {
		//compares whether equal comapre returns 0 if equal
		if (!root->leftmostChild->getTitle().compare(title)) {
			return root;
		}
		tmp = fireFind(title, root->leftmostChild);
		if (tmp != TREENULLPTR) {
			return tmp;
		}
	}
	if (root->rightSibling != TREENULLPTR) {
		if (!root->rightSibling->getTitle().compare(title)) {
			return root;
		}
		tmp = fireFind(title, root->rightSibling);
		if (tmp != TREENULLPTR) {
			return tmp;
		}
	}
	return TREENULLPTR;
}

//getRoot time complexity
//big theta(1)
//O(1)
TREENODEPTR OrgTree::getRoot() {
	return OrgTree::root;
}
OrgTree::OrgTree() {
	root = TREENULLPTR;
}
//copy constructor time complexity
//big theta(n)
//O(n)
OrgTree::OrgTree(OrgTree& rhs){
	root = TREENULLPTR;
	size = rhs.getSize();	
	root = copy(rhs.root,root);
	
}
TREENODEPTR OrgTree::copy(TREENODEPTR oldNode,TREENODEPTR parent) {
	if (oldNode == TREENULLPTR){
		return TREENULLPTR;
	}
	TREENODEPTR copyNode = new TreeNode(oldNode->getTitle(), oldNode->getName());
	copyNode->parent = parent;
	copyNode->leftmostChild = copy(oldNode->leftmostChild,copyNode);
	copyNode->rightSibling = copy(oldNode->rightSibling,parent);
	return copyNode;


}
void OrgTree::clear(TREENODEPTR subRoot) {
	if (subRoot == TREENULLPTR) {
		return;
	}
	//delete left subtree
	clear(subRoot->leftmostChild);
	//delete right subtree
	clear(subRoot->rightSibling);
	//delete root
	size--;
	delete subRoot;
	
}
//return the current node
TREENODEPTR OrgTree::readHire(TREENODEPTR parent, std::string newTitle, std::string newName) {
	size++;
	TREENODEPTR tmp = parent;
	//check for no children
	if (tmp->leftmostChild == TREENULLPTR) {
		tmp->leftmostChild = new TreeNode(newTitle, newName);
		tmp->leftmostChild->parent = tmp;
		return tmp->leftmostChild;
	}
	//iterate until no right sibling 
	tmp = tmp->leftmostChild;
	while (tmp->rightSibling != TREENULLPTR) {
		tmp = tmp->rightSibling;
	}
	tmp->rightSibling = new TreeNode(newTitle, newName);
	tmp->rightSibling->parent = tmp->parent;
	return tmp->rightSibling;
}


