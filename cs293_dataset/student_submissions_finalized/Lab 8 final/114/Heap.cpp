#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <string>

template<typename T>
string Heap<T>::getBinary(int totalNodes) {
    
  int q = totalNodes;
  int r = totalNodes;
  string binary = "";

  while (true) {

    if (q == 1 || q == 0) {
      break;
    } else {
      r = q % 2;
      q /= 2;

      binary = to_string(r) + binary;
    }
  }

  return binary;

}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* current = root;
  TreeNode<T>* newNode = new TreeNode(obj);

  totalNodes++;
  string binary = getBinary(totalNodes);

  if (binary == "") {

    root = newNode;
    return;

  } else {

    int i = 0;

    for(; i < binary.length()-1; i++) {
      if (binary[i] == '0') {
        current = current->left;
      } else if (binary[i] == '1') {
        current = current->right;
      }
    }

    if (binary[i] == '0') {
      current->left = newNode;
      newNode->parent = current;
    } else if (binary[i] == '1') {
      current->right = newNode;
      newNode->parent = current;
    }

    while (newNode->parent != nullptr) {
      if (newNode->parent->object < newNode->object) {
        T temp = newNode->object;
        newNode->object = newNode->parent->object;
        newNode->parent->object = temp;
      } else {
        break;
      }
      newNode = newNode->parent;
    }

  }

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T>* current = root;

  if (root == nullptr) {
    return;
  }
  
  string binary = getBinary(totalNodes);

  if (binary == "") {
    delete root;
    root = nullptr;
    totalNodes -= 1;
    return;
  }

  int i = 0;

  for(; i < binary.length()-1; i++) {
    if (binary[i] == '0') {
      current = current->left;
    } else if (binary[i] == '1') {
      current = current->right;
    }
  }


  if (binary[i] == '0') {
    root->object = current->left->object;
    delete current->left;
    current->left = nullptr;
  } else if (binary[i] == '1') {
    root->object = current->right->object;
    delete current->right;
    current->right = nullptr;
  }

  current = root;

  while (current != nullptr) {
    if (current->left != nullptr) {
      if (current->right != nullptr) {
        if (current->left->object < current->object && current->right->object < current->object) {
          break;
        } else if (current->right->object < current->left->object) {
          T temp = current->object;
          current->object = current->left->object;
          current->left->object = temp;
          current = current->left;
        } else {
          T temp = current->object;
          current->object = current->right->object;
          current->right->object = temp;
          current = current->right;
        }
      } else {
        if (current->left->object < current->object) {
          break;
        } else {
          T temp = current->object;
          current->object = current->left->object;
          current->left->object = temp;
          current = current->left;
        }
      }
    } else {
      break;
    }
  }

  totalNodes -= 1;

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node, const string& prefix, bool isLeft) {

  // insert your code here

  if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        TreeNode<T> *curr = node;
        // enter the next tree level - left and right branch
        printHeap(node->left, prefix + (isLeft ? "│   " : "    "), true);
        node = curr;
        printHeap(node->right, prefix + (isLeft ? "│   " : "    "), false);
        node = curr;
    } 

  return;
} 
