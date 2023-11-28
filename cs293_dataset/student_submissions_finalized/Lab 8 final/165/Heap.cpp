#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<bits/stdc++.h>

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){//root case
    root = new TreeNode<T>(obj);
    lastNode = root;
  }
  else if(root->left == nullptr){//left of root
    root->left = new TreeNode<T>(obj);
    lastNode = root->left;
    lastNode->parent = root;
    lastNodeCode.push_back(0);
  }
  else if(root->right == nullptr){//right of root
    root->right = new TreeNode<T>(obj);
    lastNode = root->right;
    lastNode->parent = root;
    lastNodeCode[0] = 1;
  }
  else{
    
    if(lastNode->parent->right == nullptr){//case when lastNode is a left node of parent
      //cout<<"lastNode is the leftNode of parent"<<endl;
      lastNode->parent->right = new TreeNode<T>(obj);
      TreeNode<T>* prevLastNode = lastNode;
      lastNode = lastNode->parent->right;//new lastNode is right of parent
      lastNode->parent = prevLastNode->parent;//parents are same
      lastNodeCode[lastNodeCode.size()-1] = 1;//store binary bit towards right
    }
    else{//present LastNode is the right node of parent
      //cout<<"lastNode is the rightNode of parent"<<endl;
      int i;
      for(i=lastNodeCode.size()-1;i>=0;i--){//adding one bit to current LastNode to get new LastNode
        if(lastNodeCode[i] == 0){
          lastNodeCode[i] = 1;
          break;
        }
        else{
          lastNodeCode[i] = 0;
        }
      }
      if(i==-1){//case when the tree was complete
        //cout<<"Hi"<<endl;
        lastNodeCode.push_back(0);
      }
      TreeNode<T> *curr = root;
      i = 0;
      while(curr->left!= nullptr){//traverse tree with the help of lastNodeCode array
        if(lastNodeCode[i] == 0){
          curr = curr->left;
        }
        else{
          curr = curr->right;
        }
        i++;
      }
      curr->left = new TreeNode<T>(obj);
      lastNode = curr->left;
      lastNode->parent = curr;
      lastNode->parent->left = lastNode;

    }
  }
  TreeNode<T> *curr = lastNode;
  while(curr!=root){//put new inserted object in the correct location while moving upwards
    if(curr->parent->object < curr->object){//if inserted object is greater than its parent, swap
      swap(curr->object , curr->parent->object);
      curr = curr->parent;//move upwards
    }
    else{// if condition doesn't match, heap property satisfied--break
      break;
    }
  }
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {
  //cout<<"here"<<endl;
  // insert your code here
  if(lastNode == root){//base case
    root = nullptr;
    return;
  }
  root->object = lastNode->object;
  //cout<<lastNode->object<<endl;
  
  if(lastNode->parent->right == lastNode){//if lastNode is the rightNode of parent
    
    lastNode = lastNode->parent->left;
    //cout<<lastNode->object<<endl;
    lastNodeCode[lastNodeCode.size() - 1] = 0;
    //cout<<lastNode->parent->right->object<<endl<<endl;
    lastNode->parent->right = nullptr;
  }
  else{//lastNode is the leftNode of parent
    
    int i;
    
    for(i = lastNodeCode.size()-1;i>=0;i--){//subtraction of a bit from lastNodeCode
      if(lastNodeCode[i] == 1){
        lastNodeCode[i] = 0;
        break;
      }
      else{
        lastNodeCode[i] = 1;
      }
    }
    if(i==-1){//case when leftmostNode is getting deleted
      lastNodeCode.pop_back();
    }
    lastNode->parent->left = nullptr;
    TreeNode<T>* curr = root;
    i=0;
    while(curr->right != nullptr){//if right is not nullptr , left cannot be left pointer by structural property of heap
      if(lastNodeCode[i] == 0){
        curr = curr->left;
      }
      else{
        curr = curr->right;
      }
      i++;

    }
    lastNode = curr;//traverse with help of lastNodeCode array to find the LastNode
    //cout<<lastNode->object<<endl;
  }
  Heapify(root);
  //cout<<lastNode->object<<endl;
  //printHeap(root);
  return ;
}
template<typename T>
void Heap<T>::Heapify(TreeNode<T>* root){

  TreeNode<T> *curr = root;
  if(curr->left == nullptr)//if no left node exists then right node also doesn't exist --  we have rached a leaf--return
    return;
  else if(curr->right == nullptr){// if only right node is null, apply heapify on only the left node
    if(curr->object < curr->left->object){
      swap(curr->object , curr->left->object);
    }
    return;
  }
  //both left and right child of the curr node exist
  if(curr->object < curr->left->object && curr->object < curr->right->object){//if both are less , see which is greater and swap
    if(curr->right->object < curr->left->object){
      swap(curr->object , curr->left->object);
    }
    else{
      swap(curr->object , curr->right->object);
    }
  }
  else if(curr->object < curr->left->object){//only left is greater--no checking reqd just swap
    swap(curr->object , curr->left->object);
  }
  else if(curr->object < curr->right->object){//only right is greater--no checking reqd just swap
    swap(curr->object , curr->right->object);
  }
  else{
    return;
  }
  Heapify(root->left);//recursively call heapify on the left and right nodes
  Heapify(root->right);
  return;

}
template<typename T>
void Heap<T>::recursiveDelete(TreeNode<T>* root){

  recursiveDelete(root->left);
  recursiveDelete(root->right);
  delete root;

}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  // static const string& prefix = "";
  // static bool isLeft = false;
  // if( root != nullptr )
  // {
  //       cout << prefix;

  //       cout << (isLeft ? "|--" : "|__" );

  //       // print the value of the node
  //       cout << root->JourneyCode << endl;
  //       TreeNode<T> *curr = root;
  //       root = root->left;
  //       // enter the next tree level - left and right branch
  //       printBST( prefix + (isLeft ? "│   " : "    "), true);
  //       root = curr->right;
  //       printBST( prefix + (isLeft ? "│   " : "    "), false);
  //       root = curr;
  // }
  helper("",false);
  return;
}

template<typename T>
void Heap<T>::helper(const string& prefix, bool isLeft) { 

    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        helper( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        helper( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
