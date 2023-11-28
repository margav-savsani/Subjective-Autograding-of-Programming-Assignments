#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define preorder 0
#define inorder 1
#define postorder 2

struct TreeNode{
    int key;
    int value;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(){left=nullptr; right=nullptr; parent=nullptr; key=-1; value=-1; height=0;}
    // ~TreeNode();
};

class BST{
    TreeNode* root; 
    TreeNode* found_ptr; 
    string walk;
   
public:
    BST(){root=new TreeNode; walk = "";}
    void insert(int key, int value);
    bool find(int key, int value);
    void remove(int key, int value);
    void traverse(int type);
    int getMinimum();
    void PreOrder_Walk(TreeNode* x);
    void PostOrder_Walk(TreeNode* x);
    void InOrder_Walk(TreeNode* x);
    int countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
    
    
    TreeNode* successor(TreeNode* x);
    TreeNode* predecessor(TreeNode* x);
    void printBST(const string& prefix, bool isLeft);

    void rotate(TreeNode* y, TreeNode* x);
    void printer();
    // void LeftRight(TreeNode * currNode, TreeNode * parentNode, TreeNode * grandParentNode);
    void DoubleRotation(TreeNode * currNode, TreeNode * parentNode, TreeNode * grandParentNode);

    int getBalance(TreeNode* x);
    int height(TreeNode * N);
    
};
int max(int a, int b){
    if (a > b) return a;
    return b;
}
void BST:: insert(int key_, int value_){
    
    TreeNode* x = root; //copying address of root in x, now x will act as an iterator
    
    TreeNode* y; //will be used for a new node
    cout << x << endl;
    y = new TreeNode;
    TreeNode* z; //trailing pointer
    cout << x->left << " " << x->right << endl;
    
    while( x!=nullptr && (x->right!=nullptr || x->left!=nullptr)){ //when x is not pointing at nothing
        z=x; //stores parent
        if(key_ < x->key) x=x->left;
        else x=x->right;
    }
    y->key=key_;
    y->value=value_;
    if(x==nullptr) {
        y->parent=z; 
        if(y->key < z->key) z->left = y; 
        else z->right = y;
        // y->height = 1;
        // while(z->parent!=nullptr){
        //     if(z->right!=nullptr && z->left!=nullptr) {
        //         z->height = 1 + max(z->left->height, z->right->height);
        //         z = z->parent;
        //     }
        //     else if(z->right != nullptr && z->left ==nullptr){
        //         z->height = z->right->height + 1;
        //         z = z->parent;
        //     }
        //     else if(z->right == nullptr && z->left !=nullptr){
        //         z->height = z->left->height + 1;
        //         z = z->parent;
        //     }
        //     else if(z->left==nullptr && z->right==nullptr){
        //         z->height = 1;
        //         z=z->parent;
        //     }
        // }
    }
    else {
        y->parent=x;
        if(x->key==-1){// new node is root itself, i.e inserting a root in an empty tree
            root->key=key_; 
            root->value=value_;
            delete y;
        }
        else if (y->key < x->key) {
            x->left=y;

        }
        else x->right=y;
        // while(x->parent!=nullptr){
        //     if(x->right!=nullptr && x->left!=nullptr) {
        //         x->height = 1 + max(x->left->height, x->right->height);
        //         x = x->parent;
        //     }
        //     else if(x->right != nullptr && x->left ==nullptr){
        //         x->height = x->right->height + 1;
        //         x = x->parent;
        //     }
        //     else if(x->right == nullptr && x->left !=nullptr){
        //         x->height = x->left->height + 1;
        //         x = x->parent;
        //     }
        //     else if(x->left==nullptr && x->right==nullptr){
        //         x->height = 1;
        //         x=x->parent;
        //     }
        
        // }
        y->height = 1;
        while(y!=nullptr){
            y=y->parent;
            if(y!=nullptr && y->key != -1 && y->value!= -1){
                if(y->left!=nullptr && y->right!=nullptr) y->height = 1 + max(y->left->height, y->right->height);
                else if(y->left!=nullptr && y->right==nullptr) y->height = 1 + y->left->height;
                else if(y->left==nullptr && y->right!=nullptr) y->height = 1 + y->right->height;
                else if(y->left==nullptr && y->right==nullptr) y->height = 1 ;
            }
            if(y!=nullptr) cout << y->height << " key" << y->key << endl;
        }
    //y is child, x is its parent
    }
    
}

