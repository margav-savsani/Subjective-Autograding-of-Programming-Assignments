#include <iostream>
#include <streambuf>
#include <stack>

const int LEFT = 0;
const int RIGHT = 1;

class BinarySearchTree{
    //Each BinarySearchTree is owned by it's parent owns it's children
    //Left subtree of a node contains elements less than or equal to the node
    //Right subtree of a node contains elements strictly greater than the node
public:
    BinarySearchTree* parent; //used as a weak pointer, ie it does not own its parent
    BinarySearchTree* left;
    BinarySearchTree* right;
    int value;
    BinarySearchTree(int value = 0, BinarySearchTree* parent = nullptr, BinarySearchTree* left = nullptr, BinarySearchTree* right = nullptr){
        this->parent=parent;
        this->left=left;
        this->right=right;
        this->value=value;
    }
    ~BinarySearchTree(){
        //deletes only the children of the node
        if(left)
            delete left;
        if(right)
            delete right;
    }    
    BinarySearchTree* find_min_of_subtree(){
        //Returns the minimum element of the subtree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!left)
            return this;
        else
            return left->find_min_of_subtree();
    }
    BinarySearchTree* find_max_of_subtree(){
        //Returns the maximum element of the subtree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!right)
            return this;
        else
            return right->find_max_of_subtree();
    }
    BinarySearchTree* find_max_of_tree(){
        //Returns the maximum element of the tree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!parent)
            return this->find_max_of_subtree(); 
        return parent->find_max_of_tree();
    }
    BinarySearchTree* find_min_of_tree(){
        //Returns the maximum element of the tree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!parent)
            return find_min_of_subtree();
        return this->find_min_of_tree();
    }
    BinarySearchTree* find_element_in_subtree(int val){
        //returns a pointer to the topmost instance of the element having the same value in the subtree(starting from and including the root)
        //returns NULL if the element is not found
        if(value==val)
            return this;
        if(value<val && left)
            return left->find_element_in_subtree(val);
        if(value>val && right)
            return right->find_element_in_subtree(val);
        return NULL;
    }
    BinarySearchTree* find_element_in_tree(int val){
        //returns a pointer to the topmost instance of the element having the same value in the tree
        //returns NULL if the element is not found
        if(!parent)
            return find_element_in_subtree(val);
        return parent->find_element_in_tree(val);
    }
protected:
    void insert_in_subtree(int val){
        //inserts a value in the binary search tree at the appropriate location
        //this does not move any of the existing elements
        //Insertion happens in the subtree(including the root)
        //May not preserve the properties of the binary tree if insertion happens in the wrong subtree
        if(val<=value){
            if(!left)
                left = new BinarySearchTree(val, this);
            else left->insert_in_subtree(val);
        }
        else{
            if(!right)
                right = new BinarySearchTree(val, this);
            else right->insert_in_subtree(val);
        }
    }
public:
    void insert_in_tree(int val){
        //inserts a value in the binary search tree at the appropriate location
        //this does not move any of the existing elements
        //Insertion happens in the whole tree
        if(!parent)
            return insert_in_subtree(val);
        return parent->insert_in_subtree(val);
    } 
    void rotate(BinarySearchTree* top_node, int dir1, int dir2){
        //assumes that the node to be rotated has atleast one child in the direction dir1 and also the grandchild is present in the spcified direction
        // it is fine if the grandchild is not present when both directions are the same
        if(dir1==LEFT && dir2==LEFT){
            BinarySearchTree* mid_node = top_node->left;
            if(top_node->parent){
                if(top_node->parent->left==top_node)
                    {top_node->parent->left = top_node->left;}
                else
                    {top_node->parent->right = mid_node;}
            }
            mid_node->parent = top_node->parent;
            top_node->parent = mid_node;
            top_node->left = mid_node->right;
            if(top_node->left)
                top_node->left->parent = top_node;
            mid_node->right = top_node;
        }
        if(dir1==RIGHT && dir2==RIGHT){
            BinarySearchTree* mid_node = top_node->right; 
            if(top_node->parent){
                if(top_node->parent->left==top_node)
                    top_node->parent->left = mid_node;
                else
                    top_node->parent->right = mid_node;
            }
            mid_node->parent = top_node->parent;
            top_node->parent = mid_node;
            top_node->right = mid_node->left;
            if(top_node->right)
                top_node->right->parent = top_node;
            mid_node->left = top_node;
        }
        if(dir1==RIGHT && dir2==LEFT){
            BinarySearchTree* mid_node = top_node->right;
            BinarySearchTree* end_node = top_node->right->left;
            if(top_node->parent){
                if(top_node->parent->left == top_node)
                    top_node->parent->left = end_node;
                else
                    top_node->parent->right = end_node;
            }
            end_node->parent = top_node->parent;
            top_node->right = end_node->left;
            if(top_node->right)
                top_node->right->parent = top_node;
            mid_node->left = end_node->right;
            if(mid_node)
                mid_node->left->parent = mid_node;
            end_node->left = top_node;
            end_node->right = mid_node;
            mid_node->parent = end_node;
            top_node->parent = end_node;
        }
        if(dir1==LEFT && dir2==RIGHT){
            BinarySearchTree* mid_node = top_node->left;
            BinarySearchTree* end_node = top_node->right;
            if(top_node->parent){
                if(top_node->parent->left == top_node)
                    top_node->parent->left = end_node;
                else
                    top_node->parent->right = end_node;
            }
            end_node->parent = top_node->parent;
            top_node->left = end_node->right;
            if(top_node->left)
                top_node->left->parent = top_node;
            mid_node->right = end_node->left;
            if(mid_node)
                mid_node->right->parent = mid_node;
            end_node->right = top_node;
            end_node->left = mid_node;
            mid_node->parent = end_node;
            top_node->parent = end_node;
        }
    }
    void non_recursive_printall_in_subtree(){
        std::stack<BinarySearchTree*> s;
        BinarySearchTree* x = this;
        std::cout<<(value)<<" ";
        if(left) s.push(left);
        if(right) s.push(right);
        while(!s.empty()){
            x = s.top();
            s.pop();
            std::cout<<x->value<<" ";
            if(x->left)
                s.push(x->left);
            if(x->right)
                s.push(x->right);
        }
    } 
};

int main(){
    BinarySearchTree* A = new BinarySearchTree(-1);
    A->insert_in_tree(10);
    A->insert_in_tree(20);
    A->insert_in_tree(11);
    A->insert_in_tree(5);
    A->insert_in_tree(7);
    A->insert_in_tree(1);
    A->non_recursive_printall_in_subtree();
    std::cout<<std::endl;
    A->rotate(A->right, RIGHT, LEFT);
    A->non_recursive_printall_in_subtree();
    std::cout<<std::endl;
    delete A;   
}
