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
  bool isGPLeftChild;
  if(greatGrandParentNode!=NULL){
    
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
  }
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;
 
  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  // updateAVLParentChild(currNode, parentNode, true);
  
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

  //height updation
  grandParentNode->height = grandParentNode->height - 2;
  // printBinaryTree(parentNode, "", 1);

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
  bool isGPLeftChild;
  if(greatGrandParentNode!=NULL){
    
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
  }  
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
  

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

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

  //height updation
  grandParentNode->height = grandParentNode->height - 2;
  parentNode->height -= 1;
  currNode->height += 1;

  // printBinaryTree(currNode, "", 1);

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{

  TreeNode *greatGrandParentNode = grandParentNode->parent;
  bool isGPLeftChild;
  if(greatGrandParentNode!=NULL){
    
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
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

 
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  updateAVLParentChild( grandParentNode, currNode, true);

  updateAVLParentChild( parentNode, currNode, false );

  updateAVLParentChild(T2, grandParentNode, false);

  updateAVLParentChild(T3, parentNode, true);

   //height updation
  grandParentNode->height = grandParentNode->height - 2;
  parentNode->height -= 1;
  currNode->height += 1;

  // printBinaryTree(currNode, "", 1);

  
  return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  bool isGPLeftChild;
  if(greatGrandParentNode!=NULL){
    
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
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);
  
  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = parentNode->left;

  updateAVLParentChild( grandParentNode, parentNode, true);

  updateAVLParentChild(currNode, parentNode,  false );

  updateAVLParentChild(T2, grandParentNode, false);
  
   //height updation
  grandParentNode->height = grandParentNode->height - 2;

  // printBinaryTree(parentNode, "", 1);
  
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

  TreeNode* x = root; //for checking
  TreeNode* y = NULL; //for pointing to the parent
  TreeNode* node = new TreeNode(jrnyCode, price);

  if(root == NULL){
    root = node; //no balancing req
    return true;
  }

  while(x != NULL){
    y = x;
    if( AVLLessThan(node, x) )
      x = x->left;
    else
      x = x->right;
  }
  
  // node->parent = y;

  // if( AVLLessThan(node, y))
  //   y->left = node;
  // else
  //   y->right = node;

  if( AVLLessThan(node, y))
    updateAVLParentChild(node,y,true);
  else
    updateAVLParentChild(node,y,false);

    // x = node->parent;
    // if(x->right==NULL || x->left==NULL){
    //   x->height += 1;
    // }

    // x = x->parent;
    // while(x!=NULL){

    //   if(x->right==NULL){
    //     x->height = x->left->height + 1;
    //   }
    //   else if(x->left==NULL){
    //     x->height = x->right->height + 1;
    //   }
    //   else{
    //     x->height = max(x->left->height, x->right->height) + 1;
    //   }

    //   x = x->parent;
    // }
  TreeNode* temp = node->parent;  
  TreeNode *currNode = node->parent;
  TreeNode *parentNode = node->parent->parent;
  int newht;

  
  x = y;
  while(x!=NULL){
    if(x->left == NULL ){
      // if(x->right==NULL)
      x->height = x->right->height + 1;
      if(x->height > 1){//imbalance
        if(x->right->right!=NULL){
          temp = x->right;
          rotateRightRight(x->right->right, x->right, x);
          x = temp;
          if(x->parent==NULL)
            root = x;
          // return true;
        }
        else{
          temp = x->right->left;
          rotateRightLeft(x->right->left, x->right, x);
          x = temp;
          if(x->parent==NULL)
            root = x;
        }
      }
    }
    else if( x->right == NULL ){
      x->height = x->left->height + 1;
      if(x->height > 1){//imbalance
        if(x->left->left!=NULL){
          temp = x->left;
          rotateLeftLeft(x->left->left, x->left, x);
          x = temp;
          if(x->parent==NULL)
            root = x;
        }
        else{
          temp = x->left->right;
          rotateLeftRight(x->left->right, x->left, x);
          x = temp;
          if(x->parent==NULL)
            root = x;
        }
      }
    }
    else{ 
      newht = max(x->left->height, x->right->height) + 1;    
      if( newht == x->height ){
        return true;
      }
      else{
        x->height = newht;

        if(abs(x->left->height - x->right->height) > 1){
          
          if(parentNode==x->left && currNode==parentNode->left){
            rotateLeftLeft(currNode, parentNode, x);
            x = parentNode;
            if(x->parent==NULL)
              root = x;
          }
          else if(parentNode==x->left && currNode==parentNode->right){
            rotateLeftRight(currNode, parentNode, x);
            x = currNode;
            if(x->parent==NULL)
              root = x;
          }
          else if(parentNode==x->right && currNode==parentNode->left){
            rotateRightLeft(currNode, parentNode, x);
            x = currNode;
            if(x->parent==NULL)
              root = x;
          }
          else{
            rotateRightRight(currNode, parentNode, x);
            x = parentNode;
            if(x->parent==NULL)
              root = x;
          }

        }
        
      }

    }
    
    currNode = parentNode;
    parentNode = x;
    x = x->parent;
    
  }

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
  // printBinaryTree(root,"",1);
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

   TreeNode* temp = root; 
   TreeNode* dummy = new TreeNode( jrnyCode, 0); //price arbitrary since comparision is on jc

    while(temp != NULL){
        if(!AVLLessThan(temp, dummy) && !AVLLessThan(dummy, temp)){
            return 1;
        }
        if(AVLLessThan(dummy, temp)){
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
//..................................................................
// TreeNode* AVLTree::succ( TreeNode* x){
//     if(x->right!=NULL)
//         return AVLTree::getMinimum(x->right);
//     else{
//         TreeNode* y = x->parent;
//         if(y==NULL)
//             return NULL;
//         while( y != NULL && x==y->right){
//             x=y;
//             y=y->parent;
//         }
//         return y;
//     }
// }

// TreeNode* AVLTree::getMinimum(TreeNode* t){
//     TreeNode* temp = t;
//     TreeNode* temp2 = NULL;

//     if(temp==NULL){
//         return NULL;
//     }

//     while( temp != NULL){
//         temp2 = temp;
//         temp = temp->left;
//     }
    
//     return temp2; 
// }



bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.
    // if( !BST::find(JourneyCode,price) ){
    //     return false;
    // }
    // else{
  //       TreeNode* temp = root;
  //       TreeNode* x = NULL;
  //       TreeNode* node = new TreeNode(jrnyCode, 0);

  //       while( !AVLLessThan(node, temp) && !AVLLessThan(temp,node) && temp!=NULL ){
  //           if(AVLLessThan(node, temp) ){
  //               temp = temp->left;
  //           }
  //           else{
  //               temp = temp->right;
  //           }
  //       }
  //       if(temp==NULL)  
  //           return false;

  //       // if(temp->JourneyCode == JourneyCode){ //node to be deleted is found, its temp why to check again if temp is not null means found

  //           //------when temp is the leaf------
  //           if(temp->left==NULL && temp->right==NULL){ 
                
  //               if(temp->parent==NULL){ //deleting root node
  //                   root = NULL; //tree deleted
  //                   return true;
  //               }
  //               if(temp->parent->left == temp){ //temp is the leftchild of its parent
  //                   x = temp->parent;
  //                   updateAVLParentChild(NULL, temp->parent, true);
  //                   // temp->parent->left = NULL; //temp deleted
  //                   // return true;
  //                   temp = x;
  //               }
  //               else{ 
  //                   x = temp->parent;
  //                   updateAVLParentChild(NULL, temp->parent, false);
  //                   // temp->parent->right = NULL; //temp being rightchild
  //                   // return true;
  //                   temp = x;
  //               }
  //           } 
  //           //---------temp has only one child--------
  //           else if(temp->left==NULL || temp->right==NULL){

  //               TreeNode* p,  *notNullChild;
  //               p = temp->parent;  //p is the parent of temp

  //               //notNullChild is the only not NULL child of temp
  //               if(temp->left==NULL){
  //                   notNullChild=temp->right;
  //               }
  //               else{
  //                   notNullChild = temp->left;
  //               }
         
  //               if(p==NULL){
  //                   root = notNullChild;
  //                   root->parent=NULL;
  //                   return true;
  //               }
  //               // cout<<"oh no";
  //               if(p->left == temp){ //temp is the leftchild of p
  //                   // p->left =  notNullChild;
  //                   // notNullChild->parent = p;
  //                   x = temp->parent;
  //                   updateAVLParentChild( notNullChild, p, true);
  //                   // return true;
  //                   temp = x;
  //               }
  //               else{ //temp being right child  
  //                   // p->right = notNullChild;
  //                   // notNullChild->parent = p;
  //                   x = temp->parent;
  //                   updateAVLParentChild( notNullChild, p, false);
  //                   // return true;
  //                   temp = x;
  //               }
  //           }
  //           //---------temp has two children---------
  //           else{

  //               TreeNode* suc = AVLTree::succ(temp);
  //               x = suc->parent;
  //               bool yes = AVLTree::remove(suc->getjc());
  //               if(!yes)
  //                   return false;
  //               updateAVLParentChild(temp->left, suc, true);
  //               updateAVLParentChild(temp->right, suc, false);
  //               if(temp->parent==NULL)
  //                 root = suc;
  //               else{
  //                 if(temp->parent->left==temp)//temp is the left child
  //                   updateAVLParentChild(suc, temp->parent, true);
  //                 else
  //                   updateAVLParentChild(suc, temp->parent, false);
  //               }

  //               temp = x;
  //           }

  //       // }

  //   // } 

  // // It is your responsibility to find out the right x, y, z (or currNode,
  // // parentNode, grandParentNode) following Prof. Garg's lectures
  // //
  // // Once you identify these correctly, simply invoking the appropriate
  // // rotation(s) should do the job.
  // // You don't even need to invoke rotation twice for the double
  // // rotations -- the way rotationLeftRight is implemented, and
  // // rotationRightLeft should be implemented, you should be able to achieve
  // // the effect of the double rotation using one invokation of the
  // // appropriate member function.

  // // You MUST use only AVLLessThan to compare two journey codes.  You
  // // can create a new node containing the journey code to be searched
  // // (along with some arbitrary price) and invoke AVLLessThan on the
  // // current node in the tree that you are inspecting and the new node
  // // to do your comparison.

  // // REMEMBER to update the height of appropriate nodes in the tree
  // // after a successful deletion.
  //   TreeNode *x1, *x2, *x3, *currNode, *parentNode;
  //   int newht;
  //   x = temp;
  //   if(x->right==NULL && x->left==NULL){
  //       x->height = 0;
  //     }
  //   else if(x->right==NULL)
  //       x->height = x->left->height+1;
  //   else if(x->left==NULL)
  //       x->height = x->right->height+1;

  //   while(x!=NULL){

  //     if(x->left==NULL || x->right==NULL){
  //       if(x->height > 1){
  //         x1 = childWithMaxNodes(x->left, x->right);
  //         if(x1 == x->left){
  //           x2 = childWithMaxNodes(x1->left, x1->right);
  //           if(x2 == x1->left){
  //             rotateLeftLeft(x2, x1, x);
  //             x = x1;
  //           }else{
  //             rotateLeftRight(x2, x1, x);
  //             x = x2;
  //           }
  //         }else{
  //           x2 = childWithMaxNodes(x1->left, x1->right);
  //           if(x2==x1->left){
  //             rotateRightLeft(x2, x1, x);
  //             x = x2;
  //           }else{
  //             rotateRightRight(x2, x1, x);
  //             x = x1;
  //           }
  //         }
  //       }
  //       cout<<"after1\n";
  //     }
  //     else{
  //       newht = max(x->left->height, x->right->height) + 1;    
  //       // if( newht == x->height ){
  //       //   return true;
  //       // }
  //       // else{
  //         x->height = newht;
  //         cout<<"after2\n";

  //         if(abs(x->left->height - x->right->height) > 1){
            
  //           if(parentNode==x->left && currNode==parentNode->left){
  //             rotateLeftLeft(currNode, parentNode, x);
  //             x = parentNode;
  //             if(x->parent==NULL)
  //               root = x;
  //           }
  //           else if(parentNode==x->left && currNode==parentNode->right){
  //             rotateLeftRight(currNode, parentNode, x);
  //             x = currNode;
  //             if(x->parent==NULL)
  //               root = x;
  //           }
  //           else if(parentNode==x->right && currNode==parentNode->left){
  //             rotateRightLeft(currNode, parentNode, x);
  //             x = currNode;
  //             if(x->parent==NULL)
  //               root = x;
  //           }
  //           else{
  //             rotateRightRight(currNode, parentNode, x);
  //             x = parentNode;
  //             if(x->parent==NULL)
  //               root = x;
  //           }
  //           cout<<"after3\n";

  //         // }      
  //     }

  //   }
  //   cout<<"after4\n";
  //   currNode = parentNode;
  //   parentNode = x;
  //   x = x->parent;
  //   }
    



    // while(x!=NULL){
    //   if(x->right==NULL && x->left==NULL){
    //     x->height = 0;
    //   }
    //   else if(x->right==NULL)
    //     x->height = x->left->height+1;
    //   else if(x->left==NULL)
    //     x->height = x->right->height+1;
    //   else{
    //     //no child of x is null
    //     x->height = max(x->left->height, x->right->height) + 1;
    //   }
    //   x = x->parent;
    // }
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

// TreeNode* AVLTree::childWithMaxNodes(TreeNode* t1, TreeNode* t2){
//   if(t1==NULL)
//     return t2;
//   if(t2==NULL)
//     return t1;
//   if(t1->height > t2->height)
//     return t1;
//   else
//     return t2;
// }


