#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <cmath>
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
   if(grandParentNode->parent==NULL) { // if there is no greatgrandparent
    TreeNode* t2 = parentNode->right;  // storing the address of right child of parent 
    updateAVLParentChild(grandParentNode,parentNode,false); //updating nodes
    updateAVLParentChild(t2,grandParentNode,true);
    grandParentNode->height -= 2; // after the rotation, height of grandparent will be decreased by 2
    parentNode->parent=NULL; // as greategrandparent = NULL
    root=parentNode; // updating the root pointer
    return true;
  }
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
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
 TreeNode *T3 = parentNode->right;  // storing the address of right child of parent 

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, true); //updating nodes
  updateAVLParentChild(grandParentNode, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  grandParentNode->height -=2; // after the rotation, height of grandparent will be decreased by 2
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  if(grandParentNode->parent==NULL) { // if there is no greatgrandparent
    TreeNode* t2 = currNode->left;// storing the address of left child of currNode
    TreeNode* t3 = currNode->right;// storing the address of right child of currNode
    currNode->parent=NULL; // removing the connection b/w currNode and parentNode
    parentNode->right=NULL;
    updateAVLParentChild(parentNode,currNode,true);
    updateAVLParentChild(grandParentNode,currNode,false); // updating nodes
    updateAVLParentChild(t2, parentNode, false);
    updateAVLParentChild(t3, grandParentNode, true);
    currNode->height +=1; // currNode height will be incresed by 1
    grandParentNode->height -=2; // grandparent will descend by 2 steps
    parentNode->height--; // parentNode will descend by 1 step 
    root=currNode; // updating the root
    return true;
  }

  TreeNode *greatGrandParentNode = grandParentNode->parent;

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

  TreeNode *T2 = currNode->left; // storing the address of left child of currNode
  TreeNode *T3 = currNode->right; // storing the address of right child of currNode

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, true);
  updateAVLParentChild(grandParentNode, currNode, false); //updating the nodes
  updateAVLParentChild(T2, parentNode, false);
  updateAVLParentChild(T3, grandParentNode, true);
  currNode->height ++;  // currNode height will be incresed by 1
  grandParentNode->height -=2;  // grandparent will descend by 2 steps
  parentNode->height--; // parentNode will descend by 1 step 
  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
 if(grandParentNode->parent==NULL) { // if there is no greatgrandparent
    TreeNode* t2 = currNode->right; // storing the address of left child of currNode
    TreeNode* t3 = currNode->left; // storing the address of right child of currNode
    currNode->parent=NULL; // removing the connection b/w currNode and parentNode
    parentNode->right=NULL;
    updateAVLParentChild(parentNode,currNode,false);
    updateAVLParentChild(grandParentNode,currNode,true);
    updateAVLParentChild(t2, parentNode, true);
    updateAVLParentChild(t3, grandParentNode, false);
    currNode->height +=1; // currNode height will be incresed by 1
    grandParentNode->height -=2; // grandparent will descend by 2 steps
    parentNode->height--; // parentNode will descend by 1 step 
    root=currNode; // updating the root
    return true;
  }

  TreeNode *greatGrandParentNode = grandParentNode->parent;

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

  TreeNode *T2 = currNode->right;
  TreeNode *T3 = currNode->left;

  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(parentNode, currNode, false);
  updateAVLParentChild(grandParentNode, currNode, true);
  updateAVLParentChild(T2, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  currNode->height +=1; // currNode height will be incresed by 1
  grandParentNode->height -=2; // grandparent will descend by 2 steps
  parentNode->height--; // parentNode will descend by 1 step 
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  if(grandParentNode->parent==NULL) {// if there is no greatgrandparent
    TreeNode* t2 = parentNode->left; // storing the address of left child of parent
    updateAVLParentChild(grandParentNode,parentNode,true);
    updateAVLParentChild(t2,grandParentNode,false); // updating nodes
    grandParentNode->height -= 2; // after the rotation, height of grandparent will be decreased by 2
    parentNode->parent=NULL; // as greategrandparent = NULL
    root=parentNode; // as greategrandparent = NULL
    return true;
  }
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
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
 TreeNode *T3 = parentNode->left; // storing the address of left child of parent

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false); //updating nodes
  updateAVLParentChild(grandParentNode, parentNode, true);
  updateAVLParentChild(T3, grandParentNode, false);
  grandParentNode->height -= 2; // after the rotation, height of grandparent will be decreased by 2
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

TreeNode* AVLTree::find_tree(TreeNode* x,int JourneyCode) {
        TreeNode* tmp =new TreeNode(JourneyCode,1); // 1 is arbitarty price value
        
        if(x == NULL) {
            return NULL;
        }
        bool x_lt = AVLLessThan(x,tmp); // using less_than function to satisfy our needs 
        bool x_gt = AVLLessThan(tmp,x); 
        if(!x_lt && !x_gt) { // == is !> and !<
            return x;
        }
        if(x_gt) {
            return find_tree(x->left,JourneyCode); // recursive search in left tree
        }
        else {
            return find_tree(x->right,JourneyCode); // recursive search in right tree
        }
        return NULL;
}

