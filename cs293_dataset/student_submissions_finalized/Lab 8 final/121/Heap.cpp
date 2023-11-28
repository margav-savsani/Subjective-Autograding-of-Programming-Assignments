#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj){ 
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
  int numL = numLeaves;
  while(numL!=0){
    bin_rep =  bin_rep + (numL%2)*mul;
    mul*=10;
    numL = numL/2;
  }

  string path=to_string(bin_rep);
  //if the string is 1001 we need to go left 2 times and then right once to locate empty 
  //place for insertion. We need to ignore the first digit, it only denotes that the heap is not empty
  TreeNode<T>* z = root;  //z finally denotes the parent where leaf is to be inserted
  for(int i=1; i<=(path.size()-2);i++){  //reading 2nd to 2nd last letter of string
    if(path[i]=='0') z = z->left;
    else if(path[i]=='1') z = z->right;
    else cout<<"WEIRD STRING"<<endl; //just for debugging 
  }
  if(path[path.size()-1] == '0') {
    z->left = new TreeNode<T>(obj);
    z = z->left;
  }
  else if (path[path.size()-1] == '1') {
    z->right = new TreeNode<T>(obj);
    z = z->right;
  }

  if(z->parent==nullptr) return;
  //now heap condition is to be satisfied
  while(z->parent->object < z->object){
    //swap parent and this node
    T temp = z->object;
    z->object = z->parent->object;
    z->parent->object = temp;

    z = z->parent;
    if(z->parent == nullptr) break;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  // finding the successor node
  // since we know the number of leaves present, we know where the successor is.
  // we will find the path to it by calculating binary form of number of leaves.
  
  //trivial case 
  if(numLeaves==0) return;
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

  string path=to_string(bin_rep);
  //if the string is 1001 we need to go left 2 times and then right once to locate successor 
  //We need to ignore the first digit, it only denotes that the heap is not empty
  TreeNode<T>* z = root;  //z finally denotes the successor
  for(int i=1; i<=(path.size()-1);i++){  //reading 2nd to last letter of string
    if(path[i]=='0') z = z->left;
    else if(path[i]=='1') z = z->right;
    else cout<<"WEIRD STRING"<<endl; //just for debugging 
  }
  //fill z in root
  root->object = z->object;
  //remove z
  //modify parent
  TreeNode<T> *p = z->parent;
  if(p!=nullptr){
    if(numLeaves%2 == 0){ //z is left child
      p->left = nullptr;
    }
    else{ //z is right child
      p->right = nullptr;
    }
  }
  delete z;
  numLeaves--;
  this->Heapify(root);
  return;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *n){
  if((n->left==nullptr) && (n->right==nullptr)){
    return;
  }
  if(n->left==nullptr){
    if(n->object < n->right->object){
      //swap these two
      T temp = n->object;
      n->object = n->right->object;
      n->right->object = temp;
    }
    return;
  }
  if(n->right==nullptr){
    if(n->object < n->left->object){
      //swap these two
      T temp = n->object;
      n->object = n->left->object;
      n->left->object = temp;
    }
    return;
  }
  if(!(n->left->object < n->object) || !(n->right->object < n->object)){
    bool isleft = true;
    T larger = n->left->object;
    if(n->left->object < n->right->object){
      larger = n->right->object;
      isleft = false;
    }
    if(isleft){
      //swap left and parent
      T temp = n->object;
      n->object = n->left->object;
      n->left->object = temp;     
      return Heapify(n->left); 
    }
    else{
      //swap right and parent
      T temp = n->object;
      n->object = n->right->object;
      n->right->object = temp;
      return Heapify(n->right);
    }
  }
}
template<typename T>
void Heap<T>::printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    // root->printInfo();
    cout<<root->object; 
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  string prefix = "";
  bool isLeft = false;
  // insert your code here
  printBinaryTree(root, prefix, isLeft);
}

  
