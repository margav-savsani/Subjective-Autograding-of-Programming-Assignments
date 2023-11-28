#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#include  <bits/stdc++.h>
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





// template <typename T> class Heap {
//   TreeNode<T> *root;

//  public:
//   Heap() {root = nullptr;}
//   ~Heap() {;}

//   void insert(T obj);
//   void delMax();
//   T getMax() {return root->object; // insert your own code here if needed
//   }
//   void printHeap(TreeNode<T> *node);
//   //  void displayAboveThresh(int thresh);
// };

template <typename T> class Heap
{
	TreeNode<T> *root;
	TreeNode<T> *lastNode;
	// TreeNode *nfi;      // nodeForInsertion
	int noOfNodes;      // No of nodes in heap
	TreeNode<T> **arr;     // Array of TreeNodes.

public:
	Heap() { 
        root = nullptr;
        lastNode = nullptr;
        noOfNodes == 0;
    }
	~Heap() { ; }

	void insert(T obj);
	void delMax();
	T getMax() { return root->object; }
	void printHeap(TreeNode<T> *node);

	TreeNode<T> *leftmostNode( TreeNode<T> *node );
	TreeNode<T> *getNFI(T t);
	void MyPrint(const string& prefix, bool);
	TreeNode<T>* goBack(TreeNode<T>* node);
	T MaxObj(T a, T b);



};

#endif

