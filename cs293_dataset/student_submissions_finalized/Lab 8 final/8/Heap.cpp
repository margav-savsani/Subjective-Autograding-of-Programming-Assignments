#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<cmath> 


template<typename T>
TreeNode<T>* Heap<T>::findInsertionParent(){
  return find_node((total_nodes+1)>>1);
}

template<typename T>
void Heap<T>::bubble_up(TreeNode<T>* node){
  if (node == root)
  {
    return;
  }
  
  TreeNode<T>* ptr = node;
  while (ptr -> parent-> object < ptr-> object )
  {
    switch_nodes(ptr, ptr-> parent);
    ptr = ptr -> parent;
    if (ptr == root) break;
  }
  
}

template<typename T>
void Heap<T>::insert(T obj) {
  if (!total_nodes)
  {
    root = new TreeNode<T>(obj);
    total_nodes++;
    return;
  }


  TreeNode<T>* f_node = findInsertionParent();

  TreeNode<T>* temp = new TreeNode<T>(obj);
  temp -> parent = f_node; 
  if (f_node -> left == nullptr)
  {
   f_node -> left = temp; 
  }
  else{
    f_node -> right = temp;
  }

  bubble_up(temp);

  total_nodes++;

}

int countBits(int n){
  int count = 0;
  while(n){count++;n>>=1;}

  return count;
}

template<typename T>
TreeNode<T>* Heap<T>::find_node(int n)
{
  TreeNode<T>* ptr = root;
  int total_bits = countBits(n);
  for (int i = 1; i < total_bits; i++)
  {
    if (((n>>(total_bits-i -1)) & 1))
    {
      ptr = ptr -> right;
    }

    else{
      ptr = ptr -> left;
    }
  }


  return ptr;
  
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node){
  if (node -> right == nullptr &&  node -> left == nullptr)
  {
    return; 
  }

  if (node -> right == nullptr)
  {
    if (node -> object < node -> left -> object)
    {
      switch_nodes(node, node -> left);
    }
    return;
  }
      
  TreeNode<T>* max_node;
  if (node -> object < node -> left -> object  )
  {
    max_node = node -> left;
  }
  else if(node -> object < node -> right -> object) {
    max_node = node -> right;
  }

  else{
    return;
  }
  
  switch_nodes(node, max_node);
  heapify(max_node);
}

template<typename T>
void Heap<T>::switch_nodes(TreeNode<T>* node1, TreeNode<T>* node2){
  
  T node1_obj = node1 -> object;
  node1-> object = node2 -> object;
  node2 -> object = node1_obj;
  return;
}


template<typename T>
void delete_leaf(TreeNode<T> * node){
  if (node -> parent -> left == node)
  {
    node -> parent -> left = nullptr;
  }
  else{
    node -> parent -> right = nullptr;
  }
  
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T>* r_node = find_node(total_nodes);
  switch_nodes(root, r_node);
  delete_leaf(r_node);
  total_nodes--;
  
  heapify(root);

}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node,string prefix, bool isLeft) {
  if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object.rating<< endl;
        TreeNode<T> *curr = node;
        // enter the next tree level - left and right branch
        printHeap( node -> left,prefix + (isLeft ? "│   " : "    "), true);
        //curr -> printNode();
        printHeap( node-> right,prefix + (isLeft ? "│   " : "    "), false);
        node = curr;
    }

  return;
}


  
