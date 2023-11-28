#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *curr=new TreeNode<T>(obj);
  last=curr;
  TreeNode<T> *temp=curr;
    if(root==nullptr){
        root=curr;
        end=root;
        return;
    }
    else{
        //Since heaps are left justified and level
        //we must find the empty spot and update end
        if(end->left==nullptr){//The empty spot is simply the left child of end and end needn't be updated
            end->left=curr;
            curr->parent=end;
        }
        else if(end->right==nullptr){//The empty spot is the right child of end and now end must be updated
            end->right=curr;
            curr->parent=end;
            //Now to update 'end'
            curr=curr->parent;
            while(true){
                if(curr->parent==nullptr){
                    while(curr->left!=nullptr){
                        curr=curr->left;
                    }
                    end=curr;
                    break;
                }
                if(curr->parent->left==curr){
                    curr=curr->parent->right;
                    while(curr->left!=nullptr){
                        curr=curr->left;
                    }
                    end=curr;
                    break;
                }
                curr=curr->parent;
            }

        }
        //Shifting up the tree incase heap property not satisfied
        while(true){
            if(temp->parent == nullptr){
                return;
            }
            if(temp->object < temp->parent->object){
                return;
            }
            else{
                T obj = temp->parent->object;
                temp->parent->object=temp->object;
                temp->object= obj;
                temp=temp->parent;
            }
        }
    }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  //end doesn't change
    //printHeap(root);
    if(end->left !=nullptr){
        if(end->right!=nullptr){
            root->object=end->right->object;
            end->right=nullptr;
        }
        else{
            root->object=end->left->object;
            end->left=nullptr;
        }
    }
    else{
        //End changes
        TreeNode<T> *temp=end;
        if(end==root){
            root=nullptr;
            end=nullptr;
            return;
        }
        while(true){
            if(temp->parent==nullptr){
                while(temp->right!=nullptr){
                    temp=temp->right;
                }
                end=temp->parent;
                root->object = temp->object;
                end->right=nullptr;
                break;
            }
            //Finding the first ancestor of end such that it is its parent's right child
            else if(temp->parent->right==temp){
                temp=temp->parent->left;
                while(temp->right!=nullptr){
                    temp=temp->right;
                }
                end=temp->parent;
                root->object=temp->object;
                end->right=nullptr;
                break;
            }
            temp=temp->parent;
        }   
    }
    TreeNode<T> *temp=root;
    while(true){
        if(temp->left==nullptr){
            return;
        }
        else{
            if(temp->right!=nullptr){//Heapifying by moving the objects down the heap
                if(temp->left->object < temp->right->object){
                    if(temp->object < temp->right->object){
                        T obj = temp->object;
                        temp->object = temp->right->object;
                        temp->right->object = obj;
                        temp=temp->right;
                    }
                    else{
                        return;
                    }
                }
                else{
                    if(temp->object < temp->left->object){
                        T obj = temp->object;
                        temp->object = temp->left->object;
                        temp->left->object = obj;
                        temp=temp->left;
                    }
                    else{
                        return;
                    }
                }
            }
            else{
                if(temp->object < temp->left->object){
                    T obj = temp->object;
                    temp->object=temp->left->object;
                    temp->left->object=obj;
                    temp=temp->left;
                }
                else{
                    return;
                }
            }
        }
    }

  return;
}

template<typename T>
void Heap<T>::printRec(const string& prefix, bool isLeft){
    if( root != nullptr ){
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printRec( prefix + (isLeft ? "│   " : "    "), true);
        root=curr;
        root = root->right;
        printRec( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here
  TreeNode<T> *temp=root;
  root = node;
  printRec("", false);
  root=temp;
  return;
}

  
