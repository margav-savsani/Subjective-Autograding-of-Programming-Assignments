#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include<string>

template<typename T>
void Heap<T>::insert(T obj) {   

  // insert your code here
  if(root == nullptr){            //case when root is null, we simply add a node and make it root
    root = new TreeNode<T>(obj);
    numnodes++;
    return;
  }
  //binary representation of numnodes + 1;
  int n = numnodes + 1;
  int binary=0;
  int i=1;
  while(n != 0){
    binary = binary + (n % 2)*i;
    n = n/2;
    i *= 10;
  }
  std::string str = to_string(binary);            //storing the binary number as string for easy access

  TreeNode<T> *a = new TreeNode<T>(obj);     //for inserting
  TreeNode<T> *b;        //for traversing
  b = root;
  if(binary == 10){              //case when only root is present
    root->left = a;
    a->parent = root;
  }
  else if(binary == 11){          //case when only root with left node is present
    root->right = a;
    a->parent = root;
  }
  else{
    for (int i = 1; i < str.length()-1; i++)     //loop through the binary string ignoring starting 1
    {
      char x = str.at(i);
      if(x=='0'){                          //traversing based on digits of binary number
        b = b->left;
      }
      else{
        b = b->right;
      }
    }
    char y = str.at(str.length()-1);
    if(y=='0'){                             //inserting new node appropriately at right location, updating pointers
      b->left = a;
      a->parent = b; 
    }
    else{
      b->right = a;
      a->parent = b;
    }
  }

  //now node has been inserted to the right of the bottom right node
  //we need to satisfy heap property
  //a is the inserted node, b its parent
  while(a != root){                           //going up the heap from a and updating objects to satisfy heap property
    if(a->parent->object < a->object){
      T temp;
      temp = a->object;
      a->object = a->parent->object;
      a->parent->object = temp;
    }
    a = a->parent;
  }

  numnodes++;                                //as we have inserted a node

}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){        //funciton to heapify 
  if(node == nullptr){                 //if node is nullptr
    return;
  }
  if(node->left == nullptr){            //when node is in last layer
    return;
  }
  if(node->right == nullptr){             //node is in second last layer with right chlid null, just compare with left and swap if needed
    if(node->object < node->left->object)
      swap(node->object,node->left->object);
      heapify(node->left);
  }
  else{
    if(node->left->object < node->right->object){         //checking for larger object among children , swapping if needed 
      if(node->object < node->right->object){
        swap(node->object,node->right->object);
        heapify(node->right);                            //heapifying children
      }
    }
    else{
      if(node->object < node->left->object){
        swap(node->object,node->left->object);
        heapify(node->left);
      }
    }
  }
}

template<typename T>
void Heap<T>::delMax() {   
  
  if(numnodes == 0){       //no nodes
    return;
  } 
  if(numnodes==1){        //just the root
    delete root;
    numnodes=0;
    return;
  }
  int n = numnodes;
  int binary=0;
  int i=1;
  while(n != 0){
    binary = binary + (n % 2)*i;
    n = n/2;
    i *= 10;
  }

  std::string str = to_string(binary);         //string representation of binary number
  TreeNode<T> *alpha;
  
  alpha = root;
  for (int i = 1; i < str.length(); i++){    //traversing the tree to find the node to be deleted
      char x = str.at(i);
      if(x=='0'){
        alpha = alpha->left;
        
      }
      else{
        alpha = alpha->right;
        
      }
  }
  root->object = alpha->object;              //setting root object as that of to be deleted node
  if(alpha == alpha->parent->right){         //updating pointers
    alpha->parent->right=nullptr;
  }
  else alpha->parent->left = nullptr;

  delete alpha;
  
  heapify(root);                             //heapifying
  
  numnodes--;                               //as we have deleted a node
  return;
}

template<typename T>
void printall(TreeNode<T> *node, const string& prefix, bool isLeft=false){    //function to print all nodes, inspired from printBST function in lab 4 and 5
  if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        cout << node->object 
            << endl;

        printall( node->left,prefix + (isLeft ? "│   " : "    "), true);
        printall( node->right,prefix + (isLeft ? "│   " : "    "), false);
    }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here
  printall(node, "", false);

  return;
}

  
