#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "tree.h"


bool BST::insert(int value)//inserts the node 
//basically checks if the node is already present or not, if it is present, then just returns false else
//inserts the required TreeNode and returns true
{
  TreeNode *ptr = root;
	bool done{false};
	
	TreeNode *node;
	node = new TreeNode;
	node->value = value;
	node->left = nullptr;
	node->right = nullptr;
	node->height=0;
	node->h_diff=0;
	
	if(root == nullptr){	
		root = node;
		node->parent = nullptr;
		return true;
	}
	
	if(find(value)){	
		return false;
	}
	
	else{
		
		while(true){
			
			if(ptr->value >= value){	
				if(ptr->left == nullptr){
					node->parent = ptr;
					ptr->left = node;
					node = nullptr;
					update_length(ptr, 1);
					avl_insert(ptr->left);
					break;
				}
				else{
					ptr = ptr->left;
				}
			}
			
			else {
				if(ptr->right == nullptr){
					node->parent = ptr;
					ptr->right = node;
					node = nullptr;
					update_length(ptr, 1);
					avl_insert(ptr->right);
					break;
				}
				else{
					ptr = ptr->right;
				}
			}
		}
   		
		return true;
	}
}

void BST::avl_insert(TreeNode *ptr){

	TreeNode *parent=ptr->parent;
	TreeNode *grandparent=parent->parent;
	if(grandparent == nullptr)
		return;
	if(grandparent->h_diff != 0 && grandparent->h_diff != 1){
		if(grandparent->value > parent->value && parent->value > ptr->value){
			rotate(grandparent, parent);
		}
		else if(grandparent->value < parent->value && parent->value< ptr->value){
			rotate(grandparent, parent);
		}
		else {
			rotate(parent, ptr);
			rotate(grandparent, ptr);
		}
		update_length(grandparent, 0);
		update_length(parent, 0);
		update_length(ptr, 1);
		
	}
	else{
		avl_insert(ptr->parent);
	}
}

void BST::rotate(TreeNode *parent, TreeNode *child){
	if(parent->left==child){
		TreeNode *grand=parent->parent;
		TreeNode *tree=child->right;
		if(grand==nullptr){
			if(tree==nullptr){
				parent->left=nullptr;
				child->right=parent;
				parent->parent=child;
				child->parent=nullptr;
				root=child;
			}
			else{
				parent->left=tree;
				child->right=parent;
				parent->parent=child;
				child->parent=nullptr;
				tree->parent=parent;
				root=child;
			}
		}
		else{
	
			if(tree==nullptr){
				parent->left=nullptr;
				child->right=parent;
				parent->parent=child;
				child->parent=grand;
				if(grand->right==parent)grand->right=child;
				else grand->left=child;
				
			}
			else{
				parent->left=tree;
				child->right=parent;
				parent->parent=child;
				child->parent=grand;
				tree->parent=parent;
				if(grand->right==parent)grand->right=child;
				else grand->left=child;
			}
		}
	}
	else{
		TreeNode *grand=parent->parent;
		TreeNode *tree=child->left;
		if(grand==nullptr){
			if(tree==nullptr){
				parent->right=nullptr;
				child->left=parent;
				parent->parent=child;
				child->parent=nullptr;
				root=child;
			}
			else{
				parent->right=tree;
				child->left=parent;
				parent->parent=child;
				child->parent=nullptr;
				tree->parent=parent;
				root=child;
			}
		}
		else{
			if(tree==nullptr){
				parent->right=nullptr;
				child->left=parent;
				parent->parent=child;
				child->parent=grand;
				if(grand->right==parent)grand->right=child;
				else grand->left=child;
				
			}
			else{
				parent->right=tree;
				child->left=parent;
				parent->parent=child;
				child->parent=grand;
				tree->parent=parent;
				if(grand->right==parent)grand->right=child;
				else grand->left=child;
			}
		}
	}
}

void BST::update_length(TreeNode *ptr, int recur){
  if(ptr==nullptr){
    return;
  }
  int right, left;
  if(ptr->right == nullptr)right=0;
  else right=ptr->right->height+1;
  if(ptr->left == 0) left=0;
  else left=ptr->left->height+1;
  
  ptr->height=max(right, left);
  ptr->h_diff = abs(right-left);
  
  if(recur==1)
  	update_length(ptr->parent, 1);
  else
  	return;
}

//myfind method returns the pointer of the TreeNode struct if it is found nullptr otherwise 
TreeNode* BST::myfind(int value) { 
	
	TreeNode *ptr = root;
	while(true){
		if(ptr == nullptr)
			return nullptr;
		else{
			if(ptr->value> value){
				ptr=ptr->left;
			}
			else if(ptr->value<value){
				ptr=ptr->right;
			}
			else if(ptr->value==value){
				return ptr;
			}
		}
	}
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int value){
	TreeNode *ptr = myfind(value); 
	if(ptr == nullptr){
		return false;
	}
	else{
		return true;
	}
}
	
