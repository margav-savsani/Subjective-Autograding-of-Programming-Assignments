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
  if(greatGrandParentNode == nullptr){  //grandParentNode is root
    TreeNode *T3 = parentNode->right;
    
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    parentNode->parent =nullptr;
    root = parentNode;
    if(grandParentNode->right==nullptr){
      grandParentNode->height =0;
    }
    else{
      grandParentNode->height =grandParentNode->height-2;
    }
    return true;
  }
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

  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode == nullptr){
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    currNode->parent =nullptr;
    root = currNode;
    if(grandParentNode->right==nullptr){ //updating the heights manually
      grandParentNode->height=0;
    }
    else{
      grandParentNode->height=grandParentNode->height-1;
    }
    if(parentNode->left==nullptr){
      parentNode->height=0;
    }
    else{
      parentNode->height=parentNode->left->height+1;
    }
    currNode->height=1+max(currNode->left->height,currNode->right->height);
    return true;
  }
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
  updateAVLParentChild(T3, grandParentNode, true);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  // very similar to leftRight
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode == nullptr){
    TreeNode *T2 = currNode->right;
    TreeNode *T3 = currNode->left;
    updateAVLParentChild(parentNode, currNode, false);
    updateAVLParentChild(grandParentNode, currNode, true);
    updateAVLParentChild(T2, parentNode, true);
    updateAVLParentChild(T3, grandParentNode, false);
    currNode->parent =nullptr;
    root = currNode;
    if(grandParentNode->left==nullptr){
      grandParentNode->height=0;
    }
    else{
      grandParentNode->height=grandParentNode->height-1;
    }
    if(parentNode->right==nullptr){
      parentNode->height=0;
    }
    else{
      parentNode->height=parentNode->right->height+1;
    }
    currNode->height=1+max(currNode->right->height,currNode->left->height);
    return true;
  }

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

  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Implement this yourself
  //very similar to leftleft
  TreeNode *greatGrandParentNode = grandParentNode->parent;

  if(greatGrandParentNode == nullptr){
    TreeNode *T3 = parentNode->left;
    updateAVLParentChild(grandParentNode, parentNode, true);
    updateAVLParentChild(T3, grandParentNode, false);
    parentNode->parent=nullptr;
    root = parentNode;
    if(grandParentNode->left==nullptr){
      grandParentNode->height=0;
    }
    else{
      grandParentNode->height=grandParentNode->height-2;
    }
    return true;
  }
  
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

  TreeNode *T3 = parentNode->left;

  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  updateAVLParentChild(currNode, parentNode, false);
  updateAVLParentChild(grandParentNode, parentNode, true);
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

  if (root == nullptr)
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }

  else{
    TreeNode* ins_node = new TreeNode(jrnyCode, price);
    TreeNode * Root= root;
    while(true){
      if((AVLLessThan(Root,ins_node))==true){
        if(Root->right==nullptr){
          updateAVLParentChild(ins_node,Root,false);
          break;
        }
        else{
          Root = Root->right;
          continue;
        }
      }
      else if((AVLLessThan(ins_node,Root))==true){
        if(Root->left==nullptr){
          updateAVLParentChild(ins_node,Root,true);
          break;
        }
        else{
          Root = Root->left;
          continue;
        }
      }
      else{
        break;
      }
    }

  traverseUpAVL(ins_node);//insert normally then traverse up
  return true;
  }
}

