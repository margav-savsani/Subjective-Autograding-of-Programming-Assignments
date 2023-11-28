#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void swap(TreeNode<T> *child, TreeNode<T> *parent);

template <typename T>
TreeNode<T> *Heap<T>::getroot()
{
	return root;
}

template <typename T>
void Heap<T>::insert(T obj)
{
	// insert your code here
	if (root == NULL)
	{
		TreeNode<T> *node = new TreeNode<T>(obj);
		root = node;
		num_elements++;
		return;
	}
	TreeNode<T> *ptr = root;
	int steps = (num_elements % 2 == 0) ? ((num_elements - 2) / 4) : ((num_elements - 1) / 4);
	while (steps != 0)
	{
		int t = steps % 2;
		if (t == 1)
		{
			ptr = ptr->right;
		}
		else
		{
			ptr = ptr->left;
		}
		steps /= 2;
	}
	TreeNode<T> *node = new TreeNode<T>(obj);
	if (ptr->left == NULL)
	{
		ptr->left = node;
		node->parent = ptr;
		num_elements++;
	}
	else
	{
		ptr->right = node;
		node->parent = ptr;
		num_elements++;
	}
	while (ptr != NULL)
	{
		if (node->object > ptr->object)
		{
			swap(root, node, ptr);
			ptr = ptr->parent->parent;
		}
	}

	return;
}

// template <typename T>
// void Heap<T>::delMax()
// {

// 	// insert your code here

// 	return;
// }

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *root)
{
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
	if (node == NULL)
	{
		return;
	}
	cout << node->object << " ";
	if (node->left != NULL)
	{
		printHeap(node->left);
	}
	if (node->right != NULL)
	{
		printHeap(node->right);
	}

	return;
}

template <typename T>
void swap(TreeNode<T> *root, TreeNode<T> *child, TreeNode<T> *parent)
{
	if (parent == NULL || child == NULL)
	{
		return;
	}
	if (parent->parent == NULL)
	{
		if (child = parent->right)
		{
			TreeNode<T> *temp = child->left;
			child->left = parent->left;
			if (child->left != NULL)
			{
				child->left->parent = child;
			}
			parent->left = temp;
			if (temp != NULL)
			{
				temp->parent = parent;
			}
			parent->right = child->right;
			if (child->right != NULL)
			{
				child->right->parent = parent;
			}
			child->right = parent;
			parent->parent = child;
			child->parent = NULL;
			root = child;
		}
		if (child = parent->left)
		{
			TreeNode<T> *temp = child->right;
			child->right = parent->right;
			if (child->right != NULL)
			{
				child->right->parent = child;
			}
			parent->right = temp;
			if (temp != NULL)
			{
				temp->parent = parent;
			}
			parent->left = child->left;
			if (child->left != NULL)
			{
				child->left->parent = parent;
			}
			child->left = parent;
			parent->parent = child;
			child->parent = NULL;
			root = child;
		}
	}
	else
	{
		if (child = parent->right)
		{
			TreeNode<T> *temp = child->left;
			child->left = parent->left;
			if (child->left != NULL)
			{
				child->left->parent = child;
			}
			parent->left = temp;
			if (temp != NULL)
			{
				temp->parent = parent;
			}
			parent->right = child->right;
			if (child->right != NULL)
			{
				child->right->parent = parent;
			}
			child->right = parent;
			if (parent = parent->parent->left)
			{
				parent->parent->left = child;
				child->parent = parent->parent;
			}
			else
			{
				parent->parent->right = child;
				child->parent = parent->parent;
			}
			parent->parent = child;
		}
		if (child = parent->left)
		{
			TreeNode<T> *temp = child->right;
			child->right = parent->right;
			if (child->right != NULL)
			{
				child->right->parent = child;
			}
			parent->right = temp;
			if (temp != NULL)
			{
				temp->parent = parent;
			}
			parent->left = child->left;
			if (child->left != NULL)
			{
				child->left->parent = parent;
			}
			child->left = parent;
			if (parent = parent->parent->left)
			{
				parent->parent->left = child;
				child->parent = parent->parent;
			}
			else
			{
				parent->parent->right = child;
				child->parent = parent->parent;
			}
			parent->parent = child;
		}
	}
}