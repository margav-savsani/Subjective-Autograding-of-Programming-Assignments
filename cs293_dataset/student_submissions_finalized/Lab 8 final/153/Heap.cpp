#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <math.h>
#include "dictionary.h"

int padBitReverse(int);
template<typename T>
void swapNodeContent(TreeNode<T>*, TreeNode<T>*);

template<typename T>
ostream& operator<<(ostream& os, const TreeNode<T> &toPrint){
  os << toPrint.object;
  return os;
}

bool operator<(const Review& one, const Review& two){
	return one.rating < two.rating;	
}
bool operator>(const Review& one, const Review& two){
	return one.rating > two.rating;	
}



template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(this->root == nullptr){
    this->root = new TreeNode<T>(obj);
    this->num_nodes++;
    return;
  }

  TreeNode<T>* cur = this->findInsertionParent();
  if(cur->left == nullptr){ 
    cur->left = new TreeNode<T>(obj);
    cur->left->parent = cur;
    cur = cur->left;
  }
  else if(cur->right == nullptr){
    cur->right = new TreeNode<T>(obj);
    cur->right->parent = cur;
    cur = cur->right;
  }
  else {
    cerr << "\tWARNING: findInsertionParent found a node no nullptr children\n";
    return;
  }

  this->num_nodes++;

  this->bubbleUp(cur);
  return;
}

template<typename T>
T Heap<T>::delMax() {
  // insert your code here
  if(this->root == nullptr) return T();

  const T return_val = this->root->object;
  TreeNode<T>* last_node = this->findElementAt(this->num_nodes);
  swapNodeContent(last_node, this->root);

  if(last_node->parent == nullptr) this->root = nullptr;
  else if(last_node == last_node->parent->left) last_node->parent->left = nullptr;
  else last_node->parent->right = nullptr;

  delete last_node;
  this->num_nodes--;

  this->heapify(this->root);

  return return_val;
}



template<typename T>
TreeNode<T>* Heap<T>::findInsertionParent(){
  int insert_parent_location = ceil( ( (float)this->num_nodes )/2 );
  return this->findElementAt(insert_parent_location);
}
template<typename T>
TreeNode<T>* Heap<T>::findElementAt(int index){
  if(index < 1 || index > this->num_nodes) return nullptr;

  TreeNode<T>* res = this->root;
  int guide=(padBitReverse((index))>>1);

  while(guide > 1){
    if(guide&1) res=res->right;
    else res = res->left;
    guide>>=1;
  }

  return res;
}



template<typename T>
void Heap<T>::bubbleUp(TreeNode<T>* node){
  if(node == nullptr) return;
  if(node->parent == nullptr) return;
  if(*(node->parent) > *node ) return;

  swapNodeContent(node, node->parent);
  this->bubbleUp(node->parent);
}
template<typename T>
void Heap<T>::heapify(TreeNode<T>* node){
  if(node == nullptr) return;
  if(node->left == nullptr) return;
  
  TreeNode<T>* next = node->left;
  T max = next->object;
  if(node->right != nullptr && max < node->right->object){
    next = node->right;
    max = next->object;
  }

  if(!(node->object < max)) return;

  swapNodeContent(node, next);
  this->heapify(next);
}



template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  if(node == nullptr) return;

  this->printHeapMain(node, "");

  return;
}
template<typename T>
void Heap<T>::printHeapMain(TreeNode<T> *node, string pref) {
  if(node == nullptr) return;

  cout << pref;
  bool is_left = false;
  if(node->parent != nullptr) is_left = node->parent->left == node;
  cout << (is_left ? "├──" : "└──") << *node << "\n";

  string new_pref = pref.append(is_left ? "|  ": "   ");
  this->printHeapMain(node->left, new_pref);
  this->printHeapMain(node->right, new_pref);
}



template<typename T>
int Heap<T>::getHeight(){
  TreeNode<T>* cur = this->root;
  int res=-1;

  while(cur != nullptr){
    res++; 
    cur=cur->left;
  }

  return res;
}



template<typename T>
void swapNodeContent(TreeNode<T>* one, TreeNode<T>* two){
  if(one == nullptr || two == nullptr || one==two) return;
  T temp = one->object;
  one->object = two->object;
  two->object = temp;
}

int padBitReverse(int inp){
  int res=1;
  while(inp){
    res<<=1;
    res|=(inp&1);
    inp>>=1;
  }

  return res;
}

//int main(){
//  Heap<int> *heap = new Heap<int>();
//
//  // cout << padBitReverse(6);
//  heap->insert(4);
//  heap->insert(7);
//  heap->insert(9);
//  heap->insert(12);
//  heap->insert(15);
//  heap->insert(20);
//  heap->insert(16);
//
//  heap->delMax();
//
//  heap->printHeap(heap->root);
//
//  cout<<endl;
//} 
