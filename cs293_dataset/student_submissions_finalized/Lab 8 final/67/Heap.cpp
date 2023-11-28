#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
	// insert your code here
	TreeNode<T>* toAdd = new TreeNode<T>(obj);
	if(!root){
		root = toAdd;
		count = 1;
		return;
	}
	count++;
	TreeNode<T>* currNode = root;
	bool traverseInProgress = false;
	for(int i=31;i>0;i--){
		if(currNode->object < toAdd->object ){
			T temp = toAdd->object;
			toAdd->object = currNode->object;
			currNode->object = temp;
		}
		if( !traverseInProgress && !(count>>i) ){
			continue;
		}
		if( !traverseInProgress ){
			traverseInProgress = true;
			continue;
		}
		if(((count>>i)&1) == 0){
			currNode = currNode->left;
		}else{
			currNode = currNode ->right;
		}
	}
	if(currNode->object < toAdd->object ){
		T temp = toAdd->object;
		toAdd->object = currNode->object;
		currNode->object = temp;
	}
	if((count&1) == 0){
		currNode ->left = toAdd;
	}else{
		currNode ->right= toAdd;
	}
	toAdd -> parent = currNode;
	return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
	if(!node)	return;
	if(node->left && node -> right){
		if(!(node->object < node->left->object &&  node->object < node->right->object))	return;
		if(node->left->object < node->right->object){
			T temp = node->right->object;
			node->right->object = node -> object;
			node -> object = temp;
			node = node-> right;
		}else{
			T temp = node->left->object;
			node->left->object = node -> object;
			node -> object = temp;
			node = node-> left;
		}
	}
	if(node->right == nullptr){
		if(node->left == nullptr)	return;
		if(!(node->object < node->left->object))	return;
		T temp = node->left->object;
		node->left->object = node -> object;
		node -> object = temp;
		node = node-> left;
		return;
		
	}
	heapify(node);
}

template<typename T>
void Heap<T>::delMax() {

	// insert your code here
	TreeNode<T>* currNode = root;
	if(count == 1){
		delete root;
		count = 0;
		root = nullptr;
		return;
	}
	bool traverseInProgress = false;
	for(int i=31;i>0;i--){
		if( !traverseInProgress && !(count>>i) ){
			continue;
		}
		if( !traverseInProgress ){
			traverseInProgress = true;
			continue;
		}
		if(((count>>i)&1) == 0){
			currNode = currNode->left;
		}else{
			currNode = currNode ->right;
		}
	}
	if(currNode->right){
		root->object = currNode->right->object;
		delete currNode->right;
		currNode->right= nullptr;
	}else{
		root-> object=currNode->left->object;
		delete currNode->left;
		currNode->left = nullptr;
	}
	count--;
	heapify(root);
	return;
}

// Adapted from Adrian Schneider's code on StackOverflow
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node,const string prefix, bool isLeft) {
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        // enter the next tree level - left and right branch
        printHeap( node->left,prefix + (isLeft ? "│   " : "    "), true);
        printHeap( node->right,prefix + (isLeft ? "│   " : "    "), false);
    }
}

template<typename T>
void Heap<T>::recursiveDelete(TreeNode<T> *node){
	if(node->right){
		recursiveDelete(node->right);
		node->right = nullptr;
	}
	if(node->left){
		recursiveDelete(node->left);
		node->left = nullptr;
	}
	delete node;
	return;
}

template<typename T>
Heap<T>::~Heap(){
	recursiveDelete(root);
	root = nullptr;
}
