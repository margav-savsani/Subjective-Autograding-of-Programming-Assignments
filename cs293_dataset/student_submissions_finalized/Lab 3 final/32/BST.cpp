#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4
using namespace std;

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
    root = nullptr;

}

BST::BST(TreeNode *root){
    this->root = root;
}



//check if given journey is already present in tree
bool BST::journeyCheck(struct TreeNode *l, int JourneyCode){

 		if (l == nullptr)
 		return true;

 		else{
 		   return	l->JourneyCode != JourneyCode && journeyCheck(l->left, JourneyCode) && journeyCheck(l->right, JourneyCode);
 		}
}


// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {

  struct TreeNode* curr = root;
  struct TreeNode* prev = root;

  if (journeyCheck(root, JourneyCode))
  {


  if (root == nullptr)
  {
      root = new struct TreeNode;
  	  root->price = price;

      root->JourneyCode = JourneyCode;
      return true;
  }

  while(curr!=nullptr && curr->JourneyCode!=JourneyCode){

  	if(curr->price < price)
  	{
  		prev = curr;
  		curr = prev->right;
  	}

  	else
  	{
  	    prev = curr;
  		curr = prev->left;
  	}
 }

  if(curr == nullptr)
  {
  	curr = new struct TreeNode;
  	curr->parent = prev;

  	if(prev->price < price)
  	{
  		curr->price = price;
        curr->JourneyCode = JourneyCode;
  		prev->right = curr;

  		return true;
  	}

  	else
  	{
  	    curr->price = price;
        curr->JourneyCode = JourneyCode;
  		prev->left = curr;

  		return true;
  	}

}

  }
  else
  return false;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{

	struct TreeNode* curr = root;
  	struct TreeNode* prev = root;

	while(curr!=nullptr && curr->JourneyCode != JourneyCode){

  	if(curr->price < price)
  	{
  		prev = curr;
  		curr = prev->right;
  	}

  	else
  	{
  	    prev = curr;
  		curr = prev->left;
  	}


}
  	if(curr == nullptr)
  	return false;

	else if(curr->JourneyCode == JourneyCode && curr->price == price)
	{
	    return true;
	}

	else
	return false;

 }

struct TreeNode* BST::predecessor(struct TreeNode* node)
{
 	struct TreeNode* pre;

 	if (node->left != nullptr)
    {
            struct TreeNode* tmp = node->left;

            while (tmp->right!=nullptr)
                tmp = tmp->right;

            return tmp ;
    }
 }

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{

	struct TreeNode *curr = root, *prev = nullptr;

	if(root == nullptr)
	return false;
	// if root is being removed with one
	if(root->JourneyCode == JourneyCode && root->price==price)
	{
		if (curr->left==nullptr && curr->right==nullptr)
		{
			root=nullptr;
			return true;
		}

		else if (curr->left != nullptr && curr->right ==nullptr)
		{
			root->left->parent = nullptr;
			root=root->left;
			return true;
		}

		else if (curr->left == nullptr && curr->right !=nullptr)
		{
			root->right->parent = nullptr;
			root=root->right;

			return true;
		}

		else
		{
		   struct TreeNode* prec = predecessor(curr);
  		   root = prec;

  		   if(prec->parent==curr){;}
  		   else{
  		     prec->parent->right = prec->left;

  		     if(prec->left!=nullptr)
  		     prec->left->parent = prec->parent;

  		     curr->left->parent = prec;
  		    prec->left=curr->left;
  		  }

  		  curr->right->parent = prec;
  		  prec->right = curr->right;
  		  root->parent = nullptr;

  		  return true;

		}

	}

	// If root is not being removed:
	while(curr!=nullptr && curr->JourneyCode!=JourneyCode)
	{
  	   if(curr->price < price)
  	   {
  		  prev = curr;
  		  curr = prev->right;
  	   }

  	   else
  	   {
  	      prev = curr;
  		  curr=prev->left;
       }


	}

  if (curr==nullptr)
  return false;

  else if(curr->JourneyCode==JourneyCode && curr->price==price){

  	// When Node is a LEAF
  if (curr->left==nullptr && curr->right==nullptr)
  {
  		if(prev->right == curr)
  		{
  		   prev->right = nullptr; return true;
  	    }

  		else
  		{
  		    prev->left=nullptr; return true;
  	    }

  }


  	// When Node has ONLY ONE RIGHT CHILD

  	else if (curr->left==nullptr )
  	{
  	    curr->right->parent = prev;
  		if(prev->right == curr)
  		{
           prev->right = curr->right; return true;
        }

  		else
  		{
  		   prev->left=curr->right;
  		   return true;
  	    }


  	}


  	//When NOde has only ONE LEFT CHILD
  	else if (curr->right==nullptr )
  	{

  		if(prev->right == curr)
  		{
  			curr->left->parent = prev;
  		    prev->right = curr->left;
  		    return true;
  	    }

  		else
  		{
  		   curr->left->parent = prev;
  		   prev->left=curr->left;
           return true;
  	    }
  	}

  	else
  	{
  		struct TreeNode* prec = predecessor(curr);

  		if(prec->parent==curr)
  		{
  			if (curr->parent->left == curr)
  				curr->parent->left = prec;

  			else
  				curr->parent->right = prec;
            prec->parent = curr->parent;

  			prec->right=curr->right;
  			curr->right->parent = prec;

  			return true;
  		}


  		else if(prec->left!=nullptr)
  		{
  		   prec->left->parent=prec->parent;
  		   prec->parent->right = prec->left;
  		}

  		else if(prec->parent!=curr)
  		prec->parent->right=nullptr;

  		if(curr->parent!=nullptr)
  		{
  			if (curr->parent->left == curr)
  				curr->parent->left = prec;
  			else
  				curr->parent->right = prec;
  			prec->parent = curr->parent;
  		}

  		if(curr->left!=prec)
  		{

  		curr->left->parent = prec;
  		prec->left = curr->left;

  		}


  		curr->right->parent = prec;
  		prec->right = curr->right;

  		return true;
  	}



  	}
	else
		return false;



 return false;
}

