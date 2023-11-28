#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
class listOfObjects
{
public:
    T object;
    listOfObjects<T> *next;
    listOfObjects<T> *prev;

    // Constructor
    listOfObjects(T initValue)
    {
        object = initValue;
        next = prev = nullptr;
    }

    // Destructor
    ~listOfObjects() { ; }
};

class TreeNode
{
private:
    int val; // Journey code: This is the key for BST and AVL tree
public:
    TreeNode *left;   // Pointer to left child  (NULL, if no left child)
    TreeNode *right;  // Pointer to right child (NULL, if no right child)
    TreeNode *parent; // Parent of this node (NULL, if no parent)
    // Constructor:
    TreeNode(int value)
    {
        val = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    // Destructor: Define this as per your requirements
    ~TreeNode() {}

    // Print information about tree node on cout
    void printInfo()
    {
        cout << "[value: " << val << "]";
    }

    int get_val() { return val; }
    // Overloaded < operator
    // Usage: tree_node1 < tree_node2
    // Returns true if tree_node1.JourneyCode < tree_node2.JourneyCode
    // Returns false otherwise.
    //
    // Note that since JourneyCode is a private member of TreeNode,
    // we can't directly use tree_node1.JourneyCode < tree_node2.JourneyCode
    // from outside this class.

    bool operator<(TreeNode const &node)
    {
        if (val < node.val)
            return true;
        else
            return false;
    }

    // Makes current node the left child of parentNode if
    // isLeftChild is set to true; otherwise, it makes current node
    // the right child of parentNode.  In either case, the function
    // returns true.
    //
    // If parentNode is NULL, the function returns false.
    //
    // Note that if parentNode already had a left child, say x, and if
    // you are setting current node to be the new left child of
    // parentNode, then x will no longer be the left child of parentNode.
    // In fact, unless you save a pointer to x, you may no longer be able
    // to access x at all by walking down the tree from its root.
    // A similar observation applies if parentNode already had a right child,
    // and you are setting current node to be the new right child of
    // parentNode.

    bool updateParentChild(TreeNode *parentNode, bool isLeftChild)
    {
        if (parentNode != nullptr)
        {
            parent = parentNode;
            if (isLeftChild)
            {
                parentNode->left = this;
            }
            else
            {
                parentNode->right = this;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
};

class BST //binary search tree class
{
private:
    TreeNode *root;
    void recursiveDelete(TreeNode *currNode)
    {
        if (currNode != nullptr)
        {
            TreeNode *leftChild = currNode->left;
            TreeNode *rightChild = currNode->right;

            delete currNode;
            recursiveDelete(leftChild);
            recursiveDelete(rightChild);
        }
        return;
    }

    bool BSTLessThan(TreeNode *leftArg, TreeNode *rightArg)
    {
        if ((leftArg != nullptr) && (rightArg != nullptr))
        {
            bool result = (*leftArg < *rightArg);
            return result;
        }
        else
        {
            cerr << "Unexpected exceptional condition!" << endl;
            exit(-1);
        }
    }

public:
    // Constructors
    BST()
    {
        root = nullptr;
    }

    BST(TreeNode *newRoot)
    {
        root = newRoot;
    }

    // Destructor
    ~BST()
    {
        recursiveDelete(root);
    }

    bool insert(int value)
    {

        TreeNode *y = nullptr;
        TreeNode *x = root;
        // We need to create z as a pointer so that the same address is not pointed every time when the function is called.
        TreeNode *z = new TreeNode(value);

        while (x != nullptr)
        {
            y = x;

            if (BSTLessThan(z, x))
            {
                x = x->left;
            }
            else // if(BSTLessThan(x,z))
            {
                x = x->right;
            }
            // else
            // {
            //   //cout<<"gone"<<endl;
            //   return false;
            // }
        }

        z->parent = y;

        if (y == nullptr)
        {
            root = z;
        }
        else if (BSTLessThan(z, y))
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        TreeNode *w = y;
        while (w != nullptr)
        {
            // cout<< w->get_Journeycode() <<w->height <<endl;
            // w->update_height();
            // cout<< w->get_Journeycode() <<w->height <<endl;
            w = w->parent;
        }
        return true;
    };
    void print()
    {
        //printBinaryTree(root, "", false);
        printBST("",false);
        return;
    }

    void printBST(const string &prefix, bool isLeft = false)
    {
        if (root != nullptr)
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "|__");

            // print the value of the node
            cout << root->get_val() << endl;
            TreeNode *curr = root;
            root = root->left;
            // enter the next tree level - left and right branch
            printBST(prefix + (isLeft ? "│   " : "    "), true);
            root = curr->right;
            printBST(prefix + (isLeft ? "│   " : "    "), false);
            root = curr;
        }
    }
};

class Node
{
public:
    int value;
    listOfObjects<Node> *adjacency;
    // insert other fields and methods as appropriate
};

class Graph
{
    int numNodes;
    int numEdges;
    fstream graphFile;

    Node *nodes;
    int *visited;
    int ind_com;
    int node_cycle;
    BST *tree;
    listOfObjects<int> *stack;
    // Add appropriate fields as necessary for your implementation

public:
    Graph(int nNodes, int nEdges, string gFileName)
    {
        numNodes = nNodes;
        numEdges = nEdges;
        graphFile.open(gFileName, ios::out);
        if (!graphFile.is_open())
        {
            cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
            exit(-1);
        }

        graphFile << numNodes << endl;
        graphFile << numEdges << endl;

        nodes = new Node[numNodes];
        if (nodes == nullptr)
        {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
        }

        for (int i = 0; i < numNodes; i++)
        {
            nodes[i].value = i + 1;
        }

        visited = new int[numNodes];
        for (int i = 0; i < numNodes; i++)
        {
            visited[i] = 0;
        }

        srand(time(0));
        int n1, n2;
        int countEdges = 0;

        while (countEdges < numEdges)
        {
            // cout<<"enter"<<endl;
            do
            {
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
            //cout << n1 << " " << n2 << endl;
            bool present = false;
            if (nodes[n1].adjacency == nullptr) //checking if the adjacency list is empty
            { 
                // cout << "1" << endl;
                nodes[n1].adjacency = new listOfObjects<Node>(nodes[n2]);
            }
            else
            {
                //cout << "1dash" << endl;
                listOfObjects<Node> *last = nodes[n1].adjacency;
                while (last != nullptr)
                {
                    if (last->object.value == nodes[n2].value)
                    {
                        present = true;
                        break;
                    }
                    last = last->next;
                }
                if (present == true)
                {
                    continue;
                }
                last = nodes[n1].adjacency;
                while (last->next != nullptr)
                {
                    last = last->next;
                }

                last->next = new listOfObjects<Node>(nodes[n2]);
            }

            if (nodes[n2].adjacency == nullptr) //checking if the adjacency list is empty
            {
                // cout << "2" << endl;
                nodes[n2].adjacency = new listOfObjects<Node>(nodes[n1]);
            }
            else
            {
                // cout << "2dash" << endl;
                listOfObjects<Node> *last = nodes[n2].adjacency;
                while (last->next != nullptr)
                {
                    last = last->next;
                }
                last->next = new listOfObjects<Node>(nodes[n1]);
            }

            graphFile << n1 + 1 << " " << n2 + 1 << endl;
            countEdges++;
            // cout<<countEdges<<endl;
            //cout << "hi" << endl;
        }
        ind_com = 0;
        node_cycle = 0;
        tree = nullptr;
        stack = nullptr;
        // cout<<"hello"<<endl;
        //  Add appropriate code as necessary for your implementation
    }

    ~Graph()
    {
        if (graphFile.is_open())
        {
            graphFile.close();
        }
        delete[] nodes;
        // Add appropriate code as necessary for your implementation
    }

    // Add appropriate method declarations as necessary for your implementation
    void DFS(Node node, int value);
    void modifiedDFS();
    void printResults();
};

#endif