int AVLTree::find(int jrnyCode)
{
  if(find_tree(root,jrnyCode)==NULL) return 0; // if we dont find a node with the required Journeycode.
  return 1;
}

bool AVLTree::insert(int jrnyCode, int price)
{
    cnt++;
    TreeNode *x,*y,*z;
    y=NULL;
    x=root; // A pointer pointed to root node.
    z=new TreeNode(jrnyCode,price); // Creating a new node with given parameters
    while(x!=NULL) {
      y=x;
      if(AVLLessThan(z,x)){ // moving left if z < x
        x= x->left;
      }
      else x= x->right; // else right
    }
      z->parent = y;
      if(y==NULL) {
        root=z;  // Insertion of first node into the tree
        return true;
      }
      else {
        if(AVLLessThan(z,y)) y->left=z; //checking the value to insert the node into corrcet place
        else y->right = z;
      }
        bool isleft = AVLLessThan(z,y);
        updateAVLParentChild(z,y,isleft);
        z->height=0; // intialising the heigth to 0
        TreeNode* tmp=z; // storing the address of new node

        TreeNode *a,*b,*c;
        // 3 pointers to store curr,parent,grandparent
        c = NULL;
        b = NULL;
        a = tmp;

        if(cnt==1) return true; // no imbalance at first node
        if(cnt==2) {
            a->parent->height++; // no imabalnce with 2 nodes too
            return true;
        }
        if(cnt==3){
          if(a->parent->parent==NULL) {
            return true;  // if the tree is already balanced
          }
          
        }
            // updating b,c
            b = a->parent;
            c = b->parent;

            int l=-1,r=-1;
          if(b->left!=NULL) l=b->left->height;
          if(b->right!=NULL) r=b->right->height;
          b->height = 1+max(l,r);
          // updating the heigths of b,c after insertion at a
            int lef_ht=-1,ri_ht=-1;
          if(c->left!=NULL) lef_ht=c->left->height;
          if(c->right!=NULL) ri_ht=c->right->height;
          c->height = 1+max(lef_ht,ri_ht);
          
          while(c!=NULL) { // reaching the root
            bool is_left = AVLLessThan(b,c);
            if(is_left) {
              if(c->right!=NULL) { // if right node is not null
                if(abs(c->right->height - c->left->height >= 2)) { // condition of imbalance
                  break;
                }
                else { // if there is no tree/node to the right of c
                  a=b;
                  b=c;
                  if(c->parent == NULL) break; // reched the root.
                  c=c->parent; // updating c
                  int l=-1,r=-1;
                  if(c->left!=NULL) l = c->left->height;
                  if(c->right!=NULL) r = c->right->height;
                   c->height = 1+max(l,r);
                  // updating height of c after moving it to c->parent
                }
              }
              else {
                if(c->left->height >=1 ) break; // imbalanced
                else {
                  a=b;
                  b=c;
                  if(c->parent == NULL) break;
                  c=c->parent;
                  // updating height of c after moving it to c->parent
                  int l=-1,r=-1;
                  if(c->left!=NULL) l=c->left->height;
                  if(c->right!=NULL) r=c->right->height;
                  c->height = 1+max(l,r);
                }
              }
            }
            if(!is_left) {
              if(c->left!=NULL) {// if left node is not null
                if(abs(c->right->height - c->left->height >= 2)) { // imbalance spotted
                  break;
                }
                else {
                  a=b;
                  b=c;
                  if(c->parent == NULL) break; // reached root
                  c=c->parent;
                  // updating height of c after moving it to c->parent
                  int l=-1,r=-1;
                  if(c->left!=NULL) l=c->left->height;
                  if(c->right!=NULL) r=c->right->height;
                  c->height = 1+max(l,r);
                }
              }
              else {
                if(c->right->height >=1 ) break;
                else {
                  a=b;
                  b=c;
                  if(c->parent == NULL) break; // reached root
                  c=c->parent;
                  // updating height of c after moving it to c->parent
                  int l=-1,r=-1;
                  if(c->left!=NULL) l=c->left->height;
                  if(c->right!=NULL) r=c->right->height;
                  c->height = 1+max(l,r);
                }
              }
            }

          }
      
        // identifying a,b,c completed
       
        TreeNode* var = c;
        
        if(c->left==b) {
          if(a==b->left)  {
            rotateLeftLeft(a,b,c);
          }
          else if(a==b->right){
            rotateLeftRight(a,b,c);
          }
        }
        else if(c->right==b) {
          if(a==b->left) {
            rotateRightLeft(a,b,c);
            }
          else if(a==b->right) {
            rotateRightRight(a,b,c);
          }
        }
        
  return true;
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


