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
    // also finding it considering that greatGrandParentNode is
    // not the nullptr
  
    bool isGPLeftChild;
    
    if(greatGrandParentNode!=nullptr){
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
    
    // if greatGrandParentNode is equal to nullptr, then
    // root becomes the parentnode {referring prof slides}
    if(greatGrandParentNode==nullptr) root = parentNode;

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
    // also finding it considering that greatGrandParentNode is
    // not the nullptr

    bool isGPLeftChild;
    if(greatGrandParentNode!=nullptr){
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
    
    // if greatGrandParentNode is equal to nullptr, then
    // root becomes the currnode {referring prof slides}
    if(greatGrandParentNode==nullptr) root = currNode;

    return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

    // Moreover, currNode is the left child of parentNode, and
    // parentNode is the left child of grandParentNode
    // That's why we are doing a rotateRightLeft
    
    TreeNode *greatGrandParentNode = grandParent->parent;
    
    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode
    // also finding it considering that greatGrandParentNode is
    // not the nullptr

    bool isGPLeftChild;
    if(greatGrandParentNode!=nullptr){
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
    
    // Let T2 be the left child of currNode (i.e. of x)
    TreeNode *T2 = currNode->left;
    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T3 = currNode->right;
    
    // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
    
    // Make parentNode (y in Prof. Garg's lectures) the left child of
    // currNode (x in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that parentNode should be
    // made the right child of currNode
    updateAVLParentChild(parent, currNode, false);
    
    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // currNode (x in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that grandParentNode
    // should NOT be made the right child of currNode
    updateAVLParentChild(grandParent, currNode, true);
    
    // We use "false" as the third argument of the following call to indicate
    // that T2 should NOT become the left child of grandparent
    updateAVLParentChild(T2, grandParent, false);
    
    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the left child of parent
    updateAVLParentChild(T3, parent, true);
    
    // if greatGrandParentNode is equal to nullptr, then
    // root becomes the currnode {referring prof slides}
    if(greatGrandParentNode==nullptr) root = currNode;

    return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentnode, TreeNode *grandParentnode)
{
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

    // Moreover, currNode is the left child of parentNode, and
    // parentNode is the left child of grandParentNode
    // That's why we are doing a rotateRightRight
    
    TreeNode *greatGrandParentNode = grandParentnode->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode
    // also finding it considering that greatGrandParentNode is
    // not the nullptr
    
    bool isGPLeftChild;
    if(greatGrandParentNode!=nullptr){
        if (greatGrandParentNode->left == grandParentnode) {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentnode) {
            isGPLeftChild = false;
        }
        else {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }
    
    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parentnode->left;
    
    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(parentnode, greatGrandParentNode, isGPLeftChild);
    
    // Make currNode (x in Prof. Garg's lectures) the left child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that currNode should be
    // made the right child of parentNode
    updateAVLParentChild(currNode, parentnode, false);
    
    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that grandParentNode
    // should NOT be made the right child of parentNode
    updateAVLParentChild(grandParentnode, parentnode, true);
    
    // We use "false" as the third argument of the following call to indicate
    // that T3 should become the right child of grandParentNode
    updateAVLParentChild(T3, grandParentnode, false);
    
    // if greatGrandParentNode is equal to nullptr, then
    // root becomes the parentnode {referring prof slides}
    if(greatGrandParentNode==nullptr) root = parentnode;

    return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
    // storing the data of node which has to be inserted in node 'NEW'
    TreeNode *NEW = new TreeNode(jrnyCode,price);

    // storing the root in the ins_l(insert to left)
    TreeNode *ins_l = root;
    
    // creating a new node which is used to find the node
    // where we have to insert the node
    TreeNode *ins_r = nullptr;
      
    // after completing the loop, data of the node where
    // we have to insert the new node is stored in the
    // ins_r
    while(ins_l!=nullptr)
    {
        ins_r = ins_l;
        if(AVLEqualTo(NEW,ins_l)) break;
        if(AVLLessThan(NEW,ins_l)) ins_l = ins_l->left;
        else ins_l = ins_l->right;
    }
    
    // if the ins_r found to be nullptr, than that means
    // tree is empty, so root becomes our inserting node, i.e. NEW
    if(ins_r==nullptr)
    {
        root = NEW;
        return true;
    }

    // inserting the new node to the left of the ins_r
    if(AVLLessThan(NEW,ins_r))
    {
        ins_r->left=NEW;
        updateAVLParentChild(NEW, ins_r, true);
    }
    
    // inserting the new node to the right of the ins_r
    else
    {
        ins_r->right = NEW;
        updateAVLParentChild(NEW, ins_r, false);
    }
      
    // storing the data of the parent of the inserting node
    TreeNode *for_height = ins_r;
      
    // for storing the height of each node in their private variable height
    while(for_height!=nullptr)
    {
        for_height->update_the_height();
        for_height = for_height->parent;
    }
    
    // storing position of the child node, i.e. Child_Node &
    // also storing the position of the parent node, i.e. Parent_Node
    // 'true' is used for left side of tree
    // and 'false' is used for the right side of tree
    bool child_position = true, parent_position = true;
    
    // loop for invoking the appropriate rotation
    // while inserting the node in the AVL tree
    for(int i = 0; true; i++)
    {
        // storing the node to be inserted in the Child_Node
        TreeNode *Child_Node = NEW;
        
        // pointer in which the data of the parent of
        // child is stored
        TreeNode *Parent_Node;
        
        // pointer in which the data of the grandparent of
        // child is stored
        TreeNode *GrandP_Node;
        
        // storing the parent of the child
        Parent_Node = Child_Node->parent;
        
        // will exit from loop if Parent_Node is nullptr
        if(Parent_Node == nullptr) break;
        
        // storing the grandparent of the child
        GrandP_Node = Child_Node->parent->parent;
        
        // will exit from loop if Parent_Node is nullptr or imbalance is correct
        if(GrandP_Node == nullptr || GrandP_Node->get_imbalance()<=1) break;
        
        // if imbalance is not correct then rotating the tree
        if(GrandP_Node->get_imbalance()>1)
        {
            // storing the value of the position for Child_Node and Parent_Node
            if(Child_Node == Parent_Node->left) child_position = true;
            if(Child_Node == Parent_Node->right) child_position = false;
            if(Parent_Node == GrandP_Node->left) parent_position = true;
            if(Parent_Node == GrandP_Node->right) parent_position = false;
            
            // for implying the rotateLeftLeft function
            if(child_position == true && parent_position == true)
            {
                rotateLeftLeft(Child_Node,Parent_Node,GrandP_Node);
                
                // storing GrandP_Node in a new node for updating
                // the height of the tree after rotation
                TreeNode *store = GrandP_Node;
                while(store!=nullptr)
                {
                    store->update_the_height();
                    store = store->parent;
                }
            }
            
            // for implying the rotateLeftRight function
            if(child_position == false && parent_position == true)
            {
                rotateLeftRight(Child_Node,Parent_Node,GrandP_Node);
                
                // storing GrandP_Node in a new node for updating
                // the height of the tree after rotation
                GrandP_Node->update_the_height();
                TreeNode *store = Parent_Node;
                while(store!=nullptr)
                {
                    store->update_the_height();
                    store = store->parent;
                }
            }
    
            // for implying the rotateRightLeft function
            if(child_position == true && parent_position == false)
            {
                rotateRightLeft(Child_Node,Parent_Node,GrandP_Node);
                
                // storing GrandP_Node in a new node for updating
                // the height of the tree after rotation
                GrandP_Node->update_the_height();
                TreeNode *store = Parent_Node;
                while(store!=nullptr)
                {
                    store->update_the_height();
                    store = store->parent;
                }
            }
        
            // for implying the rotateRightRight function
            if(child_position == false && parent_position == false)
            {
                rotateRightRight(Child_Node,Parent_Node,GrandP_Node);
                
                // storing GrandP_Node in a new node for updating
                // the height of the tree after rotation
                TreeNode *store = GrandP_Node;
                while(store!=nullptr)
                {
                    store->update_the_height();
                    store = store->parent;
                }
            }
        }
        
        // for checking the imbalance for the every node
        // so putting child to its parent so that
        // the loop continues
        Child_Node = Child_Node->parent;
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
    
    // create a new node containing the journey code to be searched
    TreeNode *to_find = new TreeNode(jrnyCode,10101);
            
    // storing our root in ins_l(insert in left)
    TreeNode *ins_l = root;

    // using while loop to check whether our to_find node
    // is there in AVL Tree or not
    while(!AVLEqualTo(to_find,ins_l))
    {
        // if journeycode of to_find is less than that of root,
        // than go to left subtree
        if(AVLLessThan(to_find,ins_l))
        {
            ins_l = ins_l->left;
            
            // defined in BST.cpp setting is to 0, i.e. false,
            // reflecting left subtree
            value = 0;
            if(ins_l==nullptr) break;
        }
        // else it goes to the right subtree
        else
        {
            ins_l = ins_l->right;
            
            // defined in BST.cpp setting is to 1, i.e. true,
            // reflecting left subtree
            value = 1;
            if(ins_l==nullptr) break;
        }
    }
            
    // if our node is not present then returns -1
    if(ins_l==nullptr) return -1;
            
    // value of price is returned from the get_price function defined in Tree.h,
    // which returns the price of the node
    // if node is present then returning its price
    else return ins_l->get_price();
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


