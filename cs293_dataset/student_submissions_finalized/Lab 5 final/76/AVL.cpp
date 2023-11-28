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
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(grandParentNode==root){        //if greatgrandparent is null
    TreeNode*T3=parentNode->right;  
    updateAVLParentChild(grandParentNode,parentNode,false); //grandparent is right to parent
    updateAVLParentChild(T3,grandParentNode,true);  //T3 is left to grandparent
    parentNode->parent=NULL;
    root=parentNode;
  }
  
  
  else{
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cout << "Unexpected condition encountered!" << endl;
    return false;
  }

  TreeNode *T3 = parentNode->right;

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);  
  updateAVLParentChild(currNode, parentNode, true);     //currnode is left to parentnode
  updateAVLParentChild(grandParentNode, parentNode, false); //grandparentnode is right to parentnode
  updateAVLParentChild(T3, grandParentNode, true);}         //T3 is left to grandparentnode

  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{


  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(grandParentNode==root){//if greatgrandparentnode is null

    TreeNode*T2=currNode->left;
    TreeNode*T3=currNode->right;
    updateAVLParentChild(parentNode,currNode,true);     //parentnode is left to currnode
    updateAVLParentChild(grandParentNode,currNode,false); //grandparentnode is right to currnode
    updateAVLParentChild(T2,parentNode,false);  //T2 is right to parentnode
    updateAVLParentChild(T3,grandParentNode,true);  //T3 is left to grandparentnode
    currNode->parent=NULL;
    root=currNode;
  }
  else{  


  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cout << "Unexpected condition encountered!" << endl;
    return false;
  }
  TreeNode *T2 = currNode->left;
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, true);     //parentnode is left to currnode
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false); //grandparentnode is right to currnode
  
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
  updateAVLParentChild(T2, parentNode, false);      //T2 is right to parentnode

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);} //T3 is left to grandparentnode

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  TreeNode *greatGrandParentNode = grandParent->parent;
  if(grandParent==root){//if greatgrandparentnode is null
    TreeNode*T2=currNode->left;
    TreeNode*T3=currNode->right;
    updateAVLParentChild(parent,currNode,false);    //parent is right to currnode
    updateAVLParentChild(grandParent,currNode,true);//grandparent is left to currnode
    updateAVLParentChild(T3,parent,true); //T3 is left to parent
    updateAVLParentChild(T2,grandParent,false);//T2 is right to grandparent
    currNode->parent=NULL;
    root=currNode;
  }
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  else{
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cout << "Unexpected condition encountered!" << endl;
    return false;
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
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parent, currNode, false);//parent is right to currnode
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParent, currNode, true);//grandparent is left to currnode
  
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
  updateAVLParentChild(T2, parent, true);//T2 is left to parent 

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);//T3 is right to grandparent
  }

  return true;
  
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  if(grandParent==root){//if greatgrandparent is null
    TreeNode*T3=parent->left;
    updateAVLParentChild(grandParent,parent,true);//grandparent is left to parent
    updateAVLParentChild(T3,grandParent,false);//T3 is right to grandparent
    parent->parent=NULL;
    root=parent;
  }
  else{
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cout << "Unexpected condition encountered!" << endl;
    return false;
  }
  TreeNode *T3 = parent->left;  

  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
  
  updateAVLParentChild(currNode, parent, false);//currnode is right to parent
  
  updateAVLParentChild(grandParent, parent, true);//grandparent is left to parent
  

  
  updateAVLParentChild(T3, grandParent, false);//T3 is right to grandparent
 
  }
  return true;
}



// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  TreeNode *ins; //to store the inserted node
  TreeNode *a;
  TreeNode *b;
  TreeNode *t=new TreeNode(jrnyCode,price);  //to compare jrnycodes in AVLlessthan function
  if(root == NULL){
    root = new TreeNode(jrnyCode,price);        
    return true;
    }
  if(find(jrnyCode)>-1)
    return false;
     TreeNode *curr =root;
    while(true){      
      if(AVLLessThan(curr,t)){
        if(curr->right!=NULL){
          curr=curr->right;//iterating over right tree
        }
        else{
          TreeNode *currn = new TreeNode(jrnyCode,price);
          updateAVLParentChild(currn,curr,false);//currn is right to curr
          ins=currn;            //copying currn to ins
          break;
        }
      }
      else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }
            else{
                TreeNode *lurrn = new TreeNode(jrnyCode,price);
                updateAVLParentChild(lurrn,curr,true);         //lurrn is left to curr      
                ins =lurrn;//copying lurrn to curr
                break;                
            }
        }    
    }
    while(true){
        if(abs(getbalance(ins))<2){//storing the 2 previous ins like in the fibonacci sequence 
          a=b;
          b=ins;
          if((ins==root))
            break;      
          ins=ins->parent;
        }
      else{//ins>b>a
        if((b==ins->left)&&(a==b->left))//setting appropriate rotations based on the relative positions of a,b,ins
          return rotateLeftLeft(a,b,ins);
        if((a==b->left)&&(b==ins->right))
        return rotateLeftRight(a,b,ins);
        if((a==b->left)&&(b==ins->left))
        return rotateRightLeft(a,b,ins);
        if((a==b->right)&&(b==ins->right))
        return rotateRightRight(a,b,ins);
      }
    }

  return true;
    }
  
int AVLTree::getbalance(TreeNode *N)
{   //if null getbalance is 0;else calculated using height function. 
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
int AVLTree::height(TreeNode *N)
{   //height is set to zero if it is null 
    int h=0;
    if(N!=NULL){
      h=max(height(N->left), height(N->right));
      h=h+1;
    }
    return h;    
}


  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures

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

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{

 if (root == NULL){        //returs -1 if root is null
        return -1;
    }

    TreeNode *r = root;
    TreeNode *t=new TreeNode(jrnyCode,-1) ;

    while(true){

        if(r->getJourneyCode() == jrnyCode){
            
            return r->getprice();//if journeycode is found returns price of it
           
            }
        
        else if(AVLLessThan(r,t) == false)//iterating over left and right of root
        {  
             if(r->left==NULL){             
           
              return -1;
            }
            else{
              r=r->left;
            }

        }
        else 
        { 
            if(r->right==NULL){
                
               
                return -1;
            }else{
                r=r->right;
            }
        }

    }
 

return -1; 
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

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


