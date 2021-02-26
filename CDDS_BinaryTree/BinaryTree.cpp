#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
		
}

void BinaryTree::insert(int value)
{
	//If the tree is empty, set the root to be a new node with the given value.
	if (m_root == nullptr)
	{
		m_root = new TreeNode(value);
		return;
	}

	//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
	TreeNode* iter = m_root;

	// Create a TreeNode pointer that will act as an iterator pointing to the parent
	//of the current node and set it to the root.
	TreeNode* iterParent = m_root;

	//Loop until the the current node iterator reaches a nullptr.
	while (iter != nullptr)
	{
		//Check if the value we want to add to the tree is less than the value at the current node.
		if (value < iter->getData())
		{
			//Set the parent node to be the current node before the current node moves positions.
			iterParent = iter;
			//Change the current node to be the child to its left and continue.
			iter = iterParent->getLeft();
		}

		//Check if the value we want to add to the tree is greater than the value at the current node.
		else if (value > iter->getData())
		{
			//Set the parent node to be the current node before the current node moves positions.
			iterParent = iter;
			//Change the current node to be the child to its right and continue.
			iter = iterParent->getRight();
		}

		//If the value is the same as a value already in the list return 
		else if (value == iter->getData())
		{
			return;
		}
		//end loop
	}
	//If the value we want to add is less than the value of the parent node, insert the value to the left.
	if (value < iterParent->getData())
	{
		iterParent->setLeft(new TreeNode(value));
	}
		
	//Otherwise, insert the value to the right.
	else
	{
		iterParent->setRight(new TreeNode(value));
	}
		
}

void BinaryTree::remove(int value)
{
	
	//Create two TreeNode pointers: one to hold a reference to the node we want to remove
	//and another to hold a reference to its parent.
	TreeNode* remove = m_root;
	TreeNode* parent = m_root;
	
	//Try to find the node that matches the value given and its parent in the tree.
	if (findNode(value, remove, parent))
	{
		//If the node cannot be found return.
		return;
	}
		
	//Check to see if the node has a right
	if (remove->hasRight())
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		//Set the first iterator to point to the right child of the node we want to remove.
		TreeNode* iterator = remove->getRight();
		TreeNode* ParentIterator = remove;

		//Loop while the first iterator has a value to its left
		while (iterator->hasLeft())
		{
			//Set the second iterator to be the value of the first iterator.
			//Set the first iterator to be the value to the left of it
			ParentIterator = iterator;
			iterator = iterator->getLeft();
		}
		//end loop

		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.
		remove->setData(iterator->getData());

		//Check if the second iterator has a left child.
		if (ParentIterator->hasLeft())
		{
			//Check if the left child stores the same data as the node we wanted to remove.
			if (ParentIterator->getLeft()->getData() == remove->getData())
			{
				//Set the second iterators left child to be the first iterators right child.
				ParentIterator->setLeft(iterator->getRight());
			}
		}

		//Check if the second iterator has a right child.
		if (ParentIterator->hasRight())
		{
			//Check if the right child contains the same data as the node we want to remove.
			if (ParentIterator->getRight()->getData() == remove->getData())
			{
				//Set the right child of the second iterator to be the right child of the first iterator.
				ParentIterator->setRight(iterator->getRight());
			}
		}

		// Delete the first iterator
		delete iterator;
	}

	//Otherwise, if the node doesn't have a right child
	else if (remove->hasRight())
	{
		//check if the parent of the node to remove has a left child.
		if (parent->getLeft())
		{
			//Check if the data that the left child holds is the same as the data the node to remove holds.
			if (parent->getLeft()->getData() == remove->getData())
			{
				//Set the left child of the parent node to be the left child of the node to remove.
				parent->setLeft(remove->getLeft());
			}
		}

		//Check if the parent of the node to remove has a right child.
		if (parent->hasRight())
		{
			//Check if the data the right child holds is the same as the data the node to remove holds.
			if (parent->getRight()->getData() == remove->getData())
			{
				//Set the right child of the parent node to be the left child of the node to remove.
				parent->setRight(remove->getLeft());
			}
		}

		//Check if the node we want to remove is the root.
		if (remove == m_root)
		{
			//Set the root to be its left child.
			m_root = remove->getLeft();
		}

		
		delete remove;
	}
}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.
	TreeNode* iter = m_root;
	
	//Loop through the tree while the iterator isn't nullptr.
	while (iter != nullptr)
	{
		//Check if the node has the data we want
		if (iter->getData() == value)
		{
			//Return the iterator
			return iter;
		}

		//If the node doesn't have the data we want, check to see if it's higher in value.	
		else if (value > iter->getData())
		{
			//Set the iterator to be its current right child.
			iter = iter->getRight();
		}
		
		//If the node doesn't have the data we want, check to see if it's lower in value.
		else if (value < iter->getData())
		{
			//Set the iterator to be its current left child.
			iter = iter->getLeft();
		}	
	}
	//end loop

	//Return nullptr
	return nullptr;
}

void BinaryTree::draw(TreeNode* selected)
{
	int x = RAYLIB_H::GetScreenWidth() / 2;
	int y = 50;

	draw(m_root, x, y, 300, selected);
}

bool BinaryTree::findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent)
{
	//Create two iterators: one that will point to the current node to compare the search value to,
	//and the other to hold a reference to the parent.
	TreeNode* parentIter = m_root;
	TreeNode* currentIter = m_root;

	//Loop while the current node iterator isn't nullptr
	while (currentIter != nullptr)
	{
		//Check if the search value is the same as the current nodes data.
		if (currentIter->getData() == searchValue)
		{
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			nodeFound = currentIter;
			nodeParent = parentIter;
			//Return true.
			return true;
		}

		//Check if the search value is greater than the value at the current node.
		else if (searchValue > currentIter->getData())
		{
			//Set the parent node to be the current node.
			//Set the current node to be the child to the right of the current node.
			parentIter = currentIter;
			currentIter = parentIter->getRight();
		}
		//Check if the search value is less than the value at the current node.
		else if (searchValue < currentIter->getData())
		{
			//Set the parent node to be the current node.
			//Set the current node to be its left child.
			parentIter = currentIter;
			currentIter = parentIter->getLeft();
		}
		//end loop
	}
	//Return false.
	return false;
}

void BinaryTree::draw(TreeNode* currentNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	//Decrease the horizontal space as the nodes draw
	horizontalSpacing /= 2;

	//Checks if thr current node is null
	if (currentNode)
	{
		//Draws the left child if this node had one
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draws the current node
		currentNode->draw(x, y, (selected == currentNode));
	}