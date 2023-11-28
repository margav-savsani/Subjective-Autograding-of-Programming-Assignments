#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
	// insert your code here
	T* toAdd = new T();
	*toAdd = obj;
	if(!root){
		root = new T(obj);
		numberOfLayers = 1;
		count = 1;
		return;
	}
	count++;
	T* currNode = root;
	bool traverseInProgress = false;
	for(int i=4;i>0;i--){
		if(toAdd->object > currNode->object){
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
		if((count>>i)&1 == 0){
			currNode = currNode->left;
		}else{
			currNode = currNode ->right;
		}
	}
	if(count&1 == 0){
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
		if(node->object > node->left->object && node->object > node->right->object)	return;
		if(node->right->object > node->left->object){
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
		if(node->left->object > node->object){
			T temp = node->left->object;
			node->left->object = node -> object;
			node -> object = temp;
			node = node-> left;
			return;
		}
	}
	heapify(node);
}

template<typename T>
void Heap<T>::delMax() {

	// insert your code here
	T* currNode = root;
	if(count == 1){
		delete root;
		count = 0;
		root = nullptr;
		return;
	}
	bool traverseInProgress = false;
	for(int i=4;i>0;i--){
		if( !traverseInProgress && !(count>>i) ){
			continue;
		}
		if( !traverseInProgress ){
			traverseInProgress = true;
			continue;
		}
		if((count>>i)&1 == 0){
			currNode = currNode->left;
		}else{
			currNode = currNode ->right;
		}
	}
	if(currNode->right){
		currNode->right->object = root->object;
		delete currNode->right;
		currNode->right= nullptr;
		count--;
		heapify(root);
		return;
	}
	currNode->left->object = root-> object;
	delete currNode->left;
	currNode->left = nullptr;
	count--;
	heapify(root);
	return;
}

template<typename T>
// Adapted from Adrian Schneider's code on StackOverflow
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
