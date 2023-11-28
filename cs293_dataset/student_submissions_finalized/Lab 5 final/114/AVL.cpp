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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  // If greatgrandparentNode is root, it doesnt have parent
  if (greatGrandParentNode != nullptr) {
    if (greatGrandParentNode->left == grandParentNode) {
      // isGPLeftChild = true;
      updateAVLParentChild(parentNode, greatGrandParentNode, true);
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      // isGPLeftChild = false;
      updateAVLParentChild(parentNode, greatGrandParentNode, false);
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  else {
    // grandParentNode is the root of the tree
    root = parentNode;
    parentNode->parent = nullptr;
  }  
  

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode

  // Assigning x as left of y
  updateAVLParentChild(currNode, parentNode, true);

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

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;


  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode

  // Assigning z as right of y
  updateAVLParentChild(grandParentNode, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);

  //Updating height
  grandParentNode->height = h(grandParentNode->left, grandParentNode->right);
  parentNode->height = h(parentNode->left, parentNode->right);


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
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  // If greatgrandparentNode is root, it doesnt have parent
  if (greatGrandParentNode != nullptr) {
    if (greatGrandParentNode->left == grandParentNode) {
      // isGPLeftChild = true;
      updateAVLParentChild(currNode, greatGrandParentNode, true);
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      // isGPLeftChild = false;
      updateAVLParentChild(currNode, greatGrandParentNode, false);
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  else {
    // grandParentNode is the root of the tree
    root = currNode;
    currNode->parent = nullptr;

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
  // updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  
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
       
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode

  // Assigning y as left of x
  updateAVLParentChild(parentNode, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode

  // Assigning z as right of x
  updateAVLParentChild(grandParentNode, currNode, false);

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode

  // Assigning T2 as right of y
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode

  // Assigning T3 as left of z
  updateAVLParentChild(T3, grandParentNode, true);

  // Updating the height
  parentNode->height = h(parentNode->left, parentNode->right);
  grandParentNode->height = h(grandParentNode->left, grandParentNode->right);
  currNode->height = h(currNode->left, currNode->right);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  // If greatgrandparentNode is root, it doesnt have parent
  if (greatGrandParentNode != nullptr) {
    if (greatGrandParentNode->left == grandParentNode) {
      // isGPLeftChild = true;
      updateAVLParentChild(currNode, greatGrandParentNode, true);
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      // isGPLeftChild = false;
      updateAVLParentChild(currNode, greatGrandParentNode, false);
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  else {
    // grandParentNode is the root of the tree
    root = currNode;
    currNode->parent = nullptr;

  }  

  // updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Assigning z as left of y
  updateAVLParentChild(grandParentNode, currNode, true);

  // Assigning y as right of x
  updateAVLParentChild(parentNode, currNode, false);

  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  
  // Assigning T3 as left of y
  updateAVLParentChild(T3, parentNode, true);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode

  // Assigning T2 as right of z
  updateAVLParentChild(T2, grandParentNode, false);

  // Updating height
  grandParentNode->height = h(grandParentNode->left, grandParentNode->right);
  parentNode->height = h(parentNode->left, parentNode->right);
  currNode->height = h(currNode->left, currNode->right);
  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // If greatgrandparentNode is root, it doesnt have parent
 if (greatGrandParentNode != nullptr) {
    if (greatGrandParentNode->left == grandParentNode) {
      // isGPLeftChild = true;
      updateAVLParentChild(parentNode, greatGrandParentNode, true);
    }
    else if (greatGrandParentNode->right == grandParentNode) {
      // isGPLeftChild = false;
      updateAVLParentChild(parentNode, greatGrandParentNode, false);
    }
    else {
      cerr << "Unexpected condition encountered!" << endl;
      return false;
    }
  }
  else {
    // grandParentNode is the root of the tree
    root = parentNode;
    parentNode->parent = nullptr;
  }  


  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = parentNode->left;

  // Assigning z as left of y
  updateAVLParentChild(grandParentNode, parentNode, true);

  // Assigning x as right of y
  updateAVLParentChild(currNode, parentNode, false);
  
  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode

  // Assigning T2 as right of z
  updateAVLParentChild(T2, grandParentNode, false);

  // Updating height
  grandParentNode->height = h(grandParentNode->left, grandParentNode->right);
  parentNode->height = h(parentNode->left, parentNode->right);
  
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

  if (root == nullptr){

    root = new TreeNode(jrnyCode, price);
    root->height = 0;   


  } else {
    
    struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

    // new TreeNode that I am going to insert
    TreeNode* dummy = new TreeNode(jrnyCode, price);

    // Finds for right location to insert dummy
    while (currNode != nullptr) {

        if (AVLLessThan(currNode, dummy)) {
          parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if (AVLLessThan(dummy, currNode)) {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else { 
            return false;
        }
    
    }


        // inserting TreeNode dummy and setting its parent
        currNode = dummy;
        dummy->parent = parentOfCurrNode;


    // Setting child of parent of dummy
    if (AVLLessThan(currNode, parentOfCurrNode)) {
        parentOfCurrNode->left = currNode;
    } else {
        parentOfCurrNode->right = currNode;
    }

    // I can convert BST into AVL only if height of root is greater than 1. 
    // But, since we haven't updated height yet, condition is root greater than 0.
    if (root->height > 0) {
        TreeNode *grandParentNode = currNode;
        TreeNode *ParentNode = nullptr;
        TreeNode *ChildNode = nullptr;

        //Recurses till grandParentNode is root
        while(grandParentNode != nullptr){

            // h function returns updated height by giving its children as inputs
            grandParentNode->height = h(grandParentNode->left, grandParentNode->right);


            if (grandParentNode->left != nullptr && grandParentNode->right != nullptr){
              int diff = grandParentNode->left->height - grandParentNode->right->height;

              // if the imbalance is -2 or less, 2 or more, we have to update based order of grandparent, parent and child
              if (diff > 1 || diff < -1){
                if (AVLLessThan(ParentNode, grandParentNode)) {
                  if (AVLLessThan(ChildNode, ParentNode)) {
                      rotateLeftLeft(ChildNode, ParentNode, grandParentNode);
                  } else {
                    rotateLeftRight(ChildNode, ParentNode, grandParentNode);
                  } 
                } else {
                  if (AVLLessThan(ChildNode, ParentNode)){
                    rotateRightLeft(ChildNode, ParentNode, grandParentNode);
                  } else {
                    rotateRightRight(ChildNode, ParentNode, grandParentNode);
                  }
                }
              }

            }  else if (grandParentNode->left == nullptr && grandParentNode->right != nullptr){


              // if grandparent has no left child and right child has height more than 1, we have to update based order of grandparent, parent and child
              if (grandParentNode->height > 1){
                if (AVLLessThan(ParentNode, grandParentNode)) {
                  if (AVLLessThan(ChildNode, ParentNode)) {
                      rotateLeftLeft(ChildNode, ParentNode, grandParentNode);
                      grandParentNode->height = h(grandParentNode->left, grandParentNode->right);
                      ParentNode->height = h(ParentNode->left, ParentNode->right);
                  } else {
                    rotateLeftRight(ChildNode, ParentNode, grandParentNode);
                  } 
                } else {
                  if (AVLLessThan(ChildNode, ParentNode)){
                    rotateRightLeft(ChildNode, ParentNode, grandParentNode);
                  } else {
                    rotateRightRight(ChildNode, ParentNode, grandParentNode);
                  }
                }

              }

            } else if (grandParentNode->right == nullptr && grandParentNode->left != nullptr){

              // if grandparent has no right child and left child has height more than 1, we have to update based order of grandparent, parent and child
              if (grandParentNode->height > 1){
                if (AVLLessThan(ParentNode, grandParentNode)) {
                  if (AVLLessThan(ChildNode, ParentNode)) {
                      rotateLeftLeft(ChildNode, ParentNode, grandParentNode);
                  } else {
                    rotateLeftRight(ChildNode, ParentNode, grandParentNode);
                  } 
                } else {
                  if (AVLLessThan(ChildNode, ParentNode)){
                    rotateRightLeft(ChildNode, ParentNode, grandParentNode);
                  } else {
                    rotateRightRight(ChildNode, ParentNode, grandParentNode);
                  }
                }
              }

            }


          // We have to update child, parent, grandparent as we are moving upwards till we find root
          ChildNode = ParentNode;
          ParentNode = grandParentNode;
          grandParentNode = grandParentNode->parent;
        }

    } else {

      // If height is not greater than 1, we will work it as Binary Tree
      while (parentOfCurrNode != nullptr){
        
        parentOfCurrNode->height = h(parentOfCurrNode->left, parentOfCurrNode->right);

        parentOfCurrNode = parentOfCurrNode->parent;
      
      }

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

  TreeNode *temp = root;

  TreeNode* dummy = new TreeNode(jrnyCode, 0);

  // It finds for the TreeNode till we reach the bottom
  while(temp != NULL){
    if(AVLEqualTo(temp, dummy)){
      return 1;
    }
    else if(AVLLessThan(dummy, temp)){
      temp = temp->left;
    }
    else{
      temp = temp->right;
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
  TreeNode *temp = root;
  TreeNode* dummy = new TreeNode(jrnyCode, 0);

    while(temp != NULL){

        if(AVLEqualTo(dummy, temp)){

            if (temp == root){
                if (temp->left == NULL && temp->right == NULL){
                    delete temp;
                    root = NULL;
                    return true;

                } else {

                    if (temp->left == NULL){
                        root = temp->right;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else if (temp->right == NULL){
                        root = temp->left;
                        root->parent = NULL;
                       
                        delete temp;
                        return true;

                    } else {
                        if (temp->right->left != NULL){

                            TreeNode *temp2 = temp->right->left;

                            while(temp2->left != NULL){
                                temp2 = temp2->left;
                            }

                            // root->JourneyCode = temp2->JourneyCode;
                            // root->price = temp2->price;

                            // To copy values of temp2 to root
                            Equate(root, temp2);


                            if(temp2->right != NULL){
                                temp2->parent->left = temp2->right;
                                temp2->right->parent = temp2->parent;
                            } else {
                                temp2->parent->left = NULL;
                            }

                            // root->height = h(root->left, root->right);
                            // temp2->parent->height = h(temp2->parent->left, temp2->parent->right);

                            TreeNode* dumm = temp2->parent;

                            while (dumm != NULL){
                              dumm->height = h(dumm->left, dumm->right);
                              dumm = dumm->parent;
                            }

                            delete temp2;
                            delete dumm;
                            return true;

                        } else {

                            temp->right->left = root->left;
                            temp->right->left->parent = temp->right;
                            root = temp->right;
                            root->parent = NULL;

                            root->height = h(root->left, root->right);

                            delete temp;
                            return true;
                        }
                    }

                }

            } else if(temp->left == NULL && temp->right == NULL){

                if(temp->parent->left == temp){
                    temp->parent->left = NULL;
                }
                else{
                    temp->parent->right = NULL;
                }

                // temp->parent->height = h(temp->parent->left, temp->parent->right);

                TreeNode* dumm = temp->parent;

                while (dumm != NULL){
                  dumm->height = h(dumm->left, dumm->right);
                  dumm = dumm->parent;
                }

                delete temp;
                delete dumm;
                return true;
            } else if(temp->left == NULL){

                if(temp->parent->left == temp){

                    temp->parent->left = temp->right;
                    temp->right->parent = temp->parent;

                }
                else{

                    temp->parent->right = temp->right;
                    temp->right->parent = temp->parent;

                }

                // temp->parent->height = h(temp->parent->left, temp->parent->right);

                TreeNode* dumm = temp->parent;

                while (dumm != NULL){
                  dumm->height = h(dumm->left, dumm->right);
                  dumm = dumm->parent;
                }

                    delete temp;
                    delete dumm;
                    return true;


            } else if(temp->right == NULL){

                if(temp->parent->left == temp){
                    temp->parent->left = temp->left;
                }
                else{
                    temp->parent->right = temp->left;
                }

                temp->left->parent = temp->parent;
                // temp->parent->height = h(temp->parent->left, temp->parent->right);
                
                TreeNode* dumm = temp->parent;

                while (dumm != NULL){
                  dumm->height = h(dumm->left, dumm->right);
                  dumm = dumm->parent;
                }

                delete temp;
                delete dumm;
                return true;
            } else {

                TreeNode *temp2 = temp->right;

                while(temp2->left != NULL){
                    temp2 = temp2->left;
                }

                // The next two lines will be done by Equate function given next
                // temp->JourneyCode = temp2->JourneyCode;
                // temp->price = temp2->price;
                Equate(temp, temp2);

                if (temp2->parent == temp){
                    if (temp2->right != NULL){
                        temp2->parent->right = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->right = NULL;
                    }
                

                } else {

                    if (temp2->right != NULL){
                        temp2->parent->left = temp2->right;
                        temp2->right->parent = temp2->parent;
                    } else {
                        temp2->parent->left = NULL;
                    }

                }

                  // temp2->parent->height = h(temp2->parent->left, temp2->parent->right);
                  // temp->height = h(temp->left, temp->right);

                  TreeNode* dumm = temp2;

                  while (dumm != NULL){
                    dumm->height = h(dumm->left, dumm->right);
                    dumm = dumm->parent;
                  }

                delete temp2;
                delete dumm;
                return true;
            }

        // temp->price > price
        } else if(AVLLessThan(dummy, temp)){
            temp = temp->left;
        } else {
            temp = temp->right;

        }

    }

    return false;

}