void BST::preorder(struct TreeNode *l)
{
 		if (l==nullptr)
 		return;

 		else
 		{
 			cout<<l->JourneyCode<<" ";
 			preorder(l->left);
 			preorder(l->right);
 		}
};

void BST::postorder(struct TreeNode *l)
{
	if (l==nullptr)
	return;

    else
    {
        postorder(l->left);
        postorder(l->right);
        cout<<(l->JourneyCode)<<" ";

    }
};


void BST::inorder(struct TreeNode *l)
{
	if (l==nullptr)
	return;

    else
    {
        inorder(l->left);
        cout<<(l->JourneyCode)<<" ";
        inorder(l->right);
    }

};

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal==0)
	preorder(root);

    else if (typeOfTraversal==1)
	postorder(root);

    else
	inorder(root);

    return;
}



// Returns the price of the cheapest journey
int BST::getMinimum()
{

	struct TreeNode* curr=root;

	while(curr->left != nullptr)
	{
		curr = curr->left;
	}

	return curr->price;
}
// Part II


//sub-function for countJourneysInPriceBound

int BST::inorderBoundCount(int lowerBound, int upperBound, struct TreeNode* l)
{
	if (l==nullptr)
	return 0;

 	else
 	{
 		int count = inorderBoundCount(lowerBound, upperBound, l->left);

 		if(l->price <= upperBound && l->price >= lowerBound)
 		count += 1;

 		count += inorderBoundCount(lowerBound, upperBound, l->right);

 		return count;
 	}

}




// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{

	return inorderBoundCount(lowerPriceBound, upperPriceBound, root);

}


//function to INsert in file
void fileInsert(const std::string& name, const std::string& content, bool append = false)
{
    std::ofstream outfile;

    if (append)
        outfile.open(name, std::ios_base::app);

    else
        outfile.open(name);

    outfile << content <<endl;
    outfile.close();
}

//helper func for customStore
void BST::Store(string filename, struct TreeNode* l)
{

	if (l==nullptr)
	{
	    fileInsert(filename, "E", 1);
	    return;
	}

	std::string JourneyCode = std::to_string(l->JourneyCode);
	std::string price = std::to_string(l->price);

	if(l==root)
	{ // Storing root
	   string code = JourneyCode + " " + price;
	   fileInsert(filename, code, 0);
	}

	else if(l->parent->right==l)
	{ // Storing right child
		string code = "{ R "+ JourneyCode + " " + price;
		fileInsert(filename, code, 1);
	}

	else
	{ //Storing left child
	    string code = "{ L "+ JourneyCode + " " + price;
		fileInsert(filename, code, 1);
	}

	Store(filename, l->left);
	Store(filename, l->right);

	if(l!=root)
	{ //Close a subtree
	    string code = "}";
	    fileInsert(filename, code, 1);
	}

	return;

}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
	Store(filename, root);
	fileInsert(filename, "X",1);

    return;

}

// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.





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
        cout << root->JourneyCode << endl;
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
        result.push_back(to_string(root->JourneyCode) + "\n");
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
