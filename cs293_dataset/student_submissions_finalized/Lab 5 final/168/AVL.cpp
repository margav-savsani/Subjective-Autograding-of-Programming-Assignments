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


//function that adjusts the height of the given node
void AVLTree::adjustHeight(TreeNode* node){
  int lheight,rheight;

  //setting heights to -1 if null

  if(!node->left){
    lheight=-1;
  }
  else{
    lheight=node->left->height;
  }
  if(!node->right){
    rheight=-1;
  }
  else{
    rheight=node->right->height;
  }
  if(lheight>rheight){
    node->height=lheight+1;
  }
  else{
    node->height=rheight+1;
  }
}


bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  TreeNode* T3=parentNode->right;
  
  if(!greatGrandParentNode){
    //grandParentNode is the root of the tree
    root=parentNode;
    updateAVLParentChild(root,nullptr,true);
  }
  else{
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
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, true);
  //YES


  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);
  //YES


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
  //YES


  adjustHeight(currNode); 
  adjustHeight(grandParentNode);
  while(parentNode){
    adjustHeight(parentNode);
    parentNode=parentNode->parent;
  }

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
    
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  if(!greatGrandParentNode){
    root=currNode;
    updateAVLParentChild(currNode,nullptr,true);
  }
  else{
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
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }
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
       
  // Let's implement these updations below.
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  adjustHeight(grandParentNode);
  adjustHeight(parentNode);
  while(currNode){
    adjustHeight(currNode);
    currNode=currNode->parent;
  }

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the right child of grandParentNode.  That's
  // why we are doing a rotateRightLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
    
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  if(!greatGrandParentNode){
    root=currNode;
    updateAVLParentChild(currNode,nullptr,true);
  }
  else{
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

    // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  }

  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should be
  // made the right child of currNode
  updateAVLParentChild(parentNode, currNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);
  
  // Recall from Prof. Garg's lectures that the right subtree of 
  // parentNode (i.e. y in Prof. Garg's lectures) and left subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the RightLeft rotation.  So do don't need to update the
  // right child of parentNode and the left child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // grandParentNode (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // parentNode (i.e. of z).
       
  // Let's implement these updations below.
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of grandParentNode
  updateAVLParentChild(T2, grandParentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of parentNode
  updateAVLParentChild(T3, parentNode, true);

  adjustHeight(grandParentNode);
  adjustHeight(parentNode);
  while(currNode){
    adjustHeight(currNode);
    currNode=currNode->parent;
  }

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  TreeNode* T3=parentNode->left;
  
  if(!greatGrandParentNode){
    //grandParentNode is the root of the tree
    root=parentNode;
    updateAVLParentChild(root,nullptr,true);
  }
  else{
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
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  }

  // Make currNode (x in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that currNode should be
  // made the right child of parentNode
  updateAVLParentChild(currNode, parentNode, false);
  //YES


  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);
  //YES


  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the left subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the left child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the left subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the right
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the right child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);
  //YES

  adjustHeight(currNode); 
  adjustHeight(grandParentNode);
  while(parentNode){
    adjustHeight(parentNode);
    parentNode=parentNode->parent;
  }

  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode nodeInsert(jrnyCode,price);
  nodeInsert.height=0;
  //insert root if the tree was empty
  if(!root){
    root=new TreeNode(nodeInsert);
    updateAVLParentChild(root,nullptr,true);
    return true;
  }

  TreeNode* parentIns=nullptr;
  TreeNode* temp=root;
  //find position to insert the node
  while(temp){
    parentIns=temp;
    if(AVLLessThan(&nodeInsert,temp)){
        temp=temp->left;
    }
    else{
        temp=temp->right;
    }
  }

  if (AVLLessThan(parentIns,&nodeInsert)){
    nodeInsert.parent=parentIns;
    temp=new TreeNode(nodeInsert);
    updateAVLParentChild(temp,parentIns,false);
  }
  else{
    nodeInsert.parent=parentIns;
    temp=new TreeNode(nodeInsert);
    updateAVLParentChild(temp,parentIns,true);
  }

  // The insert is done, now we update the heights

  while(parentIns){
    adjustHeight(parentIns);
    parentIns=parentIns->parent;
  }
  
  //printing the tree before rotations
  //cout<<"BEFORE ROTATIONS"<<endl<<endl;
  //print();
  //cout<<endl<<endl;

  //Restoring balance by rotations
  temp=temp->parent;
  TreeNode* z =nullptr;
  //finding z, the node which has an imbalance
  while(temp){
    int lheight,rheight;
    if(!temp->left){
      lheight=-1;
    }
    else{
      lheight=temp->left->height;
    }
    if(!temp->right){
      rheight=-1;
    }
    else{
      rheight=temp->right->height;
    }

    if((lheight-rheight>1) || (rheight-lheight>1)){
      z=temp;
      break;
    }
    temp=temp->parent;
  }
  if(z){
    
    TreeNode* y;
    TreeNode* x;
    int case1=-1,case2=-1;    //for case1 and case2, 0 is left and 1 is right

    //finding which rotation to call
    if(AVLLessThan(&nodeInsert,z)){
      y=z->left;
      case1=0;
    }
    else{
      y=z->right;
      case1=1;
    }

    if(AVLLessThan(&nodeInsert,y)){
      x=y->left;
      case2=0;
    }
    else{
      x=y->right;
      case2=1;
    }

    //calling the rotate functions
    if(case1==0 && case2==0){
      rotateLeftLeft(x,y,z);
    }
    else if(case1==0 && case2==1){
      rotateLeftRight(x,y,z);
    }
    else if(case1==1 && case2==0){
      rotateRightLeft(x,y,z);
    }
    else if(case1==1 && case2==1){
      rotateRightRight(x,y,z);
    }
  }

  //printing the tree after rotations
  //cout<<"AFTER ROTATIONS"<<endl<<endl;
  //print();
  //cout<<endl<<endl;
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  TreeNode* match=new TreeNode(jrnyCode,0);

  if(!root){
    return -1;
  }
  
  if(!(AVLLessThan(match,root)) && !(AVLLessThan(root,match))){
    return 1;
  }

  TreeNode* temp=root;
  int found;
  if(AVLLessThan(root,match)){
    root=root->right;
    found=find(jrnyCode);
  }
  else{
    root=root->left;
    found=find(jrnyCode);
  }
  root=temp;
  return found;
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

bool AVLTree::remove(int jrnyCode)
{
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


