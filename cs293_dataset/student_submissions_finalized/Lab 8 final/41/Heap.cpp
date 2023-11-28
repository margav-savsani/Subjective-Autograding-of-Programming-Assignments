#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void swap_nodes(TreeNode<T>* &elem_1, TreeNode<T>* &elem_2){
  T obj_1 = elem_1 -> object;
  T obj_2 = elem_2 -> object;
  elem_1 -> object = obj_2;
  elem_2 -> object = obj_1;
}

int* return_array(int number){
  int count = 0, store_number = number;
  while(store_number > 0){
    store_number = store_number / 2;
    count++;
  }
  int* array = new int[count+1];
  for(int i = 0; i < count; i++){
    array[i] = number % 2;
    number = number / 2;
  }
  int start = 0, end = count - 1;
  while (start < end){
    int temp = array[start];
    array[start] = array[end];
    array[end] = temp;
    start++;
    end--;
  }
  array[count] = 2;
  return array;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  total_elements++;
  TreeNode<T> *new_Node = new TreeNode(obj);

  if(root == nullptr){
    root = new_Node;
    return;
  }
  //cout<<"abcd "<<total_elements;
  TreeNode<T> *curr_Node = root;

  int *answer = return_array(total_elements);
  // int binary_count = 0;
  // for(int i = 0; answer[i]!=2; i++) binary_count++;
  int j = 0;
  while(answer[j] != 2) j++;

  int i = 1;
  while(i<j-1){
    if(answer[i] == 0) curr_Node = curr_Node -> left;
    else curr_Node = curr_Node -> right;
    i++;
  }
  if(answer[j-1] == 0){
    curr_Node->left = new_Node;
  }
  else curr_Node->right = new_Node;

  new_Node->parent = curr_Node;

  curr_Node = new_Node;

  while(curr_Node -> parent != nullptr){
    if(curr_Node->parent->object < curr_Node->object){
      swap_nodes(curr_Node, curr_Node->parent);
      curr_Node = curr_Node -> parent;
    }
    else break;
  }
  return;
}

template<typename T>
void Heapify(TreeNode<T> *passed_node){

  if(passed_node == nullptr) return;

  TreeNode<T> *store_left = passed_node->left;
  TreeNode<T> *store_right = passed_node->right;

  if(store_left == nullptr && store_right == nullptr) return;

  if((store_right == nullptr && store_left != nullptr) && (passed_node->object < store_left->object)){
    swap_nodes(passed_node, store_left);
    Heapify(store_left);
    return;
  }

  if((store_right != nullptr && store_left == nullptr) && (passed_node->object < store_right->object)){
    swap_nodes(passed_node, store_right);
    Heapify(store_right);
    return;
  }

  if(store_right != nullptr && store_left != nullptr)
  {
    if((store_left->object < passed_node->object) || (store_right->object < passed_node->object)) return;
    else{
      if(store_left->object < store_right->object){
        swap_nodes(passed_node, store_right);
        Heapify(store_right);
      }
      else{
        swap_nodes(passed_node, store_left);
        Heapify(store_left);
      }
      return;
    }
  }
}

template<typename T>
void Heap<T>::delMax() {

  if(total_elements==0) return;
  if(total_elements == 1){
    root = nullptr;
    total_elements = 0;
    return;
  }

  // insert your code here

  TreeNode<T> *curr_Node = root;

  int *answer = return_array(total_elements);

  int i = 1;
  while(answer[i] != 2){
    if(answer[i] == 0) curr_Node = curr_Node -> left;
    else curr_Node = curr_Node -> right;
    i++;
  }

  swap_nodes(curr_Node, root);

  // curr_Node = curr_Node->parent;

  bool isLeft = (curr_Node->parent->left == curr_Node);
  if(isLeft){
    curr_Node->parent->left = nullptr;
  }
  else curr_Node->parent->right = nullptr;
  delete(curr_Node);

  total_elements -= 1;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printTree("", node, false);
  return;
}

template<typename T>
void printTree(const string& prefix, TreeNode<T> *node, bool isLeft = false){
  if(node != nullptr)
  {
    cout << prefix;
    cout << (isLeft ? "|--" : "|__" );

    // print the value of the node
    // node->print_object();
    cout << node->object << endl;
    TreeNode<T>* curr = node; 
    node = node->left;
    // enter the next tree level - left and right branch
    printTree(prefix + (isLeft ? "│   " : "    "), node, true);
    node = curr->right;
    printTree(prefix + (isLeft ? "│   " : "    "), node, false);
    node = curr;
  }
}