#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
	num++;
	// cout << num << endl;          // very useful for debugging
	TreeNode<T> *leaf=new TreeNode<T>(obj);
	if (num==1) {root=leaf; ; return;}
	int n=num;
	int bin[32];     // array to store binary number
	int i=0;         // counter for binary array
	
	while (n>0) {    // storing the bits of n in array
		bin[i] = n%2;
		n = n/2;
		i++;
	}
	
	TreeNode<T> *currNode=root;
	for (int j=i-2; j>=1; j--) {   // don't forget to remove the condition involving nullptr, even though it doesn't matter
		if (bin[j]==0 && (currNode->left != nullptr)) currNode=currNode->left;
		else if (bin[j]==1 && (currNode->right != nullptr)) currNode=currNode->right;
	}
	
	if (bin[0]==1) {currNode->right=leaf; leaf->parent = currNode;}
	else {currNode->left=leaf; leaf->parent = currNode;}
	
	TreeNode<T> *childNode=leaf;
	while (currNode != nullptr) {
		if (currNode->object < childNode->object) {
			T x;
			TreeNode<T> *temp=new TreeNode<T>(x);
			temp->object=childNode->object;
			childNode->object=currNode->object;
			currNode->object=temp->object;
		}
		currNode=currNode->parent;
		childNode=childNode->parent;
		
	}
	return;
}

template<typename T>
void Heap<T>::delMax() {
	int n=num;
	int bin[32];     // array to store binary number
	int i=0;         // counter for binary array
	
	while (n>0) {    // storing the bits of n in array
		bin[i] = n%2;
		n = n/2;
		i++;
	}

	if (num==1) {root=nullptr; num--; return;}
	// cout << "1\n";
	TreeNode<T> *currNode=root;
	for (int j=i-2; j>=0; j--) { 
		if (bin[j]==0) currNode=currNode->left;
		else if (bin[j]==1) currNode=currNode->right;
	}
	bool isLeft = false;
	// cout << currNode << endl;
	if (currNode->parent->left == currNode) isLeft = true;
	root->object=currNode->object;           // This is for xchanging content in root with leaf
	if (isLeft) currNode->parent->left=nullptr;  //
	else currNode->parent->right=nullptr;        // This is for deleting the leaf

	TreeNode<T> *tr = root;
	T x;
	TreeNode<T> *temp=new TreeNode<T>(x);   // just a temporary node
	while (tr->left != nullptr) {
		if (tr->right != nullptr) {   // swapping the content in parent with left/right child
			TreeNode<T> *t=(tr->left->object < tr->right->object ? tr->right : tr->left);
			if (tr->object < t->object) {
				temp->object = tr->object;
				tr->object = t->object;
				t->object = temp->object;
				tr=t;
			}

			else break;
		}

		else {
			if (tr->object < tr->left->object) {
				temp->object=tr->left->object;
				tr->object=tr->left->object;
				tr->left->object=temp->object;
				tr=tr->left;
			}
			else break;
		}
	}
	// cout << "exit\n";
	// insert your code here
	
	num--;
	return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
/*
To implement a heap with a binary tree with O(log n) time complexity, you need to store the total number of nodes as an instance variable.

Suppose we had a heap of 10 total nodes.

If we were to add a node...

We increment the total number of nodes by one. Now we have 11 total nodes. We convert the new total number of nodes (11) to its binary representation: 1011.

With the binary representation of the total nodes (1011), we get rid of the first digit. Afterwards, we use 011 to navigate through the tree to the next location to insert a node in. 0 means to go left and 1 means to go right. Therefore, with 011, we would go left, go right, and go right...which brings us to the next location to insert in.

We examined one node per level, making the time complexity O(log n)
	ref: https://stackoverflow.com/questions/18241192/implement-heap-using-a-binary-tree#comment46842275_21391589
*/


// I kinda cheated by initailizing a global variable num in Heap.h


/*	
	Converting from decimal to binary representation
	ref: *https://www.geeksforgeeks.org/program-decimal-binary-conversion/
*/
