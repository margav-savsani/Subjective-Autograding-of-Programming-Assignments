#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  //handling base case for the insertion where both root and end are null
  if (root == nullptr){
    root = new TreeNode<T>(obj);
    end = root;
    return;
  }
  else{
    //going up the tree to find the node from where direction of parent changes
    TreeNode<T> *temp = end;
    TreeNode<T> *temp_parent = temp->parent;
    //counter to count the number of nodes we went up
    int count=0;
    while (temp_parent != nullptr && temp_parent->right == temp){
      temp = temp_parent;
      temp_parent = temp_parent->parent;
      count++;
    }

    //if no parent then we are at root and so special case as the whole level will be full and need to go to next level    
    if (temp_parent == nullptr){
      while (temp->left){
        temp = temp->left;
      }
      temp->left = new TreeNode<T>(obj);
      end = temp->left;
      end->parent = temp;
    }
    //if not special case then going down the tree to get to the next place to insert the node
    else {
      temp = temp_parent->right;

      //special case when end was a left child
      if (temp==nullptr){
        temp_parent->right = new TreeNode<T>(obj);
        end = temp_parent->right;
        end->parent = temp_parent;
      }
      //otherwise going down the tree
      else{
        while(count-1){
          temp = temp->left;
          count--;
        }
        temp->left = new TreeNode<T>(obj);
        end = temp->left;
        end->parent = temp;
      }
    }
    //updating the variables and then bubbling up the newly inserted value to satisfy the heap property
    temp = end;
    temp_parent = temp->parent;

    //if heap condition not satisfied then this loop will run
    while (temp_parent != nullptr && temp->parent->object < temp->object){
      T t = temp->parent->object;
      temp->parent->object = temp->object;
      temp->object = t;
      temp = temp_parent;
      temp_parent = temp_parent->parent;

    }
  }
  //just to check the code
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {
  //if root is null then nothing happens
  if (root != nullptr){
    // base case when the root is deleted
    if (root-> right == nullptr && root->left == nullptr){
      delete root;
      root = nullptr;
      end = nullptr;
      return;
    }

    //otherwise traversing the tree to find the element which will be the end after deletion
    T t = root->object;
    root->object = end->object;
    end->object = t;
    TreeNode<T> *temp = end;
    TreeNode<T> *temp_parent = temp->parent;
    int count=0;
    while (temp_parent != nullptr && temp_parent->left == temp){
      temp = temp_parent;
      temp_parent = temp_parent->parent;
      count++;
    }

    //same as insert but this time we will go on other side (i.e. left instead of right as in case of insert)

    //if we reach root then special case
    if (temp_parent == nullptr){
      while (temp->right){
        temp = temp->right;
      }
    }
    //othewise traversing down the tree to reach final node
    else {
      temp = temp_parent->left;
      while(count){
        temp = temp->right;
        count --;
      }
    }
    if (end->parent->left == end){
      end->parent->left = nullptr;
    }
    else{
      end->parent->right = nullptr;
    }
    delete end;
    end = temp;
    //heapifying after deleting node and replacing it to root
    Heapify();
  }
  //just to check the code
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  //similar to the one in outlab 5 but with static variables instead of the parameters
  static string prefix="";
  static bool isLeft=false;
  static int recursion = -1;
  recursion ++;
  if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        // enter the next tree level - left and right branch
        string prevpre=prefix;

        //updating the variables to go into next recursion level
        bool previs = isLeft;
        if (recursion!=0){
          prefix = prefix + (isLeft ? "│   " : "    ");
        }
        else {
          prefix = prefix + "    ";
        }
        isLeft = true;
        printHeap(node->left);

        //updating the variables to go into next recursion level
        isLeft = false;
        printHeap(node->right);

        //restoring the values stored in the variables
        prefix = prevpre;
        isLeft = previs;
    }
  recursion--;
}

template<typename T>
void Heap<T>::Heapify() {

  TreeNode<T> *temp=root;
  //looping until both the childs are zero
  while (temp->left != nullptr || temp->right != nullptr){

    //checking the special case when only either left child or only right child exists
    if (temp->right == nullptr){
      if (temp->object < temp->left->object){
        T t = temp->object;
        temp->object = temp->left->object;
        temp->left->object = t;
        temp = temp->left;
        continue;
      }
      else{
        break;
      }
    }
    else if (temp->left == nullptr){
      if (temp->object < temp->right->object){
        T t = temp->object;
        temp->object = temp->right->object;
        temp->right->object = t;
        temp = temp->right;
        continue;
      }
      else{
        break;
      }
    }
    //if not then just bubbling down the root till heap condition is satisfied 
    if (temp->object < temp->left->object){
      if (temp->right->object < temp->left->object || (!(temp->right->object < temp->left->object) && !(temp->left->object < temp->right->object))){
        T t = temp->object;
        temp->object = temp->left->object;
        temp->left->object = t;
        temp = temp->left;
        continue;
      }
    }
    if (temp->object < temp->right->object){
      if (temp->left->object < temp->right->object || (!(temp->left->object < temp->right->object) && !(temp->right->object < temp->left->object))){
        T t = temp->object;
        temp->object = temp->right->object;
        temp->right->object = t;
        temp = temp->right;
        continue;
      }
    }
    break;
  }
  // insert your code here
  
  return;
}

  
