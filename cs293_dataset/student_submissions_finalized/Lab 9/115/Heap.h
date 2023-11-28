#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode
{
	public:
	T object;
	TreeNode<T> *left;
	TreeNode<T> *right;
	TreeNode<T> *parent;
	TreeNode(T initObj)
	{
		object = initObj;
		left = right = parent = nullptr;
	}
	~TreeNode() {;}
};

template <typename T> class Heap
{
	public:
	TreeNode<T>* root;

	public:
	Heap() {root = nullptr;}
	~Heap() {;}

	T delMax();
	T getMax()
	{
		if(root==NULL)
		{
			return *(new T);
		}
		return root->object;
	}
	void printHeap(TreeNode<T> *node);
	void print(string prefix, bool isLeft);
	void heapify_for_insert(TreeNode<T>* node);
	TreeNode<T>* nextleaf(TreeNode<T>* node);
	TreeNode<T>* leaf(TreeNode<T> *node);
	bool isTreeFull(TreeNode<T> * node);
	int height(TreeNode<T> *node);
	void heapify(TreeNode<T>* node);
	void Interchange(TreeNode<T>* node1,TreeNode<T>* node2);
	void insert(T obj);
};
#endif