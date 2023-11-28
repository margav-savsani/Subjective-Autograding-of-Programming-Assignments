#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {\

    for(int i=0; i<numEdges; i++){  // iterating through all nodes to find connected components
        if(nodes[i].visited == 0){  // not visited in previous component
            connected++;
            listOfObjects<BST *> *new_bst = new listOfObjects<BST *>(new BST());    // a new BST for a new component
            if(trees == NULL)
                trees = new_bst;
            else{
                new_bst->next = trees;
                trees->prev = new_bst;
                trees = new_bst;
            }

            listOfObjects<Node *> *t = new listOfObjects<Node *>(&(nodes[i]));
            t->next = adjacency[i];
            listOfObjects<stackNode *> *stack = new listOfObjects<stackNode *>(new stackNode(&(nodes[i]), t));

            Node *parent = &(nodes[i]); // node previously visited
            Node *curr = &(nodes[i]);   // node currently on
            curr->parent = curr->value;

            // the actual dfs
            while(stack != NULL){
                curr = stack->object->progress->object;
                if(curr->value == stack->object->node->value) {     // we are just checking next adjacent node, so no need of checking this node again
                curr->visited++;    // update visiting

                if(curr->visited == 2){     // second time visiting
                    twice_visited++;
                    once_visited--;
                    if(curr->parent != -1)  // part of a cycle if it was already visited from somewhere else
                        nodes_cycle++;
                }

                // updating first and second parents
                if(curr->parent == -1)
                    curr->parent = parent->value;
                else
                    curr->parent2 = parent->value;
                
                // inserting into tree
                if(curr->visited <= 2)
                    trees->object->insert(curr->value);
                }

                parent = curr;
                // checking for next compatible node in adjacency list
                if(stack->object->progress->next != nullptr){
                    listOfObjects<Node *> *temp = stack->object->progress->next;
                    bool yes = false;   // compatibility

                    while(temp != nullptr){
                        if(temp->object->visited < 2 && temp->object->value != curr->parent && temp->object->value != curr->parent2){
                            listOfObjects<Node *> *z = new listOfObjects<Node *>(temp->object);
                            z->next = adjacency[temp->object->value -1];
                            listOfObjects<stackNode *> *new_stack = new listOfObjects<stackNode *>(new stackNode(temp->object, z));
                            stack->object->progress = temp;
                            if(stack == NULL)
                                stack = new_stack;
                            else{
                                new_stack->next = stack;
                                stack->prev = new_stack;
                                stack = new_stack;
                            }

                            yes = true;
                            break;
                        }
                        temp = temp->next;
                    }
                    parent = curr;
                    if(yes) continue;   // new node inserted into stack
                }
                
                // no further paths from current node => remove from stack and traceback

                // finding currnode in stack already
                listOfObjects<stackNode *> *q = stack->next;
                bool found = false;
                while(q != nullptr){
                    if(q->object->node->value == curr->value)
                        found= true;
                    q = q->next;
                }
                if(!found)
                    curr->parent = -1;

                // updating parent variable for next iteration
                if(parent->visited == 2)
                    parent = &(nodes[parent->parent2 -1]);
                else
                    parent = &(nodes[parent->parent -1]);

                stack = stack->next;    // popping currnt element
            }
        }
    }

    return;
}

void Graph::printResults() {
    cout << connected << endl;
    cout << once_visited << endl;
    cout << twice_visited << endl;
    cout << nodes_cycle << endl;

    for(auto i=trees; trees!=NULL; trees=trees->next)
        trees->object->printBST("");
    return;
}

#endif