//InOrder Tree Traversal
void BST :: InOrder_Walk(TreeNode* x){
    
    if(x!=nullptr){//when x is not pointing at nothing
        InOrder_Walk(x->left);
        cout <<"; key: " << x->key << ", height: " << x->height ;
        string temp = to_string(x->key);
        walk = walk.append(temp);
        walk = walk.append(",");
        InOrder_Walk(x->right);
    }
}

void BST :: PreOrder_Walk(TreeNode* x){
    
    if(x!=nullptr){//when x is not pointing at nothing
        cout << x->key;
        PreOrder_Walk(x->left);
        PreOrder_Walk(x->right);
    }
}

void BST :: PostOrder_Walk(TreeNode* x){
   
    if(x!=nullptr){//when x is not pointing at nothing
        PostOrder_Walk(x->left);
        PostOrder_Walk(x->right);
        cout << x->key;
    }
}

// void BST :: printBST(){
//     InOrder_Walk(root);
//     cout << "hello";
// }

bool BST :: find(int key_, int value){
    TreeNode*x = root; 
    
    while(x!=nullptr){ // atleast one child exists and key not found
        if(key_ == x->key) {
            found_ptr=x; 
            // cout << "found " << x->key << endl; 
            return true;}
        if(key_ < x->key) {
            x=x->left;
        }
        else x=x->right;
    }
    found_ptr=nullptr;
    return false; //key found nowhere
}

void BST :: traverse(int type){
    if(type==0) PreOrder_Walk(root);
    else if(type==1) InOrder_Walk(root);
    else if(type==2) PostOrder_Walk(root);
}

int BST:: getMinimum(){
    TreeNode* x = root;
    while(x->left!=nullptr){
        x = x->left;
    }
    return x->key;
}

TreeNode* BST:: successor(TreeNode* x){ //node at extreme left in right subtree
    TreeNode* y=nullptr;
    if(x!=nullptr) y=x->right;
    if(y!=nullptr){ //when right subtree exists
        //returning minimum
        while(y->left!=nullptr) y = y->left;
    }
    // //when right subtree does not exist
    // while(x->parent != nullptr && x==x->parent->right){ 
    //     //keep going up the tree till the node is left subtree of its parent tree
    //     x=x->parent;
    //     x->parent=x->parent->parent;
    // }
    return y;
}
TreeNode* BST:: predecessor(TreeNode* x){//extreme right node in left subtree
    TreeNode* y=nullptr;
    if(x!=nullptr) y=x->left;
    if(y!=nullptr){ //when left subtree exists
        //returning max in left subtree
        while(y->right!=nullptr) y = y->right;
    }
    // //when right subtree does not exist
    // while(x->parent != nullptr && x==x->parent->left){ 
    //     //keep going up the tree till the node is left subtree of its parent tree
    //     x=x->parent;
    //     x->parent=x->parent->parent;
    // }
    return y;
}

