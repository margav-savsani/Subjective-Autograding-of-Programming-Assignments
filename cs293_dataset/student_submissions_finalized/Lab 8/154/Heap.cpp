#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

std::string toBinary(int n)
{
    std::string r = "";
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

template <typename T>
void Heap<T>::insert(T obj){
	if (root == nullptr)
	{
		root = new TreeNode<T>(obj);
		end = root;
		count++;
		// go up till root
		return;
	}
	TreeNode<T> *temp = end;
	while (temp->parent != nullptr && temp->parent->right != temp)
	{
		temp = temp->parent;
	}
	if (temp != root)
	{
		temp = temp->parent->right;
	}
	while (temp->left != nullptr)
	{
		temp = temp->left;
	}
	end = temp->left = new TreeNode<T>(obj, temp, nullptr, nullptr);
	count++;
	temp = end;
	while(temp!=root){
		if(temp->parent > temp) break;
		swap(temp->object, temp->parent->object);
		temp = temp->parent;
	}
	return;
}

template <typename T>
void Heap<T>::delMax(){
	// insert your code here
	if (count < 1)
		return;
	if (count == 1)
	{
		delete root;
		root = nullptr;
		count = 0;
	}
	auto temp = getparent(count);
	temp = (count%2==0) ? temp->left : temp->right;
	swap(root->object, temp->object);
	if(count%2==0){
		temp->parent->left=nullptr;
	}
	else temp->parent->right=nullptr;
	delete temp;
	count--;
	Heapify(root);
	return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node){

	// insert your code here

	return;
}

template <typename T>
TreeNode<T> *Heap<T>::getparent(int n){
	string s = toBinary(n);
	auto temp = root;
	for(int i=1; i<len(s)-1; i++){
		if(s[i] == '0') temp = temp->left;
		else temp = temp->right;
	}
	return temp;
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node){
	if(node->left != nullptr){
		if (node->right != nullptr){
			if(node->left < node && node->right < node){
				return;
			}
			if(node->left < node->right){
				swap(node->object, node->right->object);
				Heapify(node->right);
			}
			else{
				swap(node->object, node->left->object);
				Heapify(node->left);
			}
		}
		else{
			if(node->left > node){
				swap(node->object, node->left->object);
				Heapify(node->left);
			}
		}
	}
	return;
}
