#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
//constructor
BST::BST(){
    this->root=NULL;
     }
BST::BST(TreeNode *root){
    this->root=root;
     }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True 
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* to= new TreeNode(JourneyCode,price);//this is the node to be searched
    TreeNode * parent_ptr;
    TreeNode * child_ptr;
    child_ptr=root;
    parent_ptr=NULL;
    //loops continues till node is found
    while(child_ptr!=NULL){
        if(child_ptr->price==price && child_ptr->JourneyCode==JourneyCode){
            //if the node is found,return false as the node is already present
            return false;
        }
        //traverse the tree to find the node
        parent_ptr=child_ptr;
        if(price<=child_ptr->price){
            //if the price is left move to left
            child_ptr=child_ptr->left;
        }
        else{
            //if the price is more, move to right
            child_ptr=child_ptr->right;
        }

    }
    //attatching the node to the tree
    //comparing its price with the price of the parent node and accordingly joining it in the BST
    //if the price is equal, I have added it to the left
    to->parent=parent_ptr;
    if(parent_ptr==NULL){
        root=to;
        return true;
    }
    else{
        if(to->price<=parent_ptr->price){
            parent_ptr->left=to;
            return true;
        }
        else{
            parent_ptr->right=to;
            return true;
        }
    }

    return false;
    }

//finding the price in the tree
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode * roo;
    roo=root;
    while(roo!=NULL){
        if( price==roo->price && JourneyCode==roo->JourneyCode){//if the journey code and price match, return true
            return true;
        }
        if(price<=roo->price){//else traverse the tree
            roo=roo->left;
        }
        else{
            roo=roo->right;//else traverse the tree
        }
    }

  return false;
 }
	

//returns the predecessor value of the top found in the tree starting from top
TreeNode* BST::get_min(TreeNode* top){
    TreeNode * roo;
    roo=top;
    while(roo->right!=NULL){// move to right until you reach rightmost element
        roo=roo->right;
    }
    return roo; 
}

//removes the element from the tree
bool BST::remove(int JourneyCode, int price) { 
    //initialising the variables
    TreeNode * parent_ptr;
    parent_ptr=NULL;
    TreeNode * child_ptr;
    child_ptr=root;
// finding the node in the tree
    while(child_ptr !=NULL ){
        parent_ptr=child_ptr;
        if(price<child_ptr->price){
            child_ptr=child_ptr->left;
        }
        else if(price>child_ptr->price){
            child_ptr=child_ptr->right;
        }
        else {
            if(child_ptr->JourneyCode==JourneyCode){
                break;
            }
            else{
                child_ptr=child_ptr->left;
            }

        }
    }
    //if the required child is not found, function returns false
    if(child_ptr==NULL){
        return false;
    }

    //Leaf node that is teh required node has no children
   if(child_ptr->left==NULL && child_ptr->right==NULL){
    //in this case the  parent pointer simply starts poingting to null
    parent_ptr=child_ptr->parent;
        if(parent_ptr==NULL){
            root=NULL;
            return true;
        }
        if((parent_ptr->left) == (child_ptr)){
            parent_ptr->left=NULL;
        }
        else{
            parent_ptr->right=NULL;
        }
        return true;
    }
//if one child pointer is NULL
    else if(child_ptr->left==NULL || child_ptr->right==NULL){
        //initialisng the parent pointer
       parent_ptr=child_ptr->parent;
        if(parent_ptr==NULL){
            //if parent pointer is NULL that is the element to be deleted is thr root
            if(child_ptr->left!=NULL){
                root=child_ptr->left;
                root->parent=NULL;
            }
            else{
                root=child_ptr->right;
                root->parent=NULL;
            }
        }
        else{// if the required node is the left child
        if( parent_ptr->left==child_ptr){//elemnent to be deleted is the right child
            if(child_ptr->left!=NULL){//done
                parent_ptr->left=child_ptr->left;
                (child_ptr->left)->parent=parent_ptr;
            }
            else{
                parent_ptr->left=child_ptr->right;
                (child_ptr->right)->parent=parent_ptr;
            }
            
        }
        else {//if the parent has right child
            if(child_ptr->left!=NULL){//if child pointer has no right child
                parent_ptr->right=child_ptr->left;
                (child_ptr->left)->parent=parent_ptr;
            }
            else{
                parent_ptr->right=child_ptr->right;// if child pointer has no left child
                (child_ptr->right)->parent=parent_ptr;
            }
            
        }
        return true;
        }
    }
    // Having two children
    //using predecessor method
    else{
        //getting the predecessor 
       TreeNode * pre=get_min(child_ptr->left);
        TreeNode temp(pre->JourneyCode,pre->price);
        //deleting the predecessor
        remove(pre->JourneyCode,pre->price);
        //replacing the root by predecessor
        child_ptr->JourneyCode=temp.JourneyCode;
        child_ptr->price=temp.price;
        return true;
    }
    return true;
}
	
	
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST:: print_code(TreeNode * node){
    cout<<node->JourneyCode<<endl;
}

