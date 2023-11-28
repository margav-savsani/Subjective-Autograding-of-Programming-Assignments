#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


	
using namespace std;
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  
	TreeNode<T>* node = new TreeNode<T>(obj);
  
  	// maintain the tract of number of elements.
	n++;
  
	if ( n==1 ) root = node; // initial condition 
  
	else {
  
  		// calculate the binary form of number of elements in the Heap.
  		// 0 indicates its in left subtree.
  		// 1 indicates its in right subtree.
		int number = n; 
		int binaryNum[32];// stores number in binary form
		int i = 0;
		while (number > 0) {

			binaryNum[i] = number % 2;
        		number = number / 2;
        		i++;
		}
 
 		// find the final position to insert.
		TreeNode<T>* curr_root = root;
		for (int j = i - 2; j > 0; j--){
    
    	
			if ( binaryNum[j] == 0 ){
    		
    				curr_root = curr_root->left;
    			}
    	
    			else {
    		
    				curr_root = curr_root->right;
    			}
		}
    
    		
		if ( binaryNum[0] == 0){
    
			curr_root->left = node;
			node->parent = curr_root;
		}
    		
		else {
    
 			curr_root->right = node;
			node->parent = curr_root; 
		}

	}
	
	// maintain the tract of last element
	last_element = node;
	
	// heapify the tree.		
	TreeNode<T>* curr_node = node;
	// swap the elements untill parent value is greater than object value.
	while ( curr_node->parent != nullptr ) {
		
		if ( curr_node->parent->object < curr_node->object ) {
	
			T value = curr_node->object;
			curr_node->object = curr_node->parent->object;
			curr_node->parent->object = value;
			curr_node = curr_node->parent;
		}
		else break;
		
		
	}
				     
	return;
}

template<typename T>
void Heap<T>::delMax() {

	// insert your code here
  
	// Base cases
	if ( root == nullptr ) return;
  	if ( root == last_element ) {
  	
  		root = nullptr;
  		last_element = nullptr;
  		n--;// maintain the track of elements.
  		return;
  	}
  	// shift last element object to the top.
	root->object = last_element->object ;// change the object of the root.
	TreeNode<T>* dady = last_element->parent;
	
	// check whether last_element is left child or right child of the parent.
	// if it is right child then it is the last element.
	if ( dady->left != nullptr && dady->right != nullptr ) {
  	
  		dady->right = nullptr;
  		last_element = dady->left;
  		n--;
  	}
  	
  	else {
  		
  		// else find the last element using binary method... as we did in insertion.
  		dady->left = nullptr;
  		n--;// keep the track of elements.
  		int number = n;
		int binaryNum[32];
		int i = 0;
		while (number > 0) {

			binaryNum[i] = number % 2;
        		number = number / 2;
        		i++;
		}
 
		TreeNode<T>* curr_root = root;
		for (int j = i - 2; j >= 0; j--){
    
    	
			if ( binaryNum[j] == 0 ){
    		
    				curr_root = curr_root->left;
    			}
    	
    			else {
    		
    				curr_root = curr_root->right;
    			}
		}
    
		last_element = curr_root;

	} 	
  
  	// heapify the Heap, from the root.
	TreeNode<T>* curr_root = root;

	while ( curr_root->left != nullptr || curr_root->right != nullptr  ) {
  	
		T parent_side = curr_root->object;
  		T left_side;
  		bool left_greater = false;
  		T right_side;
  		bool right_check = false;
  		// check whether left object is greater than parent object.
  		if ( curr_root -> left != nullptr && parent_side < curr_root -> left->object ){
  		
  			left_side = curr_root -> left->object;
  			left_greater = true;
  		}
  		
  		// Similarly check whether right object is greater than parent object.
  		if ( curr_root -> right != nullptr && parent_side < curr_root ->right->object){
  		
  			right_side = curr_root -> right->object;
  			right_check = true;
  		}
  	
  		// if both are greater.
  		if ( right_check== true && left_greater == true ) {

  		
  			// check which is maximum 
  			if ( curr_root ->right->object < curr_root -> left->object ){
  			
  				curr_root->object = curr_root -> left->object;
  				curr_root -> left->object = parent_side;
  			}
  			else {
  			
  				curr_root->object = curr_root -> right->object;
  				curr_root ->right->object = parent_side;
  			}
  		
		}
  		// if only left is greater
  		else if (  right_check == false && left_greater == true ){
  	
  			curr_root->object = curr_root -> left->object;
  			curr_root -> left->object = parent_side;
  		}
  		
  		// if only right is greater replace by right.
		else if ( right_check == true && left_greater == false ) {
  		
  			curr_root->object = curr_root -> right->object;
  			curr_root ->right->object = parent_side;
  		}
  		
  		else  break;	
  		
	}
 		
	return;
	
}

template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft) {
  // changed the arguments of the member function.
  // insert your code here
	if( root != nullptr )
	{

       	cout << prefix;
       	cout << (isLeft ? "|--" : "|__" );
       	cout<< root->object<<endl;
       	TreeNode<T> *curr = root;
       	root = root->left;
       	printHeap( prefix + (isLeft ? "│   " : "    "), true);
        	root = curr->right;
        	printHeap( prefix + (isLeft ? "│   " : "    "), false);
        	root = curr;	
        		
        	
	}

	return;
	
}

  
