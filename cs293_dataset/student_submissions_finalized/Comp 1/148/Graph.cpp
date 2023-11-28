#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

bool BST::insert(int val)
{
        TreeNode *present = root; // This will be updated and used in the loop
        
        // Make a new Node so that we can use <
        TreeNode *newNode = new TreeNode(val);
        if(present == nullptr){
            // Tree was empty earlier, just insert it at root
            root = newNode;
            newNode = root;
            return true;
        }
        while(true){
            if(present->val == val){
                // Duplicate
                return false;
            }
            if (BSTLessThan(newNode, present)){
                if (present->left == nullptr){
                    // Found a place to insert, present->left
                    present->left = newNode; // Make a new node with null left and right and parent = present
                    newNode = present->left;
                    newNode->parent = present;
                    break;
                }
                else{
                    // Keep traversing
                    present = present->left;
                    
                }
            }
            else{
                if (present->right == nullptr){
                    // Insert at present->right 
                    present->right = newNode; // Make a new node with null left and right and parent = present
                    newNode = present->right;
                    newNode->parent = present;

                    break;
                }
                else{
                    present = present->right ;
                    
                }
            }
        }


    // We are only inserting at the leaves. So we only need to find the height of the present node


  
  return true;
}



// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
        listOfBSTs *presentBST = nullptr;//The present bst we are constructing,  since we need one for each connected component
  for (int i = 0; i < numNodes; i++) {
          // Go to each node and see if it has been visited
         if(nodes[i].nVisited == 0){
            if(presentBST == nullptr){
                bsts = new listOfBSTs;
                presentBST = bsts;
                nConnected += 1;
            }
            else{
                presentBST->next = new listOfBSTs;
                presentBST = presentBST->next;
                nConnected += 1;
            }
            presentBST->bst->insert(nodes[i]);
            nodes[i].nVisited = 1;
            nOnce += 1;
            linkedListNodes *stack = new linkedListNodes(&nodes[i]);
            /* cout << "Added " << stack->node->value   << endl; */
            
            while(stack != nullptr){
                    // Use stack to implement dfs in an iterative way
                    if (stack->node->nVisited ==2){
                        //Go back in the stack to find previous occurence of node
                        // This might not always form a cycle so first need to check
                        bool formsCycle = false;
                        linkedListNodes *findCycles = stack->prev;
                        while(findCycles != nullptr){
                            if(findCycles->node == stack->node){
                                formsCycle = true;
                                break;
                            }
                                findCycles = findCycles->prev;
                        }
                        if (formsCycle){
                                // Change the actual vertices
                        
                                linkedListNodes *findCycles = stack->prev;
                                while(findCycles != nullptr){
                                    if (!findCycles->node->partOfCycle){
                                        findCycles->node->partOfCycle = true;
                                        nCycle += 1;
                                    }
                                    if(findCycles->node == stack->node){
                                        break;
                                    }
                                findCycles = findCycles->prev;
                                }
                            
                        }
                    }
                    linkedListNodes *neighbors = adjacency[stack->node->value-1];// -1 because of the way we store values
                    bool brokeOut = false || stack->node->nVisited > 2;
                    /* cout << "Present stack head " << stack->node->value  << endl; */
                    while(neighbors != nullptr){
                            /* cout << "   checking neighbor " << neighbors->node->value  << endl; */
                            if(neighbors->node->nVisited != 2){
                                if (neighbors->node != stack->node->parent1 && neighbors->node != stack->node->parent2 && neighbors->node->parent1 != stack->node && neighbors->node->parent2 != stack->node){
                                    // We'll visit this node next
                                    if(neighbors->node->nVisited == 0){
                                        nOnce += 1;
                                        neighbors->node->nVisited = 1;
                                    }    
                                    else{
                                        nOnce -= 1;
                                        nTwice += 1;
                                        neighbors->node->nVisited = 2;
                                    }
                                    if (neighbors->node->parent1 == nullptr){
                                        /* cout << "Added parent"  << endl; */
                                        neighbors->node->parent1 = stack->node;
                                    }
                                    else{
                                    
                                        neighbors->node->parent2 = stack->node;
                                    }
                                    presentBST->bst->insert(neighbors->node);
                                    stack->next = new linkedListNodes(neighbors->node);
                                    stack->next->prev = stack;
                                    stack = stack->next;
                                    /* cout << "Added " << neighbors->node->value   << endl; */
                                    brokeOut = true;
                                    break;
                                }
                            }
                            neighbors = neighbors->next;
                    }
                    if(brokeOut){
                        continue;
                    }
                    else{
                        // Pop from stack
                        linkedListNodes *toDel = stack;
                        stack = stack->prev;
                        delete toDel;
                        if(stack != nullptr){
                        stack->next = nullptr;
                        }
                    }
            }

         } 
  }
  return;
}

void Graph::printResults() {
  cout << "No. of connected components: " << nConnected  << endl;
  cout << "No. of nodes visited once: " << nOnce  << endl;
  cout << "No. of nodes visited twice: " << nTwice << endl;
  cout << "No. of nodes that are present in a cycle: " << nCycle << endl;
  listOfBSTs *presentBST = bsts;
  while(presentBST != nullptr){
    presentBST->bst->print();
    presentBST = presentBST->next;
  }
  return;
}

#endif
