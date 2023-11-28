//Singly Linked List Node
class LLNode{
    public:
    int value;
    LLNode* next;
    
    LLNode(int value_){
        value = value_;
        next = nullptr;
    }
    ~LLNode(){
        if (next) delete next;
    }
};
//Linked List with sorted elements
class LL{
    LLNode* head;
    LLNode* tail;

    public:
    unsigned int size;
    LL(){
        head=tail=nullptr;
        size=0;
    }
    bool insert(int val); // unique insert
    ~LL(){
        delete head;
    }
    bool isempty(){return size==0;}
    bool islone(){return size==1;}
    void print(){//i thought this would be useful
        for (LLNode* curr=head;curr!=nullptr;curr=curr->next){
            file<<curr->value<<' ';
        }
        file<<endl;
    }
    void clear(){//clear the linked list
        delete head;
        head=tail=nullptr;
        size=0;
    }
    LLNode* Head(){return head;}
};

class Node{
    public:
    LL incoming;//incoming edges
    LL outgoing;//outgoing edges

    LL relations; // other nodes st this R other
    LL* common;// useful for collapsed graph
    Node* parentnode;//useful for collapsed graph, tree implementation of union ADT
    int label;
    Node(){parentnode=this;common=nullptr;}
    ~Node(){if (common) delete common;}
    bool addEdge(int other,bool outgoing);
    void labelnode(int i){label=i;}
    Node* getroot(){//return representative node of partition
        if (parentnode==this) return this;
        return  parentnode->getroot();
    }
    bool isroot(){return (this==parentnode);}//if it is the representative node
    static bool setunion(Node* one, Node* two){// set union operation for nodes
        Node* rootone = one->getroot();
        Node* roottwo = two->getroot();
        if (rootone==roottwo) return false;// no self edges
        if (rootone->label>roottwo->label) roottwo->parentnode = rootone;
        else rootone->parentnode = roottwo;
        return true;
    }// assign to whichever is larger
};

// edges 1-numnodes, accessed arr[*-1]
class Graph{//dynamically changes to collapsed graph when required
    int numNodes;//number of nodes
    Node* nodearray;//arrayofnodes
    int numParts;//number of partitions
    int* classarray;// representative node for each node in collapsed graph
    public:
    Graph(int numNodes_){
        classarray=nullptr;
        numNodes = numNodes_;
        nodearray = new Node[numNodes];
        for(int i=0;i<numNodes;i++) nodearray[i].labelnode(i+1);
    }
    ~Graph(){
        delete[] nodearray;
        delete[] classarray;
    }
    bool addEdge(int from, int to){// update directed edge ledgers for both nodes
        if (1>from||from>numNodes||1>to||to>numNodes) return false;
        return (nodearray[from-1].addEdge(to-1,true)&&nodearray[to-1].addEdge(from-1,false));
    }
    LL getSource();// return LL of source nodes
    bool addRelation(int from, int to){// update relation ledger
        if (1>from||from>numNodes||1>to||to>numNodes) return false;
        return nodearray[from-1].relations.insert(to-1);
    }
    void computeRelations(); // compute and update all relations in this graph
    void printRelations();// print all the relations in the graph
    bool collapse();// collapse graph
    void print();//print graph details
    bool similarrule2(Node* nnode,Node* prevnode);// check if nodes are related by rule 2
};