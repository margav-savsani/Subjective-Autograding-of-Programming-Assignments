#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
	T object;
	TreeNode<T> *left;
	TreeNode<T> *right;
	TreeNode<T> *parent;

	TreeNode(T initObj) {
		object = initObj;
		left = right = parent = nullptr;
	}
	~TreeNode() {;}
};

template <typename T> class Heap {
	TreeNode<T>* root;
	unsigned short count; //number of elements in the heap
	//making heap as large as 2^16-1
	void rdelete(TreeNode<T> *node){ //recursively deleting nodes rooted at given node
		if (node!=nullptr){
			rdelete(node->left);
			rdelete(node->right);
			delete node;
		}
	}

public:
	Heap() {root = nullptr;count=0;}
	~Heap() {rdelete(root);}

	void insert(T obj);
	void delMax();
	T getMax() {return root->object;}
	void printHeap(TreeNode<T> *node);
	void printHeap(TreeNode<T> *node,const string& prefix, bool isLeft);
	//  void displayAboveThresh(int thresh);
};
#endif

