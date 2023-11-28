#include "tree.h"
//given a node, compute the values of the shortest, longest paths to a leaf node in
//any of the node's subtrees.
void update_lengths(TreeNode *node){
    if(node->left == NULL && node->right == NULL){
        node->shortest = 0; //leaf node
        node->longest = 0;
        return;
    }
    //if any one of the children is NULL, shortest will be 0
    //longest will be decided by the non-NULL child
    if(node->left == NULL){ 
        node->shortest = 0;
        node->longest = node->right->longest + 1;
        return;
    }
    if(node->right == NULL){
        node->shortest = 0;
        node->longest = node->left->longest + 1;
        return;
    }
    else{
        //need to find the earliest child that is a leaf or has both subtrees.
        TreeNode *temp = node->left;
        //Another implementation of the shortest path length function.
        // int x = 1, y = 1;
        // while(temp->shortest == 0){
        //     if(temp->left != NULL){temp = temp->left; x++;}
        //     else if(temp->right != NULL){temp = temp->right; x++;}
        //     else break;
        // }
        // x += temp->shortest;
        // temp = node->right;
        // while(temp->shortest == 0){
        //     if(temp->left != NULL){temp = temp->left; y++;}
        //     else if(temp->right != NULL){temp = temp->right; y++;}
        //     else break;
        // }
        // y += temp->shortest;
        // node->shortest = min(x, y);
        node->shortest = min(node->left->shortest, node->right->shortest) + 1;
        //for the longest path
        node->longest = max(node->left->longest, node->right->longest) + 1;
        return;
    }
}

int TreeNode::getImbalance(){
    return longest - shortest;
}

TreeNode::TreeNode(Journey j): journey(j){};

BST::BST(TreeNode *r){root = r;}
BST::BST(){root = NULL;}

bool BST::insert(Journey j){
    if(root == NULL){ //inserting into an empty tree
        root = new TreeNode(j);
        return true;
    }
    if(find(j)) return false; //journey pair exists
    TreeNode *current = root;
    TreeNode *parent = NULL;
    while(true){
        parent = current;
        //move parent to a child based on price
        if(j < current->journey) current = current->left;
        else current = current->right;
        if(current == NULL) break;
        //reached a leaf
    }
    TreeNode *to_insert = new TreeNode(j); //node to insert
    to_insert->parent = parent;
    //put node as left child if its price <
    //in right if >=
    if(j < parent->journey) parent->left = to_insert;
    else parent->right = to_insert;
    current = to_insert;
    while(current != NULL){
        update_lengths(current);
        current = current->parent;
    }
    return true;
}

bool BST::find(Journey j){
    if(root == NULL) return false;
    TreeNode* current = root;
    while(true){
        if(current->journey == j) return true;
        else{
            if(j < current->journey) current = current->left;
            else current = current->right;
        }
        if(current == NULL) return false;
        //reached a leaf, but pair not found
    }
}

bool BST::remove(Journey j) {
    if(!find(j)) return false;
    //pair doesn't exist
    TreeNode *node = root;
    //find the node to be removed
    while(true){
        if(node->journey == j) break;
        else{
            if(j < node->journey) node = node->left;
            else node = node->right;
        }
    }
    //is a leaf
    //make appropriate parent's child pointer NULL
    if(node->left == NULL && node->right == NULL){
        if(node == root){
            root = NULL; //empty tree now
            return true;
        }
        if(node->parent->left == node) node->parent->left = NULL;
        else node->parent->right = NULL;
        TreeNode *current = node->parent; //updating the path lengths of all the previous nodes.
        while(current != NULL){
            update_lengths(current);
            current = current->parent;
        }
        delete node;
        return true;
    }
    //if only one of the node's subtrees is non-empty, make its parent point to it.
    //if node is root, set the sub-tree's root as root
    if(node->right == NULL){
        if(node == root){
            delete root;
            root = node->left;
            return true;
        }
        if(node->parent->left == node) node->parent->left = node->left;
        else node->parent->right = node->left;
        node->left->parent = node->parent;
        TreeNode *current = node->parent; //updating the path lengths of all the previous nodes.
        while(current != NULL){
            update_lengths(current);
            current = current->parent;
        }
        delete node;
        return true;
    }
    if(node->left == NULL){
        if(node == root){
            delete root;
            root = node->right;
            return true;
        }
        if(node->parent->left == node) node->parent->left = node->right;
        else node->parent->right = node->right;
        node->right->parent = node->parent;
        TreeNode *current = node->parent; //updating the path lengths of all the previous nodes.
        while(current != NULL){
            update_lengths(current);
            current = current->parent;
        }
        delete node;
        return true;
    }
    //find the successor, (leftmost of right subtree (non-empty))
    TreeNode *succ = node->right;
    while(succ->left != NULL) succ = succ->left;
    //copy the journey of the successor
    Journey temp = succ->journey;
    //remove the successor node
    //cases based on if it has a parent (of whom it is a left child)
    //or if it is the right child of the node itself
    if(succ->left == NULL && succ->right == NULL){
        if(node->right == succ){
            node->right = NULL;
        }
        else succ->parent->left = NULL;
        TreeNode *current = succ->parent; 
        //updating the path lengths of all the previous nodes.
        while(current != NULL){
            update_lengths(current);
            current = current->parent;
        }
        delete succ;
    }
    else{
        if(node->right == succ){
            node->right = succ->right;
            succ->right->parent = node;
        }
        else{
            succ->parent->left = succ->right;
            succ->right->parent = succ->parent;
        }
        TreeNode *current = succ->parent; 
        //updating the path lengths of all the previous nodes.
        while(current != NULL){
            update_lengths(current);
            current = current->parent;
        }
        delete succ;
    }
    node->journey = temp;
    return true;
}
	
// Returns the code of the minimum journey (ordered by codes)
int BST::getMinimum() {
    //move left till leaf not found
    TreeNode *current = root;
    while(current->left != NULL){
        current = current->left;
    }
    return current->journey.getCode();
}

//*********************************************************************************************//

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->journey.getCode() << endl;
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
        result.push_back(to_string(root->journey.getCode()) + "\n");
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
