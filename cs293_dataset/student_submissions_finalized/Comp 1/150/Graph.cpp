#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
// calling helper function with bst
// checking if node is not even visied giving different component
void Graph::modifiedDFS() {
  BST* x= new BST;
  myBST =  new listOfObjects<BST*>(x);
  listOfObjects<BST*>* a = myBST;
  for (int i=0;i<numNodes;i++){
      if (nodes[i].visited==0){  
         BST* x= new BST;
         a->next =  new listOfObjects<BST*>(x);
         a=a->next;      
         nodes[i].visited++;
         visit(&nodes[i],nullptr,a->object);
        component++;      
      }
  }
  return;
}

// visit function for nodes
// will backtrack if no of nodes are visited twice
// bst is passed by reference c
void Graph::visit(Node* A ,Node* B,BST* c){
  c->insert(A->value);
  // arrival for start
   if (B == nullptr){
          A->arrival = arrival++;
   }
   // adjacency list at A
    listOfObjects<Node*>* b= A->a->next;  
    while (b !=nullptr){ 
       if (( b->object->visited == 1 && b->object->value != B->value && b->object!= A->parent1) || (b->object->visited==0))
    {  
   
      if (b->object->visited ==0){
        b->object->parent1= A;
        b->object->arrival = arrival++;
      }
      b->object->visited++;
      visit(b->object,A,c);
    }  
    // finding no of cycles
    // by backedge
      if ( b->object->arrival!= -1 && b->object->arrival < A->arrival && b->object != B && b->object != A->parent1){
            Node* a = A;
        do {
          if (a!=nullptr){
            a->iscycle=1;
            a=a->parent1;
            }
           }
          while (a!=nullptr && a != b->object );
          b->object->iscycle=1;
      }   
   
    b=b->next;
    }
}
// printing result checking the parameter
void Graph::printResults() {
   int x =0;
   int y=0;
   for (int i=0;i<numNodes;i++){
      x = x + nodes[i].iscycle;
       if(nodes[i].visited==2){
          y++;
       }
   }
   cout << "No of Components:" << component << endl;
   cout << "No. of nodes visited once: " << numNodes-y<<endl;
   cout << "No. of nodes visited twice: " << y<<endl;
   cout << "No. of nodes that are present in a cycle:" << x<<endl;
   listOfObjects<BST*>*a = myBST->next;
   while (a != nullptr)
   {
    a->object->printBST("",a->object->root);
    a=a->next;
   }
   return;
}

#endif
