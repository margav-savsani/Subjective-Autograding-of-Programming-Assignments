#include "BST.h"

// updates the height of all nodes from curr up on the path to root
void AbstractBST::updateHeightsOnPath(TreeNode *curr){
    if (!curr) return; // nothing to do.

    // the only possible leaf along the path is curr, as later we only go up from curr.
    if (curr->isLeaf()){ 
        curr->height = 0; // should already be 0, just safety. Remove this later.
        curr = curr->parent; // possibly curr is nullptr now.
    }
    while(curr){
        curr->height = 1 + max(
            (curr->left) ? curr->left->height: 0, 
            (curr->right) ? curr->right->height: 0
        ); // height of a leaf is 0, not 1 as will be calculated from the above expression. But notice curr and any parent of curr has a child - and so the expression applies!
        curr = curr->parent;
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two nodes in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int AbstractBST::find(int JourneyCode){
    const TreeNode *loc = getnode(JourneyCode);
    return (loc) ? loc->price: -1;
}

const TreeNode *AbstractBST::getnode(int JourneyCode){
    // You MUST use only LessThan to compare two journey codes.

    // Not required, it's taken care of
    // // Check if the tree is empty.
    // if (!root)
    //     return nullptr; // the journey cannot possibly be here in the tree.
    
    TreeNode *curr = root;
    const TreeNode to_find(JourneyCode); // set the default price to -1.

    // binary search loop to search for the JourneyCode.
    while (true){

        if (!curr) return nullptr;
        
        // invariant: curr is never null.

        // if (*curr == to_find) return curr; - we must only use LessThan for checks, so check for this last when equality is guaranteed.

        if (LessThan(&to_find, curr)) 
            curr = curr->left; // search in the left subtree of curr.
        else if (LessThan(curr, &to_find))
            curr = curr->right; // search in the right subtree of curr.
        else return curr; // curr.JourneyCode == to_find.JourneyCode - we've found it!
    }
    // The above loop is bound to terminate since depth of the tree left to check is bounded below by 0 and is strictly decreasing. And we return from inside the loop as well - since we do return but no `break`.
}


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that NO two elements being inserted have the SAME journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int JourneyCode, int price){
    // check if the tree is empty
    if (!root){
        root = new TreeNode(JourneyCode, price);
        return true;
    }

    TreeNode *tmp = new TreeNode(JourneyCode, price);
    TreeNode *curr = root;

    // binary search loop. Search for where to put it.
    while (true){

        // invariant: curr is never null.
        
        if (LessThan(tmp, curr)){
            if (curr->left) 
                curr = curr->left; // search in the left subtree of curr.
            else{
                updateParentChild(tmp, curr, true); // place it if left subtree does not exist. This insert preserves the bst property.
                break;
            }
        }
        else if (LessThan(curr, tmp)){ // tmp > curr is curr < tmp
            if (curr->right) 
                curr = curr->right; // search in the right subtree of curr
            else{
                updateParentChild(tmp, curr, false); // place it if right subtree does not exist
                break;
            }
        }
        else return false; // an element with the same journey code is already in the array - we do not add it again.
    }
    // The above loop is bound to terminate since depth of the tree left to check is bounded below by 0 and is strictly decreasing.


    // update heights if a TreeNode was inserted at some place not equal to root.
    updateHeightsOnPath(curr);
    return true;
}


// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

// Implement deletion in BST
    
// You MUST use only BSTLessThan to compare two journey codes.  You
// can create a new node containing the journey code to be searched
// (along with some arbitrary price) and invoke BSTLessThan on the
// current node in the tree that you are inspecting and the new node
// to do your comparison.

// REMEMBER to update the height of appropriate nodes in the tree
// after a successful deletion.

// We use "return true" below to enable compilation.  Change this as you
// see fit.
bool BST::remove(int JourneyCode){
    return true;
}


