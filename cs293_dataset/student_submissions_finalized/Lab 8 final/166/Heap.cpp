#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
string dec(int x)
{
  string re="";
  while(x>1)
  {
    if (x%2==0)
    {
      re.append("0");    
    }
    else
    {
      re.append("1");
    }
    x=x/2;
  }
  return re;
}

template<typename T>
void Heapone(TreeNode<T> *see1){
  while(see1->parent != nullptr){
    if(see1->parent->object<see1->object){
    T xex = see1->object;
    see1->object=see1->parent->object;
    see1->parent->object=xex;
    }
    see1=see1->parent;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    TreeNode<T> *temp;
    temp= new TreeNode<T>(obj);
    root=temp;
  }
  else{
    TreeNode<T> *curr;
    curr = root;
    string x=dec<T>(n+1);
    int l=x.length();
    TreeNode<T> *temp;
    temp= new TreeNode<T>(obj);
    if(n==1){
      curr->left = temp;
      curr->left->parent=curr;
      Heapone(curr->left);
    }
    else if(n==2){
      curr->right = temp;
      curr->right->parent=curr;
      Heapone(curr->right);
    }
    else if(n==3){
      curr->left->left=temp;
      curr->left->left->parent=curr->left;
      Heapone(curr->left->left);
    }
    else{
      for(int i=l-1;i>0;i--){
        if(x[i] == '1'){
          curr=curr->right;
        }
        else {curr=curr->left;}
      }


      if(x[0] == '0'){
        curr->left=temp;
        curr->left->parent=curr;
        Heapone(curr->left);
      }
      else{
        curr->right=temp;
        curr->right->parent=curr;
        Heapone(curr->right);
      }
    
  }
}
n=n+1;
  printHeap(root);
  return;
  }

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void printer(const string& prefix,TreeNode<T> *node,bool isLeft) {
  if(node!=nullptr){
    cout<<prefix;

    cout<< (isLeft ? "|--" : "|__");

    cout<<node->object<<endl;
    TreeNode<T> *curr = node;
    node=node->left;
    printer(prefix + (isLeft ? "|  " : "   "),node,true);
    node=curr->right;
    printer(prefix + (isLeft ? "|  " : "   "),node,false);
    node=curr;
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
    printer("",root,false);
  }

  
