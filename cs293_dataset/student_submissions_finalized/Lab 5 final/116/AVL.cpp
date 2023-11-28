#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include<algorithm>
#endif





bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr)
  {
  
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
  }
  // Let T3 be the right child of parentnode initially , we will use T3 afterwards as it's position also changes.
  TreeNode *T3 = parentNode->right;

 

  // we will make parentnode as  child of greatGrandParentNode .
  //if both y and w=greatgrandparentnode  are not nullptr, then make w as parent of y ,if z is left child of w (w->left=this) else if z is right child of w then (w->right=this) .
 //else if y=nullptr and w!=nullptr, if z is left child of w (w->left=nullpt) else if z is right child of w then (w->right=nullptr) . 
 //else if x!= nullptr and w=nullptr then x->parent=nulptr. else nothing to do.
 if(greatGrandParentNode!=nullptr)
 {
   updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
 }
  // Make x the left child of y 
  // The last parameter is "true" to indicate that x should be
  // made the left child of y.
  //if both x and y are not nullptr then make y as parent of x and z->right=this.
 //else if x=nullptr and z!=nullptr  then z->right=nullptr.
 //else if x!= nullptr and z=nullptr then x->parent=nulptr. else nothing to do.

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
  
  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  bool isGPLeftChild;
 if(greatGrandParentNode!=nullptr) 
 {
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
 }
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  if(greatGrandParentNode!=nullptr)
 {
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

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{ 

 TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr) 
  {
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
  }
  //if both x and w=greatgrandparentnode  are not nullptr, then make w as parent of x ,if z is left child of w (w->left=this) else if z is right child of w then (w->right=this) .
 //else if x=nullptr and w!=nullptr, if z is left child of w (w->left=nullpt) else if z is right child of w then (w->right=nullptr) . 
 //else if x!= nullptr and w=nullptr then x->parent=nulptr. else nothing to do.
 TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
if(greatGrandParentNode!=nullptr)
 {
   updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
 }
 //if both x and z are not nullptr then make x as parent of z and z->right=this.
 //else if x=nullptr and z!=nullptr  then z->right=nullptr.
 //else if x!= nullptr and z=nullptr then x->parent=nulptr. else nothing to do.

  updateAVLParentChild( grandParent, currNode, true);
  
 //if both x and y are not nullptr then make x as parent of y and z->right=this.
 //else if x=nullptr and z!=nullptr  then z->right=nullptr.
 //else if x!= nullptr and z=nullptr then x->parent=nulptr. else nothing  
  
 updateAVLParentChild(parent, currNode ,false );  
 
 
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, grandParent, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, parent, true);

 

  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if(greatGrandParentNode!=nullptr)
  {

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
  }
  TreeNode *T2 =parent->left;
  
  //if both x and w=greatgrandparentnode  are not nullptr, then make w as parent of x ,if z is left child of w (w->left=this) else if z is right child of w then (w->right=this) .
 //else if x=nullptr and w!=nullptr, if z is left child of w (w->left=nullpt) else if z is right child of w then (w->right=nullptr) . 
 //else if x!= nullptr and w=nullptr then x->parent=nulptr. else nothing to do.
if(greatGrandParentNode!=nullptr)
 {
   updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
 }
  //if both x and z are not nullptr then make x as parent of z and z->right=this.
  //else if x=nullptr and z!=nullptr  then z->right=nullptr.
  //else if x!= nullptr and z=nullptr then x->parent=nulptr. else nothing to do.

  updateAVLParentChild( grandParent, parent, true);
  
 //if both x and y are not nullptr then make x as parent of y and z->right=this.
 //else if x=nullptr and z!=nullptr  then z->right=nullptr.
 //else if x!= nullptr and z=nullptr then x->parent=nulptr. else nothing  
  
 updateAVLParentChild( currNode ,parent, false ); 
  
 

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of grandParent.
  updateAVLParentChild(T2, grandParent, false);
  
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.
int AVLTree:: height(TreeNode *node)
{
  if (node == NULL)
    return -1;
  else if (node->left==nullptr && node->right==nullptr)
    return 0; 
  else if (node->left==nullptr)   
    return (height(node->right)+1);
  else if (node->right==nullptr)
    return (height(node->left)+1);
  else
    return max(height(node->left),height(node->right))+1;
}



int AVLTree::getImbalance(TreeNode* node)
{  
    
  
  return  height(node->left)-height(node->right);
   
}
   
void AVLTree:: updateHeight(TreeNode* node) {
  node->height=max(height(node->left),height(node->right));
  return;
}  
   
bool AVLTree::insert(int jrnyCode, int price)
{       
  TreeNode* node;
  node=new TreeNode(jrnyCode,price);
        
  TreeNode* current= root; 
    
  TreeNode* parentOfcurr=nullptr;
  if(root==nullptr){
    root=new TreeNode(jrnyCode,price);
    return true;
  }  
      
  while (current != nullptr) 
  {
    if (AVLLessThan(current,node)) 
    {
      
      parentOfcurr = current;
      current = current->right;
       
      
    }
    else if (AVLLessThan(node,current) )
    {
    
      parentOfcurr = current;
      current = current->left;
      
    }
    else
    {// current->JourneyCode == JourneyCode
      return false;
    }
  }
  
   
     
  if (current==nullptr)
  {  current=new TreeNode(jrnyCode,price);
    if (AVLLessThan(current,parentOfcurr)){
     parentOfcurr->left=current;
    
    }
   else
   {
     parentOfcurr->right=current;
   }
   parentOfcurr->height= height(parentOfcurr);
   

   while(parentOfcurr!=nullptr)
  
   {
     TreeNode* x=nullptr;
     TreeNode* y= current;
     TreeNode* z=parentOfcurr;
     while(z->parent!=nullptr)
     {
       int n =getImbalance(z);
       if(n<2 && n>-2)
       {  
          x=y;
          y= z;
          z=z->parent;
       }
      }
     if(x!=nullptr && y!=nullptr && z!=nullptr)
     {
        if((AVLLessThan(y,z)) && AVLLessThan(x,y)) 
       {
         return 
      
         rotateLeftLeft(x, y, z);
       }

       else if (AVLLessThan(y,z) && AVLLessThan(y,x))
       {
         return 
         rotateLeftRight(x, y, z);
       }
      
       else if (AVLLessThan(z,y) && AVLLessThan(y,x))
       {
         return
         rotateRightRight(x, y, z);
        }
      
       else 
       {
         return
         rotateRightLeft(x, y, z);
       }
      }
    parentOfcurr=parentOfcurr->parent;
    }
    return true;
  }
  
  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  
  
}



int AVLTree::find(int jrnyCode)
{
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode* node;
  node=new TreeNode(jrnyCode,0); 
  if(currNode==nullptr)
  return -1;
  while (currNode != nullptr) 
  {
    if (AVLLessThan(currNode,node)) 
    {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
      
      
    }
    else if (AVLLessThan(node,currNode)) 
    {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
      currNode->height=currNode->height+1;
      
    }
    
    else  
    {// currNode->JourneyCode == JourneyCode
       
      currNode->getPrice();
        
    }
  }

  return -1;

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


