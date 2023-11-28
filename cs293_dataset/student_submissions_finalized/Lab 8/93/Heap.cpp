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
		root = new TreeNode(obj);
		size++;
		return;
	}

	size++;
	stack<bool> S;
	int n = 2;
	while(n>0){
		S.push(n%2);
		n /= 2;
	}
	S.pop();
	auto temp = new TreeNode(obj);
	auto root_ptr = root;
	while(!S.empty()){
		bool dir = S.top();
		S.pop();
		if((*temp) < (root_ptr->object)){
			if(dir){
				auto temp1 = root_ptr->right;
				root_ptr->right = temp;
				temp = temp1;
				root_ptr->right->parent = root_ptr;
				if(temp){
					root_ptr->right->left = temp->left;
					root_ptr->right->right = temp->right;
				}
			}
			else{
				auto temp1 = root_ptr->left;
				root_ptr->left = temp;
				temp = temp1;
				root_ptr->left->parent = root_ptr;
				if(temp){
					root_ptr->left->left = temp->left;
					root_ptr->left->right = temp->right;
				}
			}

		}
	}
}

template <typename T>
void Heap<T>::delMax()
{

	// insert your code here

	return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

	// insert your code here

	return;
}
