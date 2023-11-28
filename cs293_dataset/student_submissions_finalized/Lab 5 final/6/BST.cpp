#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool BST::insert(int jrnyCode, int price)
{

	TreeNode *dummy = nullptr;
	TreeNode *start = root;
	TreeNode *newnode = new TreeNode(jrnyCode, price);
	if (root == nullptr)
		root = newnode;
	else
	{
		while (start != nullptr)
		{
			dummy = start;
			if (BSTLessThan(newnode, start))
				start = start->left;
			else
				start = start->right;
		}
		if (BSTLessThan(newnode, dummy))
			updateBSTParentChild(newnode, dummy, true);
		else
			updateBSTParentChild(newnode, dummy, false);
	}

	TreeNode *leaf = dummy;
	while (true)
	{
		if (dummy == nullptr)
			break;
		else if ((dummy->right == nullptr || dummy->left == nullptr) && dummy == leaf)
			dummy->height++;
		else
		{
			int l = dummy->height;
			int rl = -1, ll = -1;
			if (dummy->right != nullptr)
				rl = dummy->right->height;
			if (dummy->left != nullptr)
				ll = dummy->left->height;
			dummy->height = max(rl, ll) + 1;
			if (l == dummy->height)
				break;
		}
		dummy = dummy->parent;
	}
	return true;
}

int BST::find(int jrnyCode)
{
	TreeNode *dummy = root;
	TreeNode *newnode = new TreeNode(jrnyCode, 0);

	while (dummy != nullptr && jrnyCode != dummy->get_JourneyCode()) //  loop will continue until correct node is found
	{
		if (BSTLessThan(newnode, dummy))
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}
	if (dummy == nullptr) // node not present
		return -1;
	if (jrnyCode == dummy->get_JourneyCode()) // node found
		return 1;
	return -1;
}

TreeNode *BST::find_node(int jrnyCode)
{
	TreeNode *dummy = root;
	TreeNode *newnode = new TreeNode(jrnyCode, 0);

	while (dummy != nullptr && jrnyCode != dummy->get_JourneyCode()) //  loop will continue until correct node is found
	{
		if (BSTLessThan(newnode, dummy))
			dummy = dummy->left;
		else
			dummy = dummy->right;
	}
	if (dummy == nullptr) // node not present
		return nullptr;
	if (jrnyCode == dummy->get_JourneyCode()) // node found
		return dummy;
	return nullptr;
}

TreeNode *BST::getMinimumNode(TreeNode *start)
{
	TreeNode *start_ = start;
	while (start_->left != nullptr) // Moves leftwards until a leaf occurs
	{
		start_ = start_->left;
	}
	return start_;
}

bool BST::remove(int jrnyCode)
{
	if (jrnyCode == 0) // invalid node to be deleted
		return false;
	TreeNode *rem = find_node(jrnyCode); // assure the presence of node to be deleted
	if (rem == nullptr)
		return false;

	TreeNode *current;
	if (rem->left == nullptr && rem->right == nullptr) // Case 1 - node to be deleted has no children
	{
		if (rem == root)
		{
			rem->update_values(0, 0);
			current = nullptr;
		}
		else if (rem == rem->parent->left)
		{
			current = rem->parent;
			updateBSTParentChild(nullptr, current, true);
		}
		else
		{
			current = rem->parent;
			updateBSTParentChild(nullptr, current, false);
		}
		delete rem;
	}
	else if (rem->left == nullptr) // Case 2 - node to be inserted has only right child
	{

		TreeNode *dummy = rem->right;

		if (rem == root)
		{
			updateBSTParentChild(dummy, nullptr, true);
			root = dummy;
			current = nullptr;
		}
		else if (rem == rem->parent->left)
		{
			current = rem->parent;
			updateBSTParentChild(dummy, current, true);
		}
		else
		{
			current = rem->parent;
			updateBSTParentChild(dummy, current, false);
		}
		delete rem;
	}
	else if (rem->right == nullptr) // Case 2 - node to be inserted has only right child
	{
		TreeNode *dummy = rem->right;
		if (rem == root)
		{
			updateBSTParentChild(dummy, nullptr, false);
			root = dummy;
			current = nullptr;
		}
		else if (rem == rem->parent->left)
		{
			current = rem->parent;
			updateBSTParentChild(dummy, current, true);
		}
		else
		{
			current = rem->parent;
			updateBSTParentChild(dummy, current, false);
		}
		delete rem;
	}
	else // if node to be present has both children
	{
		TreeNode *min = getMinimumNode(rem->right); // min is calculated in right subtree
		current = min->parent;
		rem->update_values(min->get_JourneyCode(), min->get_price());
		if (min == rem->right)
		{
			TreeNode *temp = rem->right->right;
			updateBSTParentChild(temp, rem, false);
		}
		else if (min->right == nullptr)
			updateBSTParentChild(nullptr, current, true);
		else
		{
			TreeNode *dummy = min->right;
			updateBSTParentChild(dummy, current, true);
		}
		delete min;
	}
	TreeNode *leaf = current;
	while (true)
	{
		if (current == nullptr)
			break;
		else if (current->right == nullptr && current->left == nullptr && current == leaf)
			current->height--;
		else
		{
			int l = current->height;
			int rl = -1, ll = -1;
			if (current->right != nullptr)
				rl = current->right->height;
			if (current->left != nullptr)
				ll = current->left->height;
			current->height = max(rl, ll) + 1;
			if (l == current->height)
				break;
		}
		current = current->parent;
	}
	return true;
}
