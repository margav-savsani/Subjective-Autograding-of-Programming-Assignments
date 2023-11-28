#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include<cstdlib>
#include<string>


 //This function is used to make the heap sorted again after insertion
template<typename T>
void Heap<T>::insert1(TreeNode<T> *node){
  while(node->parent!=nullptr){
    if(node->object.rating <=node->parent->object.rating){ //swap will happen till the heap is not sorted
      return;
    }
    else{
      TreeNode <T>*swap = new TreeNode<T>(node->object); //swapping if rating of parent<child
      node->object.rating = node->parent->object.rating;
      node->parent->object.rating = swap->object.rating;
      node = node->parent;
    } 
  }
  
}


//This is used if both the left and the right subtree are sorted but there is a mismatch at the parent node
template<typename T>
void Heap<T>::heapify(int rating){
  root->object.rating = rating;
  TreeNode<T>* root_copy = root;
  if(root_copy->left!=nullptr && root_copy->right!=nullptr){ //if there are both the left and right subtrees
    while(root_copy->left!=nullptr && root_copy->right!=nullptr){ //will go on till the heap is sorted
      if(root_copy->object.rating>=root_copy->left->object.rating && root_copy->object.rating>=root_copy->right->object.rating){
        return;
      }
      else{ //swap with the max rating of the children
        if(root_copy->left->object.rating >=root_copy->right->object.rating){
          TreeNode <T>*swap = new TreeNode<T>(root_copy->object);
          root_copy->object.rating = root_copy->left->object.rating;
          root_copy->left->object.rating = swap->object.rating;
          root_copy = root_copy->left;
        }
        else{
          TreeNode <T>*swap = new TreeNode<T>(root_copy->object);
          root_copy->object.rating = root_copy->right->object.rating;
          root_copy->right->object.rating = swap->object.rating;
          root_copy = root_copy->right;
        }
      }
    }
  }

  else{
    if(root_copy->right==nullptr && root_copy->left!=nullptr){ //if right is null and left is not 
      if(root_copy->object.rating>=root_copy->left->object.rating) { //heap is already sorted
        return;
      }
      else{               
        TreeNode <T>*swap = new TreeNode<T>(root_copy->object); //if not sorted swap
        root_copy->object.rating = root_copy->left->object.rating;
        root_copy->left->object.rating = swap->object.rating;
        root_copy = root_copy->left; 
      }
    }
  }

}


//nodes1 is the number of nodes after insertion ,if insertion. else number of nodes before, after deletion
//nodes2 is the total number of nodes if the binarytree is complete 
//level is the level of the tree at which we are present
//no = 0 denotes insertion and no = 1 for deletion
//obj is the object to be inserted
template<typename T>
void Heap<T>::recur(TreeNode<T> *node,int nodes1,int nodes2,T obj,int no,int level) { 
  TreeNode<T> *PArent; //used to keep update of parent of the node
  bool isleft; //checking if we are going to leftsubtree or the rightsubtree
  if(nodes1-((nodes2-1)/2)<=((nodes2+1)/4)){ //condition for going to left subtree
    level--;            //updating level
    PArent = node;      //updating parent
    if(node!=nullptr){
      node = node->left;//updating node
    }
    isleft= true;       //updating isLeft
  }
  else{                   //condition for going to right subtree
    level--;              //updating level
    PArent = node;        //updating parent
    if(node!=nullptr){
      node = node->right; //updating node
    }
    isleft = false;       //updating isLeft
  }
  if(no == 0){ //for insertion
    if(node == nullptr){            //going to the point where we have to insert the node
      node = new TreeNode<T>(obj);  //creating the node
      node->parent = PArent;        //updating the parent of the node
      if(isleft){
        PArent->left = node;        //updating the child of the parent
      }
      else{
        PArent->right = node;
      }
      num_nodes++;                  //increasing the number of nodes
      insert1(node);               
      return;
    }
  }
  else{
    if(level==1){                       //for deletion
      node->parent = nullptr;           //removing the parent-node connection
      if(isleft){
        PArent->left = nullptr;         //removing the node-parent connection
      }
      else{
        PArent->right = nullptr;  
      }
      heapify(node->object.rating);
      return ;
    }

  }
  int x = (nodes2+1)/4;
  if(isleft){
    recur(node,nodes1-(nodes2+1)/4,(nodes2-1)/2,obj,no,level);    //recursion if we are in left subtree
  }
  else{
    recur(node,nodes1-(nodes2+1)/2,(nodes2-1)/2,obj,no,level);    //recursion if we are in right subtree
  }
  

}


//used for inserting the node with the object to be obj
template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode <T>*root_copy = root; //copy of the root
  if(root == nullptr){           //insertion of the first element
    root = new TreeNode<T>(obj); //creating the node
    num_nodes++;                 //increasing the number of nodes
  }
  else{
    int p =1;
    int level = 0;
    int nonodes = num_nodes;
    while(nonodes>=0) {
      nonodes = nonodes - p;
      p = p*2;
      level++;
     
    }
    recur(root_copy,num_nodes+1,p-1,obj,0,level);
  }

  return;
}


//used for deleting the root
template<typename T>
void Heap<T>::delMax() {
  TreeNode <T>* root_copy = root; //copy of the root
  int p =1;
  int level = 0;
  int nonodes = num_nodes;
  while(nonodes>0) {
    nonodes = nonodes - p;
    p = p*2;
    level++;
  }
    if(num_nodes>1){
      recur(root_copy,num_nodes,p-1,root->object,1,level); //if there is more than 1 node else set root as nullptr
    }
    else{
      root = nullptr;
    }
     num_nodes--; //decreasing the number of nodes
  
  return;
}

template<typename T>
void Heap<T>::print(TreeNode<T> *node,const string& prefix, bool isLeft){
  if( node != nullptr ){
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the rating of the node object
        cout << node->object.rating<< endl;
        TreeNode<T> *curr = node;
        node = node->left;
        // enter the next tree level - left and right branch
        print( node,prefix + (isLeft ? "│   " : "    "), true);
        node = curr->right;
        print(node, prefix + (isLeft ? "│   " : "    "), false);
        node = curr;
  }
  return;

}
//used for printing the heap
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  print(node,"",false); 

  
  return;
}

  
