#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    root = new TreeNode<T> (obj);
    last = new TreeNode<T> (obj);
    last = root;
    return;
  }
  class TreeNode <T> *iterator = new class TreeNode <T> (obj);
  iterator = last;
  
  //Code to find the next empty place and put the element in it
  while(1){
    if ( iterator->parent == nullptr ){
      while(iterator->left != nullptr ){
        iterator = iterator->left;
      }
      iterator->left = new TreeNode<T> (obj);
      last = iterator->left;
      last->parent = iterator;
      break;
    }
    if ( iterator->parent->right != iterator ){
      iterator=iterator->parent;
      if ( iterator->right == nullptr ){
        iterator->right =  new TreeNode<T> (obj);
        last = iterator->right;
        last->parent = iterator;
        break;
      }
      else{
        iterator = iterator->right;
        while(iterator->left!=nullptr){
          iterator = iterator->left;
        }
        iterator->left = new TreeNode<T> (obj);
        last = iterator->left;
        last->parent = iterator;
        break;
      }
    }
    iterator = iterator->parent;
  }

  //Now let's balance the heap
  iterator = last;
  while(iterator->parent!=nullptr && iterator->parent->object < iterator->object ){
    T temp;
    temp = iterator->parent->object;
    iterator->parent->object = iterator->object;
    iterator->object = temp;
    iterator = iterator->parent;
  }

  //Let's check for invalid inserts
  return;
}

template<typename T>
void Heap<T>::delMax() {
  if (root == nullptr){
    return;
  }
  //swap the last object and root
  swap(root->object,last->object);

  //Delete the last object now and  update the last and root
  
  //if last was root
  if (last->parent == nullptr){
    root = nullptr;
    last = nullptr;
    return;
  }
  //if last was right child
  else if(last->parent->right==last){ 
    last = last->parent->left ;
    last->parent->right = nullptr;
  }
   //if last was left child
  else if(last->parent->left == last){
    //delete the old last node
    last = last->parent;
    last->left = nullptr;
    //let's find the new last node
      while(true){
        //keep going up unless u find that u can't go up anymore
        // u r the right child
        if ( last->parent == nullptr ){
            //can't go up anymore
            while(last->right!=nullptr){
                last = last->right;
            }
            break;
        }
        else if (last->parent->right==last){
          //u were the right child
          last = last->parent->left;
          while(last->right != nullptr){
            last = last->right;
          }
          break;
        }
        else{
          last = last->parent;
        }
      }
  }

  //Heapfiy
  TreeNode<T> *heaper = root;
  while(true){
    //before deciding the state, let's check for exceptional cases
    //heaper has reached a leaf
    if ( heaper->left == nullptr && heaper->right == nullptr ){
      break;
    }

    //heaper has reached parent of last with only 1 child
    if ( heaper->left != nullptr && heaper->right == nullptr){
      if ( heaper->object < heaper->left->object){
        swap(heaper->object,heaper->left->object);
        heaper = heaper->left;
      }
      break;
    }

    //decide the state
    // 1 - p > l,r
    // 2 - l > p,r
    // 3 - r > p, l
    int state = 1;
    T largest = heaper->object;
    if ( largest < heaper->left->object){
      state = 2;
      largest = heaper->left->object;
    }
    if ( largest < heaper->right->object){
      state = 3 ;
      largest = heaper->right->object;
    }

    //take action according to the state
    if (state==1){
      break;
    }
    else if(state==2){
      swap(heaper->left->object, heaper->object);
      heaper = heaper->left;
    }
    else if(state==3){
      swap(heaper->right->object,heaper->object);
      heaper = heaper->right;
    }
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  if (node==nullptr){
    return;
  }
  
  pHeap("",node);

  return;
}

template<typename T>
void Heap<T>::pHeap(const string& prefix, TreeNode<T> *Node, bool isLeft){
  if( Node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << Node->object << endl;
        // enter the next tree level - left and right branch
        pHeap( prefix + (isLeft ? "│   " : "    "), Node->left,true);
        pHeap( prefix + (isLeft ? "│   " : "    "), Node->right ,false);
    }
}