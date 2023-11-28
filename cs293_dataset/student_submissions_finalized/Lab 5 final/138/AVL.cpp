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
  TreeNode *T3 = parentNode->right;
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  //handling the case of NULL pointer 
  if(greatGrandParentNode==NULL){
    parentNode->parent=NULL;
    root=parentNode;
  }
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
 else{ bool isGPLeftChild;
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

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;
  //handling the case of NULL pointer
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode==NULL){
    currNode->parent=NULL;
    root=currNode;
  }
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  else{
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

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
 // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->left;
  //handling the case of nULL pointer
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  if(greatGrandParentNode==NULL){
    currNode->parent=NULL;
    root=currNode;
  }
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

else{  bool isGPLeftChild;
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
  updateAVLParentChild(parentNode, currNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, true);
  
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
  updateAVLParentChild(T2, parentNode, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, false);

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{ 
  TreeNode *T3 = parentNode->left;
   TreeNode *greatGrandParentNode = grandParentNode->parent;
   //handling case of NULL pointer
  if(greatGrandParentNode==NULL){
    parentNode->parent=NULL;
    root=parentNode;  
  }
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  else{
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
  updateAVLParentChild(currNode, parentNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, true);

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
  updateAVLParentChild(T3, grandParentNode, false);
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
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
  TreeNode* to= new TreeNode(jrnyCode,price);//this is the node to be searched
    TreeNode * parent_ptr;
    TreeNode * child_ptr;
    child_ptr=root;
    parent_ptr=NULL;
    //loops continues till node is found
    while(child_ptr!=NULL){
        if(*child_ptr=*to){
          totalComparisonCost += perComparisonCost;
            //if the node is found,return false as the node is already present
            return false;
        }
        totalComparisonCost += perComparisonCost;
        //traverse the tree to find the node
        parent_ptr=child_ptr;
        if(AVLLessThan(to,child_ptr)){
            //if the price is left move to left
            child_ptr=child_ptr->left;
        }
        else{
            //if the price is more, move to right
            child_ptr=child_ptr->right;
        }
    }
    //attatching the node to the tree
    //comparing its price with the price of the parent node and accordingly joining it in the BST
    //if the price is equal, I have added it to the left
    to->parent=parent_ptr;
    if(parent_ptr==NULL){
        root=to;
        totalParentChildUpdateCost+=perParentChildUpdateCost;
    }
    else{
        if(AVLLessThan(to,parent_ptr)){
            parent_ptr->left=to;
            totalParentChildUpdateCost+=perParentChildUpdateCost;
        }

        else{
            parent_ptr->right=to;
            totalParentChildUpdateCost+=perParentChildUpdateCost;
        }
    }

    // to is the new node inserted
    // parent_ptr is its parent

    bool imb=false;

    while(to!=NULL){
      //if parent_ptr is NULL
      if(parent_ptr==NULL){
        //if both children of root are NULL
        if(to->right==NULL && to->left==NULL){
          break;
        }

        //if left child is NULL
        else if(to->left==NULL){
          to->height=(to->right)->height+1;
          if((to->right)->height>=1){
            parent_ptr=to;
            imb=true;
          }
          break;
        }

        //if right child is NULL
        else if(to->right==NULL){
          to->height=(to->left)->height+1;
          if((to->left)->height>=1){
            parent_ptr=to;
            imb=true;
          }
          break;
        }

        //if no child is NULL
        else{
          to->height=max((to->left)->height+1,(to->right)->height+1);
          if(abs((to->left)->height-(to->right)->height)>1){
            parent_ptr=to;
            imb=true;
          }
          break;
         }
      }

      //parent_ptr is not NULL
      else{
        //if right is to
        if(parent_ptr->right==to){
          //if left is NULL
          if(parent_ptr->left==NULL){
            parent_ptr->height+=1;
            //if imbalance is there in case of left NULL
            if((parent_ptr->right)->height>=1){
              imb=true;
              //if imbalance is true then only break
              break;
            }
          }
          // if left is not NULL
          else{
          //update parent_ptr->height
            parent_ptr->height=max((parent_ptr->left)->height+1,(parent_ptr->right)->height+1);
          }
        }

        //parent_ptr left is to
        else{
          // if right is NULL
          if(parent_ptr->right==NULL){
            parent_ptr->height+=1;
            //check imbalance
            if((parent_ptr->left)->height>=1){
              imb=true;
              //if imbalance is true, then only break
              break;
            }  
          }
            // if right is not NULL
            else{
              //update parent_ptr->height
              parent_ptr->height=max((parent_ptr->left)->height+1,(parent_ptr->right)->height+1);
            }
        }
      }
      //checking for imbalance
      if(parent_ptr->left!=NULL && parent_ptr->right!=NULL){
        if(abs((parent_ptr->left)->height-(parent_ptr->right)->height)>1){
          imb=true;
          break;
        }
      }
      //updation
      to=parent_ptr;
      parent_ptr=parent_ptr->parent;
    }

    //initialising the x and y as right child
    bool yRight=false;
    bool xRight=false;
    //if imbalance is created
    if(imb==true){
      TreeNode*z= parent_ptr;
      TreeNode* y;
      TreeNode* x;

      //fixing y
      if(z->right==NULL){
        y=z->left;
      }
      else if(z->left==NULL){
        y=z->right;
        yRight=true;
      }
      else if ((z->right)->height>(z->left)->height){
        y=z->right;
        yRight=true;
      }
      else{
        y=z->left;
      }
      
      //fixing x
      if(y->right==NULL){
        x=y->left;
      }
      else if(y->left==NULL){
        x=y->right;
        xRight=true;
      }
      
      else if((y->right)->height>(y->left)->height){
        x=y->right;
        xRight=true;
      }
      else if((y->right)->height<(y->left)->height){
        x=y->left;
      }
      else{
        //in case of equal height
        if(y==z->right){
          x=y->right;
          xRight=true;
        }
        else{
          x=y->left;
        }
      }

   //calling appropriate functions and setting heights
   //after the rotation the heights are set accordingly
   //in each case appropriate changes are done

   if(xRight==true && yRight==true){
        rotateRightRight(x,y,z);
        z->height=z->height-2;
        return true;
   }

   else if(xRight==false && yRight==true){
        rotateRightLeft(x,y,z);
        y->height=y->height-1;
        x->height=x->height+1;
        z->height=z->height-2;
        return true;
   }
   else if(xRight==true && yRight==false){
        rotateLeftRight(x,y,z);
        y->height=y->height-1;
        x->height=x->height+1;
        z->height=z->height-2;
        return true;
   }
   else{
        rotateLeftLeft(x,y,z);
        z->height=z->height-2;
        return true;
   }

   }
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
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
  TreeNode * roo;
  roo=root;
  TreeNode * to_find=new TreeNode(jrnyCode,0);

  while(roo!=NULL){
    if(*to_find=*roo){//if the journey code and price match, return true
      totalComparisonCost += perComparisonCost;
      return roo->get_price();
    }
    totalComparisonCost += perComparisonCost;
    if(AVLLessThan(to_find,roo)){//else traverse the tree
      roo=roo->left;
    }

    else{
      roo=roo->right;//else traverse the tree
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


