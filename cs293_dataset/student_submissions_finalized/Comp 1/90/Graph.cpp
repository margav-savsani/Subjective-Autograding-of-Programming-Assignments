#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// The insert function for BST as implemented
// in Lab3
void BST::insert(int value){
  TreeNode* curr = root;
	TreeNode* curr_parent = nullptr;

  // Finding the parent node iteratively
	while(curr != nullptr){
		curr_parent = curr;
		if(curr->value <= value) curr = curr->right;
		else curr = curr->left;
	}


  // When the root itself is nullptr
	if(curr_parent == nullptr) root = new TreeNode(value);
  // Otherwise
	else{
    // Right child
		if(curr_parent->value <= value){
			curr_parent->right = new TreeNode(value);
			curr_parent->right->parent = curr_parent;
		}
		else{
      // Left child
			curr_parent->left = new TreeNode(value);
			curr_parent->left->parent = curr_parent;
		}
	}
}

// Print BST function again taken from Lab3
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

// Checks whether the graph can reach
// up from node1 to node2 or not, 
// through the predecessor chain
bool reachup(Node* node1, Node* node2){
  Node* tmp = node1;
  while(node1 != node2){
    if(node1 == nullptr) return false;
    node1 = node1->predecessor;
  }
  return true;
}

// Performs a DFS with specified modifications
// And inserts elements into the BST tree
// as and when it visits the nodes in this
// connected component
void Graph::DFS(Node* node, BST* tree){
  node->visited++; // increment visited count
  //BST INSERT
  tree->insert(node->value); //insert into BST

  // Now recursively perform DFS on its adjacenct nodes
  for(int i=0; i<node->adjacency.size();i++){
    Node *adj_node = node->adjacency.get(i);
    if(adj_node->visited == 0){
      // If the adjacent node has not been visited earlier
      // Then set its predecessor and perform DFS on it
      adj_node->predecessor = node;
      DFS(adj_node,tree);
    }
    else if(adj_node->visited == 1 && adj_node != node->predecessor){
      // If the adjacent node has been visited earlier once
      // and it is not the predecessor of this node, in which case
      // it makes no sense to go back from where it came
      if(adj_node->predecessor != node){
        // In case this node is not the predecessor of adjacent node
        // then all the nodes which come in between including this 
        // node and the adj_node are part of the same cycle
        if(reachup(node, adj_node)){
          // If node has to climb up through predecessors
          // to reach adj_node
          Node* tmp = node;
          while(tmp != adj_node->predecessor){
            tmp->incycle = true;
            tmp = tmp->predecessor;
          } 
        }
        else{
          // If adj_node has to climb up through predecessors
          // to reach node
          Node* tmp = adj_node;
          while(tmp != node->predecessor){
            tmp->incycle = true;
            tmp = tmp->predecessor;
          } 
        }
      }
      DFS(adj_node,tree); //Recursively perform DFS
    }
  }
}

void Graph::modifiedDFS(){
  // list<BST*> * tree = trees;
  while(true){
    //checks if any node remains unvisited
    int unvisited = -1;
    for(int i=0; i<numNodes; i++){
      if(nodes[i].visited == 0){
        unvisited = i;
        break;
      }
    }
    if(unvisited == -1) break;
    else{
      // Performs DFS on the unvisited node
      BST* tree = new BST();
      DFS(&nodes[unvisited], tree);
      // tree->printBST("");
      // Pushes the tree into the list
      trees.push(tree);
    }
    numConnectedComp++; //Incrementing number of connected components
  }
}

// Prints all the results
void Graph::printResults() {
  cout << "Number of connected components: " << numConnectedComp << endl;
  int visit1 = 0;
  for(int i=0; i<numNodes;i++){
    if(nodes[i].visited == 1) visit1++;
  }
  cout << "Number of nodes visited once: " << visit1 << endl;
  cout << "Number of nodes visited twice: " << numNodes - visit1 << endl;
  for(int i=0; i<numNodes;i++){
    if(nodes[i].incycle) numNodesinCycle++;
  }
  cout << "Number of nodes present in a cycle: " << numNodesinCycle << endl;
  for(int i=0; i<trees.size();i++){
    cout << "Connected Component-" << i+1 << ":" << endl;
    trees.get(i)->printBST("");
    cout << "********\n";
  }
  // trees->object->printBST("");
  return;
}

#endif