//pre order traversal of the tree
void BST:: pre_order(TreeNode * node){
    if(node==NULL){
        return;
    }
    else{
        //first node is examined, then the left hcild and then the right child
        print_code(node);
        pre_order(node->left);
        pre_order(node->right);
    }

}

//post order traversal of the tree
void BST:: post_order(TreeNode * node){
    if(node==NULL){
        return;
    }
    else{
        //first left child is examined, then the right child and lastly the node
        post_order(node->left);
        post_order(node->right);
        print_code(node);  
    }
    
}

//in order traversal of the tree
void BST:: in_order(TreeNode * node){
    if(node==NULL){
        return;
    }
    else{
        //first node's left child is examined then the value then right child of the node
        in_order(node->left);
        print_code(node);
        in_order(node->right);
    }
    
}

//type of traversal
//depending on the value of type of traversal calls the appropriate function
void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        pre_order(root);
    }
    if(typeOfTraversal==1){
        post_order(root);
    }
    if(typeOfTraversal==2){
        in_order(root);
    }
    return;
    }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode * roo;
    roo=root;
    while(roo->left!=NULL){//moves left till you reach the leftmost element
        roo=roo->left;
    }
    return roo->price; 
    }

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
//does inorder traversal
void BST:: in_order_check(TreeNode * node, int & counter,int lowerPriceBound, int upperPriceBound ){
    if(node==NULL){
        return;
    }
    else{
        // this function does the inorder traversal of the tree and increments the counter variable if node with required value are found
        in_order_check(node->left,counter,lowerPriceBound,  upperPriceBound );
        if (node->price>=lowerPriceBound && node->price<=upperPriceBound){
            counter++;
        }
        in_order_check(node->right, counter,lowerPriceBound,  upperPriceBound );
    }
}

//counts the journeys in between
//calls the inorder check function which counts and returns the required value
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int counter=0;
    in_order_check( root,counter,lowerPriceBound,upperPriceBound);
    return counter;
    }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

	
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


// function defined to print the value in the file
void BST::print_val(TreeNode *node,ofstream &outfile){
    outfile<<node->JourneyCode<<" "<<node->price<<endl;
} 

//does teh EULER traversal of the tree and inputs in teh file
void BST::Euler_travers (TreeNode*node,ofstream &outfile){
if(node!=NULL){
    print_val(node,outfile);
}
//denotes left child
if(node->left!=NULL){
    outfile<<"["<<endl;
    Euler_travers(node->left,outfile);
    outfile<<"]"<<endl;
}
//denoted right child
if(node->right!=NULL){
    outfile<<"<"<<endl;
    Euler_travers(node->right,outfile);
    outfile<<">"<<endl;
}

}

//stores teh tree in te file by calling teh function
void BST::customStore(string filename) { 
    ofstream outfile;
    outfile.open(filename);
    Euler_travers(root,outfile);
    return; 
}

// this function loads the ree into another tree
void BST::customLoad (int flag, string filename) { 
//initialising variables
ifstream f1(filename); 
string line;
string word;
//head is the pointer which tracks where the variable is to be inserted
TreeNode*head=root;
char last_found;
int left_open=0;
int left_close=0;
int right_count=0;

// read file line by line
while (getline(f1, line)) {


int word_count = 0;
    stringstream ss(line);
//counting the number of words in the file
    while (ss >> word) {
        ++word_count;
    }
 
// if word count =2 that means that line represents a node
if(word_count==2){
    // if its the root
    if(head==NULL){
        stringstream words(line);
        words >> word;
        root=new TreeNode();
// storing the data in thhe root
        root->JourneyCode=stoi(word);
        words >> word;

        root->price=stoi(word);
        head=root;
    }
    else{
        // if tree is not NULL
        //initiallisng the variables
        TreeNode*element =new TreeNode();
        stringstream words(line);
        words >> word;
        element->JourneyCode=stoi(word);
        words >> word;
        element->price=stoi(word);
      // if this is the last found element, accordingly inserting the node at right or left and shifting the head pointer
        if (last_found=='['){
            head->left=element;
            element->parent=head;
            head=head->left;
        }
       
        if (last_found=='<'){
            head->right=element;
            element->parent=head;
            head=head->right;
        } 
    }
}

else{
   const char *c = line.c_str();
     // setting last found variable so that the next element is inserted as left tree
    if(strcmp(c,"[")==0){
        last_found='[';
        left_open++;
    }
     //setting last found variable so that next element is inserted as right tree
  if(strcmp(c,"<")==0){
        last_found='<';
        right_count++;
    }
    //moving the head
  if(strcmp(c,">")==0){
        head=head->parent;
    }
    //moving the head
    if(strcmp(c,"]")==0){
        left_close++;
        head=head->parent;
    }
    //if no left tree is found
    if(right_count==1 && left_open==0){
        root=NULL;
        return;
    }
    // if teh argument passed in 4, print the left tree
    //if teh root has no left tree print NULL
    // if the number of opening and closing brackets are equal that means left tree gets complete
    if(left_open==left_close && flag==4 && left_open!=0){
        root=root->left;
        return;
    }
    }
}
return;
}


// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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