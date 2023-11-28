#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode
  
  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft
  if (grandParentNode->parent ==nullptr){
      parentNode->parent=nullptr;
      root= parentNode;
      
  }
  else{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  
  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);}

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the right subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode
   // Let's implement these updations below.
       
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
   if (grandParentNode->parent ==nullptr){
       currNode->parent=nullptr;
      root= currNode;
  }
  else{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  

  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parentNode and the right child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParentNode (i.e. of z).
       
  
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
   // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode
   // Let's implement these updations below.
       
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;
  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
   if (grandParent->parent ==nullptr){
      currNode->parent= nullptr;
      root= currNode;
  }
  else{
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  

  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);}

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, true);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parentNode and the right child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParentNode (i.e. of z).
       
  
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parent, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);

  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->left;
  
  if (grandParent->parent ==nullptr){
       parent->parent=nullptr;
      root= parent;
  }
  else{
  TreeNode *greatGrandParentNode = grandParent->parent;

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);  }
  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parent, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParent, parent, true);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the right subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree:: nodelong (TreeNode *x){  // to return the height of the node
 if (x==nullptr) return -1; //if height of a leaf is 0

 return max(nodelong(x->left),nodelong( x->right))+1; //recursive 
}

bool AVLTree::insert(int jrnyCode, int price)
{  
   TreeNode * B[1000];
   int m=0;
    TreeNode *z= new TreeNode(jrnyCode,price);//create a fake node with the values to be inserted in BST
    TreeNode *y=nullptr;
    TreeNode *x=root;
    while(x!=nullptr){ //iterate till we find a position to insert
        y=x; 
        m++;
         B[m]=x;   // store the pointers to the ansectors in an array whose values for longest path and shortest path have to be changed
        if (AVLLessThan(z,x))//using AVL less than function here
           x=x->left; 
        else {x=x->right;}

    }

     m++;
     B[m]= z;
    z->parent=y; //assign parent node to new node

    if (y==nullptr) 
      {root=z;
      B[0]=root;}
    else if (AVLLessThan(z,y))  // to compare the key of new node with its parent
      updateAVLParentChild(z,y,true);
    else updateAVLParentChild(z,y,false);
        
    int ancestors=m;
     
    while(m>0){ //iterate over all ancestors

      B[m]->height= nodelong(B[m]);  ;  // change the height here 
      m--;} 
      m=ancestors;
      
     if (B[m]->parent== nullptr ){return true; } // check if the parent exists
     if (B[m]->parent->parent== nullptr ){return true; } //check if the grandparent exists
     while(B[m]->parent->parent !=nullptr){
        int balance = getBalance(B[m]->parent->parent); // check the balance of the grandparent
        if(balance >1 || balance <-1){
          Rotation(B[m],balance); // if the balance is not right call the rotation function
          break;
        }
        m--;
      }
      m=ancestors;
      while(m>0){ // rotation change the height of the ansectors that are rotated

      B[m]->height= nodelong(B[m]);  ;  // change values here 
      m--;} 

  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
} 

void AVLTree::Rotation(TreeNode * currnode ,int balance){
  // Left Left Case
    if (balance > 1 && AVLLessThan(currnode,currnode->parent))
        rotateLeftLeft(currnode,currnode->parent,currnode->parent->parent);
 
    // Right Right Case
    if (balance < -1 &&  AVLLessThan(currnode->parent,currnode))
        rotateRightRight(currnode,currnode->parent,currnode->parent->parent);
 
    // Left Right Case
    if (balance > 1 && AVLLessThan(currnode->parent,currnode))
         rotateLeftRight(currnode,currnode->parent,currnode->parent->parent);
 
    // Right Left Case
    if (balance < -1 && AVLLessThan(currnode,currnode->parent))
      rotateRightLeft(currnode,currnode->parent,currnode->parent->parent);
}

int AVLTree::getBalance(TreeNode *x) //returns height imbalance of the tree
{
    if (x == nullptr)  // root is null
        return 0; // only one child
    else if (x->left == nullptr && x->right != nullptr) return - x->right->height;
     else if (x->right == nullptr && x->left != nullptr ) return  x->left->height;
     else if (x->right == nullptr && x->left ==nullptr ) return  0; // leaf node
     else return x->left->height - x->right->height;
}
// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.


