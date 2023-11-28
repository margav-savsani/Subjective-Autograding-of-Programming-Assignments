#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


	

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  
	TreeNode<T>* node = new TreeNode(obj);
  
	n++;
  
	if ( n==1 ) root = node;
  
	else {
  
		int number = n;
		int binary[32];
		int i = 0;
		while (number > 0) {

			binaryNum[i] = number % 2;
        		number = number / 2;
        		i++;
		}
 
		TreeNode<T>* curr_root = root;
		for (int j = i - 2; j > 0; j--){
    
    	
			if ( binaryNum[i] == 0 ){
    		
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
			node->parent = curr_node; 
		}

	}
	
	last_element = node;
  
      
	return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  
  last_element->left = root->left;
  last_element->right = root->right;
  
  if ( root->left != nullptr ){
  
  	root->left->parent = last_element;
  }
  if ( root->right != nullptr ) {
  
  	root->right->parent = last_element;
  
  }
  
  last_element->parent = null;
  
  TreeNode<T>* curr_root = last_element;
  
  
  	
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  
