#ifndef STD_hEADERS_h
#include "std_headers.h"
#endif

#ifndef hEAP_h
#include "Heap.h"
#endif




template<typename T>
TreeNode<T> *Heap<T>::lastnodetoinsert(TreeNode<T> *node,TreeNode<T> *prevnode,int x,int y){
  if((node==NULL)&&(x==y)){return prevnode;}
  if(node==NULL || y>x){return NULL;}
  TreeNode<T> *a=lastnodetoinsert(node->left,node,x,y+1);
  if(a!=NULL){return a;}
  TreeNode<T> *b=lastnodetoinsert(node->right,node,x,y+1);
  if(b!=NULL){return b;}
  return NULL;
}
template<typename T>
TreeNode<T> *Heap<T>::lastnode(TreeNode<T> *node,TreeNode<T> *prevnode,int x,int y){
  if(node!= NULL && x==y){return node;}
  if(x==y){return prevnode;}
  //if(node==NULL){return NULL;}
  TreeNode<T> *a=lastnode(node->left,prevnode,x,y+1);
  if(a==prevnode){return a;}
  if(a!=NULL) prevnode=a;
  TreeNode<T> *b=lastnode(node->right,prevnode,x,y+1);
  if(b==prevnode){return b;}
  if(b!=NULL) prevnode=b;
  return prevnode;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *r=root;
  TreeNode<T> *prevnode=NULL;
  TreeNode<T> *toheap;
  int level=0;
  while(r!=NULL){
        level++;
        prevnode=r;
        r=r->left;
        
      }
      
      r=root;
  if(r==NULL){root=new TreeNode<T> (obj);
              toheap=root;
              
              return;
              }
  else{
      
      TreeNode<T> *x=lastnodetoinsert(r,NULL,level-1,0);
      if(x==NULL){
                  prevnode->left=new TreeNode<T> (obj);
                  prevnode->left->parent=prevnode;
                  toheap=prevnode->left;
                  }
      else{
        prevnode=x;
        if(prevnode->left==NULL){ prevnode->left=new TreeNode<T> (obj);
                              prevnode->left->parent=prevnode;
                              toheap=prevnode->left;
                            }
        else if(prevnode->right==NULL){prevnode->right=new TreeNode<T> (obj);
                              prevnode->right->parent=prevnode;
                              toheap=prevnode->right;
                              }
      }
  }
  while(true){
    if(toheap->parent==NULL){break;}
    if(toheap->parent->object<toheap->object){
      T x=toheap->object;
      toheap->object=toheap->parent->object;
      toheap->parent->object=x;
      }
    else break; 
    toheap=toheap->parent;
  }

  return;
}
template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> *r=root;
  TreeNode<T> *prevnode=NULL;
  int level=0;
      while(r!=NULL){
        level++;
        prevnode=r;
        r=r->left;
      }
      r=root;
  if(root->left==NULL && root->right==NULL){root=NULL;return;}
  else{
      
      TreeNode<T> *x=lastnode(r,NULL,level-1,0);
      cout<<x->object<<endl;
      root->object=x->object;
       if(x->parent->right!=NULL){x->parent->right=NULL;}
       else{x->parent->left=NULL;}
       delete(x);
  
  //heapify
  while(true){
    if(((r->right==NULL)&&(r->left==NULL))) break; 
    else if(r->right==NULL){
          if(r->object<r->left->object){
                      T a=r->left->object;
                      r->left->object=r->object;
                      r->object=a;
                      break;}
          else break;
    }
    else{
         if((r->object<r->right->object) || (r->object<r->left->object)){
              if(r->right->object<r->left->object){
                                          T b=r->left->object;
                                          r->left->object=r->object;
                                          r->object=b;
                                          r=r->left;}
              else{
                    T b=r->right->object;
                    r->right->object=r->object;
                    r->object=b;
                    r=r->right;
                    }
        }
        else break;
    }}}
}
  


template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  static string pre = "";
    static bool left = false;
    static int recursion_level = 0;

    recursion_level++;
    if (recursion_level == 1)
    {
        pre = "";
        left = false;
    }

    if (node != nullptr)
    {
        if (left) cout << pre <<"|--" << node->object << "\n";
        else cout << pre << "|__" << node->object << "\n";

        if (left) pre = pre + "|  ";
        else pre = pre + "   ";
        left = true;
        printHeap(node->left);
        left = false;
        printHeap(node->right);
    }
    recursion_level--;

    return;
  
  // insert your code here

  
}
/*template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if(node==nullptr ) return;
  if(node->left!=NULL){
  if(node->object<node->left->object){
    T o=node->object;
    node->object=node->left->object;
    node->left->object=o;
  
  }
  if(node->right!=NULL){
  if(node->object<node->right->object){
    T o=node->object;
    node->object=node->right->object;
    node->left->object=o;
  }
}
}*/
  


  
