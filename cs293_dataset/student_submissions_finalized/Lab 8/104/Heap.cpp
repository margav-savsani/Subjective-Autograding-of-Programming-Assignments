#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
	// insert your code here

	TreeNode<T> *ptr = new TreeNode<T>(T);
	last_node = ptr;

	if (root == nullptr)
	{
		root = ptr;
		last_node = ptr;
		insert_pointer = ptr;
		return;
	}

	if(insert_pointer->left == nullptr){
		insert_pointer->left = ptr;
		ptr->parent = insert_pointer;
	}
	else{
		insert_pointer->right = ptr;
		ptr->parent = insert_pointer;
	}

	TreeNode<T> *papa_ptr = insert_pointer;

	while(papa_ptr != nullptr){
		if(papa_ptr->left == ptr){
			break;
		}
		else{
			papa_ptr = papa_ptr->parent;
			ptr = ptr->parent;
		}
	}

	if(papa_ptr == nullptr){
		papa_ptr = root;
		while(papa_ptr->left != nullptr){
			papa_ptr = papa_ptr->left;
		}
	}
	else{
		while(true){
			if(papa_ptr->left == nullptr || papa_ptr->right == nullptr){
				break;
			}

			if(papa_ptr->left != nullptr){
				papa_ptr = papa_ptr->left;
			}
			else{
				papa_ptr = papa_ptr->right;
			}
		}
	}

	insert_pointer = papa_ptr;
	return;
}

template <typename T>
void Heap<T>::delMax()
{

	// insert your code here

	if(root == nullptr){
		return;
	}
	else if(last_node == root){
		delete last_node;
		last_node = nullptr;
		insert_pointer = nullptr;
		root = nullptr;
		return;
	}

	root->object = last_node->object;

	insert_pointer = last_node->parent;

	TreeNode<T> *papa_ptr = insert_pointer;
	TreeNode<T> *ptr = last_node;

	while(papa_ptr != nullptr){
		if(papa_ptr->right == ptr){
			break;
		}
		else{
			papa_ptr = papa_ptr->parent;
			ptr = ptr->parent;
		}
	}

	if(papa_ptr == nullptr){
		papa_ptr = root;
		while(papa_ptr->right != nullptr){
			papa_ptr = papa_ptr->right;
		}
	}
	else{
		while(true){
			if(papa_ptr->left == nullptr && papa_ptr->right == nullptr){
				break;
			}

			if(papa_ptr->right != nullptr){
				papa_ptr = papa_ptr->right;
			}
			else{
				papa_ptr = papa_ptr->left;
			}
		}
	}

	if(insert_pointer->left == last_node){
		insert_pointer->left = nullptr;
	}
	else{
		insert_pointer->right = nullptr;
	}

	delete last_node;
	last_node = papa_ptr;

	

	return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

	// insert your code here

	return;
}
