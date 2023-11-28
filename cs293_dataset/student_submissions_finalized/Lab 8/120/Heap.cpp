#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"

template<typename T>
string Heap<T>:: convert(int a){
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
  reverse(s.begin(),s.end());
  s.erase(s.begin());
  return s;
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(num==0){
    root=new TreeNode(obj);
    num++;
    return;
  }
  else{
    TreeNode currNode=root;
    string s=convert(num);
    while(s.length()!=1){
      if(s[0]=="1"){
        currNode=currNode.right();
        s.erase(s.begin());
      }
      else{
        currNode=currNode.left();
        s.erase(s.begin());
      }
    }
    if(s=="1"){
      TreeNode t=new TreeNode(obj);
      currNode.right=t;
      currNode.right.parent=currNode;
      num++;
    }
    else{
      TreeNode t=new TreeNode(obj);
      currNode.left=t;
      currNode.left.parent=currNode;
      num++;
    }
  }
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

#endif

