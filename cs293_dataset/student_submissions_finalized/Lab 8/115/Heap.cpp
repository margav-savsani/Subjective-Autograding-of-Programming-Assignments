#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj)
{
	TreeNode<T> NewNode= new TreeNode(obj);

	return;
}

template<typename T>
void Heap<T>::delMax()
{
	if(root==NULL)
	{
		return;
	}
	if(height(root)==1)
	{
		delete root;
		root=NULL;
	}
	TreeNode<T>* iterator=leaf(root);
	if(iterator->parent->left==iterator)
	{
		root->object=iterator->object;
		iterator->parent->left=NULL;
		delete iterator;
	}
	else if(iterator->parent->right=iterator)
	{
		root->object=iterator->object;
		iterator->parent->right=NULL;
		delete iterator;
	}
	heapify(root);
	return;
}

template<typename T>
void Heap<T>::Interchange(TreeNode<T>* node1,TreeNode<T>* node2)
{
	if(node1==NULL||node2==NULL)
	{
		return;
	}
	else
	{
		TreeNode<T>* node3=new TreeNode(node1->object);
		node3->parent=node1->parent;
		node3->left=node1->left;
		node3->right=node1->right;

		node1->object=node2->object;
		node1->parent=node2->parent;
		node1->left=node2->left;
		node1->right=node2->right;

		node2->object=node3->object;
		node2->parent=node3->parent;
		node2->left=node3->left;
		node2->right=node3->right;
		return;
	}
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node)
{
	if(node->object > node->left->object && node->object < node->right->object)
	{
		Interchange(node->left,node);+++++++++++++++++++++++++++++
	}
}

template<typename T>
int Heap<T>::height(TreeNode<T> *node)
{
	if(node==NULL)
	{
		return 0;
	}
	return height(node->left);
}

template<typename T>
bool Heap<T>::isTreeFull(TreeNode<T> * node)
{
	TreeNode<T>* iterator;
	int i=0;
	while(iterator!=NULL)
	{
		iterator=iterator->left;
		i++;
	}
	iterator=node;
	while(iterator!=NULL)
	{
		iterator=iterator->right;
		i--;
	}
	return (i==0);
}

template<typename T>
TreeNode<T>* Heap<T>::leaf(TreeNode<T> *node)
{
	if(node==NULL)
	{
		return NULL;
	}
	if(node->left==NULL && node->right==NULL)
	{
		return node;
	}
	if(height(node->left)==height(node->right))
	{
		return leaf(node->right);
	}
	if(height(node->left)==1+height(node->right))
	{
		return leaf(node->left);
	}
}

template<typename T>
TreeNode<T>*::nextleaf(TreeNode<T>* node,TreeNode<T>* leaf)
{
	h
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
	if(node==NULL)
	{

	}
	return;
}