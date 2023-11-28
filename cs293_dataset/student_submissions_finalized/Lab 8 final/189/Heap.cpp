#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void Heap<T>:: heapify(TreeNode<T> * Node){
  if(Node==nullptr){
    return;
  }
  else if(Node->left==nullptr&&Node->right==nullptr){
    return;
  }
  else if(Node->left!=nullptr&&Node->right==nullptr){
    if(Node->object<Node->left->object){
      // TreeNode<T> * tempNode=Node;
      // TreeNode<T> * tempNodeLeft=Node->left;
      // Node->object=tempNodeLeft->object;
      // Node->left=tempNodeLeft->left;
      // Node->right=tempNodeLeft->right;
      // Node->parent=tempNode;
      // tempNode->left=Node;
      // heapify(Node);
      T tempObject;
      tempObject=Node->object;
      Node->object=Node->left->object;
      Node->left->object=tempObject;
      heapify(Node->left);
      
    } 
  }
  else if(Node->left!=nullptr&&Node->right!=nullptr){
    if(Node->object<Node->left->object||Node->object<Node->right->object){
      if(Node->left->object<Node->right->object){
        // TreeNode<T> * tempNode=Node;
        // TreeNode<T> * tempNodeLeft=Node->left;
        // Node->object=tempNodeLeft->object;
        // Node->left=tempNodeLeft->left;
        // Node->right=tempNodeLeft->right;
        // Node->parent=tempNode;
        // tempNode->left=Node;
        // heapify(Node);
        T tempObject;
        tempObject=Node->object;
        Node->object=Node->left->object;
        Node->left->object=tempObject;
        heapify(Node->left);
      }
      else{
        // TreeNode<T> * tempNode=Node;
        // TreeNode<T> * tempNodeRight=Node->right;
        // Node->object=tempNodeRight->object;
        // Node->left=tempNodeRight->left;
        // Node->right=tempNodeRight->right;
        // Node->parent=tempNode;
        // tempNode->right=Node;
        // heapify(Node);
        T tempObject;
        tempObject=Node->object;
        Node->object=Node->right->object;
        Node->right->object=tempObject;
        heapify(Node->right);
      }
    }
  }
}

template<typename T>
int Heap<T>::leftHeight(TreeNode<T>* Node){
    int h=0;
    while(Node){
        h++;
        Node=Node->left;
    }
    return h;
}

template<typename T>
int Heap<T>::rightHeight(TreeNode<T>* Node){
    int h=0;
    while(Node){
        h++;
        Node=Node->right;
    }
    return h;
}

template<typename T>
bool Heap<T>::isComplete(TreeNode<T> * Node){
  if(leftHeight(Node)==rightHeight(Node)) return true;
  else return false;
}

template<typename T>
TreeNode<T>* Heap<T> ::getRightmostNodeOfLastLevel(TreeNode<T>* Node){
  int h= leftHeight(Node);
   
    if(h==1){
        return Node;
    }
       
    else if((h-1) == leftHeight(Node->right)){
        return getRightmostNodeOfLastLevel(Node->right);
    }
       
    else getRightmostNodeOfLastLevel(Node->left);
}

template<typename T>
void Heap<T>::switching(TreeNode<T> * Node){
  if(Node==nullptr) return;
  if(Node->parent==nullptr) return;
  
  T tempObject;
  tempObject=Node->object;
  Node->object=Node->parent->object;
  Node->parent->object=tempObject;
  switching(Node->parent);
  
  
}

template<typename T>
void Heap<T>::Insert(T obj,TreeNode<T> *Node){
  // if(Node==nullptr){
  //   Node->object=obj;
  //   Node->left=nullptr;
  //   Node->right=nullptr;
  //   Node->parent=nullptr;
  // }
  // else if(Node->left==nullptr&&Node->right==nullptr){
  //   Node->left->object=obj;
  //   Node->left->left=nullptr;
  //   Node->left->right=nullptr;
  //   Node->left->parent=Node;
  // }
  // else if(Node->left!=nullptr&&Node->right=nullptr){
  //   Node->right->object=obj;
  //   Node->right->left=nullptr;
  //   Node->right->right=nullptr;
  //   Node->right->parent=Node;
  // }
  // else if(Node->left!=nullptr&&Node->right!=nullptr){

  // }
  // if(Node==nullptr){
  //   Node->object=obj;
  //   Node->left=nullptr;
  //   Node->right=nullptr;
  //   Node->parent=nullptr;
  //  }
  // TreeNode<T> *rightMostNodeOfLastLevel=getRightmostNodeOfLastLevel(Node);
  // if(isLeftChild(rightMostNodeOfLastLevel)){
  //   rightMostNodeOfLastLevel->parent->right->object=obj;
  //   rightMostNodeOfLastLevel->parent->right->left=nullptr;
  //   rightMostNodeOfLastLevel->parent->right->right=nullptr;
  //   rightMostNodeOfLastLevel->parent->right->parent=rightMostNodeOfLastLevel->parent;
  // }
  // else{}
  if(Node==nullptr){
    Node->object=obj;
    Node->left=nullptr;
    Node->right=nullptr;
    Node->parent=nullptr;
    return;
  }
  if(Node->left!=nullptr&&Node->right==nullptr){
    Node->right->object=obj;
    Node->right->left=nullptr;
    Node->right->right=nullptr;
    Node->right->parent=Node;
    switching(getRightmostNodeOfLastLevel(root));
    return;
  }
  if(isComplete(Node->left)){
    if(isComplete(Node->right)){
      while(Node->left!=nullptr){
        Node=Node->left;
      }
      Node->left->object=obj;
      Node->left->left=nullptr;
      Node->left->right=nullptr;
      Node->left->parent=Node;
      switching(getRightmostNodeOfLastLevel(root));

    }
    else{
      Insert(Node->right);
    }
  }
  else{
    Insert(Node->left);
  }
    
    
  
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  // if(root==nullptr){
  //   root->object=obj;
  //   root->left=nullptr;
  //   root->right=nullptr;
  //   root->parent=nullptr;
  //   return;
  // }
  // else if(root->left==nullptr&&root->right==nullptr){
  //   root->left->object=obj;
  //   root->left->parent=root;
  //   return;
  // }
  // TreeNode<T> *rightMostNodeOfLastLevel=getRightmostNodeOfLastLevel(root);
  // if(isLeftChild(rightMostNodeOfLastLevel)){
  //   rightMostNodeOfLastLevel->parent->right->object=obj;
  //   rightMostNodeOfLastLevel->parent->right->left=nullptr;
  //   rightMostNodeOfLastLevel->parent->right->right=nullptr;
  //   rightMostNodeOfLastLevel->parent->right->parent=rightMostNodeOfLastLevel->parent;
  // }
  
  Insert(obj,root);
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  TreeNode<T> *prevRoot;
  prevRoot=root;
  TreeNode<T> *rightMostNodeOfLastLevel;
  rightMostNodeOfLastLevel=getRightmostNodeOfLastLevel(root);
  root->object=rightMostNodeOfLastLevel->object;
  if(isLeftChild(rightMostNodeOfLastLevel)){
    rightMostNodeOfLastLevel->parent->left=nullptr;
  }
  else{
    rightMostNodeOfLastLevel->parent->right=nullptr;
  }
  heapify(root);
  return prevRoot->object;
}

template<typename T>
void Heap<T>::printHeap1(TreeNode<T> *root,const string& prefix,bool isLeft){
  
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap1( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap1( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }

}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printHeap1(node,"",false);
}

  
