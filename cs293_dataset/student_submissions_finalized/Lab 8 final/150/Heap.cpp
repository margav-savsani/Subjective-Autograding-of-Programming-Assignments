#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


// insert following naveen garg's algorithm
// inserting at the node's right child if last node is parent's left child
// else inserting at parent's successor's left child.
// after adding heapify it to follow the heapify condition.
template<typename T>
void Heap<T>::insert(T obj) {

  // dealing with the base case of root being null.
  if (root==nullptr){
    root = new  TreeNode<T>(obj);
    last_node=root;
  //  printHeap(root);
    return;
  }
  // storing the inserted node for heapify.
  TreeNode <T>* inserted_node;
  if (last_node==root){
     root->left = new  TreeNode<T>(obj);
     last_node =root->left; // updating the last node's value.
     last_node->parent=root;
     inserted_node=root->left;
  }
  else {
     if (last_node->parent->left == last_node){
        last_node->parent->right=new  TreeNode<T>(obj);
        last_node->parent->right->parent=last_node->parent;
        last_node=last_node->parent->right; // updating the last node's value.
        inserted_node=last_node;
     }
     else{
          getsucc(last_node->parent)->left=new  TreeNode<T>(obj);
          getsucc(last_node->parent)->left->parent=getsucc(last_node->parent);
          last_node= getsucc(last_node->parent)->left; // updating the last node's value.
          inserted_node=last_node;
     }
  }
// making heap correct to follow the constraint that parent's rating > 
// child's rating by swapping them if child rating > parent rating.
while((inserted_node->parent !=nullptr)){
   if (inserted_node->parent->object<inserted_node->object)
   {
    swap(inserted_node->object,inserted_node->parent->object);
   }
   inserted_node=inserted_node->parent;
}
//printHeap(root);
return;
}

// deleting the max element acc to Naveen garg's lecture.
// swap last node and root node. delete last node's content
// now heapify the root with respect to the criteria that 
// parent should have more rating than child.

template<typename T>
T Heap<T>::delMax() {
// to return at last the deleted node object.
T deleted_node=root->object;

// dealing with the base case of root is the last and single element
if(last_node==root){
  root =nullptr;
  last_node=nullptr;
  return deleted_node;
}

// swapping the content and making it null.
swap(last_node->object,root->object);
last_node= getprec(last_node);
TreeNode<T>* succ=getsucc(last_node);
if (succ->parent->left== succ){
    succ->parent->left=nullptr;
    delete(succ); // deallocating space.
}
else {
  succ->parent->right=nullptr;
  delete(succ); // deallocating space.
}
// heapifying the root.
TreeNode<T>* myswap=root;
while (myswap->left !=nullptr){
  if (myswap->right != nullptr &&  myswap->left->object <myswap->right->object){
      if (myswap->object < myswap->right->object){
         swap(myswap->object,myswap->right->object);
         myswap=myswap->right;
      }
      else{
        break;
      }
  }
  else {
    if (myswap->object < myswap->left->object){
         swap(myswap->object,myswap->left->object);
         myswap=myswap->left;
    }
    else{
      break;
    }
  }
}
  // printHeap(root);
  return deleted_node;

}

// print the heap in a bst manner with nodes.
// it has been commented out in insert and delete.
// Bonus please :) as lines are visible as desired.
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
{
    static string prefix="";
    static bool isleft=false;
    string myprefix=prefix;
      if( node != nullptr )
    {
        cout << prefix;

        cout << (isleft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object.rating << endl;
        // enter the next tree level - left and right branch
        isleft=true;
        prefix= myprefix + "│   ";
        printHeap(node->left);
        prefix= myprefix +  "│   ";
        isleft=false;
        printHeap(node->right);
    }
    else {
      prefix="";
      isleft=false;
      return;
    }
}
}

//This returs the next node of the heap (acc. to filling order)
// Useful for delMax() and ins()
// Idea is if it is left child of parent succ is right child
// else its the left child of parent's successor. 
template<typename T>
TreeNode<T>* Heap<T>::getsucc(TreeNode<T>* node) {
if (node== root){
  return root->left;
}
if (node->parent->left == node){
   return node->parent->right;
}
else {
    return getsucc(node->parent)->left;
}
  // insert your code here
}


//This returs the previous node of the heap
// Useful for delMax()
// Idea is if it is right child of parent prec is left child
// else its the right child of parent's precedessor 
template<typename T>
TreeNode<T>* Heap<T>::getprec(TreeNode<T>* node) {

// no precedessor for root.
if (node== root){
  return nullptr;
}
if (node == root->left){
  return root;
}
if (node->parent->left == node){
  
   return getprec(node->parent)->right;
}
else {
     return node->parent->left;
}
}




