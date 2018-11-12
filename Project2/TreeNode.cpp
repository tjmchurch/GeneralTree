#include <string>
#include "TreeNode.h"
using namespace std;
	TreeNode::TreeNode(std::string newTitle, std::string newName){
		title = newTitle;
		name = newName;
		parent = TREENULLPTR;
		leftmostChild = TREENULLPTR;
		rightSibling = TREENULLPTR;
	}

	std::string TreeNode::getName()
	{
		return TreeNode::name;
	}

	std::string TreeNode::getTitle()
	{
		return TreeNode::title;
	}
