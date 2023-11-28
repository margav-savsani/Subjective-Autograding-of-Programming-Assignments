#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

// #ifndef HEAP_H
#include "Heap.h"


template <typename T>
int height(TreeNode<T>* node){
	int h=0;
	TreeNode<T>* currNode = node;
	while(currNode->left != nullptr){
		h++;
		currNode = currNode->left;
	}

	return h;
}

template <typename T>
TreeNode<T>* insertAt(TreeNode<T>* node, int h, int i=0){

	if(node->left == nullptr && h-1 == i) {
		return node;
	}
	else if(node->right == nullptr && h-1 == i){
		return node;
	}
	else{
		TreeNode<T>* check = insertAt(node->left, h, i+1);
		if(!check){
			return insertAt(node->right, h, i+1);
		}
		else{
			return check;
		}
	}
	return nullptr;
	
}

template <typename T>
void Heap<T>::insert(T obj)
{
	// insert your code here
	if(root == nullptr){
		root = new TreeNode<T>(obj);
		return;
	}
	TreeNode<T>* newNode;
	int h = height(root);
	newNode = insertAt(root, 0, h);
	if(newNode){
		if(!newNode->left){
			newNode->left = new TreeNode<T>(obj);
			newNode->left->parent = newNode;
		}
		else if(!newNode->right){
			newNode->right = new TreeNode<T>(obj);
			newNode->right->parent = newNode;
		}
		else{
			newNode = root;
			while(newNode->left!=nullptr){
				newNode = newNode->left;
			}
			newNode->left = new TreeNode<T>(obj);
		}
	}
	

}

template <typename T>
T Heap<T>::delMax()
{

	// insert your code here

	// return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
	// insert your code here
	if(node == nullptr) return;
	else{
		printHeap(node->left);
		cout << node->object << " ";
		printHeap(node->right);
	}

}


int main(){
	cout << "hello" << endl;
	Heap<int>* H = new Heap<int>();
	H->insert(12);
	H->insert(10);
	H->printHeap(H->root);
}