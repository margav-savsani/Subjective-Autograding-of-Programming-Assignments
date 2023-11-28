#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include<cmath>

template<typename T>
void Heap<T>::insert(T obj) {
  if (root == nullptr){
    count++;
    root = new TreeNode<T>(obj);
    return;
  }
  if (root != nullptr){
    count++;
    int size = log2(count)+1, *array, a = count, i=size-1;
    array = new int[size];
    while(a!=0){
      array[i]=a%2;
      a=a/2;
      i--;
    }
    TreeNode<T> *currNode = root, *parNode; 
    bool lastj;
    for (int j=1; j<size; j++){
      if(array[j]==0){
        lastj = false;
        parNode = currNode;
        currNode = currNode->left;
      }
      else if(array[j]==1){
        lastj = true;
        parNode = currNode;
        currNode = currNode->right;
      }
    }
    if (lastj){
      currNode = new TreeNode<T>(obj);
      parNode->right = currNode;
      currNode->parent = parNode;
    }
    else if (!lastj){
      currNode = new TreeNode<T>(obj);
      parNode->left = currNode;
      currNode->parent = parNode;
    } 
  }
  return;
}

template<typename T>
void Heap<T>::Heapify(){
  int size = log2(count)+1, *array, a = count, i=0;
  array = new int[size];
  while(a!=0){
    array[i]=a%2;
    a=a/2;
    i++;
  }
  TreeNode<T> *currNode = root;
  for (int j=1; j<size; j++){
      if(array[j]==0){
        currNode = currNode->left;
      }
      if(array[j]==1){
        currNode = currNode->right;
      }
    }
  while (currNode->parent != nullptr){
    if((currNode->object) > ((currNode->parent)->object)){
      if ((currNode->parent)->left == currNode){
        TreeNode<T> *childl = currNode->left, *childr = currNode->right, *parNode = currNode->parent, *T1 = (currNode->parent)->right, *grandParentNode = (currNode->parent)->parent;       
        bool gpisNull = false, isLeft=false;
        if (grandParentNode == nullptr) { gpisNull = true; }
        else { if (grandParentNode->left == currNode->parent){ isLeft = true; } }
        currNode->parent = nullptr;
        parNode->right = currNode->right;
        parNode->left = currNode->left;
        currNode->left = parNode;
        currNode->right = T1;
        parNode->parent = currNode;
        if(!gpisNull){
          if(isLeft){
            grandParentNode->left = currNode;
            currNode->parent = grandParentNode;
          }
          else {
            grandParentNode->right = currNode;
            currNode->parent = grandParentNode;
          }
        }
      }
      else if ((currNode->parent)->right == currNode){
        TreeNode<T> *childl = currNode->left, *childr = currNode->right, *parNode = currNode->parent, *T1 = (currNode->parent)->left, *grandParentNode = (currNode->parent)->parent;
        bool gpisNull = false, isLeft = false;
        if ( grandParentNode == nullptr){ gpisNull = true; }
        else { if (grandParentNode->left == currNode->parent) { isLeft = true; } }
        currNode->parent = nullptr;
        parNode->right = currNode->right;
        parNode->left = currNode->left;
        currNode->right = parNode;
        currNode->left = T1;
        parNode->parent = currNode;
        if(!gpisNull){
          if(isLeft){
            grandParentNode->left = currNode;
            currNode->parent = grandParentNode;
          }
          else {
            grandParentNode->right = currNode;
            currNode->parent = grandParentNode;
          }
        }
      }
    }
    else { break; }
  }
  return;
}

