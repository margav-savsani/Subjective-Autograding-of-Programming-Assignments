#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <algorithm>
#include <string>

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
string Heap<T>:: convert(int a){//converts the int to binary representation and removes leading digits from the string
  int x=a;
  string s="";
  while(x!=0){
    if(x%2==1){
      string s1="1";
      s+=s1;
    }
    else{
      s+="0";
    }
    x=x/2;
  }
  reverse(s.begin(),s.end());//reverses string
  s.erase(s.begin());// erases first character
  return s;
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(num==0){// when  number of nodes is zero
    root=new TreeNode(obj);
    num++;
    return;
  }
  else{ // when number of nodes is greater  than zero
    TreeNode<T> *currNode=root;
    string s=convert(num+1);
    while(s.length()!=1){//traverses to reach node's parent
      if(s[0]=='1'){
        currNode=currNode->right;
        s.erase(s.begin());
      }
      else{
        currNode=currNode->left;
        s.erase(s.begin());
      }
    }
    if(s=="1"){//if right node
      TreeNode<T> *t=new TreeNode<T>(obj);
      currNode->right=t;
      currNode->right->parent=currNode;
      currNode=currNode->right;
      num++;
    }
    else{//if left node
      TreeNode<T> *t=new TreeNode<T>(obj);
      currNode->left=t;
      currNode->left->parent=currNode;
      currNode=currNode->left;
      num++;
    }
    while(currNode->parent!=nullptr){//Heapify step
      if(currNode->parent->object<currNode->object){
        T obj=currNode->parent->object;
        currNode->parent->object=currNode->object;
        currNode->object=obj;
        currNode=currNode->parent;
      }
      else{
        break;
      }
    }
    //Heapify step
    return ;
  }
}

template<typename T>
void Heap<T>::delMax(){
  // insert your code here
  if(num==0){return;}// if no node is present
  if(num==1){// when only root is present
    root=nullptr;
    num-=1;
    return;
  }
  else{// when number of nodes is greater  than zero
    TreeNode<T> *currNode=root;
    string s=convert(num);
    while(s.length()!=1){
      if(s[0]=='1'){
        currNode=currNode->right;
        s.erase(s.begin());
      }
      else{
        currNode=currNode->left;
        s.erase(s.begin());
      }
    }
    if(s=="0"){//if left node
      T obj2 = currNode->left->object;
      root->object=obj2;
      currNode->left=nullptr;
      num--;
    }
    else{// if right node
      T obj2 = currNode->right->object;
      root->object=obj2;
      currNode->right=nullptr;
      num--;
    }
    currNode = root;
    //Heapify step
    while(true){// Heapify step
      if(currNode->left==nullptr && currNode->right==nullptr ){break;}//Null if left is nullptr and right is nullptr
      if(currNode->right==nullptr){// if right is nullptr and left is not nullptr
        if(currNode->object<currNode->left->object){
          T obj2 = currNode->left->object;
          currNode->left->object=currNode->object;
          currNode->object=obj2;
          break;
        }
        break;
      }
      if(currNode->left->object<currNode->object && currNode->right->object<currNode->object){//already if it satisfies Heap Condition
        break;
      }
      if(currNode->right->object<currNode->left->object){// if left is max then swap left with current node
        T obj=currNode->object;
        currNode->object=currNode->left->object;
        currNode->left->object=obj;
        currNode=currNode->left;
        continue;
      }
      else{//if right is max then swap right with current node
        T obj=currNode->object;
        currNode->object=currNode->right->object;
        currNode->right->object=obj;
        currNode=currNode->right;
        continue;
      }
    }
  return;
}}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printHeapTree(node,"",false);//Calls printHeapTree
  return;
}

template<typename T>
void printHeapTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {//Same code from previous lab
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout <<root->object<< endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  return;
}


