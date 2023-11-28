#include"graph.h"

bool LL::insert(int val){// ordered insert
    if (size==0){//to empty LL
        tail = head = new LLNode(val);
        size=1;
        return true;
    }
    if (val>tail->value){// largest value, for sorted inputs wanted to keep constant time
        size++;
        tail->next=new LLNode(val);
        tail=tail->next;
    }
    else if (val<head->value){//smallest value, for sorted inputs wanted to keep constant time
        size++;
        LLNode* nh = new LLNode(val);
        nh->next=head;
        head = nh;
    }
    else if(val==head->value||val==tail->value) return false;// no repeats
    else {// insert inside
        for(LLNode* curr=head;curr->next!=nullptr;curr=curr->next){
            if (curr->next->value>val){
                size ++;
                LLNode* nu = new LLNode(val);
                nu->next = curr->next;
                curr->next=nu;
            }
            else if (curr->next->value==val) return false;
        }
    }
    return true;
}
// implementing rule 2 for two nodes
bool Graph::similarrule2(Node* nnode,Node*prevnode){
    if(nnode==nullptr||prevnode==nullptr) return false;// exit gracefully
    if (nnode->incoming.isempty()||prevnode->incoming.isempty()) return false;// both must be source
    LL* parentsnew = &nnode->incoming; // parents of nnode
    LL* parentsprev = &prevnode->incoming;// parents of prevnode

    LLNode** newrel = new LLNode*[parentsnew->size]; // array of relations from parents of newnode
    LLNode** prevrel = new LLNode*[parentsprev->size];// array of relations from parents of prevnode
    //initialising newrel and prevrel
    LLNode* it = parentsnew->Head();
    for(int i = 0; it!=nullptr ;i++){
        newrel[i]=nodearray[it->value].relations.Head();
        it=it->next;
    }
    it = parentsprev->Head();
    for(int i = 0; it!=nullptr ;i++){
        prevrel[i]=nodearray[it->value].relations.Head();
        it=it->next;
    }
    // check if each new parent is the relation of a prevparent
    LLNode* curr = parentsnew->Head();
    for(int i=0; i<parentsnew->size; i++){
        bool isthere = false;
        for(LLNode* p = parentsprev->Head();p != nullptr;p = p->next){
            for(LLNode *anc = newrel[i];anc!=nullptr;anc = anc->next){
                if(anc->value == p->value){
                    isthere = true;
                    break;
                }
            }
            if(isthere) break;
        }
        if(!isthere) {
            delete[] newrel;
            delete[] prevrel;
            return false;
        }
    }
    //check the vice versa
    for(int i=0; i<parentsprev->size; i++){
        bool isthere = false;
        for(LLNode* p = parentsnew->Head();p != nullptr;p = p->next){
            for(LLNode *anc = prevrel[i];anc!=nullptr;anc = anc->next){
                if(anc->value == p->value){
                    isthere = true;
                    break;
                }
            }
            if(isthere) break;
        }
        if(!isthere) {
            delete[] newrel;
            delete[] prevrel;
            return false;
        }
    }
    delete[] newrel;
    delete[] prevrel;
    return true;

}
// add edge in node <othernode> <outgoing?>
bool Node::addEdge(int other, bool outgo){
    if (outgo){
        return outgoing.insert(other); 
    }
    return incoming.insert(other);
}
// return Linked List of source nodes
LL Graph::getSource(){
    LL toreturn;
    for(int i=0;i<numNodes;i++){
        if (nodearray[i].incoming.isempty()){// source node => no incoming edges
            toreturn.insert(i+1);
        }
    }
    return toreturn;
}
/*
    start from the source nodes
    at each step we define the layer to be the set of nodes all of whose parents have been visited
    we check relations among and with the previously visited nodes
    then move to the next layer
*/
void Graph::computeRelations(){
    //condition 3; 1 is already done in main
    for(int i=0;i<numNodes;i++){
        if (nodearray[i].incoming.islone()){
            nodearray[i].relations.insert(nodearray[i].incoming.Head()->value);
        }
    }
    //looking at all combinations for insert by rule 2
    bool* visited = new bool[numNodes]; // if node is yet visited - given if all incoming edges were already visited
    int* unvisitedparents = new int[numNodes];// number of unvisited parent nodes
    for (int i=0;i<numNodes;i++){ // initialising arrays
        visited[i]=false;
        unvisitedparents[i]=nodearray[i].incoming.size;
    }
    LL current_layer; //going layer by layer
    
    while(1){//every layer
        for(int i=0;i<numNodes;i++){
            if (unvisitedparents[i]==0&&!visited[i]) current_layer.insert(i);
        }
        if (current_layer.isempty()) break;
        // update from previous layer
        for (LLNode* curr = current_layer.Head();curr!=nullptr;curr=curr->next){
            for(int i=0;i<numNodes;i++){
                if (!visited[i]) continue;

                if (similarrule2(&nodearray[curr->value],&nodearray[i])){ //update with parent level
                    nodearray[curr->value].relations.insert(i);
                    nodearray[i].relations.insert(curr->value);
                }
            }
        }
        //update from the same layer
        for (LLNode* curr = current_layer.Head();curr!=nullptr;curr=curr->next){
            for (LLNode* nex = curr;nex!=nullptr;nex=nex->next){
                if (similarrule2(&nodearray[curr->value],&nodearray[nex->value])){
                    nodearray[curr->value].relations.insert(nex->value);
                    nodearray[nex->value].relations.insert(curr->value);
                }
            }
        }
        //update variables/states for the next level
        for (LLNode* curr = current_layer.Head();curr!=nullptr;curr=curr->next){
            unvisitedparents[curr->value] = -1;
            visited[curr->value]=1;
            for (LLNode* nextnd = nodearray[curr->value].outgoing.Head();nextnd!=nullptr;nextnd=nextnd->next ){
                unvisitedparents[nextnd->value]--;
            }
        }
        current_layer.clear();//empty current_layer for next layer
    }//clear memory
    delete[] visited;
    delete[] unvisitedparents;

}