//this function finds the point of imabalance in tree (if any) after an insertion and updates the heights of tthe nodes till then
//and rebalances the tree by performing rotations
void AVLTree::traverseUpAVL(TreeNode* node)
{
  if(node==nullptr){
    return;
  }
  TreeNode* node_traversing = node;
  while(true){
    if(node_traversing->parent==nullptr){  //equivalent to it being the root of the tree
      if((node_traversing->left==nullptr)&&(node_traversing->right==nullptr)){
        break;
      }
      else if(node_traversing->right==nullptr){
            if(node_traversing->left->height>=1){
              if(AVLLessThan(node,node_traversing->left)==true){
                rotateLeftLeft(node_traversing->left->left,node_traversing->left,node_traversing);
              }
              else{ 
                rotateLeftRight(node_traversing->left->right,node_traversing->left,node_traversing);
              }
              break;
            }
            else{
              break;
            }
            
      }
      else if(node_traversing->left==nullptr){
        if(node_traversing->right->height>=1){
          if(AVLLessThan(node,node_traversing->right)==true){
            rotateRightLeft(node_traversing->right->left,node_traversing->right,node_traversing);
          }
          else{
            rotateRightRight(node_traversing->right->right,node_traversing->right,node_traversing);
          }
          break;
        }
        else{
          break;
        }
      }
      else{
        if((node_traversing->left->height-node_traversing->right->height)>1){
          if(AVLLessThan(node,node_traversing->left)==true){
            rotateLeftLeft(node_traversing->left->left,node_traversing->left,node_traversing);
          }
          else{
            rotateLeftRight(node_traversing->left->right,node_traversing->left,node_traversing);
          }
        }
        else if((node_traversing->right->height-node_traversing->left->height)>1){
          if(AVLLessThan(node,node_traversing->right)==true){
            rotateRightLeft(node_traversing->right->left,node_traversing->right,node_traversing);
          }
          else{
            rotateRightRight(node_traversing->right->right,node_traversing->right,node_traversing);
          }
        }
        break;
        }
    }
    else{
      if(node_traversing->parent->left==node_traversing){
        if((node_traversing->parent->right==nullptr)||(node_traversing->parent->right->height < node_traversing->parent->left->height)){
          node_traversing->parent->height++;
          if(node_traversing->left==nullptr && node_traversing->right==nullptr){
            node_traversing=node_traversing->parent;
            continue;
          }
          else if(node_traversing->right==nullptr){
            if(node_traversing->left->height>=1){
              if(AVLLessThan(node,node_traversing->left)==true){
                rotateLeftLeft(node_traversing->left->left,node_traversing->left,node_traversing);
              }
              else{ 
                rotateLeftRight(node_traversing->left->right,node_traversing->left,node_traversing);
              }
              break;
            }
            else{
              node_traversing=node_traversing->parent;
              continue;
            }
          } 
          else if(node_traversing->left==nullptr){
            if(node_traversing->right->height>=1){
              if(AVLLessThan(node,node_traversing->right)==true){
                rotateRightLeft(node_traversing->right->left,node_traversing->right,node_traversing);
              }
              else{ 
                rotateRightRight(node_traversing->right->right,node_traversing->right,node_traversing);
              }
              break;
            }
            else{
              node_traversing=node_traversing->parent;
              continue;
            }
          }
          else{
            if((node_traversing->left->height-node_traversing->right->height)>1){
              if(AVLLessThan(node,node_traversing->left)==true){
                rotateLeftLeft(node_traversing->left->left,node_traversing->left,node_traversing);
              }
              else{
                rotateLeftRight(node_traversing->left->right,node_traversing->left,node_traversing);
              }
              break;
            }
            else if((node_traversing->right->height-node_traversing->left->height)>1){
              if(AVLLessThan(node,node_traversing->right)==true){
                rotateRightLeft(node_traversing->right->left,node_traversing->right,node_traversing);
              }
              else{
                rotateRightRight(node_traversing->right->right,node_traversing->right,node_traversing);
              }
              break;
            }
            else{
              node_traversing=node_traversing->parent;
              continue;
            }
          }
        }
        else{
          break;
        }
      }
      else if(node_traversing->parent->right==node_traversing){
        if((node_traversing->parent->left==nullptr)||(node_traversing->parent->left->height < node_traversing->parent->right->height)){
          node_traversing->parent->height++;
          if(node_traversing->left==nullptr && node_traversing->right==nullptr){
            node_traversing=node_traversing->parent;
            continue;
          }
          else if(node_traversing->right==nullptr){
            if(node_traversing->left->height>=1){
              if(AVLLessThan(node,node_traversing->left)==true){
                rotateLeftLeft(node_traversing->left->left,node_traversing->left,node_traversing);
              }
              else{ 
                rotateLeftRight(node_traversing->left->right,node_traversing->left,node_traversing);
              }
              break;
            }
            else{
              node_traversing=node_traversing->parent;
              continue;
            }
          }
          else if(node_traversing->left==nullptr){
            if(node_traversing->right->height>=1){
              if(AVLLessThan(node,node_traversing->right)==true){
                rotateRightLeft(node_traversing->right->left,node_traversing->right,node_traversing);
              }
              else{ 
                rotateRightRight(node_traversing->right->right,node_traversing->right,node_traversing);
              }
              break;
            }
            else{
              node_traversing=node_traversing->parent;
              continue;
            }
          }
          else{
            if((node_traversing->left->height-node_traversing->right->height)>1){
              if(AVLLessThan(node,node_traversing->left)==true){
                rotateLeftLeft(node_traversing->left->left,node_traversing->left,node_traversing);
              }
              else{
                rotateLeftRight(node_traversing->left->right,node_traversing->left,node_traversing);
              }
              break;
            }
            else if((node_traversing->right->height-node_traversing->left->height)>1){
              if(AVLLessThan(node,node_traversing->right)==true){
                rotateRightLeft(node_traversing->right->left,node_traversing->right,node_traversing);
              }
              else{
                rotateRightRight(node_traversing->right->right,node_traversing->right,node_traversing);
              }
              break;
            }
            else{
              node_traversing=node_traversing->parent;
              continue;
            }
          }
        }
        else{
          break;
        }
      }
    }
  }
  return;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

//exactly the same as in BST except that we had to use AVLLessThan instead of BSTLessThan
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
  if(root == nullptr){
    return -1;
  }

  TreeNode * find_node = new TreeNode(jrnyCode,-1);
  TreeNode * Root = root; 
  while (true)
  {
    if((AVLLessThan(Root,find_node))==true){
      if(Root->right == nullptr)
      {
        return -1;
      }
      else{
        Root = Root->right;
        continue;
      }
    }
    else if((AVLLessThan(find_node,Root))==true){
      if(Root->left == nullptr){
        return -1;
      }
      else{
        Root = Root->left;
        continue;
      }
    }
    else{
      return Root->giveNodePrice();
    }
  return -1;
  }
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


