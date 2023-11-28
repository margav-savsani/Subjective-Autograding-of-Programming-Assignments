#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int JourneyCode, int price)
{
  // Implement insertion in BST

  // To check whether the current pivot is already present in the BST
  if (find(JourneyCode)==1){
    return false;
  }
  //cout<<"Inserting Journey: "<<JourneyCode<<" "<<price<<endl;
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  // initializes a node with the given parameters
    TreeNode *toInsert = new TreeNode(JourneyCode, price);

    if (root == NULL)
    {
        // cout<<"root is null"<<endl;
        root = toInsert;

        
        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          updateHeight(curr);

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }

    // cout<<"Price of node to be inserted"<<toInsert->price<<endl;
    // cout<<"JourneyCode of node to be inserted"<<toInsert->JourneyCode<<endl;

    TreeNode *y = new TreeNode(0,0);
    TreeNode *x = root;

    while (x != NULL)
    {
        y = x;
        if (BSTLessThan(toInsert, x))
        {
            x = (x->left);
        }
        else
        {
            x = (x->right);
        }
    }
    toInsert->parent = y;
    if (y == NULL)
    {
        root = toInsert;
        
        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          updateHeight(curr);

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }
    else if (BSTLessThan(toInsert, y))
    {
        //y->left = toInsert;
        updateBSTParentChild(toInsert, y, true); // insert left child to the left

        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          updateHeight(curr);

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }
    else
    {
        //y->right = toInsert;
        updateBSTParentChild(toInsert, y, false); // insert right child to the right

        // updating the the longest paths and the shortest paths of the nodes in the path of the new node inserted
        TreeNode* curr =  toInsert;
        while(curr!=NULL){
          updateHeight(curr);

          // cout<<"The shortest path of the node is: "<<curr->shortestPathLength<<endl;
          // cout<<"The longest path of the node is: "<<curr->longestPathLength<<endl;

          curr= curr->parent;
        }

        return true;
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode* toInsert = new TreeNode(jrnyCode, 0); // setting the journey price to arbitrary value (here, 0)
  if (root == NULL){
    return -1; // tree is empty
  }
  TreeNode* curr = root;

  //tree is not empty
  while (curr!=NULL){
    if (BSTLessThan(toInsert,curr)){
      curr = curr->left;
    }
    else if (BSTLessThan(curr, toInsert)){
      curr = curr->right;
    }
    else {
      delete toInsert;
      return 1; // node found
    }
  }
  delete toInsert;
  return -1;
}

void BST:: updateHeight(TreeNode* curr){
  if (curr==NULL){
    cerr << "Unexpected condition encountered!" << endl;
  }
  if (curr->left==NULL && curr->right==NULL){
    curr->height = 0;
  }
  else if (curr->left!=NULL && curr->right==NULL){ // only left child is present
    curr->height = 1 + curr->left->height;
  }
  else if(curr->left==NULL && curr->right!=NULL){ // only right child is present
    curr->height = 1 + curr->right->height;
  }
  else { // both children are present
    curr->height = 1 + max(curr->right->height, curr->left->height);
  }
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
    TreeNode* toDelete = new TreeNode(jrnyCode,0); // to make a dummy node to compare with other nodes
    
    if (myRemove(toDelete,root, jrnyCode)){
      return true;
    }
    else{
      return false;
    }
}

bool BST:: myRemove(TreeNode* toDelete, TreeNode* curr, int jrnyCode){
    if (curr==NULL){
      return false;
    }
    

    if (find(jrnyCode)==-1){
      return false;
    }

    if ( BSTLessThan(toDelete, curr)){
        // curr->left = myRemove(toDelete, curr->left,jrnyCode);
        myRemove(toDelete, curr->left,jrnyCode);
    }
    else if( BSTLessThan( curr, toDelete) ){
        // curr->right = myRemove(toDelete, curr->right,jrnyCode);
        myRemove(toDelete, curr->right,jrnyCode);
    }
    else{ // the current node is the node to be deleted
      if (curr->left == NULL && curr->right == NULL){ // node to be deleted is leaf
        if (curr==root){ // the leaf is the root of the tree
      
          root = NULL;
         
          
        }

        if (curr->parent->left == curr){ // left child is to be deleted
          curr->parent->left = NULL;
          curr->parent = NULL;

          
        }
        else {
          curr->parent->right = NULL; // right child is to be deleted
          curr->parent = NULL;

          
        }

      }
      else if (curr->right !=NULL && curr->left ==NULL){
        if (curr == root){
          root = curr->right;
          curr->right->parent = NULL;
          curr->right = NULL;
        }
        else {
          // parent exists
          if (curr->parent->left == curr)// current is left child
          {
              curr->right->parent = curr->parent;
              curr->parent->left = curr->right;
          } 
          else { // current is right child
              curr->right->parent = curr->parent;
              curr->parent->right = curr->right;
          }
        }

      
      }
      else if (curr->left!=NULL && curr->right == NULL){
        if (curr == root){
          root = curr->left;
          curr->left->parent = NULL;
          curr->left = NULL;
        }
        else {
          // parent exists
          if (curr->parent->left == curr)// current is left child
          {
              curr->left->parent = curr->parent;
              curr->parent->left = curr->left;
          } 
          else { // current is right child
              curr->left->parent = curr->parent;
              curr->parent->right = curr->left;
          }
        }

      }
      else{
        TreeNode* succ = minValueNode(curr->right);

        curr->setJourneyCode(succ->getJourneyCode());
        curr->setprice(succ->getprice());

        TreeNode* toDeleteSucc = new TreeNode(succ->getJourneyCode(),0);

        myRemove(toDeleteSucc, curr->right,succ->getJourneyCode());
      }

    }

    if (curr == NULL)
      return false;

    updateHeight(curr);

  return true;
}

TreeNode * BST:: minValueNode(TreeNode* node)
{
    TreeNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}