void Graph::printRelations(){//print all the relations
    for(int i=0;i<numNodes;i++){
        for(LLNode* curr=nodearray[i].relations.Head();curr!=nullptr;curr=curr->next){
            file<<'('<<i+1<<','<<curr->value+1<<')'<<' ';
        }
    }
    file<<endl;
}
//collapse the graph based on the relation closure - using the union ADT implemented by trees
bool Graph::collapse(){
    for(int i=numNodes-1;i>=0;i--){
        for(LLNode* curr=nodearray[i].relations.Head();curr!=nullptr; curr=curr->next){
            Node::setunion(&nodearray[i],&nodearray[curr->value]); // union for every edge - setunion handles duplicates
        }
    }
    classarray = new int[numNodes]; // representative node of each class
    numParts=0;
    for(int i=0;i<numNodes;i++) {
        if (nodearray[i].isroot()) {
            numParts++;
            nodearray[i].common = new LL();//setting linked list of common edges for print
        }
        classarray[i] = nodearray[i].getroot()->label;
    }
    for(int i=0;i<numNodes;i++) {
        Node* base = nodearray+i;
        Node* root = base->getroot();
        for (LLNode* curr = base->outgoing.Head();curr!=nullptr;curr=curr->next)
            if (classarray[i]!=classarray[curr->value])//connecting components - insert deals with duplicates
                nodearray[classarray[i]-1].common->insert(classarray[curr->value]-1);
    }
    return true;
}
void Graph::print(){
//print graph in the specified format
    file<<numParts<<':';
    for(int i=0,j=0;j<numParts;i++){ // diffferent partitions
        if (nodearray[i].isroot()) {
            file<<' '<<nodearray[i].label;
            j++;
        }
    }file<<endl;
    for(int i=0,j=0;j<numParts;i++){ // edges
        if (nodearray[i].isroot()) {
            for(LLNode* curr = nodearray[i].common->Head();curr!=nullptr;curr=curr->next){
                file<<nodearray[i].label<<' '<<curr->value+1<<endl;
            }
            j++;
        }
    }
}