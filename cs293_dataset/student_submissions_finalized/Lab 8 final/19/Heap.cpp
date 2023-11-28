#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  if(count == 0){
    root = new TreeNode<T>(obj);
    count ++;
    return;
  }

  TreeNode<T> *a;
  a = root;
  count ++;
  int binary[64];
  int i = 0;

  int size = count;
  while(size > 0){
    binary[i] = size % 2;
    size = size / 2;
    i++;
  }

  // used binary representation to get the last node.
  for (int j = i -2; j >= 0; j--){
    if(binary[j] == 0 && j != 0){
      a = a->left; // going to left if 0
    }
    else if(binary[j] == 1 && j != 0){
      a = a->right; // going to right if 1
    }
    else if(j == 0 && binary[j] == 0){
      a->left = new TreeNode<T>(obj);
      a->left->parent = a;
      a = a->left; // final reached created a new TreeNode to left
    }
    else if(j == 0 && binary[j] == 1){
      a->right = new TreeNode<T>(obj);
      a->right->parent = a;
      a = a->right; // final reached created a new TreeNode to Right
    }
  }

  while(a != root){
    if(a->parent->object < a->object){
      swap(a->object, a->parent->object);
      a =  a->parent;  // recursively swapping the elements to get max heap
    }
    else{
      break;
    }
  }
  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  TreeNode<T> *l;
  TreeNode<T> *r;
  TreeNode<T> *s;

  l = node->left;
  r = node->right;
  s = node;
  if(s  == nullptr){
    return;
  }

  if(l == nullptr && r == nullptr){
    return;  // if both are null return
  }

  else if(r == nullptr){
    if(s->object < l->object){
      swap(s->object, l->object);
      return;  // if r == null then check with left child and swap if needed
    }
    return;
  }

  else if(l->object < s->object &&  r->object < s->object){
    return; // if node->object is more than both of left and right return 
  }

  else{
    if(l->object < r->object){
      swap(r->object, s->object);
      heapify(r);
      return;  // swapping right child with node and heapify
    }
    else{
      swap(l->object, s->object);
      heapify(l);
      return;  // swapping left child with node and heapify
    }
  }
}


template<typename T>
void Heap<T>::delMax() {

  TreeNode<T> *a;
  a = root;

  int binary[64];
  int i = 0;

  if(count == 1){
    root = nullptr;
    count --;
    return;
  }
  int size = count;
  while(size > 0){
    binary[i] = size % 2;
    size = size / 2;
    i++;
  }  // converted count into binary form to get the last element

  for (int j = i -2; j >= 0; j--){
    if(binary[j] == 0){
      a = a->left;
    }
    else{
      a = a->right;
    }
  } // got the pointer of last element
  

  swap(a->object, root->object);
  if(a->parent->left == a){
    a->parent->left = nullptr;
    delete(a);
    count --;
    heapify(root);  // we will swap the last and root delete the last and call heapify
    return;
  }
  else if(a->parent->right == a){
    a->parent->right = nullptr;
    delete(a);
    count --;
    heapify(root);  // we will swap the last and root delete the last and call heapify
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  printHeap_recursive(node,"", false);

  return;
}

template<typename T>
void printHeap_recursive(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )  {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << (root->object);
    cout << endl;
    TreeNode<T>*curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeap_recursive(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeap_recursive(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}
  
