#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

int* Binary(int n){
    int i=0;
    int s=n;
    while(n!=0){
      n=n/2;
      i=i+1;
    }
    int *arr = new int[i];
    for(int j=0;j<i;j++){
      arr[j]=s%2;
      s=s/2;
    }
    return arr;
}
//Used this function to convert the given integer as binary representation and stores the binary numbers in an array and returns it.

template<typename T>
TreeNode<T>* find(int n, TreeNode<T>* s){
  int x=n;
  int d=0;
  while(x!=0){
    x=x/2;
    d=d+1;
  }
  int *temp = new int[d];
  int y=n;
  temp=Binary(y);
  int tem[d];
  for(int j=0;j<d;j++){
    tem[j]=temp[d-j-1];
  }
  TreeNode<T>*c=s;
  int g=1;
  int k=1;
  while(k!=d){
    if(tem[g]==1){
      c=c->right;
      g=g+1;
      k=k+1;
    }
    else{
      c=c->left;
      g=g+1;
      k=k+1;
    }
  }
  return c;
}
//This function is used to find the location of the last node present in the heap.

template<typename T>
void Heapify(TreeNode<T>* k){
  if(k->right!=nullptr && k->left!=nullptr){
    if(k->left->object < k->object && k->right->object < k->object){
        Heapify(k->right);
        Heapify(k->left);
    }
    else{
      if(k->left->object<k->right->object){
        T f=k->object;
        k->object=k->right->object;
        k->right->object=f;
        Heapify(k->right);
      }
      else{
        T f=k->object;
        k->object=k->left->object;
        k->left->object=f;
        Heapify(k->left);
      }
    }
  }
  else if(k->right==nullptr && k->left!=nullptr){
      if(k->object<k->left->object){
        T f=k->object;
        k->object=k->left->object;
        k->left->object=f;
        return;
      }
    }
  else{
    return;
  }
}
// This function is used to heapify the present heap at the node location which is provided as the parameter.

template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    root=new TreeNode<T>(obj);
    sz=1;
    return;
  }
  else{
    TreeNode<T>* c=root;
    int b=0;
    int a=sz+1;
    while(a!=0){
      a=a/2;
      b=b+1;
    }
    int *as = new int[b];
    as=Binary(sz+1);
    int sa[b];
    for(int z=0;z<b;z++){
      sa[z]=as[b-1-z];
    }
    // Here I created a new array and stored the reverse order of the original array I got by using Binary function.
    int k=1;
    int l=1;
    while(k!=b-1){
      if(sa[l]==1){
        c=c->right;
        l=l+1;
        k=k+1;
      }
      else{
        c=c->left;
        l=l+1;
        k=k+1;
      }
    }
    // Here I found the location where the new node should be added in the heap
    if(sa[l]==1){
      TreeNode<T>* p=new TreeNode<T>(obj);
      c->right=p;
      c->right->parent=c;
      sz=sz+1;
      int v=1;
      while(v<sz){
        v=v*2;
      }
      v=v/2;
      int k=v-1;
      while(k!=0){
        Heapify(find(k,root));
        k=k-1;
      }
      return;
    }
    else{
      TreeNode<T>* p=new TreeNode<T>(obj);
      c->left=p;
      c->left->parent=c;
      sz=sz+1;
      int v=1;
      while(v<sz){
        v=v*2;
      }
      v=v/2;
      int k=v-1;
      while(k!=0){
        Heapify(find(k,root));
        k=k-1;
      }
      return;
    }
  }
  // insert your code here

  return;
}
// Here I used the idea of binary number concept to find the location of the newly coming node.
  // insert your code here


template<typename T>
void Heap<T>::delMax() {
  int x=sz;
  if(sz==0)return;
  if(sz==1){
    root=nullptr;
    sz--;
    return;
  }
  TreeNode<T>* c=find(x,root);
  root->object=c->object;
  if(c->parent->right==c){
    c->parent->right=nullptr;
  }
  else{
    c->parent->left=nullptr;
  }
  Heapify(root);
  // insert your code here
  sz--;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  {
    static string prefix="";
    static bool n=0;
    if(node == root){prefix="";n=0;}
    if( node != nullptr )
    {
        cout << prefix;

        if(n==1){
        cout << ( "|--");
        }
        if(n==0){
          cout<<("|__");
        }

        // print the value of the node
        cout << node->object << endl;
        bool x = n;
        string mys = prefix;
        prefix=mys+(x ? "│   " : "    ");
        n=1;
        // enter the next tree level - left and right branch
        printHeap(node->left);
        n=0;
        prefix=mys+(x ? "│   " : "    ");
        printHeap(node->right);
    }
}
//Here I used the static concept to keep the prefix and alter it in iterative way
  //  cout << prefix;

  //       cout << (isLeft ? "|--" : "|__" );

  //       // print the value of the node
  //       cout << root->JourneyCode << endl;
  //       TreeNode *curr = root;
  //       root = root->left;
  //       // enter the next tree level - left and right branch
  //       printBST( prefix + (isLeft ? "│   " : "    "), true);
  //       root = curr->right;
  //       printBST( prefix + (isLeft ? "│   " : "    "), false);
  //       root = curr;
  // insert your code here

  return;
}

  
