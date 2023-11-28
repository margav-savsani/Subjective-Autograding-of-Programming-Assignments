#include "myTree.cpp"

// class AVL{
//     TreeNode* root;

// public:
//     void rotate(TreeNode* y, TreeNode*x); //rotate y about x
// };

int BST :: getBalance(TreeNode *x){
    int height_left = 0;
    if(x!=nullptr && x->left!=nullptr) height_left = x->left->height;
    int height_right = 0;
    if(x!=nullptr && x->right!=nullptr) height_left = x->right->height;
    return (height_left - height_right);
}
/**
 * @brief single rotation - it is working perfectly fine
 *
 * @param y rotate y
 * @param x about x
 */
void BST :: rotate(TreeNode* y, TreeNode*x){
    if(y!=nullptr && x!=nullptr){
        if(y->right==x){ //rotate y counter clockwise - 3 cases in this - if y is left or right child and if y has no parent
            if(y->parent!=nullptr){ //y is not the root node itself
                x->parent=y->parent;
                y->right = x->left;
                if(y==y->parent->left){//y is left child
                    y->parent->left=x;
                }
                else if(y==y->parent->right){ //y is right child
                    y->parent->right=x;
                }
                y->parent=x;
                x->left=y;
            }
            else {//y is the root
                    x->parent=y->parent;
                    y->parent=x;
                    y->right = x->left;
                    x->left = y;
                    root = x;
             }
        }
        else if(y->left==x){ //rotate y clockwise - 3 cases in this - if y is left or right child and if y has no parent
            if(y->parent!=nullptr){
                x->parent=y->parent;
                y->left = x->right;
                if(y==y->parent->left){//y is left child
                    y->parent->left=x;
                }
                else if(y==y->parent->right){ //y is right child
                    y->parent->right=x;
                }
                y->parent=x;
                x->right = y;
            }
            else{ //y is root
                x->parent=y->parent;
                y->parent=x;
                y->left = x->right;
                x->right = y;
                root = x;
            }
        }
    }
}
/**
 * @brief double rotation, basically single rotation twice
 *
 * @param currNode pivot node
 * @param parentNode rotate parent node about currNode
 * @param grandParentNode then grandparent node about curr Node
 */
void BST :: DoubleRotation(TreeNode * currNode, TreeNode * parentNode, TreeNode * grandParentNode){
    rotate(parentNode, currNode);
    rotate(grandParentNode, currNode);
}
// void BST :: RightLeft(TreeNode * currNode, TreeNode * parentNode, TreeNode * grandParentNode){
//     rotate(parentNode, currNode);
//     rotate(grandParentNode, currNode);
// }

/**
 * @brief since we can't access pointers directly from main, this function helps in printing the rotated tree
 *
 */
void BST :: printer (){
    rotate(root->right, root->right->right);
}

int main(){
    BST * T;
    T = new BST;
    
    T->insert(5,1);
    T->insert(6,1);
    T->insert(7,1);
    T->printBST("", false) ;
    T->printer();
    T->printBST("", false);
}
