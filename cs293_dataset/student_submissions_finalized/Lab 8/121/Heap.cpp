#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj){ //returns a node where new value can be copied
  //if no leaf is already present
  numLeaves++; 
  //so numLeaves now tells the serial number at which the new leaf will be inserted
  if(numLeaves==1){ //heap is empty
    root = new TreeNode<T>(obj);
    return;
  }
  //now we will generate path to new element by calculating it's binary representation
  //we can use the fact that knowing the number of leaves tells you precisely where the
  //node is to be inserted
  int bin_rep=0, mul=1;
  while(numLeaves!=0){
    bin_rep =  bin_rep + (numLeaves%2)*mul;
    mul*=10;
    numLeaves = numLeaves/2;
  }

  string path=to_string(bin_rep);
  //if the string is 1001 we need to go left 2 times and then right once to locate empty 
  //place for insertion. We need to ignore the first digit, it only denotes that the heap is not empty
  TreeNode<T>* z = root;  //z finally denotes the parent where leaf is to be inserted
  for(int i=1; i<=(path.size()-2);i++){  //reading 2nd to 2nd last letter of string
    if(path[i]=='0') z = z->left;
    else if(path[i]=='1') z = z->right;
    else cout<<"WEIRD STRING"<<endl;
  }
  if(path[path.size()-1] == '0') {
    z->left = new TreeNode<T>(obj);
    return;
  }
  else if (path[path.size()-1] == '1') {
    z->right = new TreeNode<T>(obj);
    return;
  }
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  // finding the successor node
  // since we know the number of leaves present, we know where the successor is.
  // we will find the path to it by calculating binary form of number of leaves.
  
  //trivial case 
  if(numLeaves==1){
    root=nullptr;
    numLeaves--;
    return;
  }
  int bin_rep=0, mul=1;
  while(numLeaves!=0){
    bin_rep =  bin_rep + (numLeaves%2)*mul;
    mul*=10;
    numLeaves = numLeaves/2;
  }

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  
  return;
}

  
