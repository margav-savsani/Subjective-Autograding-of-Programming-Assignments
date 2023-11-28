#include<iostream>
#include<fstream>
#include "Graph.h"
using namespace std;
int main(){
    ofstream out("outgraph.txt");
    int num_nodes;
    cin>>num_nodes;
    Graph DAG(num_nodes);
    //Filling the nodes array
    for(int i=0; i<num_nodes; i++){
        Node node(i+1);
        DAG.nodes[i] = node;
    }
    // //!!
    // for(int i = 0; i<num_nodes; i++) cout<<DAG.nodes[i].value<<" ";
    // cout<<endl;
    // //!!
    //Filling the adjacency matrix
    while(true){
        int parent; int child;
        cin>>parent; cin>>child;
        if(parent == -1 || child == -1 ){
            break;
        }
        DAG.nodes[parent-1].outDegree++;
        DAG.nodes[child-1].inDegree++;
        DAG.adjMatrix[parent-1][child-1] = 1;
        listOfObjects<Node> *parentsCopy = DAG.nodes[child-1].parents;
        if(parentsCopy == nullptr){
            DAG.nodes[child-1].parents = new listOfObjects<Node>(DAG.nodes[parent-1]);
        }
        else{
            while(parentsCopy->next!=nullptr) parentsCopy = parentsCopy->next;
            parentsCopy->next = new listOfObjects<Node>(DAG.nodes[parent-1]);
            parentsCopy->next->prev = parentsCopy->next;
        }
    }
    //Getting Source Nodes
    for(int i = 0; i<num_nodes; i++){
        if(DAG.nodes[i].inDegree==0){
            DAG.numSourceNodes++;
            if(DAG.SourceNodes==nullptr){
                DAG.SourceNodes = new listOfObjects<Node>(DAG.nodes[i]);
            }
            else{
                DAG.SourceNodes->next = new listOfObjects<Node>(DAG.nodes[i]);
                DAG.SourceNodes->next->prev = DAG.SourceNodes;
                DAG.SourceNodes = DAG.SourceNodes->next;
            }
        }
    }
    //Restoring SourceNodes
    while(true){
        if(DAG.SourceNodes==nullptr) break;
        if(DAG.SourceNodes->prev == nullptr) break;
        DAG.SourceNodes = DAG.SourceNodes->prev;
    }
    //DFS on all source Nodes
    DAG.time = 0;
    for(int i = 0; i<DAG.numSourceNodes; i++){
        DAG.DFS(DAG.SourceNodes->object.value -1);
        if(i!=DAG.numSourceNodes-1){
            DAG.SourceNodes = DAG.SourceNodes->next;
        }
    }
    DAG.time = 0;
    //Restoring SourceNodes
    while(true){
        if(DAG.SourceNodes==nullptr) break;
        if(DAG.SourceNodes->prev == nullptr) break;
        DAG.SourceNodes = DAG.SourceNodes->prev;
    }
    // //!!
    // cout<<"Printing Source Nodes: ";
    // while(true){
    //     cout<<DAG.SourceNodes->object.value<<" ";
    //     if(DAG.SourceNodes->next == nullptr) break;
    //     DAG.SourceNodes = DAG.SourceNodes->next;
    // }
    // cout<<endl;
    // while(true){
    //     if(DAG.SourceNodes==nullptr) break;
    //     if(DAG.SourceNodes->prev == nullptr) break;
    //     DAG.SourceNodes = DAG.SourceNodes->prev;
    // }
    // //!!
    //Sorting the nodes array in decreasing order of depTime
    for(int i=0;i<num_nodes;i++){		
		for(int j=i+1;j<num_nodes;j++)
		{
			if(DAG.nodes[i].depTime<DAG.nodes[j].depTime)
			{
				Node temp  = DAG.nodes[i];
				DAG.nodes[i]=DAG.nodes[j];
				DAG.nodes[j]=temp;
			}
		}
	}
    // //!!
    // for(int i = 0; i<num_nodes; i++){
    //     cout<<DAG.nodes[i].value<<" ";
    // }
    // cout<<endl;
    // //!!
    //Updating similarity matrix
    //Taking user input of similarity between nodes
    while(true){
        int i; int j;
        cin>>i>>j;
        if(i == -1 || j == -1 ){
            break;
        }
        DAG.similarityRelation[i-1][j-1] = 1;
    }
    //Finding similarity according to rest rules
    for(int i = 0; i < num_nodes; i++){
        // //!!
        // cout<<"At node with value: "<<DAG.nodes[i].value<<endl;
        // //!!
        Node currNode = DAG.nodes[i];
        //if inDegree is 0, skip
        if(currNode.inDegree == 0) {
            // //!!
            // cout<<"Continuing because Indegree is 0"<<endl;
            // //!!
            continue;
        }
        if(currNode.inDegree == 1){
            DAG.similarityRelation[currNode.value-1][currNode.parents->object.value-1] = 1;
            // //!!
            // cout<<"Added Relation because of 3rd reason"<<endl;
            // //!!
        }
        for(int j = i; j>=0; j--){
            // //!!
            // cout<<"Checking pairs for "<<currNode.value<<" and "<<DAG.nodes[j].value<<endl;
            // //!!
            bool flag = 0;
            bool check1 = 1;
            bool check2 = 1;
            listOfObjects<Node> *node1ParentCopy = currNode.parents;
            listOfObjects<Node> *node2ParentCopy = DAG.nodes[j].parents;
            while(node1ParentCopy!=nullptr){
                bool checker = 0;
                for(listOfObjects<Node> *node2ParentCopyCopy = node2ParentCopy;node2ParentCopyCopy!=nullptr; node2ParentCopyCopy = node2ParentCopyCopy->next){
                    if(DAG.similarityRelation[node1ParentCopy->object.value - 1][node2ParentCopyCopy->object.value -1]==1){
                        checker = 1; break;
                    }
                }
                if(checker == 0) check1 = 0;
                if(check1 == 0){flag = 1; break;}
                node1ParentCopy = node1ParentCopy->next;
            }
            if(flag == 1) continue;
            node1ParentCopy = currNode.parents;
            node2ParentCopy = DAG.nodes[j].parents;
            while(node2ParentCopy!=nullptr){
                bool checker = 0;
                for(listOfObjects<Node> *node1ParentCopyCopy = node1ParentCopy;node1ParentCopyCopy!=nullptr; node1ParentCopyCopy = node1ParentCopyCopy->next){
                    if(DAG.similarityRelation[node2ParentCopy->object.value - 1][node1ParentCopyCopy->object.value -1]==1){
                        checker = 1; break;
                    }
                }
                if(checker == 0) check2 = 0;
                if(check2 == 0){flag = 1; break;}
                node2ParentCopy = node2ParentCopy->next;
            }
            if(flag == 1) continue;
            if(check1==1 && check2==1){
                DAG.similarityRelation[DAG.nodes[i].value - 1][DAG.nodes[j].value - 1] = 1;
                DAG.similarityRelation[DAG.nodes[j].value - 1][DAG.nodes[i].value - 1] = 1;
            }
            
        }

    }
    //Printing the Source Nodes:
    out<<"Source Nodes: ";
    for(int i = 0; i<DAG.numSourceNodes; i++){
        out<<DAG.SourceNodes->object.value<<" ";
        DAG.SourceNodes = DAG.SourceNodes->next;
    }
    out<<endl<<endl;
    
    // //!!
    // DAG.printsimilarityMatrix();
    // //!!

    //Printing Similar Node Pairs:
    out<<"Similar Node Pairs: ";
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < num_nodes; j++){
            if(DAG.similarityRelation[i][j]==1){
                out<<"("<<i+1<<", "<<j+1<<") ";
            }
        }
    }
    out<<endl<<endl;

    //Making adjacency matrix symmetric
    for(int i = 0; i< num_nodes; i++){
        for(int j = 0; j<num_nodes; j++){
            if(DAG.similarityRelation[i][j] == 1){
                DAG.similarityRelation[j][i] = 1;
            }
        }
        DAG.visited[i] = 0;
    }
    // //!!
    // DAG.printsimilarityMatrix();
    // //!!
    //Finding and assigning components
    int numComponents = 0;
    listOfObjects<int> *Components = nullptr;
    for(int i = 0; i<num_nodes; i++){
        if(DAG.visited[i]==0){
            int var = 0;
            DAG.DFSFindComponent(i, var);
            // cout<<"Var: "<<var+1<<endl;
            DAG.DFSAssignComponent(i, var);
            numComponents++;
            if(Components==nullptr){
                Components = new listOfObjects<int>(var+1);
            }
            else{
                Components->next = new listOfObjects<int>(var+1);
                Components->next->prev = Components;
                Components = Components->next;
            }
        }
    }
    while(true){
        if(Components==nullptr) break;
        if(Components->prev == nullptr) break;
        Components = Components->prev;
    }
    for(int i =0; i<num_nodes; i++){
        for(int j =i+1; j<num_nodes; j++){
            if(DAG.adjMatrix[i][j] == 1){
                DAG.collapsedadjMatrix[DAG.components[i]][DAG.components[j]] = 1;
            }
        }
    }
    //Printing Collapsed Graph:
    out<<"Collapsed Graph:"<<endl<<endl;
    out<<numComponents<<": ";
    while(Components!=nullptr){
        out<<Components->object<<" ";
        Components = Components->next;
    }
    out<<endl;
    for(int i =0; i<num_nodes; i++){
        for(int j =0; j<num_nodes; j++){
            if(i==j) DAG.collapsedadjMatrix[i][j] = 0;
            if(DAG.collapsedadjMatrix[i][j]==1){
                out<<i+1<<" "<<j+1<<endl;
            }
        }
    }

    out.close();
}