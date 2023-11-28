#include "AVL.h"

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

// The single rotations. Three updations required.

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
    if (!(currNode && parentNode && grandParentNode)) return false;

    TreeNode *y = parentNode, *z = grandParentNode; // x is not neeeded here.
    TreeNode *w = z->parent;
    // if (w) updateParentChild(y, w, w->left == z); // the third argument is more clearly written as (w->left == z) ? true: false
    // // else z is the root.
    // else{
    //     root = y; // root = z to root = y.
    //     y->parent = nullptr;
    //     totalParentChildUpdateCost += perParentChildUpdateCost;
    // }
    updateParentChild(y, w, (w)? w->left == z: true); 

    // the throw step
    TreeNode *toThrow = y->right; // possily nullptr. In case x is the inserted leaf. Then h = -1.
    updateParentChild(toThrow, z, true);

    // get z back in the tree(it was removed in the first call to updateParentChild, but z still points to the node z in memory)
    updateParentChild(z, y, false);
    return true; // successful rotation
}

// identical to ll, just all lefts <-> rights and isLeft: true<->false
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
    if (!(currNode && parentNode && grandParentNode)) return false;

    TreeNode *y = parentNode, *z = grandParentNode; // x is not neeeded here.
    TreeNode *w = z->parent;
    // if (w) updateParentChild(y, w, w->left == z); // the third argument is more clearly written as (w->left == z) ? true: false
    // // else z is the root.
    // else{ 
    //     root = y; // root = z to root = y.
    //     y->parent = nullptr;
    //     totalParentChildUpdateCost += perParentChildUpdateCost;
    // }
    updateParentChild(y, w, (w)? w->left == z: true); 

    // the throw step
    TreeNode *toThrow = y->left; // possily nullptr.
    updateParentChild(toThrow, z, false);

    // get z back in the tree(it was removed in the first call to updateParentChild)
    updateParentChild(z, y, true);
    return true; // successful rotation
}

// the double rotations. The simplest implementation( an LL followed by RR or vice versa) requires 2x3 = 6 updations, but by noting that in this case x is updated twice, we can reduce one update and so optimize to 5 updates.

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
    if (!(currNode && parentNode && grandParentNode)) return false;

    TreeNode *x = currNode, *y = parentNode, *z = grandParentNode;
    TreeNode *w = z->parent;
    // TreeNode *throwToY = x->left, *throwToZ = x->right; // one of them is possibly nullptr
    
    // throw throwToY,throwToZ / the subtrees of x to y and z.
    updateParentChild(x->left, y, false);
    updateParentChild(x->right, z, true);

    // set x to the child of w.
    // if (w) updateParentChild(x, w, w->left == z);
    // else{
    //     root = x; x->parent = nullptr;
    //     totalParentChildUpdateCost += perParentChildUpdateCost;
    // }
    updateParentChild(x, w, (w)? w->left == z: true);

    // re-connect x, y, and z.
    updateParentChild(y, x, true);
    updateParentChild(z, x, false);
    return true;
}

// identical to lr, just all lefts <-> rights and isLeft: true<->false
bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode){
    if (!(currNode && parentNode && grandParentNode)) return false;

    TreeNode *x = currNode, *y = parentNode, *z = grandParentNode;
    TreeNode *w = z->parent;
    // TreeNode *throwToY = x->left, *throwToZ = x->right; // one of them is possibly nullptr
    
    // throw throwToY,throwToZ / the subtrees of x to y and z.
    updateParentChild(x->right, y, true);
    updateParentChild(x->left, z, false);

    // set x to the child of w.
    // if (w) updateParentChild(x, w, w->left == z);
    // else{
    //     root = x; x->parent = nullptr;
    //     totalParentChildUpdateCost += perParentChildUpdateCost;
    // }
    updateParentChild(x, w, (w)? w->left == z: true);

    // re-connect x, y, and z.
    updateParentChild(y, x, false);
    updateParentChild(z, x, true);
    return true;
}


// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int JourneyCode, int price)
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

    // --- we have inserted the node. Now we must check for imbalance and rebalance. --- //

    // curr->parent = tmp->parent->parent can be the first imbalanced node, since curr will be balanced.
    TreeNode *x = tmp; 
    TreeNode *y = curr, *z = curr->parent; // z is possibly nullptr

    // update heights of x and y. (Nothing to do for x)
    y->updateHeight();

    // find the first point of imbalance along path while updating the heights. Notice that we stop here, rebalance, and then continue to update the heights from x onwards.
    for(; z; x = y, y = z, z = z->parent){
        if (z->updateHeight()) continue;
        int which_rotation = 2*(z->right == y) + (y->right == x);
        /* switch (which_rotation){
            case 0: 
                rotateLeftLeft  (x, y, z); 
                z->updateHeight(); y->updateHeight(); // update y and z's heights. Notice we must first update z's then y's. x's subtrees and hence height are unaffected by the rotation.
                break;
            case 1: 
                rotateLeftRight (x, y, z); 
                z->updateHeight(); y->updateHeight(); x->updateHeight(); // notice the order. The one that took z's place is updated last.
                break;
            case 2: 
                rotateRightLeft (x, y, z); 
                z->updateHeight(); y->updateHeight(); x->updateHeight();
                break;
            case 3: 
                rotateRightRight(x, y, z); 
                z->updateHeight(); y->updateHeight();
                break;
        } */
        // more succint representation of the above
        switch (which_rotation){
            case 0: rotateLeftLeft  (x, y, z); break;
            case 1: rotateLeftRight (x, y, z); break;
            case 2: rotateRightLeft (x, y, z); break;
            case 3: rotateRightRight(x, y, z); break;
        }
        z->updateHeight(); y->updateHeight(); // update y and z's heights after the rotation
        if (which_rotation == 1 || which_rotation == 2) 
            x->updateHeight(); // update x last since when x is updated, it is the parent of y and z and so must be updated after y and z have been updated.

        break; // if a rotation has been done, then it is easy that the height of z (or what is now in its place) is the sae as that before the insert, so the heights of all ancestors of z remain the same. So we break.
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


