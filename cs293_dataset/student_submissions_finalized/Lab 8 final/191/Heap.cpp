#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
	if(next == nullptr){
			root = new TreeNode<T>(obj);
			last = root;
			next = root;
			return;
		}
		if(next -> left == nullptr){
			next->left = new TreeNode<T>(obj);
			next->left->parent = next;
			next = next->left;
			last = next;
		}else{
			next->right = new TreeNode<T>(obj);
			next->right->parent = next;
			next = next->right;
			last = next;
		}
		auto currNode = next;
		while(currNode->parent != nullptr){
			if(currNode->parent->object < currNode->object){
				swap(currNode, currNode->parent);
				currNode = currNode->parent;
			}else{
				break;
			}
		}
		currNode = next;

		bool approach_root_right = true;
		while(currNode->parent != nullptr){
			if(currNode->parent->left == currNode){
				currNode = currNode->parent;
				approach_root_right = false;
				break;
			}else{
				currNode = currNode->parent;
			}
		}
		if(currNode ==root && approach_root_right){
			while(currNode->left != nullptr){
				currNode = currNode->left;
			}
			next = currNode;
		}
		else if(currNode->right ==nullptr){
			next = currNode;
		}
		else{
			currNode = currNode->right;
			while(currNode->left!= nullptr){
				currNode = currNode->left;
			}
			next = currNode;
		}
	return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
	if(root == nullptr)return;
		if(last==root){
			root = nullptr;
			next = nullptr;
			last = nullptr;
			return;
		}
		root->object = last->object;
		next = last->parent;
		auto currNode = last;
		
		auto c = last;
		bool approach_root_left = true;
		while(currNode->parent != nullptr){
			if(currNode->parent->right == currNode){
				currNode = currNode->parent;
				approach_root_left = false;
				break;
			}else{
				currNode = currNode->parent;
			}
		}
		if(currNode ==root && approach_root_left){
			while(currNode->right != nullptr){
				currNode = currNode->right;
			}
			c = currNode;
		}
		else{
			currNode = currNode->left;
			while(currNode->right!= nullptr){
				currNode = currNode->right;
			}
			c = currNode;
		}
		
		if(last->parent->left == last)last->parent->left = nullptr;
		else last->parent->right = nullptr;
		delete last;
		last = c;
		Heapify(root);
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
	//print();
	static string prefix="";
	string x = prefix;
	static int i=0;
	if(i == 0){
		if(node == root && node != nullptr || node->parent->right == node){
			cout<<"|__";
		}else{
			cout<<"|--";
		}
		i++;
	}
	if(node != nullptr){
		cout << node->object<<endl;
		
		
		if(node->left != nullptr){
			if(node == root){
				prefix+="    ";
			}else if(node->parent->right == node){
				prefix+="    ";
			}else{
				prefix+="|   ";
			}	
			cout<<prefix;
			cout<< "|--";
			printHeap(node->left);
			prefix = x;
		}
		if(node->right != nullptr){
			if(node == root){
				prefix+="    ";
			}else if(node->parent->right == node){
				prefix+="    ";
			}else{
				prefix+="|   ";
			}	
			cout<<prefix;
			cout<< "|__";
			printHeap(node->right);
			prefix = x;
		}
	}
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node){
		if(node->left!=nullptr && node->right!=nullptr){
			if(node->object < node->left->object){
				if(!(node->right->object < node->left->object)){
					swap(node, node->right);
					Heapify(node->right);
				}else{
					swap(node, node->left);
					Heapify(node->left);
				}
			}
			else if(node->object < node->right->object){
				swap(node, node->right);
				Heapify(node->right);
			}
		}
		else if(node->left != nullptr){
			if(node->object < node->left->object){
				swap(node, node->left);
				Heapify(node->left);
			}
		}
		else{
			return;
		}
	}

template<typename T>
void Heap<T>::swap(TreeNode<T>* node1, TreeNode<T>* node2){
		auto temp = node1->object;
		node1->object = node2->object;
		node2->object = temp;
}

template<typename T>
Heap<T>::~Heap(){
	recursive_delete(root);
}

template<typename T>
void Heap<T>::recursive_delete(TreeNode<T>* node){
	if(node != nullptr){
		recursive_delete(node->left);
		recursive_delete(node->right);
		delete node;
	}
	return;
}
