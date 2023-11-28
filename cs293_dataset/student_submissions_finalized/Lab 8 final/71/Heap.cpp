#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<cmath>

template<typename F>
void n_ins(TreeNode<F> *curr, int n, F obj){
  // static int k=0;
  // k++;
  // cout<<"recursion: "<<k<<endl;
  // cout<<"node: "<<n<<endl;
  int hf=int(log2(n+1) -1 );
  if(log2(n+1)==int(log2(n+1))) hf--;
  if(n==2 || n==3){
    TreeNode<F> *n_add= new TreeNode<F>(obj);
    n_add->parent=curr;

    if(n==2) curr->left=n_add;
    else curr->right=n_add;

    curr=n_add;
    bool done=false;
    while(curr->parent!=nullptr && !done){
      if(curr->parent->object < curr->object){
        F temp= curr->object;
        curr->object=curr->parent->object;
        curr->parent->object=temp;
      }
      else done=true;
      curr=curr->parent;
    }
    return;
  }
  if(n>3*pow(2,hf)-1){
    n_ins(curr->right, n-pow(2,hf+1), obj);
  }
  else{
    n_ins(curr->left, n-pow(2,hf), obj);
  }
  
}

template<typename Z>
Z* change(TreeNode<Z> *cur, int n){
  // static int k=0;
  // k++;
  // cout<<"recursion: "<<k<<endl;
  // cout<<"node: "<<n<<endl;
  int hf=int(log2(n+1) -1 );
  if(log2(n+1)==int(log2(n+1))) hf--;
  if(n==2) {
    // cout<<"hi0"<<endl;
    // Z *temp= new Z(cur->left->object.rating, cur->left->object.revId,cur->left->object.rev);
    Z *temp=new Z(cur->left->object);
    // cout<<"hi1"<<endl;
    cur->left=nullptr;
    // cout<<"hi2"<<endl;
    return temp;
  }
  if(n==3) {
    // cout<<"hi3"<<endl;
    // Z *temp=new Z(cur->right->object.rating,cur->right->object.revId,cur->right->object.rev);
    Z *temp=new Z(cur->right->object);
    // cout<<"hi4"<<endl;
    cur->right=nullptr;
    return temp;
  }
  if(n>3*pow(2,hf)-1){
    change(cur->right, n-pow(2,hf+1));
  }
  else{
    change(cur->left, n-pow(2,hf));
  }
} 

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){
    root= new TreeNode<T>(obj);
  }
  else{
    n_ins(root,node+1,obj);
  }

  node++;
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(node==1){
    root=nullptr;
    node--;
    return;
  }
  T *new_obj=change(root,node);
  // cout<<"hi"<<endl;
  root->object=*new_obj;
  TreeNode<T> *cur=root;
  bool done=false;
  while(!done){
    if(cur->left==nullptr && cur->right==nullptr) break;
    else if(cur->left==nullptr && cur->right!=nullptr){
      T temp = cur->right->object;
      if(cur->object < temp){
        cur->right->object=cur->object;
        cur->object=temp;
        cur=cur->right;
      }
      else done=true;
    }
    else if (cur->left!=nullptr && cur->right==nullptr){
      T temp = cur->left->object;
      if(cur->object < temp){
        cur->left->object=cur->object;
        cur->object=temp;
        cur=cur->left;
      }
      else done=true;
    }
    else{
      if(cur->right->object < cur->left->object){
        T temp = cur->left->object;
        if(cur->object < temp){
          cur->left->object=cur->object;
          cur->object=temp;
          cur=cur->left;
        }
        else done=true;
      }
      else{
        T temp = cur->right->object;
        if(cur->object < temp){
          cur->right->object=cur->object;
          cur->object=temp;
          cur=cur->right;
        }
        else done=true;
      }
    }
  }
  node--;
  // cout<<"hi2"<<endl;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  // static int n=0;
  // static string s="";
  // n++;
  // if(node!=nullptr){
  //   cout<<s;
  //   if(n==1) cout<<"|__";
  //   else {
  //     bool isLeft;
  //     if(node->parent->left=node) isLeft=true;
  //     else false;
  //     cout << (isLeft ? "|--" : "|__" );
  //   }
  //   cout<<node->object;
  //   cout<<endl;
  //   int l=s.length();
  //   s=s+"│   ";
  //   printHeap(node->left);
  //   s.erase(s.begin()+l,s.end());
  //   s=s+"    ";
  //   printHeap(node->right);
  //   s.erase(s.begin()+l,s.end());
  // }

  // return;
}

  
