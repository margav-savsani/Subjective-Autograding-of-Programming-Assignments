#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;

// Checks if nodes are similar
bool Graph::existsSimilar(Node* n1, Node* n2) {
  for (int i = 0; i < similar.len()/2; i++) {
    if (similar[2*i] == n1 && similar[2*i+1] == n2) {
        return true;
    }
  }

  return false;
}

// Checks if the node is a source node
bool Graph::existsSource(Node* n) {
  for (int i = 0; i < source.len(); i++) {
    if (source[i] == n) {
        return true;
    }
  }

  return false;
}

// Checks if there exists an edge from n1 to n2
bool Graph::existsEdge(Node* n1, Node* n2) {
    for (int i = 0; i < n1->adjancency.len(); i++) {
        if (n1->adjancency[i] == n2) {
            return true;
        }
    }

    return false;
}

// Computes source nodes if there exists no incoming edges
void Graph::sourceNodes() {
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i].revadjancency.len() == 0) {
            source.append(&nodes[i]);
        }
    }
}

// To add similar nodes to vector to print it at the last
void Graph::pushFinalSimilar(Node* n1, Node* n2) {
    for (int i = 0; i < similar.len()/2; i++) {
        if ((similar[2*i] == n1 && similar[2*i+1] == n2)) {
            return;
        }
    }

    similar.append(n1);
    similar.append(n2);
}

// To compute similar nodes
void Graph::similarNodes() {
    for (int i = numNodes-1; i >=0 ; i--) {
        for (int j = numNodes-1; j >= 0; j--) {
            // First case => If both are similar and source
            if (existsSource(&nodes[i]) && existsSource(&nodes[j]) && existsSimilar(&nodes[i], &nodes[j])) {
                pushFinalSimilar(&nodes[i], &nodes[j]);
            } else {
                // Third case => If one has edge to another and the second has no other incoming edge, checked through size of reverse adjacency list
                if (existsEdge(&nodes[i], &nodes[j])) {
                    if (nodes[j].revadjancency.len() == 1) {
                        pushFinalSimilar(&nodes[j], &nodes[i]);
                    }
                // Second case = > If both nodes has incoming edges, check if all incoming edges of either node has similar connection to atleast one node that has edge to the other node
                } else {
                    if (nodes[i].revadjancency.len() > 0 && nodes[j].revadjancency.len() > 0) {
                        bool first = true;
                        // Iterate through nodes that give incoming edge to first node
                        for (int k = 0; k < nodes[i].revadjancency.len(); k++) {
                            bool found = true;
                            for (int l = 0; l < nodes[j].revadjancency.len(); l++) {
                                if (existsSimilar(nodes[i].revadjancency[k], nodes[j].revadjancency[l])) {
                                    found = false;
                                }
                            }
                            if (found) {
                                first = false;
                                break;
                            }
                        }
                        if (first) {
                            // Iterate through nodes that give incoming edge to second node
                            for (int k = 0; k < nodes[j].revadjancency.len(); k++) {
                                bool found = true;
                                for (int l = 0; l < nodes[i].revadjancency.len(); l++) {
                                    if (existsSimilar(nodes[j].revadjancency[k], nodes[i].revadjancency[l])) {
                                        found = false;
                                    }
                                }
                                if (found) {
                                    first = false;
                                    break;
                                }
                            }
                        }
                        if (first) {
                            pushFinalSimilar(&nodes[i], &nodes[j]);
                        }
                    }
                }
            }
        }
    }

    int s = similar.len()/2;
    int p = 0;

    // We have to check case 2 again using the similar nodes we found. We will stop the while loop untill we find no increase in the list
    while (s != p) {
        for (int i = numNodes-1; i >=0 ; i--) {
            for (int j = numNodes-1; j >= 0; j--) {
                if (nodes[i].revadjancency.len() > 0 && nodes[j].revadjancency.len() > 0) {
                    bool first = true;
                    for (int k = 0; k < nodes[i].revadjancency.len(); k++) {
                        bool found = true;
                        for (int l = 0; l < nodes[j].revadjancency.len(); l++) {
                            if (existsSimilar(nodes[i].revadjancency[k], nodes[j].revadjancency[l])) {
                                found = false;
                            }
                        }
                        if (found) {
                            first = false;
                            break;
                        }
                    }
                    if (first) {
                        for (int k = 0; k < nodes[j].revadjancency.len(); k++) {
                            bool found = true;
                            for (int l = 0; l < nodes[i].revadjancency.len(); l++) {
                                if (existsSimilar(nodes[j].revadjancency[k], nodes[i].revadjancency[l])) {
                                    found = false;
                                }
                            }
                            if (found) {
                                first = false;
                                break;
                            }
                        }
                    }
                    if (first) {
                        pushFinalSimilar(&nodes[i], &nodes[j]);
                    }
                }
            }
        }

        p = s;
        s = similar.len()/2;
    }
}

