#include <iostream>
#include <fstream>
using namespace std;

class Node { 
 public:
  int object; //number of the node
  Node *next; //pointer to the next nodes
  bool marked; //marking visited or not
  bool main; //node with the max number for collapsing
  int connected; //value to be replaced with after grouping
  Node() {next = nullptr;marked = false;connected=-1;main = false;} //constructor
  Node(int value) {object = value;next  = nullptr;marked = false;connected = -1;main = false;}//constructor
};



class SinglyLinkedList{
    public:
        Node *head;//head of the list
        Node *tail;//tail of the list
};


bool adjacent(Node *graph,int val){ //checks if val is present in the list with head node as graph
    if(graph->next==nullptr){
        return false;
    }
    graph = graph->next;
    while(graph!=nullptr){
        if(graph->object == val){
            return true;
        }
        graph = graph->next;
    }
    return false;
}

bool similar_base(Node * graph,int val){ //base conditions to check for similarity
    if(graph->next==nullptr){
        return false;
    }
    graph = graph->next;
    while(graph!=nullptr){
        if(graph->object == val){
            return true;
        }
        graph = graph->next;
    }
    return false;
}
//recursive function to check for similarity based on the 2nd condition
bool similar_test(SinglyLinkedList adjacency_forward[],SinglyLinkedList adjacency_backward[],int no_of_incoming_edges[],SinglyLinkedList similar[],int node1,int node2){
    bool similar1 = false; 
    Node *head_copy = similar[node1].head;
    if(similar_base(head_copy,node2+1)){ //base condition
        return true;
    }
    else if(no_of_incoming_edges[node1]==0){ //base condition
        return false;
    }
    else{
        
        Node *incoming = adjacency_backward[node1].head->next;
        if(incoming == nullptr){ // if there is no incoming edge
            return false;
        }
        while(incoming!=nullptr){
            Node * incoming2 = adjacency_backward[node2].head->next;
            while(incoming2!=nullptr){
                
                if(similar_test(adjacency_forward,adjacency_backward,no_of_incoming_edges,similar,incoming->object-1,incoming2->object-1) ){ //reccurence to check for similarity of nodes of incoming edges
                    
                    similar1 = true;
                    break;
                }
                incoming2 = incoming2->next;
            }
            if(!similar1){ //if we don't find a pair for even one of the nodes it returns false
                return false;
            }
            similar1 =false;
            incoming = incoming->next;
            
        }
        
        return true;    
    }

}

