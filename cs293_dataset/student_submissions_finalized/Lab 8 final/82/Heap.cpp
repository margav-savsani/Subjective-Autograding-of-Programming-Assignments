#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void swap(TreeNode<T>* first, TreeNode<T>* second){
	T obj = first->object;
	first->object = second->object;
	second->object = obj;
}

template <typename T>
void Heap<T>::heapify(TreeNode<T>* node){
	TreeNode<T>* temp = node;
	while(temp != nullptr){
		if(temp->left){
			if(temp->object < temp->left->object){
				swap(temp, temp->left);
				temp = temp->left;
				continue;
			}
		}
		else if(temp->right){
			if(temp->object < temp->right->object){
				swap(temp, temp->right);
				temp = temp->right;
				continue;
			}
		}
		break;
	}
}

template <typename T>
void Heap<T>::getNextLoc(int index, TreeNode<T>*& node){
	if(index == 0){
		node = root;
		return;
	}
	getNextLoc((index-1)/2, node);
	if(index == 2*((index-1)/2) + 1){
		node = node->left;
	}
	else{
		node = node->right;
	}
}	

template <typename T>
void Heap<T>::insert(T obj)
{

	if(root == nullptr){
		root = new TreeNode<T>(obj);
		root->index = 0;
		nextLoc = root;
		lastLoc = root;
		return;
	}
	TreeNode<T>* elem;
	if(nextLoc->left == nullptr){
		nextLoc->left = new TreeNode<T>(obj);
		elem = nextLoc->left;
		nextLoc->left->index = 2*nextLoc->index + 1;
		nextLoc->left->parent = nextLoc;
	}
	else if(nextLoc->right == nullptr){
		nextLoc->right = new TreeNode<T>(obj);
		elem = nextLoc->right;
		nextLoc->right->index = 2*nextLoc->index + 2;
		nextLoc->right->parent = nextLoc;
		getNextLoc(nextLoc->right->index/2, nextLoc);
	}

	lastLoc = elem;
	while(elem->parent != nullptr){
		if(elem->parent->object < elem->object){
			swap(elem, elem->parent);
		}
		elem = elem->parent;
	}

}


template <typename T>
bool Heap<T>::isLeftMost(TreeNode<T>* node){
	TreeNode<T>* temp = root;
	while(temp!=nullptr){
		if(temp == node) return true;
		temp = temp->left;
	}
	return false;
}


template <typename T>
T Heap<T>::delMax()
{
	// insert your code here
	T toReturn;

	if(root->left == nullptr && root->right == nullptr){
		toReturn = root->object;
		delete root;
		root = nullptr;
		return toReturn;
	}

	root->object = lastLoc->object;
	nextLoc = lastLoc->parent;
	if(lastLoc->parent->right){
		lastLoc = nextLoc->left; // OR nextLoc->left;
		toReturn = nextLoc->right->object; // OR nextLoc->right;
		delete nextLoc->right;
		nextLoc->right = nullptr;
	}
	else if(lastLoc->parent->left){
		toReturn = lastLoc->object;
		TreeNode<T>* toDel = lastLoc;
		if(isLeftMost(lastLoc->left)){
			TreeNode<T>* temp = root;
			// if the last location was leftmost then the new last location would be the rightmost one.
			while(temp->right != nullptr)
			temp = temp->right;
			lastLoc = temp;

		}
		else{
			getNextLoc(lastLoc->index - 1, lastLoc);
		}
		delete toDel;
		nextLoc->left = nullptr;
	}

	heapify(root);
	return toReturn;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
	static int reclevel = -1;
	static bool prevIsLeft = true;
	static string prevPrefix = "";
	string pat1 = "|   ";
	string pat2 = "    ";
	// reclevel ++;

	// insert your code here

	if (root != nullptr)
	{
		bool isLeft = prevIsLeft;
		string prefix = prevPrefix;
		// Initializing variables
		cout << prefix;

		cout << (isLeft ? "|--" : "|__");

		// print the value of the node
		cout << root->object;
		cout << endl;
		TreeNode<T> *curr = root;
		root = root->left;
		// enter the next tree level - left and right branch
		prevIsLeft = true;
		prevPrefix = prefix + (isLeft ? pat1 : pat2);
	
		printHeap(root);
		root = curr->right;
		isLeft = !isLeft;
		printHeap(root);

		prevPrefix = prefix;
		prevIsLeft = isLeft;
		root = curr;
	}
	else
	{
		// cout << " " << endl;
	}

	// reclevel--;
}


// int main(){
// 	Heap<int>* H = new Heap<int>();
// 	H->insert(10);
// 	H->insert(12);
// 	H->insert(14);
// 	H->insert(15);
// 	H->insert(90);
// 	H->insert(13);
// 	H->insert(4);
// 	H->insert(30);
// 	H->printHeap(H->root);
// 	cout << endl;
// 	H->delMax();
// 	H->insert(1);
// 	H->insert(30);
// 	// cout << H->nextLoc->index << endl;
// 	// cout << H->lastLoc->index << endl;
// 	H->printHeap(H->root);
// }
