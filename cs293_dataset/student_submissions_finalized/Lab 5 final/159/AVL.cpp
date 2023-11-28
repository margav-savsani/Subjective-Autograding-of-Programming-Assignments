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

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  //there is special case if grandparentnode is root
  if(greatGrandParentNode==nullptr){
     TreeNode*T3=parentNode->right;
    updateAVLParentChild(grandParentNode,parentNode,false);
    updateAVLParentChild(T3,grandParentNode,true);
    parentNode->parent=NULL;
    root=parentNode;
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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

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
  updateAVLParentChild(T3, grandParentNode, true);}

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
  //this is special case when grandparentnode is root of tree
  if(greatGrandParentNode==nullptr){
   TreeNode*T2=currNode->left;
    TreeNode*T3=currNode->right;
    updateAVLParentChild(parentNode,currNode,true);
    updateAVLParentChild(grandParentNode,currNode,false);
    updateAVLParentChild(T2,parentNode,false);
    updateAVLParentChild(T3,grandParentNode,true);
    currNode->parent=NULL;
    root=currNode;
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
  updateAVLParentChild(T3, grandParentNode, true);}

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  //this is special case when grandparentnode is root of tree
  if(greatGrandParentNode==nullptr){
   TreeNode*T2=currNode->left;
    TreeNode*T3=currNode->right;
    updateAVLParentChild(parent,currNode,false);
    updateAVLParentChild(grandParent,currNode,true);
    updateAVLParentChild(T3,parent,true);
    updateAVLParentChild(T2,grandParent,false);
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
    cerr << "Unexpected condition encountered!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

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
  updateAVLParentChild(T3, parent, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T2, grandParent, false);}

  

  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  TreeNode *greatGrandParentNode = grandParent->parent;
  //this is special case when grandparentnode is root of tree
  if(greatGrandParentNode==nullptr){
    // cout<<"C";
    // TreeNode *T3 = parent->left;
    // TreeNode* temp= grandParent;
    // grandParent=parent;
    // grandParent->parent=nullptr;
    // cout<<grandParent->getjrnycode();
    // updateAVLParentChild(currNode,grandParent,false);
    // cout<<"e";
    
    // updateAVLParentChild(T3,temp,false);
    // cout<<"D";
    // updateAVLParentChild(temp,grandParent,true);
    // cout<<"f";
    TreeNode*T3=parent->left;
    updateAVLParentChild(grandParent,parent,true);
    updateAVLParentChild(T3,grandParent,false);
    parent->parent=NULL;
    root=parent;
  }
  else{
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
   TreeNode *T3 = parent->left;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  updateAVLParentChild(T3, grandParent, false);}
  
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{  TreeNode* z=new TreeNode(jrnyCode,price);
  if(root == nullptr){
        root = z;
        updateheight(root);
        return true;
    }
    if(find(jrnyCode)!= -1){
      return false;}
      else{
    TreeNode *x = root;
    while(true){
        if(AVLLessThan(z,x)){
            if(x->left!=nullptr){
                x = x->left;
        }else{
                updateAVLParentChild(z,x,true);
                updateheight(root);
                makebalance(z);
                break;    
            }
        }else{
            if(x->right!=nullptr){
                x = x->right;
            }else{
                updateAVLParentChild(z,x,false);
                updateheight(root);
                makebalance(z);
                break;               
            }
        }
    }}
    return true;
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
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{ TreeNode* z =new TreeNode(jrnyCode,0); 
  if(root==nullptr)return -1;
    TreeNode* x = root;
    while(true){     
        if(AVLGreaterThan(x,z)){     
            if(x->left==nullptr){
                return -1;
            }else{
                x = x->left;
            }
        }else if(AVLLessThan(x,z)){
            if(x->right==nullptr){
               return -1;
            }else{
                x = x->right;
            }
        }
        else{
            return x->getprice();
        }
    }
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
//for every insert makebalance function is called from that getimbalance node function is called
//it goes up the inserted node it checks for imbalanced node using checkbalance function and it it finds
//one it returns that node else it returns null pointer.
TreeNode* AVLTree:: getimbalancenode(TreeNode* r){
    TreeNode *z=r;
    if(z==nullptr){return nullptr;}
    if(checkbalance(z)){z=z->parent;return getimbalancenode(z);}
    else{return z;}
}
//checkbalance function returns true if node is balanced else return false
bool AVLTree:: checkbalance(TreeNode* r){
  int balance;
  if(r->left!=nullptr && r->right!=nullptr) {
    balance=r->left->height - r->right->height;}
  else if(r->left==nullptr && r->right!=nullptr){
    balance=r->right->height;
  }
  else if(r->left!=nullptr && r->right==nullptr){
    balance=r->left->height;
  }
  else{balance=0;}
  if(balance>1 || balance<-1){return false;}
  else{return true;}
}
//for every insert makebalance function is called now it first checks if 
//there is imbalanced ancestor node or not.if not then it does nothing just returns
//if there is imbalanced ancestor node according to lecture we got z node 
//we dont know whether y is left or right child of z and also similarily x
//so we check whether inserted node is in left subtree of z or right subtree of z,
//if it is in left subtree we take y as leftchild of z and viceversa.similarily finding x.
//then we make balance tree by calling appropriate rotate funtcion.
void AVLTree:: makebalance(TreeNode* r){
    bool isleft1;
    bool isleft2;
    TreeNode* z=getimbalancenode(r);
    if(z==nullptr){cout<<1;return;}
    else{
    AVLTree b(z->left,5,6);
    if(b.find(r->getjrnycode()) == -1){
      cout<<"a";
      isleft1=false;
    }
    else{cout<<2;isleft1 = true;}
    if(isleft1){
      AVLTree b1(z->left->left,5,6);
      if(b1.find(r->getjrnycode()) == -1){
      isleft2=false;
      }
      else{cout<<3;isleft2=true;}
    }
    else{
      AVLTree b2(z->right->left,5,6);
      if(b2.find(r->getjrnycode()) == -1){cout<<"b";
      isleft2=false;
      }
      else{isleft2=true;}
    }
    if(isleft1 == true && isleft2 == true){
      rotateLeftLeft(z->left->left,z->left,z);
      updateheight(root);
    }
    else if(isleft1 == true && isleft2==false){
      rotateLeftRight(z->left->right,z->left,z);
      updateheight(root);
    }
    else if(isleft1 == false && isleft2==false){
      rotateRightRight(z->right->right,z->right,z);
      updateheight(root);
    }
    else if(isleft1 == false && isleft2==true){
      rotateRightLeft(z->right->left,z->right,z);
      updateheight(root);
    }
    return;}

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


