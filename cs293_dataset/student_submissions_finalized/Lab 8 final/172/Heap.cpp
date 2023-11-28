
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

static int i=0;
  static string prefix="";
  static bool isLeft=false;
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* newNode=new TreeNode<T>(obj);
  if(root==nullptr) {
    root=new TreeNode<T>(obj);
    lastNode=root;
    num_of_nodes++;
  }
  else{
    TreeNode<T>* last=lastNode;
    TreeNode<T>* last_par=lastNode->parent;
    if(last_par==nullptr){
        lastNode->left=newNode;
        newNode->parent=root;
        lastNode=newNode;
        num_of_nodes++;
    }
    else{
        int found_place=0;
        while(last_par!=nullptr){
            if(last_par->left==last){
                if(last_par->right==nullptr){
                    last_par->right=newNode;
                    newNode->parent=last_par;
                    lastNode=newNode;
                    found_place=1;
                    num_of_nodes++;
                    break;
                }
                else{
                    TreeNode<T>* left_most=last_par->right;
                    while(left_most->left!=nullptr){
                        left_most=left_most->left;
                    }
                    left_most->left=newNode;
                    newNode->parent=left_most;
                    lastNode=newNode;
                    found_place=1;
                    num_of_nodes++;
                    break;
                }
            }
            else{
                last=last_par;
                last_par=last_par->parent;
            }
        }
        if(found_place!=1){
            TreeNode<T>* left_most=root;
            while(left_most->left!=nullptr){
                left_most=left_most->left;
            }
            left_most->left=newNode;
            newNode->parent=left_most;
            lastNode=newNode;
            num_of_nodes++;
        }
    }
  }
  TreeNode<T>* last=lastNode;
  TreeNode<T>* last_par=newNode->parent;
  while(last_par!=nullptr){
    if(last_par->object<last->object){
      T obj=last_par->object;
      last_par->object=last->object;
      last->object=obj;
    }
    else{break;}
    last=last_par;
    last_par=last_par->parent;
  }
  return;
}

template<typename T>
T Heap<T>::delMax(){
  T b;
  if(root==nullptr) return b;
  T a=root->object;
  root->object=lastNode->object;
  if(lastNode->parent->left==lastNode){
    lastNode->parent->left=nullptr;
    TreeNode<T>* last_par=lastNode->parent;
    int found=0;
    while(last_par->parent!=nullptr){
       if(last_par->parent->right==last_par){
          found=1;
          TreeNode<T>* right_most=last_par->parent->left;
          while(right_most->right!=nullptr){
            right_most=right_most->right;
          }
          lastNode=right_most;
       }
       last_par=last_par->parent;
    }
    if(found==0){
       TreeNode<T>* right_most=root;
       while(right_most->right!=nullptr){
        right_most=right_most->right;
       }
       lastNode=right_most;
    }
  }
  else{
    lastNode->parent->right=nullptr;
    lastNode=lastNode->parent->left;
  }
  TreeNode<T>* abs_root=root;
  while(abs_root!=nullptr){
    if(abs_root->left!=nullptr && abs_root->right!=nullptr){
      if(abs_root->object<abs_root->left->object || abs_root->object<abs_root->right->object){
        if(abs_root->right->object<abs_root->left->object){
          T obj=abs_root->object;
          abs_root->object=abs_root->left->object;
          abs_root->left->object=obj;
          abs_root=abs_root->left;
        }
        else{
          T obj=abs_root->object;
          abs_root->object=abs_root->right->object;
          abs_root->right->object=obj;
          abs_root=abs_root->right;
        }
      }
      else break;
    }
    else if(abs_root->left!=nullptr && abs_root->right==nullptr){
      if(abs_root->object<abs_root->left->object){
         T obj=abs_root->object;
         abs_root->object=abs_root->left->object;
         abs_root->left->object=obj;
         abs_root=abs_root->left;
      }
      else break;
    }
    else if(abs_root->left==nullptr && abs_root->right==nullptr){
      break;
    }
  }
  return a;
}

template<typename T>
void Heap<T>::recursive_delete(TreeNode<T>* node){
   if(node==nullptr) return;
   recursive_delete(node->left);
   recursive_delete(node->right);
   node->left=nullptr;
   node->right=nullptr;
   cout<<"#"<<endl;
   if(node!=root)delete node;
   else root=nullptr;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T>* node){
  // insert your code here
    if( node != nullptr ){
        if(i!=0){cout << prefix;
        cout << (isLeft ? "|--" : "|__" );}

        // print the value of the node
        cout << node->object << endl;
        // enter the next tree level - left and right branch
        string x=prefix;
        if(i!=0)prefix=prefix +  (isLeft ? "│   " : "    ");
        isLeft=true;
        i++;
        printHeap(node->left);
        // printHeap( prefix + (isLeft ? "│   " : "    "), true);
        // prefix=x + (isLeft ? "left" : "right");
        isLeft=false;
        printHeap(node->right);
        i--;
        prefix=x;
    }
}

  