template<typename T>
void Heap<T>::del(TreeNode<T> *Node){
  
  if (Node == nullptr){ return; }
  else {
    TreeNode<T> *leftChild = Node->left, *rightChild = Node->right;
    if (Node->parent == nullptr){
      TreeNode<T> *leftChild = Node->left, *rightChild = Node->right;
      if(rightChild == nullptr && leftChild == nullptr){
        Node = nullptr;
      }
      else if(rightChild == nullptr || leftChild == nullptr){
        if (rightChild == nullptr){
            Node = leftChild;
        }
        else {
            Node = rightChild;
        }
      }
      else {
        if (rightChild->object < leftChild->object){
          TreeNode<T> *T1 = leftChild;
          del(leftChild);
          T1->parent = nullptr;
          T1->right = rightChild;
          T1->left = leftChild;
          Node = T1;
        }
        if (leftChild->object < rightChild->object){
          TreeNode<T> *T1 = rightChild;
          del(rightChild);
          T1->parent = nullptr;
          T1->right = rightChild;
          T1->left = leftChild;
          Node = T1;
        }
      }
    }
    else {
      TreeNode<T> *ParentNode = Node->parent, *leftChild = Node->left, *rightChild = Node->right;
      bool isLeft = false;
      if (ParentNode->left == Node){ isLeft = true; }
      if(rightChild == nullptr && leftChild == nullptr){
        if (isLeft){
          ParentNode->left = nullptr;
        }
        else { ParentNode->right = nullptr; }
        Node = nullptr;
      }
      else if(rightChild == nullptr || leftChild == nullptr){
        if (rightChild == nullptr){
          if(isLeft){
            ParentNode->left = leftChild;
            leftChild->parent = ParentNode;
            Node = leftChild;
          }
          else {
            ParentNode->right = rightChild;
            rightChild->parent = ParentNode;
            Node = rightChild;
          }
        }
      }
      else {
        if (rightChild->object < leftChild->object){
          TreeNode<T> *T1 = leftChild;
          del(leftChild);
          T1->parent = ParentNode;
          if(isLeft) { ParentNode->left = T1; }
          else {ParentNode->right = T1; } 
          T1->right = rightChild;
          T1->left = leftChild;
          Node = T1;
        }
        else if (leftChild->object < rightChild->object){
          TreeNode<T> *T1 = rightChild;
          del(rightChild);
          T1->parent = ParentNode;
          if(isLeft) { ParentNode->left = T1; }
          else {ParentNode->right = T1; } 
          T1->right = rightChild;
          T1->left = leftChild;
          Node = T1;
        }
      }
    }
  }
}

  template<typename T>
  void Heap<T>::delMax() {
//     if (root == nullptr){
//       return;
//     }
//     TreeNode<T> *leftChild = root->left, *rightChild = root->right;
//     if(rightChild==nullptr && leftChild==nullptr){
//       root = nullptr;
//       return;
//     }
//     else if(rightChild==nullptr || leftChild==nullptr){
//       if (leftChild == nullptr){
//         root = rightChild;
//         return;
//       }
//       else if (rightChild == nullptr){
//         root = leftChild;
//         return;
//       }
//     }
//     else {
//       if (rightChild->object < leftChild->object){
//         TreeNode<T> *T1 = leftChild;
//         leftChild->del();
//         T1->right = rightChild;
//         T1->left = leftChild;
//         root = T1;
//       }
//       if (leftChild->object < rightChild->object){
//         TreeNode<T> *T1 = rightChild;
//         rightChild->del();
//         T1->right = rightChild;
//         T1->left = leftChild;
//         root = T1;
//       }
// //     }
    del(root);
    // insert your code here

    return;
  }

template<typename T>
void Heap<T>::print(TreeNode<T> *Node, const string& prefix, bool isLeft){
    if (Node != nullptr){
      cout << prefix;
      cout << (isLeft ? "|--" : "|__");
      cout << Node->object<< endl;
      TreeNode<T> *curr = Node;
      Node = Node->left;
      print(Node, prefix + (isLeft ? "|   " : "    "), true);
      Node = Node->right;
      print(Node, prefix + (isLeft ? "|   " : "    "), false);
      Node = curr;
    }
    else if (Node == nullptr){
      cout << "NULL tree";
    }
  }


template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  print(node, "", false);
  return;
}

  
