#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

class Node {
        public:
                int value;
                unsigned short timesVisited = 0;
                Node *parent1 = nullptr, *parent2=nullptr;
                int nVisited = 0;
                bool partOfCycle = false;

                // insert other fields and methods as appropriate
};
struct TreeNode{
        TreeNode* left, *right, *parent;
        int val;
        bool operator<(TreeNode &other) const{
                return this->val < other.val; 
        }

        TreeNode(int val){
                this->val = val;
        }
        TreeNode(Node* node){
            this->val = node->value;
        }

        bool updateParentChild(TreeNode *parentNode, bool isLeftChild)
        {
                if (parentNode != nullptr) {
                        parent = parentNode;
                        if (isLeftChild) {
                                parentNode->left = this;
                                // Only the left child is new, see if that changed the height
                        }
                        else {
                                parentNode->right = this;
                        }
                        return true;
                }
                else {
                        return false;
                }
        }
};

void printBinaryTree(TreeNode *root, const string& prefix, bool isLeft)
{
        if( root != nullptr )   {
                cout << prefix;

                cout << (isLeft ? "|--" : "|__" );

                // print the value of the node
                cout << root->val << endl;
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
                /* cout << "NULL tree" << endl; */
        }
}
class BST {

        private:
                TreeNode *root;
                // Recursively deletes all nodes in the binary tree rooted at currNode

                void recursiveDelete(TreeNode *currNode) {
                        if (currNode != nullptr) {
                                TreeNode *leftChild = currNode->left;
                                TreeNode *rightChild = currNode->right;

                                delete currNode;
                                recursiveDelete(leftChild);
                                recursiveDelete(rightChild);
                        }
                        return;
                }

                bool BSTLessThan(TreeNode* leftArg, TreeNode*rightArg) {
                        if ((leftArg != nullptr) && (rightArg != nullptr)) {
                                bool result = (*leftArg < *rightArg);
                                return result;
                        }
                        else {
                                cerr << "Unexpected exceptional condition!" << endl;
                                exit(-1);
                        }
                }

                void updateBSTParentChild(TreeNode *childNode, TreeNode *parentNode, bool isLeftChild)
                {
                        if ((childNode != nullptr) && (parentNode != nullptr)) {
                                childNode->updateParentChild(parentNode, isLeftChild);
                        }
                        else if ((childNode == nullptr) && (parentNode != nullptr)) {
                                if (isLeftChild) {
                                        parentNode->left = nullptr;
                                }
                                else {
                                        parentNode->right = nullptr;
                                }
                                // No updating of totalParentChildUpdateCost needed here
                        }
                        else if ((childNode != nullptr) && (parentNode == nullptr)) {
                                childNode->parent = nullptr;
                                // No updating of totalParentChildUpdateCost needed here
                        }
                        else {
                                // both childNode and parentNode are nullptr
                                // Nothing to do really
                                // No updating of totalParentChildUpdateCost needed here
                        }
                        return;
                }

        public:
                // Constructors
                BST() {
                        root = nullptr;
                }

                BST(TreeNode *newRoot, int perCompCost, int perParntChldUpdCost) {
                        root = newRoot;
                }

                // Destructor
                ~BST() {
                        recursiveDelete(root);
                }

                bool insert(int val);
                bool insert(Node &node){
                    return insert(node.value);
                }
                bool insert(Node *node){
                    return insert(node->value);
                }

                void print() { printBinaryTree(root, "", false); return;}
};



struct linkedListNodes{
        linkedListNodes* next, *prev;
        Node *node;

        linkedListNodes(){
                node = nullptr;
                next = prev = nullptr;
        }
        linkedListNodes(Node *nodeIn){
                this->node = nodeIn;
                next = prev = nullptr;
        }
};

struct listOfBSTs{
    BST *bst;
    listOfBSTs *next;
    listOfBSTs(){
        bst = new BST();
    }
};

class Graph {
        
        int numNodes;
        int numEdges;
        fstream graphFile;

        int nConnected = 0;// Number of connected components
        Node *nodes;
        linkedListNodes **adjacency; // Adjacency list
        listOfBSTs *bsts;// A linked list of the BSTs
        int nOnce, nTwice, nCycle; // The values to be saved

        public:
        Graph(int nNodes, int nEdges, string gFileName) {
                numNodes = nNodes;
                adjacency = new linkedListNodes*[nNodes];
                for (int i = 0; i< nNodes; i++){
                    adjacency[i] = nullptr;
                }
                numEdges = nEdges;
                graphFile.open(gFileName, ios::out);
                if (!graphFile.is_open()) {
                        cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
                        exit(-1);
                }

                graphFile << numNodes << endl;
                graphFile << numEdges << endl;

                nodes = new Node[numNodes];
                if (nodes == nullptr) {
                        cerr << "Memory allocation failure." << endl;
                        exit(-1);
                }

                for (int i = 0; i < numNodes; i++) {
                        nodes[i].value = i+1;
                }

                srand(time(0));
                int n1, n2;
                int countEdges = 0;
                nOnce = nTwice = nCycle = 0;

                bsts = nullptr;
                while (countEdges < numEdges) {
                        do {
                                n1 = rand() % numNodes;
                                n2 = rand() % numNodes;
                        } while (n1 == n2);

                        // Create an undirected edge from n1 to n2 and store in appropriate
                        // adjacency list(s).  If an undirected edge from n1 to n2 (or
                        // equivalently from n2 to n1) already exists, you shouldn't add
                        // an edge.  Only if such an undirected edge didn't exist earlier,
                        // should you add the edge and increment countEdges; otherwise,
                        // do not increment countEdges;
                        // Every time an edge is created, we also add that information to
                        // graphFile

                        linkedListNodes *present = adjacency[n1];
                        bool edgeExists = false;
                        if (present == nullptr){
                                // Hasn't been initialised yet
                                adjacency[n1] = new linkedListNodes(&nodes[n2]);
                        }
                        else{
                                while(present->next != nullptr){
                                        if(present->node == &nodes[n2]){
                                                // Found once
                                                edgeExists = true;
                                                break;
                                        }
                                        present = present->next;

                                }
                                if(present->node == &nodes[n2]){
                                        // Again here to account for the last node equalling n2
                                        // Found once
                                        edgeExists = true;
                                }
                                if (!edgeExists){
                                        present->next = new linkedListNodes(&nodes[n2]);
                                }
                        }
                        present = adjacency[n2];

                        if (present == nullptr){
                                // Hasn't been initialised yet
                                adjacency[n2] = new linkedListNodes(&nodes[n1]);
                        }
                        else if(!edgeExists){
                                // Only need to reach end of the linked list and insert
                                while(present->next != nullptr){
                                        present = present->next;
                                }

                                present->next = new linkedListNodes(&nodes[n1]);
                                present->next->prev = present;
                        }
                        if(!edgeExists){
                                graphFile << n1+1 << " " << n2+1 << endl;
                                countEdges += 1;
                        }
                }

                // Add appropriate code as necessary for your implementation
        }

        ~Graph() {
                if (graphFile.is_open()) {
                        graphFile.close();
                }
                delete[] nodes;
                // Add appropriate code as necessary for your implementation
        }

        // Add appropriate method declarations as necessary for your implementation

        void modifiedDFS();
        void printResults();
};

#endif
