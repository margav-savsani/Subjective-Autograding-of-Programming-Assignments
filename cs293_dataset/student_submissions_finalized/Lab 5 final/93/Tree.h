#include <iostream>
#include <streambuf>
#include <stack>
#include <string>

#ifndef TREE_H
#define TREE_H
#endif

class TreeNode{
    //Each TreeNode is owned by it's parent owns it's children
    //Left subtree of a node contains elements less than or equal to the node
    //Right subtree of a node contains elements strictly greater than the node
private:
    static const int LEFT = 0;
    static const int RIGHT = 1;
public:
    TreeNode* parent; //used as a weak pointer, ie it does not own its parent
    TreeNode* left;
    TreeNode* right;
    int JourneyCode;
    int price;
    int height; //height of a single node is 1
    TreeNode(int Jcode, int price, TreeNode* parent = nullptr, TreeNode* left = nullptr, TreeNode* right = nullptr){
        this->parent=parent;
        this->left=left;
        this->right=right;
        this->JourneyCode=Jcode;
        this->price = price;
        height = 1;
    }
    // ~TreeNode(){
    //     //deletes only the children of the node
    //     if(left)
    //         delete left;
    //     if(right)
    //         delete right;
    // }    
    TreeNode* find_min_of_subtree(){
        //Returns the minimum element of the subtree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!left)
            return this;
        else
            return left->find_min_of_subtree();
    }
    TreeNode* find_max_of_subtree(){
        //Returns the maximum element of the subtree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!right)
            return this;
        else
            return right->find_max_of_subtree();
    }
    TreeNode* find_max_of_tree(){
        //Returns the maximum element of the tree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!parent)
            return this->find_max_of_subtree(); 
        return parent->find_max_of_tree();
    }
    TreeNode* find_min_of_tree(){
        //Returns the maximum element of the tree including the root
        //Note that this will lead to undefined behaviour if the pointer pointing to the element is used after the parent is deleted
        if(!parent)
            return find_min_of_subtree();
        return this->find_min_of_tree();
    }
protected:
    TreeNode* insert_in_subtree(int val, int price, int& num_comp){
        //inserts a value in the binary search tree at the appropriate location
        //this does not move any of the existing elements
        //Insertion happens in the subtree(including the root)
        //May not preserve the properties of the binary tree if insertion happens in the wrong subtree
        num_comp+=1;
        if(val<=JourneyCode){
            if(!left){
                left = new TreeNode(val, price, this);
                return left;
            }
            else return left->insert_in_subtree(val, price, num_comp);
        }
        else{
            if(!right){
                right = new TreeNode(val, price, this);
                return right;
            }
            else return right->insert_in_subtree(val, price, num_comp);
        }
    }
public:
    void update_heights_of_ancestors(){
        //updates the heights of the given node and all its ancestors in the tree
        update_height();
        if(parent)
            parent->update_heights_of_ancestors();
    }
    void update_height(){
        //updates the height of the node
        if(left && right){
            height = std::max(right->height, left->height)+1;
        }
        else if(left){
            height = left->height+1;
        }
        else if(right){
            height = right->height+1;
        }
        else{
            height = 1;
        }
    }
    TreeNode* find_grandchild_of_unbalanced_ancestor(){
        //returns the location of the grandchild of the first unbalanced ancestor of the node on which the function has been called
        //the returned location is also an ancestor of the node on which this is called
        //has to be called on a leaf
        //if no such node is present, then this returns NULL
        if(!parent || !parent->parent)
            return NULL;
        if(!parent->parent->is_balanced())
            return this;
        else return parent->find_grandchild_of_unbalanced_ancestor();
    }
public:
    bool is_balanced(){
        //returns true if the difference in heights of the left and right subtrees is atmost 1
        if(left && right){
            return (left->height-right->height<=1 && left->height-right->height>=-1);
        }
        else if(left){
            return left->height<=1;
        }
        else if(right){
            return right->height<=1;
        }
        return true;
    }
    int insert_in_tree(int val, int price);
    int insert_in_BST(int val, int price);
    // int insert_in_tree(int val, int price){    
    //     //inserts a value in the binary search tree at the appropriate location
    //     //this does not move any of the existing elements
    //     //Insertion happens in the whole tree
    //     //returns 10*(number of comparisons that happen during insertion)+(number of parent-child updates)
    //     int num_comp = 0, num_updates = 1;
    //     TreeNode* temp = this;
    //     while(temp->parent){
    //         temp = temp->parent;   
    //     }
    //     temp = temp->insert_in_subtree(val, price, num_comp); //store the location of the new node in temp
    //     //update heights in the tree
    //     temp->update_heights_of_ancestors();
    //     temp = temp->find_grandchild_of_unbalanced_ancestor(); //store the address of the first unbalanced ancestor in temp
    //     if(!temp) return num_comp;
    //     std::cout<<temp->JourneyCode<<std::endl;
    //     int dir1, dir2;
    //     if(temp->parent->left == temp)
    //         dir2 = LEFT;
    //     else dir2 = RIGHT;
    //     if(temp->parent->parent->left == temp->parent)
    //         dir1 = LEFT;
    //     else dir1 = RIGHT;
    //     if(dir1==dir2){
    //         num_updates += rotate(temp->parent->parent, dir1, dir2);
    //         temp->parent->right->update_height(); 
    //         temp->parent->left->update_height();
    //         temp->parent->update_heights_of_ancestors();  
    //     }
    //     else if(dir1==LEFT){
    //         num_updates += rotate(temp->parent->parent, LEFT, RIGHT);
    //         temp->right->update_height();
    //         temp->left->update_height();
    //         temp->update_heights_of_ancestors();
    //     }
    //     else{
    //         num_updates += rotate(temp->parent->parent, RIGHT, LEFT);
    //         temp->right->update_height();
    //         temp->left->update_height();
    //         temp->update_heights_of_ancestors();
    //     }
    //     return 10*num_comp+num_updates;//since the number of updates is always less than 6, we can use this scheme to pass both
    // } 
public:
    int rotate(TreeNode* top_node, int dir1, int dir2){
        //assumes that the node to be rotated has atleast one child in the direction dir1 and also the grandchild is present in the spcified direction
        // it is fine if the grandchild is not present when both directions are the same
        //if dir1!=dir2, both the child and the grandchild have to be present
        //uses 0 for left and 1 for right in dir1 and dir2
        //does not update the heights of nodes in the the new tree
        //returns the number of parent-child updates
        int num_updates{0};
        if(dir1==LEFT && dir2==LEFT){
            TreeNode* mid_node = top_node->left;
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
            num_updates+=3;
        }
        if(dir1==RIGHT && dir2==RIGHT){
            TreeNode* mid_node = top_node->right; 
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
            num_updates+=3;
        }
        if(dir1==RIGHT && dir2==LEFT){
            TreeNode* mid_node = top_node->right;
            TreeNode* end_node = top_node->right->left;
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
            if(mid_node->left)
                mid_node->left->parent = mid_node;
            end_node->left = top_node;
            end_node->right = mid_node;
            mid_node->parent = end_node;
            top_node->parent = end_node;
            num_updates+=5;
        }
        if(dir1==LEFT && dir2==RIGHT){
            TreeNode* mid_node = top_node->left;
            TreeNode* end_node = top_node->left->right;
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
            if(mid_node->right)
                mid_node->right->parent = mid_node;
            end_node->right = top_node;
            end_node->left = mid_node;
            mid_node->parent = end_node;
            top_node->parent = end_node;
            num_updates+=5;
        }
        return num_updates;
    }
    void printInfo()
    {
        // std::cout << "[JC: " << JourneyCode << ", P: " << price << ", H: " << height << "]";
        std::cout<<JourneyCode<<" "<<height<<" ";
    }
    bool operator < (TreeNode const &node)
    {
        if (JourneyCode < node.JourneyCode) return true;
        else return false;
    }
    bool operator == (TreeNode const &node)
    {
        if (JourneyCode == node.JourneyCode) return true;
        else return false;
    }
};

using namespace std;

void printBinaryTree(TreeNode *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->printInfo();
    cout << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    // cout << "NULL tree" << endl;
  }
}

// int main(){
//     TreeNode* A = new TreeNode(-1, 10);
//     printBinaryTree(A, "", 0);
//     A->insert_in_tree(10, 10);
//     while(A->parent)
//         A = A->parent;
//     printBinaryTree(A, "", 0);
//     A->insert_in_tree(20, 20);
//     while(A->parent)
//         A = A->parent;
//     printBinaryTree(A, "", 0);
//     A->insert_in_tree(11, 11);
//     while(A->parent)
//         A = A->parent;
//     printBinaryTree(A, "", 0);
//     A->insert_in_tree(5, 5);
//     while(A->parent)
//         A = A->parent;
//     printBinaryTree(A, "", 0);
//     A->insert_in_tree(7, 7);
//     while(A->parent)
//         A = A->parent;
//     printBinaryTree(A, "", 0);
//     A->insert_in_tree(1, 1);
//     while(A->parent)
//         A = A->parent;
//     printBinaryTree(A, "", 0);
//     A->insert_in_tree(12, 12);
//     while(A->parent)
//         A = A->parent;
//     printBinaryTree(A, "", 0); 
// }
