#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <bits/stdc++.h>
template<typename T>
void Heap<T>::printBST(TreeNode<T> *node,const string& prefix, bool isLeft=false)
{
  if(node != nullptr){
    cout << prefix;

    cout << (isLeft ? "|--" : "|__" );

    // print the value of the node
    cout << node->object << endl;
    TreeNode *curr = node;
    node = node->left;
    // enter the next tree level - left and right branch
    printBST( prefix + (isLeft ? "│   " : "    "), true);
    node = curr->right;
    printBST( prefix + (isLeft ? "│   " : "    "), false);
    node = curr;
  }
  return;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){
    root = new TreeNode<T>(obj);
    noOfNodes++;
    return;
  }

  int n = ++noOfNodes;
  vector<int> a;
  while(true){
    if(n!=1){
      a.push_back(n%2);
      n = n/2;
    }
    else{
      break;
    }
  }

  TreeNode<T> *currNode = root;
  for(int i=a.size()-1;i>0;i--){
    if(a[i]==0){
      currNode = currNode->left;
    }
    else{
      currNode = currNode->right;
    }
  }

  if(a[0]==0){
    currNode->left = new TreeNode<T>(obj);
    currNode->left->parent = currNode;
    currNode = currNode->left;
  }
  if(a[0]==1){
    currNode->right = new TreeNode<T>(obj);
    currNode->right->parent = currNode;
    currNode = currNode->right;
  }

  while(currNode->parent!=nullptr){
    if(currNode->parent->object < currNode->object){
      T obj = currNode->object;
      currNode->object = currNode->parent->object;
      currNode->parent->object = obj;
      currNode = currNode->parent;
    }
    else{
      break;
    }
  }


  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root == nullptr){
    return;
  }
  if(root->left == nullptr && root->right == nullptr){
    root = nullptr;
    return;
  }

  int n=noOfNodes;
  vector<int> a;
  while(true){
    if(n!=1){
      a.push_back(n%2);
      n = n/2;
    }
    else{
      break;
    }
  }

  TreeNode<T> *currNode = root;
  for(int i=a.size()-1;i>=0;i--){
    if(a[i]==0){
      currNode = currNode->left;
    }
    else{
      currNode = currNode->right;
    }
  }

  TreeNode<T> *parentofcurrNode = currNode->parent;
  if(a[0] == 0){
    parentofcurrNode->left = nullptr;
  }
  else{
    parentofcurrNode->right = nullptr;
  }

  root->object = currNode->object;
  currNode = root;

  while(true){
    if(currNode->left!=nullptr && currNode->right!=nullptr){
      if(currNode->object < currNode->left->object && currNode->right->object < currNode->left->object){
        T obj = currNode->object;
        currNode->object = currNode->left->object;
        currNode->left->object = obj;
        currNode = currNode->left;
      }
      else if(currNode->object < currNode->right->object && currNode->left->object < currNode->right->object){
        T obj = currNode->object;
        currNode->object = currNode->right->object;
        currNode->right->object = obj;
        currNode = currNode->right;
      }
      else{
        break;
      }
    }

    else if(currNode->left!=nullptr){
      if(currNode->object < currNode->left->object){
        T obj = currNode->object;
        currNode->object = currNode->left->object;
        currNode->left->object = obj;
        currNode = currNode->left;
      }
      else{
        break;
      }
    }

    else if(currNode->right!=nullptr){
      if(currNode->object < currNode->right->object){
        T obj = currNode->object;
        currNode->object = currNode->right->object;
        currNode->right->object = obj;
        currNode = currNode->right;
      }
      else{
        break;
      }
    }

    else{
      break;
    }
  }
  noOfNodes--;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printBST(node,"");

}

  