//used to set the nodes as marked and after grouping sets the connected value to max 
void BFS(int no_of_incoming_edges[],int no_of_outgoing_edges[],SinglyLinkedList adjacency[],int source_node,int no_nodes){ 
    int max = source_node+1; //initialising the max value
    SinglyLinkedList *start = new SinglyLinkedList();
    start->head = adjacency[source_node].head;
    start->tail = adjacency[source_node].head;
    //if it does not have any incoming or outgoing edges
    if(start->head->next == nullptr){
        adjacency[source_node].head->marked = true;
        adjacency[source_node].head->connected = source_node+1;
        adjacency[source_node].head->main=true;
        return;
    }
    
    Node *start_copy = adjacency[source_node].head->next;
    //adding the adjacent nodes of the source node
    while(start_copy!=nullptr){
        
        start->tail->next = start_copy;
        start->tail = start->tail->next;
        adjacency[start->tail->object-1].head->marked = true;
        if(start->tail->object > max){
            max = start->tail->object;
        }
        start_copy = start_copy->next;
    }
    
    
    //shifting the head
    start->head = start->head->next;
    while(true){
        if(adjacency[start->head->object-1].head->next == nullptr){ //if there is no edge
            start->head = start->head->next;
        }
        else{ //adding to the list
            Node *head_copy = adjacency[start->head->object-1].head->next;
            while(head_copy!=nullptr){
                if(!adjacency[head_copy->object-1].head->marked){
                    start->tail->next = head_copy;
                    start->tail = start->tail->next;
                    adjacency[start->tail->object-1].head->marked = true;
                    if(start->tail->object > max){
                        max = start->tail->object;
                    }
                }
                head_copy = head_copy->next;
            }
            start->head = start->head->next;

        }
        if(start->head==nullptr){
            break;
        }
    }
    adjacency[max-1].head->main = true; //setting the node with max number in the grp to main
    for(int i = 0 ;i < no_nodes;i++){
        if(adjacency[i].head->marked && adjacency[i].head->connected==-1){
            adjacency[i].head->connected = max; //setting the values to group max
        }
    }
    

}
int main(int argc,char* argv[]){
    ofstream graph("outgraph.txt"); //writing to outgraph.txt
    int no_nodes;
    cin>>no_nodes; //number of nodes
    bool source[no_nodes]; //source or not
    bool user_specified_similarnodes[no_nodes][no_nodes]; //user specified similar nodes
    
    SinglyLinkedList* similar;
    similar = new SinglyLinkedList[no_nodes]; //used to store the similar nodes
    SinglyLinkedList* adjacency_forward; //outgoing edges
    adjacency_forward = new SinglyLinkedList[no_nodes];
    SinglyLinkedList* adjacency_backward;//incoming edges
    adjacency_backward = new SinglyLinkedList[no_nodes];
    SinglyLinkedList* adjacency;
    adjacency = new SinglyLinkedList[no_nodes]; //undirected edges
    SinglyLinkedList* collapse;
    collapse = new SinglyLinkedList[no_nodes]; //collapse nodes
    
    for(int i = 0;i<no_nodes;i++){
        
        adjacency_forward[i].tail = new Node(i+1);
        adjacency_forward[i].head = adjacency_forward[i].tail; //initialising adjacency_forward
        adjacency_backward[i].tail = new Node(i+1);
        adjacency_backward[i].head = adjacency_backward[i].tail;//initialising adjacency_backward
        similar[i].tail = new Node(i+1);
        similar[i].head = similar[i].tail;//initialising similar
        adjacency[i].tail = new Node(i+1);
        adjacency[i].head = adjacency[i].tail;//initialising adjacency
        collapse[i].tail = new Node(i+1);
        collapse[i].head = collapse[i].tail;//initialising collapse
    }
    int no_of_incoming_edges[no_nodes];//number of incoming edges
    int no_of_outgoing_edges[no_nodes];//number of outgoing edges
    for(int i = 0; i < no_nodes;i++){
        for(int j = 0;j<no_nodes;j++){
            user_specified_similarnodes[i][j] = false; //initialisation
        }
    }
    for(int i = 0 ; i < no_nodes ;i++){
        source[i] = true;
        no_of_incoming_edges[i] = 0;//initialsing the incoming edges to 0
        no_of_outgoing_edges[i] = 0;//initialsing the outgoing edges to 0
    }
    int n1,n2;
    while(cin>>n1>>n2){
        if(n1 == -1 && n2 == -1){
            break;
        }
        source[n2-1] = false;
        adjacency_forward[n1-1].tail->next = new Node(n2);
        adjacency_forward[n1-1].tail = adjacency_forward[n1-1].tail->next; //outgoing edges
        adjacency_backward[n2-1].tail->next = new Node(n1);
        adjacency_backward[n2-1].tail = adjacency_backward[n2-1].tail->next;//incoming edges
        
        
        no_of_incoming_edges[n2-1]++;
        no_of_outgoing_edges[n1-1]++;
    }
    

    int sim1,sim2;
    while(cin>>sim1>>sim2){
        if(sim1 == -1 && sim2 == -1){
            break;
        }
        user_specified_similarnodes[sim1-1][sim2-1] = true; //user specified similarites
        
    }

    graph<<"Source Nodes: "; //prints source nodes to the file
    for(int i = 0; i < no_nodes;i++){
        if(source[i]){
            graph<<i+1<<" ";
        }
    }
    graph<<endl;
    graph<<endl;
    for(int i = 0;i<no_nodes;i++){
        for(int j = 0; j<no_nodes;j++){
            if(source[i] && source[j] && user_specified_similarnodes[i][j]){
                similar[i].tail->next = new Node(j+1);
                similar[i].tail = similar[i].tail->next; //adding to similar
                adjacency[i].tail->next = new Node(j+1);
                adjacency[i].tail = adjacency[i].tail->next;
                adjacency[j].tail->next = new Node(i+1);
                adjacency[j].tail = adjacency[j].tail->next; //adding to adjacency for similar pairs with symmetric
            }
            else if(no_of_incoming_edges[j]==1 && adjacent(adjacency_forward[i].head,j+1)){
               
                similar[j].tail->next = new Node(i+1);
                similar[j].tail = similar[j].tail->next; //adding to similar
                adjacency[i].tail->next = new Node(j+1);
                adjacency[i].tail = adjacency[i].tail->next;
                adjacency[j].tail->next = new Node(i+1);
                adjacency[j].tail = adjacency[j].tail->next; //adding to adjacency for similar pairs with symmetric
            }
            else{
                Node *i_list =  similar[i].head;
                if(similar_test(adjacency_forward,adjacency_backward,no_of_incoming_edges,similar,i,j) && similar_test(adjacency_forward,adjacency_backward,no_of_incoming_edges,similar,j,i) &&!similar_base(i_list,j+1)){
                    
                    similar[i].tail->next = new Node(j+1);
                    similar[i].tail = similar[i].tail->next;//adding to similar
                    adjacency[i].tail->next = new Node(j+1);
                    adjacency[i].tail = adjacency[i].tail->next;
                    adjacency[j].tail->next = new Node(i+1);
                    adjacency[j].tail = adjacency[j].tail->next; //adding to adjacency for similar pairs with symmetric
                }

            }
        }
    }

    graph<<"Similar node pairs: "; //used to print similar node pairs to the file
    for(int i = 0;i<no_nodes;i++){
        Node *co = similar[i].head->next;
        while(co!=nullptr){
            graph<<"("<<i+1<<","<<co->object<<") ";
            co = co->next;
        }
    }
    graph<<endl;
    graph<<endl;
    int no = 0;
    for(int i = 0; i <no_nodes;i++){
        if(!adjacency[i].head->marked){ //BFS running on different connected components
            BFS(no_of_incoming_edges,no_of_outgoing_edges,adjacency,i,no_nodes);
            no++;
        }
    }
    
    graph<<"Collapsed graph: "<<endl; //printing the collapsed graph
    graph<<endl;
    graph<<no<<": ";
    int j = 0;
    for(int i = 0;i<no_nodes;i++){
        if(adjacency[i].head->main){
            graph<<i+1<<" ";
            j++;
        }
    }
    graph<<endl;
    for(int i = 0;i<no_nodes;i++){ //replacing the value of node to the group max
        Node *forw = adjacency_forward[i].head;
        Node *forw1 = collapse[i].head;
        forw1->object = adjacency[forw->object-1].head->connected;
        while(forw!=nullptr){
            forw->object = adjacency[forw->object-1].head->connected;
            forw = forw->next;
        }
    }
   
    for(int i = 0;i<no_nodes;i++){ //printing the edges after replacing the values with group max
        Node *forw = adjacency_forward[i].head;
        int no1 = forw->object;
        Node *forw1 = collapse[no1-1].head;
        if(forw->next!=nullptr){
            while(forw!=nullptr){
                if(forw->object!=no1 && !adjacent(forw1,forw->object)){
                    graph<<no1<<" "<<forw->object<<endl;
                    collapse[no1-1].tail->next = forw;
                    collapse[no1-1].tail = collapse[no1-1].tail->next;
                }
                forw = forw->next;
            }
        }
    
    }
    
    
    
}