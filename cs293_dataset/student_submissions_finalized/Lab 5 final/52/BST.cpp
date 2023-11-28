#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <stdlib.h>

#include <iostream>
#endif

// Returns true on successful insertion in BST. Returns false otherwise.
// No two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST
bool BST::insert(int jrnyCode, int price)
{
    // New node for insertion
	TreeNode *newNode = new TreeNode(jrnyCode, price);

	TreeNode *currNode = root;
	TreeNode *parentOfCurrNode = nullptr;
	while (currNode != nullptr)
	{
		if (BSTLessThan(currNode, newNode))
		{
			parentOfCurrNode = currNode;
			currNode = currNode->right;
		}
		else if (BSTLessThan(newNode, currNode))
		{
			parentOfCurrNode = currNode;
			currNode = currNode->left;
		}
		else
		{ // currNode->JourneyCode == JourneyCode
			return false;
		}
	}
	// JourneyCode is not present in the BST.  We must now
	// insert an appropriate child of parentOfCurrNode.

	if (parentOfCurrNode == nullptr){
		root = newNode;
        return true;
	}
	else{
		if (BSTLessThan(newNode, parentOfCurrNode)){
			updateBSTParentChild(newNode, parentOfCurrNode, 1);
		}
		else{
			updateBSTParentChild(newNode, parentOfCurrNode, 0);
		}
	}

    // Update heights
	TreeNode *y = parentOfCurrNode;
	while (y != nullptr)
	{
		if (y->updateHeight())  // if height is changed then continue
			y = y->parent;
		else                    // else break
			break;
	}

	return true;
}


// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
int BST::find(int jrnyCode)
{
    // New node for comparison
	TreeNode* key = new TreeNode(jrnyCode, -1);

	TreeNode* x = root;

	while(x!= nullptr){
		if(BSTLessThan(key, x)){
			x = x->left;
		}
		else if(BSTLessThan(x, key)){
			x = x->right;
		}
		else{
			return x->getPrice();
		}
	}

	return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// No two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.
bool BST::remove(int jrnyCode)
{
    // New node for comparison
	TreeNode* key = new TreeNode(jrnyCode, -1);

	if(root == nullptr){
		return false;
	}

    TreeNode* updateFrom = nullptr;

    // Special case for root
    if(!BSTLessThan(key, root) && !BSTLessThan(root, key)){
        TreeNode* x = root;
        // Case 1: Both child are null
        if(x->left == nullptr && x->right == nullptr){
            root = nullptr;
            delete x;
        }
        // Case 2: Left child is null
        else if(x->left == nullptr){
            root = x->right;
			updateBSTParentChild(x->right, nullptr, 0);
            delete x;
        }
        // Case 3: Right child is null
        else if(x->right == nullptr){
            root = x->left;
            updateBSTParentChild(x->left, nullptr, 0);
            delete x;
        }
        // Case 4: No child is null
        else{
            // Get successor
            TreeNode* z = x->right;
            while (z->left != nullptr){
                z = z->left;
            }

            updateFrom = z->parent;

            // Replace at root
            x->setJourneyCode(z->getJourneyCode());
            x->setPrice(z->getPrice());

            // Delete successor
            if(z->left == nullptr && z->right == nullptr){
                if(z->parent->left == z) updateBSTParentChild(nullptr, z->parent, 1);
                else if(z->parent->right == z) updateBSTParentChild(nullptr, z->parent, 0);
                delete z;
            }
            else{
                if(z->parent->left == z) updateBSTParentChild(z->right, z->parent, 1);
                else if(z->parent->right == z) updateBSTParentChild(z->right, z->parent, 0);

                delete z;
            }

        }

        
        while(updateFrom != nullptr && updateFrom->updateHeight()){
            updateFrom = updateFrom->parent;
        }

        return true;
    }
    
    TreeNode* x = root;
    // Find the node with matching journeyCode
    while(x != nullptr){
		if(BSTLessThan(key, x)){
			x = x->left;
		}
		else if(BSTLessThan(x, key)){
			x = x->right;
		}
		else{
			break;
		}
	}
    if(x == nullptr) return false;
    else{
        TreeNode* y = x->parent;
        // Case 1: Both child are null
        if(x->left == nullptr && x->right == nullptr){
            if(y->left == x) updateBSTParentChild(nullptr, y, 1);
            else if(y->right == x) updateBSTParentChild(nullptr, y, 0);
            delete x;
            updateFrom = y;
        }
        // Case 2: Left child is null
        else if(x->left == nullptr){
            if(y->left == x) updateBSTParentChild(x->right, y, 1);
            else if(y->right == x) updateBSTParentChild(x->right, y, 0);
            delete x;
            updateFrom = y;
        }
        // Case 3: Right child is null
        else if(x->right == nullptr){
            if(y->left == x) updateBSTParentChild(x->left, y, 1);
            else if(y->right == x) updateBSTParentChild(x->left, y, 0);
            delete x;
            updateFrom = y;
        }
        // Case 4: No child is null
        else{
            // Get successor
            TreeNode* z = x->right;
            while (z->left != nullptr){
                z = z->left;
            }

            updateFrom = z->parent;
            
            // Replace at current node
            x->setJourneyCode(z->getJourneyCode());
            x->setPrice(z->getPrice());

            // Delete successor
            if(z->left == nullptr && z->right == nullptr){
                if(z->parent->left == z) updateBSTParentChild(nullptr, z->parent, 1);
                else if(z->parent->right == z) updateBSTParentChild(nullptr, z->parent, 0);
                delete z;
            }
            else{
                if(z->parent->left == z) updateBSTParentChild(z->right, z->parent, 1);
                else if(z->parent->right == z) updateBSTParentChild(z->right, z->parent, 0);

                delete z;
            }

        }

        while(updateFrom != nullptr && updateFrom->updateHeight()){
            updateFrom = updateFrom->parent;
        }

        return true;
    }

}
