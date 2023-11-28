#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

// Node for a Binary Tree.
template <typename T>
class TreeNode
{
public:
	T object;
	TreeNode<T> *left = nullptr;
	TreeNode<T> *right = nullptr;
	TreeNode<T> *parent = nullptr;

	TreeNode(const T &initObj, TreeNode<T> *parent = nullptr) : object(initObj), parent(parent) {}
	~TreeNode() {} // the class using the Node will free up space. No heap memory is used in the node constructor itself.
};

template <typename T>
class Heap
{
	typedef TreeNode<T> node;
	typedef TreeNode<T> *ptr;

	ptr root;
	int size;

private:
	void swapVals(ptr a, ptr b);
	ptr getLoc(int index);
	void heapify(ptr curr);
public:
	Heap() : root(nullptr), size(0) {}
	~Heap() {}

	void insert(const T &obj);
	void delMax();
	const T &getMax() const { 
		if (!root) throw 1;
		return root->object; // insert your own code here if needed
	} 
	void printHeap(ptr node, const string &prefix = "", int index = 1) const;
	//  void displayAboveThresh(int thresh);
};
#endif
