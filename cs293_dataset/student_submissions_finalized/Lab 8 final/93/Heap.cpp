#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <stack>

template <typename T>
void Heap<T>::insert(T obj){
	// insert your code here
	if(size==0){
		root = new TreeNode<T>(obj);
		size++;
		return;
	}
	size++;
	stack<bool> S; //stores the direction in which we need to move to get to the last element
	int n = size;
	while(n>0){
		S.push(n%2);
		n /= 2;
	}
	S.pop();
	TreeNode<T>* temp = new TreeNode<T>(obj);
	TreeNode<T>* root_ptr = root;
	bool dir;
	TreeNode<T>* prev = NULL;
	while(!S.empty()){
		dir = S.top();
		S.pop();
		prev = root_ptr;
		if(!((temp->object) < (root_ptr->object))){
			T temp_obj = root_ptr->object;
			root_ptr->object = temp->object;
			temp->object = temp_obj;
		}
		if(dir)
			root_ptr = root_ptr->right;
		else 
			root_ptr = root_ptr->left;
	}
	if(dir)
		prev->right = temp;
	else
		prev->left = temp;
	temp->parent = prev;
}
//deletes the maximum element of the heap while maintaining the heap property
template <typename T>
void Heap<T>::delMax(){
	if(!size)
		return;
	int n = size;
	size--;
	if(!size){
		delete root;
		root = NULL;
		return;
	}
	stack<bool> dir; //stores the direction in which we need to move to get to the last element
	while(n>0){
		dir.push(n%2);
		n/=2;
	}
	dir.pop();
	TreeNode<T>* last = root;
	bool isLeft = 0;
	while(!dir.empty()){
		bool d = dir.top();
		dir.pop();
		if(d) {
			last = last->right;
			isLeft = 0;
		}
		else {
			last = last->left;
			isLeft = 1;
		} 
	}
	root->object = last->object;
	if(last->parent && last->parent->left == last)
		last->parent->left = NULL;
	else if(last->parent)
		last->parent->right = NULL;
	delete last;
	heapify(root);
}

//heapifies the heap
template <typename T>
void Heap<T>::heapify(TreeNode<T>* root){
	if(!root)
		return;
	if(root->left && root->right){
		if(!(root->left->object < root->right->object) && !(root->left->object < root->object)){
			auto temp = root->object;
			root->object = root->left->object;
			root->left->object = temp;
			return heapify(root->left);
		}
		else if(!(root->right->object < root->left->object) && !(root->right->object < root->object)){
			auto temp = root->object;
			root->object = root->right->object;
			root->right->object = temp;
			return heapify(root->right);
		}
	}
	else if(!root->left && !root->right)
		return;
	else if(!(root->right) &&  !(root->left->object < root->object)){
		auto temp = root->object;
		root->object = root->left->object;
		root->left->object = temp;
		return heapify(root->left);
	}
	else if(!(root->left) &&  !(root->right->object < root->object)){
		auto temp = root->object;
		root->object = root->right->object;
		root->right->object = temp;
		return heapify(root->right);
	}
	return;
}
//prints the heap in a proper format
template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node, string prefix, bool isLeft){
	if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        // enter the next tree level - left and right branch
        printHeap(node->left,  prefix + (isLeft ? "│   " : "    "), true);
        printHeap(node->right,  prefix + ( isLeft ? "│   " : "    "), false);
    }
}