void BST :: remove(int key, int value){
    find(key, value); //calling the find function to set found_ptr to required node
    if(found_ptr==nullptr) cout << "nothing to remove" << endl;
    else { //in whole else found_ptr != nullptr, but no condition on its parent and children yet
    // if node to delete is leaf
        if(found_ptr->left==nullptr && found_ptr->right==nullptr){ 
            //non root case
            if(found_ptr->parent!=nullptr){
                if(key < found_ptr->parent->key) found_ptr->parent->left = nullptr;
                else found_ptr->parent->right = nullptr;
                delete found_ptr;
                found_ptr=nullptr;
            }
            //root case i.e if parent of the leaf to remove is nullptr (i need to specify this case separately, because found_ptr->parent is called in the above case)
            else{ //found_ptr->parent == nullptr
                delete found_ptr; //deallocates the memory 
                found_ptr = nullptr; //sets the variable to nullptr
            }
        }
    //if node to delete has one subtree
        else if(found_ptr->left != nullptr && found_ptr->right==nullptr){ //only left subtree exists.
            if(found_ptr->parent!=nullptr){ //node to delete is not the root
                if(key < found_ptr->parent->key){ //all three nodes on left
                found_ptr->parent->left=found_ptr->left;
                found_ptr->left->parent=found_ptr->parent;
                delete found_ptr;
                found_ptr=nullptr;
                }
                else { //parent's right is found_ptr and foundptr's left is his child
                    found_ptr->parent->right=found_ptr->left;
                    found_ptr->left->parent=found_ptr->parent;
                    delete found_ptr;
                    found_ptr=nullptr;
                }
            }
            else{ //node to delete is root
                if(key<found_ptr->left->key){
                    found_ptr->left->parent = nullptr;
                    found_ptr->left=nullptr;
                    delete found_ptr;
                    found_ptr=nullptr;
                }
            }
        }
        else if(found_ptr->right != nullptr && found_ptr->left==nullptr){ //only right subtree exists.
            if(found_ptr->parent!=nullptr){ //if the node to delete is not root
                if(found_ptr->parent->key < key){//all three nodes on right
                    found_ptr->parent->right=found_ptr->right;
                    found_ptr->right->parent=found_ptr->parent;
                }
                
                else{ // parent - left child - right child of found_ptr
                    found_ptr->parent->left=found_ptr->right;
                    found_ptr->right->parent=found_ptr->parent;
                }
                delete found_ptr;
                found_ptr = nullptr;
            }
            else{ //node to delete is root
                found_ptr->right->parent=nullptr;
                found_ptr->right=nullptr;
                delete found_ptr;
                found_ptr=nullptr;
            }
        }
    //if node to delete has 2 subtrees
    //add condition when successor is just after the curr node
    //add conditions for root
        else{
            if(found_ptr->parent!=nullptr){//node to delete is not root
                if(key < found_ptr->parent->key){//node is left subtree
                    TreeNode* successor_node=successor(found_ptr);
                    if(successor_node->right!=nullptr){ //successor node has a right child
                        if(successor_node->parent!=nullptr){
                            if(successor_node->parent==found_ptr){ //successor_node->left=nullptr
                                found_ptr->key = successor_node->key;
                                found_ptr->value = successor_node->value;
                                successor_node->right->parent=found_ptr;
                                found_ptr->right=successor_node->right;
                            }
                            else{
                                successor_node->parent->left=successor_node->right;
                                successor_node->right->parent=successor_node->parent;
                                // successor_node->parent=found_ptr->parent;
                                // successor_node->right=found_ptr->right;
                                // successor_node->left=found_ptr->left;
                                found_ptr->key = successor_node->key;
                                found_ptr->value = successor_node->value;
                                // found_ptr->parent->left=successor_node;
                                // found_ptr->right->parent=successor_node;
                                // found_ptr->left->parent=successor_node;
                            }
                            delete successor_node;
                            successor_node=nullptr;
                        }
                    }
                    else{ //successor node does not have a right child - possible when root of right subtree is successor itself
                        if(successor_node->parent!=nullptr && successor_node->parent!=found_ptr){ //i missed second condition
                            successor_node->parent->left=nullptr;
                            
                            // successor_node->parent=found_ptr->parent;
                            // successor_node->right=found_ptr->right;
                            // successor_node->left=found_ptr->left;
                            found_ptr->key = successor_node->key;
                            found_ptr->value = successor_node->value;
                            // found_ptr->parent->left=successor_node;
                            // found_ptr->right->parent=successor_node;
                            // found_ptr->left->parent=successor_node;
                            delete successor_node;
                            successor_node=nullptr;
                        }
                        else{
                            // successor_node->parent=found_ptr->parent;
                            // successor_node->left=found_ptr->left;
                            // successor_node->right=nullptr;
                            found_ptr->key = successor_node->key;
                            found_ptr->value = successor_node->value;
                            found_ptr->right=nullptr;
                            // found_ptr->parent->left=successor_node;
                            // found_ptr->left->parent=successor_node;
                            delete successor_node;
                            successor_node=nullptr;
                        }
                    }
                }
                else{// node is right subtree
                    TreeNode* predecessor_node=predecessor(found_ptr);
                    if(predecessor_node->left!=nullptr){ //predecessor node has a left child
                        if(predecessor_node->parent!=nullptr){
                            if(predecessor_node->parent==found_ptr){ //i.e predecessor_node->right = nullptr
                                found_ptr->key = predecessor_node->key;
                                found_ptr->value = predecessor_node->value;
                                predecessor_node->left->parent=found_ptr;
                                found_ptr->left=predecessor_node->left;
                            }
                            else{
                                predecessor_node->parent->right=predecessor_node->left;
                                predecessor_node->left->parent=predecessor_node->parent;
                                // predecessor_node->parent=found_ptr->parent;
                                // predecessor_node->right=found_ptr->right;
                                // predecessor_node->left=found_ptr->left;
                                // found_ptr->parent->right=predecessor_node;
                                // found_ptr->left->parent=predecessor_node;
                                // found_ptr->right->parent=predecessor_node;
                                found_ptr->key = predecessor_node->key;
                                found_ptr->value = predecessor_node->value;
                            }
                            delete predecessor_node;
                            predecessor_node = nullptr;
                        }
                    }
                    else{ //predecessor node does not have a left child - possible when root of left subtree is predecessor itself  
                        if(predecessor_node->parent!=nullptr && predecessor_node->parent!=found_ptr){ //i missed second condition
                            predecessor_node->parent->right=nullptr;
                            // predecessor_node->parent=found_ptr->parent;
                            // predecessor_node->right=found_ptr->right;
                            // predecessor_node->left=found_ptr->left;
                            // found_ptr->parent->right=predecessor_node;
                            // found_ptr->left->parent=predecessor_node;
                            // found_ptr->right->parent=predecessor_node;
                            found_ptr->key = predecessor_node->key;
                            found_ptr->value = predecessor_node->value;
                            delete predecessor_node;
                            predecessor_node = nullptr;
                        }
                        else{
                            // predecessor_node->parent=found_ptr->parent;
                            // predecessor_node->right=found_ptr->right;
                            // predecessor_node->left=nullptr;
                            // found_ptr->parent->right=predecessor_node;
                            // found_ptr->right->parent=predecessor_node;
                            found_ptr->key = predecessor_node->key;
                            found_ptr->value = predecessor_node->value;
                            found_ptr->left=nullptr;
                            delete predecessor_node;
                            predecessor_node = nullptr;
                        }
                    }
                }
            }
            else{ //if node to delete is root with two subtrees
                TreeNode* successor_node=successor(found_ptr);
                    if(successor_node->right!=nullptr){ //successor node has a right child
                        if(successor_node->parent!=nullptr){
                            successor_node->parent->left=successor_node->right;
                            successor_node->right->parent=successor_node->parent;
                            found_ptr->key = successor_node->key;
                            found_ptr->value = successor_node->value;
                            delete successor_node;
                            successor_node=nullptr;
                            // successor_node->parent=nullptr;
                            // found_ptr->right->parent=successor_node;
                            // found_ptr->left->parent=successor_node;
                        }
                    }
                    else{ //successor node does not have a right child - possible when root of right subtree is successor itself 

                        if(successor_node->parent!=nullptr && successor_node->parent!=found_ptr){ //i missed second condition
                            successor_node->parent->left=nullptr;
                            found_ptr->key = successor_node->key;
                            found_ptr->value = successor_node->value;
                            delete successor_node;
                            successor_node=nullptr;
                            // successor_node->parent=nullptr;
                            // found_ptr->right->parent=successor_node;
                            // found_ptr->left->parent=successor_node;
                            // root = successor_node;
                        }
                        else{
                            successor_node->parent=nullptr;
                            // successor_node->left=found_ptr->left;
                            // found_ptr->left->parent=successor_node;
                            // root=successor_node;
                            found_ptr->key = successor_node->key;
                            found_ptr->value = successor_node->value;
                            delete successor_node;
                            successor_node=nullptr;
                        }
                    }
            }
        }
    }
}

int BST :: countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    TreeNode * iterator = root;
    int count = 0;
    if(iterator!=nullptr){//ensured that tree is not empty
        //traversal begins
        walk = ""; //always set walk to empty string, to nullify its previously stored value
        traverse(1);
        cout << walk  << endl;
        stringstream s(walk);
        char dummy_store;
        
        int dummy_number=0;
        while(s >> dummy_store){ 
            dummy_number=0;
            while(dummy_store != ','){
                int a = dummy_store - '0';
                dummy_number=dummy_number*10 + a;
                s >> dummy_store;
            }
            if(dummy_number >= lowerPriceBound && dummy_number <= upperPriceBound) count ++;
            if(dummy_number==upperPriceBound) break;
        }
    }
    return count; 
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
        cout << root->key << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

int main(){
    BST * T= new BST;
    T->insert(2,3);
    T->insert(1,3);
    T->insert(0,3);
    T->insert(6,3);
    T->insert(3,3);
    T->printBST("", false);
    T->traverse(1);
}