int AVLTree::find(int jrnyCode)
{ TreeNode *n= new TreeNode(jrnyCode, 100); // create a fake node
  TreeNode *x=root;
    while(x!=nullptr && jrnyCode!=x->getJourneyCode()){ //traverse the tree
        if (AVLLessThan(n, x) ) x=x->left; // at each step compare the to be found node with the current node
        else x=x->right;
    }
    if (x==nullptr) {return -1;} //if journey code not found
    else return x->getPrice();
    
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
TreeNode * AVLTree::TreeMinimum(TreeNode * x) {    //find the node with minimum journey code
    while (x->left != nullptr){  // go left untill we find a node which does not have a left child
          x=x->left;
    }
    return x;} // return pointer to the node

bool AVLTree::remove(int jrnyCode) //deletion of a node given the journey code
{ TreeNode * B[1000]; // crete an array of pointers to store the pointers to the node that are the 
  int m=0;          //ancestors of the node to be deleted
  TreeNode *n= new TreeNode(jrnyCode, 100);  //create a fake node with the input journey code
  TreeNode *x=root;
  B[0]=root;     // set the first element of the array as the root pointer
  while(x!=nullptr && jrnyCode!=x->getJourneyCode()){  //find the journey code in the tree
        if (AVLLessThan(n, x) ) {m++ ; B[m]=x->left; x=x->left ;}//simultaneously update the array B as the nodes
        else {m++ ; B[m]=x->left;x=x->right;}                    // encountered on the path will be the ancestors
  }  
  
  if (x==nullptr){    //return false if journey code not found
        return false;
  }
 
  if( (x->left == nullptr) || (x->right == nullptr) ) // check if the node has at most one child
     {  TreeNode *temp ;
        if (x->left == nullptr){ // store the child in a temporary location
            temp=x->right;    
        }
        else {
            temp=x->left;         
        }
            
        if (temp == nullptr){ //the node to be deleted is a leaf
            temp =x; // check whether the leaf was a right or a left child of its parent 
            updateAVLParentChild(nullptr,x->parent,x->parent->left==x);
       }
        else  
        updateAVLParentChild(temp,x->parent,x->parent->left==x);
        
     }

  else
      {  
          TreeNode * temp1 = TreeMinimum(x->right);  //find the  pointer to the successor of the node
          TreeNode temp =*temp1;  //store the values of the successor in a temp node
          remove(temp1->getJourneyCode()); //remove the successor
          TreeNode *left = x->left ; //store the values of the jorney code to be deleted in temporary variables 
          TreeNode *right = x->right ;//which will remain unchanged
          TreeNode *parent = x->parent ;
          
          *x =temp; // copy all values of the successor 
          x->left =left; // update the values that should not have changed
          x->right =right;
          x->parent =parent;
          x->height=nodelong(x); 
          
      }

    m--;
    int ancestors=m;

    while(m>=0){
      
        B[m]->height= nodelong(B[m]);  
        // change values of the height of the ancestors here 
        m--;} 

    m=ancestors;
      
    while(m>=0){
     
       int balance =getBalance(B[m]); //check the balance of all the ansector nodes
       if (balance >1|| balance < -1){ // if the tree is unbalnced call the rotation function
            Rotation_deletion(B[m], balance);
            int d=ancestors;
            while(d>=0){  // rotation can change height of nodes
                 B[d]->height= nodelong(B[d]);  ;  // change values of height of the ansectors here 
                 d--;} 
       }
       m--;
    }
 
   
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

void AVLTree::Rotation_deletion(TreeNode * currnode ,int balance){
   
    TreeNode *child ;
    //find the child of the currnode that the the larger height
    TreeNode *child_of_child;
    //similarly for the child of the currnode
 
  // Left Left Case
    if (balance > 1 && getBalance(currnode->left)>=0) {
        child=currnode->left;
        child_of_child =currnode->left->left;
        rotateLeftLeft(currnode->left->left,currnode->left,currnode);
        }
 
    // Right Right Case
    if (balance < -1 &&   getBalance(currnode->right)<=0){
        child=currnode->right;
        child_of_child =currnode->right->right;
        rotateRightRight(currnode->right->right,currnode->right,currnode);}
 
    // Left Right Case
    if (balance > 1 &&  getBalance(currnode->left) < 0){
        child=currnode->left;
        child_of_child =currnode->left->right;
        rotateLeftRight(currnode->left->right,currnode->left,currnode);}
 
    // Right Left Case
    if (balance < -1 &&  getBalance(currnode->left) > 0) {
      child=currnode->right;
      child_of_child =currnode->right->left;
      rotateRightLeft(currnode->right->left,currnode->right,currnode);}

    currnode->height=nodelong(currnode); //update the height of x,y,z involved in the rotation
    child->height=nodelong(child);
    child_of_child->height=nodelong(child_of_child);

}
