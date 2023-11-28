#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// constructors for TreeNode
TreeNode::TreeNode()
    : value(0), left(nullptr), right(nullptr)
{
}
TreeNode::TreeNode(int value)
    : value(value), left(nullptr), right(nullptr)
{
}
TreeNode::TreeNode(int value, TreeNode* leftChild, TreeNode* rightChild, TreeNode* parent)
    : value(value), left(leftChild), right(rightChild), parent(parent)
{
}

// constructors for BST class
BST::BST()
    : root(nullptr)
{
}
BST::BST(TreeNode* root)
    : root(root)
{
}
// destructor for BST class
// Heh's smart destruction TM
BST::~BST()
{
    if (root != nullptr) {
        {
            BST left_tree(root->left);
            BST right_tree(root->right);
        }
        delete root;
    }
}

// inserts the element
// find appropriate TreeNode to insert new TreeNode (going left for <= and right for >),
void BST::insert(int value)
{
    if (root != nullptr) {
        TreeNode* t = nullptr;
        TreeNode* t_child = root;
        while (t_child != nullptr) {
            t = t_child;
            if (value <= t_child->value)
                t_child = t_child->left;
            else
                t_child = t_child->right;
        }

        TreeNode* new_node = new TreeNode(value, nullptr, nullptr, t);

        if (value <= t->value)
            t->left = new_node;
        else
            t->right = new_node;

    } else {
        root = new TreeNode(value, nullptr, nullptr, nullptr);
    }
}

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(std::string const& prefix, bool isLeft)
{
    if (root != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        std::cout << root->value << '\n';
        TreeNode* curr = root;
        root = curr->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

Graph::Graph(int nNodes, int nEdges, string gFileName)
{
    numNodes = nNodes;
    numEdges = nEdges;

    nodes = new Node[numNodes];
    for (int i = 0; i < numNodes; i++)
        nodes[i].value = i + 1;

    graphFile.open(gFileName, std::ios::out);
    if (!graphFile.is_open()) {
        std::cerr << "Couldn't open graph file '" << gFileName << "'. Aborting ...\n";
        exit(-1);
    }

    graphFile << numNodes << '\n';
    graphFile << numEdges << '\n';

    srand(time(0));
    int n1, n2;
    int countEdges = 0;

    if (numEdges > (numNodes * (numNodes - 1)) / 2)
        numEdges = (numNodes * (numNodes - 1)) / 2;

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

        if (!nodes[n1].adjacency.contains(n2 + 1)) {
            graphFile << n1 + 1 << ' ' << n2 + 1 << '\n';
            nodes[n1].adjacency.insert(n2 + 1);
            nodes[n2].adjacency.insert(n1 + 1);
            countEdges++;
        }
    }
    graphFile.close();

    old_parent_name = new int[numNodes];
    DFST_parent_name = new int[numNodes];
    visits = new int[numNodes];
    in_cycle = new bool[numNodes];
    arrival = new int[numNodes];
    components = 0;
}

Graph::~Graph()
{
    if (graphFile.is_open()) {
        graphFile.close();
    }
    for (BST* tree_ptr : tree_ptrs)
        delete tree_ptr;
    delete[] nodes;
    delete[] old_parent_name;
    delete[] DFST_parent_name;
    delete[] visits;
    delete[] in_cycle;
    delete[] arrival;
}

void Graph::DFS_connected(int parent_name, int src_name, int& time, BST* tree_ptr, std::string prefix)
{
    visits[src_name - 1] += 1;
    tree_ptr->insert(src_name);

    if (arrival[src_name - 1] == -1)
        // setting arrival time at first arrival
        arrival[src_name - 1] = time;
    time++;

    for (int neighbour_name : nodes[src_name - 1].adjacency) {
        if (visits[neighbour_name - 1] > 0 && neighbour_name != DFST_parent_name[src_name - 1] && arrival[neighbour_name - 1] < arrival[src_name - 1]) {
            // this neighbour represents a back edge
            int head = src_name;
            while (head != neighbour_name && head != 0)
                head = DFST_parent_name[head - 1];
            if (head == neighbour_name) {
                head = src_name;
                while (head != neighbour_name) {
                    std::cout << head << " is in cycle\n";
                    in_cycle[head - 1] = true;
                    head = DFST_parent_name[head - 1];
                }
                std::cout << neighbour_name << " is in cycle\n";
                in_cycle[neighbour_name - 1] = true;
            }
        }
        if (visits[neighbour_name - 1] < 2 && neighbour_name != parent_name && neighbour_name != old_parent_name[src_name - 1]) {
            // this neighbour needs to be traversed
            if (visits[neighbour_name - 1] == 0)
                // setting neighbour's DFS search tree parent (as it wasn't set)
                DFST_parent_name[neighbour_name - 1] = src_name;

            if (old_parent_name[neighbour_name - 1] == -1)
                old_parent_name[neighbour_name - 1] = src_name;
            DFS_connected(src_name, neighbour_name, time, tree_ptr, prefix + "    ");
            if (old_parent_name[neighbour_name - 1] == src_name)
                old_parent_name[neighbour_name - 1] = -1;
        }
    }
    time++;
}

void Graph::modifiedDFS()
{
    for (int i = 0; i < numNodes; i++) {
        visits[i] = 0;
        old_parent_name[i] = -1;
        DFST_parent_name[i] = -1;
        in_cycle[i] = false;
        arrival[i] = -1;
    }

    int time = 0;

    for (int node_name = 1; node_name <= numNodes; node_name++) {
        // traversing node list and calling helper function whenever unvisited node encountered. Every such call correponds to different component
        if (visits[node_name - 1] == 0) {
            components += 1;
            BST* tree_ptr = new BST();
            DFS_connected(0, node_name, time, tree_ptr);
            tree_ptrs.push_back(tree_ptr);
        }
    }
}

void Graph::printResults()
{
    std::cout << "No of connected components: " << components << '\n';
    int once = 0, twice = 0, no_in_cycles = 0;
    for (int i = 0; i < numNodes; i++) {
        if (visits[i] == 1)
            once++;
        else if (visits[i] == 2)
            twice++;
        if (in_cycle[i])
            no_in_cycles++;
    }
    std::cout << "No of vertices visited once: " << once << '\n';
    std::cout << "No of vertices visited twice: " << twice << '\n';
    std::cout << "No of vertices in any cycle: " << no_in_cycles << '\n';

    for (BST* tree_ptr : tree_ptrs)
        tree_ptr->printBST();
}

#endif