// DFS to find collapsed nodes
int Graph::recursiveDFS(Node* source, arr<Node*>* stack, int top) {

  // iterate through each element in adjacency list of source
  for (int i = 0; i < source->adjancency.len(); i++) {
    // you can visit only once
    if (!visited[source->adjancency[i]->value-1]) {
        visited[source->adjancency[i]->value-1] = 1;       
        if (source->adjancency[i]->value > top) {
            top = source->adjancency[i]->value;
        } 
        stack->append(source->adjancency[i]);
        top = max(recursiveDFS(source->adjancency[i], stack, top), top);
    }
  }

  // iterate through each element in reverse adjacency list of source
  for (int i = 0; i < source->revadjancency.len(); i++) {
    // you can visit only once
    if (!visited[source->revadjancency[i]->value-1]) {
        visited[source->revadjancency[i]->value-1] = 1;   
        if (source->revadjancency[i]->value > top) {
            top = source->revadjancency[i]->value;
        }      
        stack->append(source->revadjancency[i]);
        top = max(recursiveDFS(source->revadjancency[i], stack, top), top);
    }
  }

  return top;
}

// Build a new graph using similar nodes
void Graph::rebuildGraph(Graph* graph) {
  for (int i = 0; i < graph->similar.len()/2; i++) {
    this->insertEdge(graph->similar[2*i]->value, graph->similar[2*i+1]->value);
  }
}

// Compute collapsed nodes
void Graph::collapsedNodes(Graph* graph) {

    // Performs DFS and returns each connected component and top most number of the component
    for (int i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            arr<Node*> stack;
            stack.append(&nodes[i]);
            int top = nodes[i].value;
            top = max(recursiveDFS(&nodes[i], &stack, 0), top);
            topcollapsed.append(top);
            collapsed.append(stack);
        }
    }

    // Checks if there is any edge between any two componenets
    for (int i = 0; i < collapsed.len(); i++) {
        for (int j = 0; j < collapsed.len(); j++) {
            bool comp = true;
            if (i != j) {
                for (int k = 0; k < collapsed[i].len(); k++) {
                    for (int l = 0; l < collapsed[j].len(); l++) {
                        if (graph->existsEdge(&graph->nodes[collapsed[i][k]->value-1], &graph->nodes[collapsed[j][l]->value-1])) {
                            if (comp) {
                                graph->Edgescollapsed.append(topcollapsed[i]);
                                graph->Edgescollapsed.append(topcollapsed[j]);
                                comp = false;
                                break;
                            }
                        }
                    }
                    if (!comp) {
                        break;
                    }
                }
            }
        }
    }
}

void Graph::printResults(Graph* graph) {
    cout << "Source nodes: ";
    for (int i = 0; i < source.len(); i++) {
        cout << source[i]->value << " ";
    }
    cout << endl;
    cout << endl;

    cout << "Similar node pairs: ";
    for (int i = 0; i < similar.len()/2; i++) {
        cout << "(" << similar[2*i]->value << ", " << similar[2*i+1]->value << ") ";
    }
    cout << endl;
    cout << endl;
    cout << "Collapsed graph:" << endl << endl;
    cout << graph->topcollapsed.len() << ": ";
    for (int i = 0; i < graph->topcollapsed.len(); i++) {
        cout << graph->topcollapsed[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < Edgescollapsed.len()/2; i++) {
        cout << Edgescollapsed[2*i] << " " << Edgescollapsed[2*i+1] << endl;
    }
}

#endif
