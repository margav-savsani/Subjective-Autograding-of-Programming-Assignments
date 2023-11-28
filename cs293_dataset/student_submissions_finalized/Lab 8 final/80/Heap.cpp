#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
TreeNode<T> * Heap<T>:: parent_next(TreeNode<T> *node){

  TreeNode<T> *par = node->parent;
  while (par!= nullptr && par->left!=node){
    node=par;
    par=par->parent;
  }
  if(par==nullptr){
    while(node->left!=nullptr){
      node=node->left;
    }
    return node;
  }

  node = par;
  if(node->right==nullptr){
    return node;
  }
  node = node->right;
  while(node->left!= nullptr && node->right!=nullptr){
    node = node->left;
  }
  return node;
}




template<typename T>
TreeNode<T> * Heap<T>:: prev_node(TreeNode<T> *node){

  TreeNode<T> *par = node->parent;
  while (par!= nullptr && par->right!=node){
    node=par;
    par=par->parent;
  }

  if(par==nullptr){
    while(node->right!=nullptr){
      node=node->right;
    }
    return node;
  }

  node = par->left;
  while(node->right!= nullptr){
    node = node->right;
  }
  return node;
}




template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *node = new TreeNode<T>(obj);
  if(root==nullptr){
    root = node;
    last = node;
    return;
  }
  TreeNode<T> *par = parent_next(last);

  if(par->left==nullptr){
    par->left=node;
  }
  else{
    par->right=node;
  }
  
  node->parent=par;
  last = node;
  // insert your code here
  while(node->parent!=nullptr && node->parent->object < node->object){
    T temp;
    temp = node->object;
    node->object = node->parent->object;
    node->parent->object = temp;
    node = node->parent;
  }

  return;
}




template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) {
  
  // insert your code here
  if(node==nullptr || node->left==nullptr){
    return;
  }

  if(node->right==nullptr){
    if(node->object < node->left->object){
      T temp = node->object;
      node->object = node->left->object;
      node->left->object = temp;
      //node = node->left;
      //Heapify(node);
    }
    return;
  }

  
  TreeNode<T>* node_next = node;
  //node_next = node;

  if(node->object < node->left->object){
    node_next = node->left;
  }
  if(node_next->object < node->right->object){
    node_next = node->right;
  }
  if(node!=node_next){
    T temp = node->object;
    node->object = node_next->object;
    node_next->object = temp;
    Heapify(node_next);
  }

  return;
}

template<typename T>
void Heap<T>::de_allocate(TreeNode<T> * pointer) {
  if(pointer!=nullptr){
    de_allocate(pointer->left);
    de_allocate(pointer->right);
    delete pointer;
  }
}



template<typename T>
void Heap<T>::delMax() {
  //printHeap(root);

  if(last==nullptr){
    return;
  }
  TreeNode<T>* par = last->parent;
  TreeNode<T>* node_to_del = last;

  if(par == nullptr){
    root = nullptr;
    last = nullptr;
    return;
  }
  // insert your code here

  T temp = root->object;
  root->object = last->object;
  last->object = temp;
  last = prev_node(last);
  
  if(par->left==node_to_del){
    par->left = nullptr;
  }
  else{
    par->right = nullptr;
  }
  delete node_to_del;
  Heapify(root);
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::my_print(const string& prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = curr->left;
        // enter the next tree level - left and right branch
        my_print( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        my_print( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}


template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  my_print("");
  //cout << endl;

  // insert your code here

  return;
}

/*
int main(){
  cout << "im alive" << endl;
  Heap<int> h;
  h.printHeap(h.get_root());

  h.delMax();
  h.printHeap(h.get_root());
  cout << "phew20" << endl;

  cout << "phew" << endl;
  h.insert(5);
  h.printHeap(h.get_root());
  cout << "phew2" << endl;




  h.delMax();
  cout << "here" << endl;
  h.printHeap(h.get_root());
  cout << "phew20" << endl;


  h.insert(100);
  h.printHeap(h.get_root());
  cout << "phew3" << endl;
  h.insert(20);
  h.printHeap(h.get_root());
  cout << "phew4" << endl;
  h.insert(25);
  h.printHeap(h.get_root());
  cout << "phew5" << endl;

  h.delMax();
  h.printHeap(h.get_root());
  cout << "phew20" << endl;

  h.insert(30);
  h.printHeap(h.get_root());
  cout << "phew6" << endl;
  h.insert(2);
  h.printHeap(h.get_root());
  cout << "phew7" << endl;
  h.insert(90);
  h.printHeap(h.get_root());
  cout << "phew8" << endl;
  h.insert(110);
  h.printHeap(h.get_root());
  cout << "phew9" << endl;
  h.insert(60);
  h.printHeap(h.get_root());
  cout << "phew10" << endl;

  h.delMax();
  h.printHeap(h.get_root());
  cout << "phew20" << endl;

  h.delMax();
  h.printHeap(h.get_root());
  cout << "phew20" << endl;
}

*/