bool BST::remove(int value) {  

	TreeNode *ptr=myfind(value);//find the treeNode to be removed and pass it on to the myremove function which returns true if it is successful in deletion false otherwise.
	if(myremove(ptr))
		return true;
	else
		return false;	
}

//myremove function returns true if it is successful in deletion false otherwise.
bool BST::myremove(TreeNode *ptr){
	if(ptr==nullptr)
		return false;
	
	else{
		//case 1--without no children
		if(ptr->left == nullptr && ptr->right==nullptr){
			if(ptr->parent == nullptr)
				root = nullptr;
			if(ptr->parent->left==ptr){
				ptr->parent->left=nullptr;
        update_length(ptr->parent, 1);
			}
			if(ptr->parent->right==ptr){
				ptr->parent->right=nullptr;
        update_length(ptr->parent, 1);
			}
      
      		avl_delete(ptr->parent);
			ptr->parent=nullptr;
			return true;
		}	
		
		//case 2--with 1 child
		//the next 2 else if are similar ,only difference is one deals when left pointer is nullptr andthe other deals with right pointer 
		else if(ptr->left==nullptr){
			ptr->right->parent=ptr->parent;
			if(ptr->parent==nullptr){
				root=ptr->right;
				ptr->right=nullptr;
			}
			else if(ptr->parent->left==ptr){
				ptr->parent->left=ptr->right;
			}
			else if(ptr->parent->right==ptr){
				ptr->parent->right=ptr->right;
			}
      update_length(ptr->parent, 1);
      		avl_delete(ptr->parent);
			ptr->parent=nullptr;
			ptr->right=nullptr;
			return true;
		}
		
		else if(ptr->right==nullptr){
			ptr->left->parent=ptr->parent;
			if(ptr->parent==nullptr){
				root=ptr->left;
				ptr->left=nullptr;
			}
			else if(ptr->parent->left==ptr){
				ptr->parent->left=ptr->left;
			}
			else if(ptr->parent->right==ptr){
				ptr->parent->right=ptr->left;
			}
   		    update_length(ptr->parent, 1);
   		    avl_delete(ptr->parent);
			ptr->parent=nullptr;
			ptr->left=nullptr;
			return true;
		}
		
		//case 3--with 2 child
		//uses recursion
		else{
			TreeNode *find_replacement = getMaxNode(ptr->left);
			ptr->value=find_replacement->value;
			myremove(find_replacement);
			return true;
		}
	}
	return false;
}

void BST::avl_delete(TreeNode *ptr){
	if(ptr==nullptr)
		return;
	else if(ptr->h_diff!=0 && ptr->h_diff!=1){
		TreeNode *child{nullptr};
		TreeNode *grandchild{nullptr};
		int right,left;
		if(ptr->right!=nullptr)right=ptr->right->height;
		else right=0;
		if(ptr->left!=nullptr)left=ptr->left->height;
		else left=0;
		if(right>left)
			child=ptr->right;
		else
			child=ptr->left;
			
		if(child->right!=nullptr)right=child->right->height;
		else right=0;
		if(child->left!=nullptr)left=child->left->height;
		else left=0;
		if(right>left)
			grandchild=child->right;
		else
			grandchild=child->left;
			
		int h=ptr->parent->h_diff;
		if(grandchild==child->left && child==ptr->left){
			rotate(ptr, child);
			update_length(child, 0);
			update_length(grandchild, 0);
			update_length(ptr, 0);
			update_length(child->parent, 1);
			if(h==child->parent->h_diff)
				return;
			else{
				avl_delete(child->parent);
			}
		}
		else if(grandchild==child->right && child==ptr->right){
			rotate(ptr, child);
			update_length(child, 0);
			update_length(grandchild, 0);
			update_length(ptr, 0);
			update_length(child->parent, 1);
			if(h==child->parent->h_diff)
				return;
			else{
				avl_delete(child->parent);
			}
		}
		else{
			rotate(child, grandchild);
			rotate(ptr, grandchild);
			update_length(child, 0);
			update_length(grandchild, 0);
			update_length(ptr, 0);
			update_length(child->parent, 1);
			avl_delete(grandchild->parent);
		}
		
	}
	else{
		avl_delete(ptr->parent);
	}
}

TreeNode * BST::getMaxNode(TreeNode* ptr){
	while(true){
		if(ptr == nullptr)
			return 0;
		if(ptr->right == nullptr)
			return ptr;
		else{
			ptr = ptr->right;
		}
	}
}

int BST::height_diff(){
	return root->h_diff;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
	
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value<< endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
	
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->value) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}

