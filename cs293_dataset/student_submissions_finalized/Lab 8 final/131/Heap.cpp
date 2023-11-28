#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
   TreeNode<T> *newnode = new TreeNode<T> (obj); //create a new node whcih is to be inserted 
  
   int height=1 ;  // heigth of the tree while going left
   int height_right =1; // heigth of the tree while going right
   TreeNode<T>  *y = root; 

   if (y==nullptr){   //base case
      root =newnode;  // root inserted in the heap
      return;
   }

   while(y->right!=nullptr){  // calculate the right height of heap
      height_right ++;
      y= y->right;

   }
   y= root;
   while(y->left!=nullptr){  // calculate the left height of heap
      height ++;
      y= y->left;
   }

   TreeNode<T>  * add  =root; // pointer to the parent of the
   if (height == height_right ) // node which will be added
      {   y->left = newnode;
          newnode->parent =y;
      }  //case when all levels were filled 
   else
      { 
          add =getlast(root,height,1); //last level is not filled 
          if (add->left == nullptr)
              add->left = newnode;  // adding a new level
          else add->right = newnode;
          newnode->parent =add;} //setting the parent of the new node

    TreeNode<T>  *x = newnode ; 
 

   while (x->parent->object < x->object && x->parent!=nullptr){ //move the newly inserted node element 
      T temp = x->object;                                      // all the way up the heap
      x->object= x->parent->object;                            //untill root is reached or  
      x->parent->object= temp;                                 // condition of max heap is met
      x= x->parent ;
      if (x->parent == nullptr) break;

   }
  
  // insert your code here
  
  return;
}

template<typename T>
TreeNode<T> * Heap<T>:: getlast(TreeNode<T> * x ,int height ,int flag ){ // get the parent of the node to be insrted
  static TreeNode<T> *  parent ;
  static TreeNode<T> *  ans =root;
  static int recursion  =0;
  if (flag==1)recursion =0;  // flag variable to set recursion value to true on each insertion
  recursion ++;

  if (x ==nullptr ){
    if (recursion == height ) // check if the recursion len=vel matches the last level height
      {
          parent =ans;
          return ans; // reduntant , doesnt matter what is returned
      } 
    recursion --;
    return nullptr;
  }
  ans = x;                       // basically idea derived from preorder traversal
  getlast(x->left ,height ,0); // recursion on left subtree
  ans = x;
  getlast(x->right, height,0);  // recursion on right subtree
  recursion--;
  return parent;
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> * max = root;
  int height=1 ;   // heigth of the tree while going left
  int height_right =1;  // heigth of the tree while going right 
  TreeNode<T>  *y = root;
   
   y= root;
   while(y->left!=nullptr){ // calculate the left height of heap
      height ++;  
      y= y->left;
   }
   y= root;
   while(y->right!=nullptr){  // calculate the left height of heap
      height_right ++;
      y= y->right;
   }
 

   TreeNode<T>  * last ;
   if (height == height_right )   //case when all levels were filled 
      last =y ;
  else last =getlast_del(root ,height,1); //last level not filled
  
  root ->object = last->object;           //swapping node with root object
  if (last->parent->right == nullptr )
      last->parent->left= nullptr;
  else last->parent->right = nullptr ;  //altering child of the parent of the deleted node
 
    TreeNode<T> * x =root;
  while (x!= nullptr && x->left !=nullptr){  // move the root object 
     TreeNode<T> * change;                   // all the way down untill
     
     if (x->right ==nullptr)
     { 
        if (x->object < x->left->object)        // reached the last level and no more swap is possible
          change = x->left;
        else break;
     }

    else if (x->object < x->right->object || x->object < x->left->object){  // condition of max heap is met
     
    if (x->right->object < x->left->object)
        change = x->left;
    else 
      change = x->right;}
    else break;
    
    T temp = x->object;      // swap algorithm
    x->object= change->object;
    change->object= temp;
    x= change  ;  
  
  }
  // insert your code here

  return;
}

template<typename T>
TreeNode<T> * Heap<T>:: getlast_del(TreeNode<T> * x ,int height ,int flag ){
   static TreeNode<T> *  parent ;
  static TreeNode<T> *  ans =root;
  static int recursion  =0;
  if (flag==1)recursion =0;   // flag variable to set recursion value to true on each insertion
  recursion ++;

  if (x ==nullptr )
    { 
      recursion --;   //basic checks performed
      return nullptr;
    }
  if (x->left == nullptr && x->right ==nullptr){
    if (recursion == height )  // this is the condition where we have found the position 
      {
                              // of the node which will be deleted
      parent =x;              // this is what is actually returned
      } 
    recursion --;
    return nullptr;
  }
  ans = x;
  
  getlast_del(x->left ,height ,0); // rcurse on left subtree
  ans = x;

  getlast_del(x->right, height,0); // recurse on right subtree
  recursion--;
  return parent;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {  // similar to lab 5
  static bool isLeft = false;
  static int recursion = 0;
  static string prefix = "";  // using static variables
  static string a = "|   ";
  recursion ++;
  
  if (recursion ==1) prefix ="";
  if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        string temp =prefix;
        bool store_left= isLeft;
        // enter the next tree level - left and right branch
        prefix = prefix + (isLeft ? a : "    ");
        isLeft =true;                // method being a mix of resursive and iteraticve way
        printHeap( node->left);      // because of the new signature of the function
        isLeft =store_left;
        prefix =temp +(isLeft ? a : "    "),
        isLeft =false;
        printHeap(node->right);
      
    }
  // insert your code here
  recursion --;
 
  return;
}

  
