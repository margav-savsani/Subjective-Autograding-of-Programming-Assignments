#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#ifndef HEAP_CPP
#define HEAP_CPP

template<typename T>
void Heap<T>::insert(T obj) { 
	// insertion to an empty Heap
	if(root == nullptr){
		root = new TreeNode<T>(obj);
		count =1;
		return;
	}

	// if not empty, increment the count and insert to that position
	count++;
	//cout<<count<<'\n';
	//traverse there
/*
	Explaining the following here - 
	we number the heap in order of the nodes being filled successively
	(eg)
						1
				2				3
			4		5		6		7
	The same in binary
						1
				10				11
			100		101		110		111
	Ignoring the first '1' this is just a 0 for every left movement and 1 for right movement,
	from left to right for each traversal down
						.
				0				1
			00		01		10		11
	we use a consisting of one 1 bit and rest zeros
	we shift rightwards using the bitwise operator 
	1000...0000 ->	0100...0000 -> 0010...0000 -> ..
	till the first 1 digit is encountered in the binary representation of count
	we use the bitwise & to see if the particular digit is 1 or not
	a&count = a if the corresponding digit in count is 1 , and 0 otherwise
	using that to traverse

	for the final node simply useing count&1 (count%2 would have also worked)

*/
	TreeNode<T>*curr = root;
	unsigned short a;
	for(a = 1<<(8*sizeof(a)-1);!(count&a);a=a>>1){} //move the 1 bit till the starting position for the next step is reached
	//one shift is still left.., then we do the loop 
	for(a=a>>1;a>1;a=a>>1){
		if (curr->object<obj){ // Maintaining the heap property
			swap(curr->object, obj);
		}
		if (count&a){// that bit is 1 - go right
			curr = curr->right;
		}
		else{ // that bit is left - go left
			curr = curr->left;
		}
	}
	//maintaining Heap property
	if (curr->object<obj){
		swap(curr->object, obj);
	}
	//final bit, have to insert from here
	if (1&count){
		curr->right = new TreeNode<T>(obj);
	}
	else{
		curr->left = new TreeNode<T>(obj);
	}
	//printHeap(root);
	return;
}

template<typename T>
void Heap<T>::delMax() {
	if (count==0) return; ///trying to delete an empty heap
	//when at the root
	if (count==1){
		delete root;
		count=0;
		return;
	}
	//otherwise,
	//goto last elem -- similar to insertion find
	TreeNode<T>* lastem,*curr = root;
	// a used like in insert
	unsigned short a;
	for(a = 1<<(8*sizeof(a)-1);!(count&a);a=a>>1){} // scan rightward for start of number
	//compare each bit except last
	for(a=a>>1;a>1;a=a>>1){
		//traverse down
		if (count&a){
			curr = curr->right;
		}
		else{
			curr = curr->left;
		}
	}
	//last step, delete and set to null
	if (1&count){
		lastem = curr->right;
		curr->right = nullptr;
	}
	else{
		lastem = curr->left;
		curr->left = nullptr;
	}

	//move the last element to the root and remove the last node
	swap(root->object,lastem->object);
	delete lastem;
	count--; //decrement count

	//heapify - move the root downstream till the heap property is satisfied
	for (TreeNode<T>* curr = root;curr->left!=nullptr;){
		if(curr->right==nullptr){ //if right is null it must be the penultimate level, can exit the loop after one comparison
			if (curr->object<curr->left->object) swap(curr->object,curr->left->object);
			return;
		} //otherwise compare with the larger child and swap if necessary
		TreeNode<T>* maxptr = (curr->left->object<curr->right->object?curr->right:curr->left);
		if (curr->object<maxptr->object){
			swap(curr->object,maxptr->object);
			curr = maxptr;
		}
		else return;
	}

	return;
}

//adapted from the print bst functions, helper function
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node,const string& prefix, bool isLeft) {

	if( node != nullptr )   {
		cout << prefix;
		
		cout << (isLeft ? "|--" : "|__" );
		
		// print the value of the node
		cout<<node->object.rating;
		cout << endl;
		TreeNode<T> *curr = node;
		node = node->left;
		// enter the next tree level - left and right branch
		printHeap(node, prefix + (isLeft ? "│   " : "    "), true);
		node = curr->right;
		printHeap(node, prefix + (isLeft ? "│   " : "    "), false);
		node = curr;
	}
}
	
template<typename T> // calls the printheap with other signature
void Heap<T>::printHeap(TreeNode<T> *node) {
	printHeap(node,"",true);
}
#endif