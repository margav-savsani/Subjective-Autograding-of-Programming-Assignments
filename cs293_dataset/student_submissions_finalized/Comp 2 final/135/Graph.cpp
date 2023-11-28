#ifndef GRAPH_CPP
#define GRAPH_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif

#ifndef GRAPH_H
#include "Graph.h"
#endif

void Graph::makeGraph(){
    cin >> numNodes;

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
        cerr << "Memory allocation failure." << endl;
        exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
        nodes[i].value = i+1;
    }

    int n1, n2;

    while(true){
        cin >> n1 >> n2;
        if(n1 != -1 && n2 != -1){
            nodes[n1-1].outNodes.insert(n2);
            nodes[n2-1].inNodes.insert(n1);
            nodes[n1-1].isSink = 0;
            nodes[n2-1].isSource = 0;
        }
        else break;
    }

    while(true){
        cin >> n1 >> n2;
        if(n1 != -1 && n2 != -1){
            if(nodes[n1-1].isSource && nodes[n2-1].isSource){
                nodes[n1-1].similarity.insert(n2);
                // nodes[n2-1].similarity.insert(n1);
            }
        }
        else break;
    }
    
    for(int i=0; i<numNodes; i++){
        if(nodes[i].inNodes.getSize() == 1){
            nodes[i].similarity.insert(nodes[i].inNodes[0]);
        }
    }
}

void Graph::sourceNodes(){
    ofstream out;
    out.open("outgraph.txt", ios::out);
    out << "Source Nodes:";
    for(int i=0; i<numNodes; i++){
        if(nodes[i].isSource){
            out << " " << nodes[i].value;
        }
    }
    out << "\n";
}

void Graph::sinkNodes(){
    ofstream out;
    out.open("outgraph.txt", ios::app);
    out << "Sink Nodes:";
    for(int i=0; i<numNodes; i++){
        if(nodes[i].isSink){
            out << " " << nodes[i].value;
        }
    }
    out << "\n";
}

bool Graph::isSimilar(Node a, Node b){
    if(a.similarity.find(b.value)) return true;
    if(a.value == b.value) return false;

    if(!a.isSource && !b.isSource){
        for(int i=0; i<a.inNodes.getSize(); i++){
            bool found = false;
            for(int j=0; j<b.inNodes.getSize(); j++){
                if(isSimilar(nodes[a.inNodes[i]-1], nodes[b.inNodes[j]-1])){
                    found = true;
                }
                // out << "Found = " << found << " -> " << nodes[a.inNodes[i]].value << " " << nodes[b.inNodes[j]].value << "\n";
            }
            if(found == false){
                return false;
            }
        }
        
        for(int i=0; i<b.inNodes.getSize(); i++){
            bool found = false;
            for(int j=0; j<a.inNodes.getSize(); j++){
                if(isSimilar(nodes[b.inNodes[i]-1], nodes[a.inNodes[j]-1])){
                    found = true;
                }
                // out << "Found = " << found << " -> " << nodes[a.inNodes[i]].value << " " << nodes[b.inNodes[j]].value << "\n";
            }
            if(found == false){
                return false;
            }
        }

        return true;
    }
    return false;
}

void Graph::updateSimilarityIndex(int a, int b){
    static int recc = 0;
    if(nodes[a-1].similarityIndex == nodes[b-1].similarityIndex && nodes[a-1].similarityIndex != -1){
        // out << recc << " Update: " << nodes[a-1].value << " " << nodes[a-1].similarityIndex << " " << nodes[b-1].value << " " << nodes[b-1].similarityIndex << "\n";
        return;
    }
    if(nodes[b-1].similarityIndex == -1){
        int l=nodes[a-1].similarityIndex;
        if(a>l) l = a;
        if(b>l) l = b;

        nodes[a-1].similarityIndex = l;
        nodes[b-1].similarityIndex = l;
        // out << recc << " Update: " << nodes[a-1].value << " " << nodes[a-1].similarityIndex << " " << nodes[b-1].value << " " << nodes[b-1].similarityIndex << "\n";
        
        for(int i=0; i<numNodes; i++){
            if(nodes[i].similarity.find(a)){
                // out << b << " " << nodes[i].value << "\n";
                recc++;
                updateSimilarityIndex(a, nodes[i].value);
                recc--;
                // updateSimilarityIndex(nodes[i].value, b);
            }
        }
        for(int i=0; i<nodes[a-1].similarity.getSize(); i++){
            // out << b << " " << nodes[b-1].similarity[i] << "\n";
            recc++;
            updateSimilarityIndex(a, nodes[a-1].similarity[i]);
            recc--;
            // updateSimilarityIndex(nodes[b-1].similarity[i], b);
        }
        return;
    }
    // if(nodes[a-1].similarityIndex == -1){
    //     int l=nodes[b-1].similarityIndex;
    //     if(a>l) l = a;
    //     if(b>l) l = b;

    //     nodes[a-1].similarityIndex = l;
    //     nodes[b-1].similarityIndex = l;

    //     return;
    // }
    int l=nodes[a-1].similarityIndex;
    if(a>l) l = a;
    if(b>l) l = b;
    if(nodes[b-1].similarityIndex>l) l = nodes[b-1].similarityIndex;
    
    nodes[a-1].similarityIndex = l;
    nodes[b-1].similarityIndex = l;
    // out << recc << " Update: " << nodes[a-1].value << " " << nodes[a-1].similarityIndex << " " << nodes[b-1].value << " " << nodes[b-1].similarityIndex << "\n";

    for(int i=0; i<numNodes; i++){
        if(nodes[i].similarity.find(b)){
            // out << b << " " << nodes[i].value << "\n";
            recc++;
            updateSimilarityIndex(b, nodes[i].value);
            recc--;
            // updateSimilarityIndex(nodes[i].value, b);
        }
    }
    for(int i=0; i<nodes[b-1].similarity.getSize(); i++){
        // out << b << " " << nodes[b-1].similarity[i] << "\n";
        recc++;
        updateSimilarityIndex(b, nodes[b-1].similarity[i]);
        recc--;
        // updateSimilarityIndex(nodes[b-1].similarity[i], b);
    }
    
    for(int i=0; i<numNodes; i++){
        if(nodes[i].similarity.find(a)){
            // out << b << " " << nodes[i].value << "\n";
            recc++;
            updateSimilarityIndex(a, nodes[i].value);
            recc--;
            // updateSimilarityIndex(nodes[i].value, b);
        }
    }
    for(int i=0; i<nodes[a-1].similarity.getSize(); i++){
        // out << b << " " << nodes[b-1].similarity[i] << "\n";
        recc++;
        updateSimilarityIndex(a, nodes[a-1].similarity[i]);
        recc--;
        // updateSimilarityIndex(nodes[b-1].similarity[i], b);
    }
}

void Graph::similarNodes(){
    ofstream out;
    out.open("outgraph.txt", ios::app);
    for(int i=0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            if(isSimilar(nodes[i], nodes[j])){
                int n1 = nodes[i].value;
                int n2 = nodes[j].value;
                updateSimilarityIndex(n1, n2);
                updateSimilarityIndex(n2, n1);
                
                nodes[i].similarity.insert(nodes[j].value);
            }
        }
    }
    out << "Similar node pairs:";
    for(int i=0; i<numNodes; i++){
        for(int j=0; j<nodes[i].similarity.getSize(); j++){
            out << " (" << nodes[i].value << ", " << nodes[i].similarity[j] << ")";
        }
    }
    out << "\n";
}

void Graph::allNodes(){
    ofstream out;
    out.open("outgraph.txt", ios::app);
    for(int i=0; i<numNodes; i++){
        Node n = nodes[i];
        out << n.value << ": InNodes-> ";
        for(int j=0; j<n.inNodes.getSize(); j++){
            out << n.inNodes[j] << " ";
        }
        out << ": OutNodes-> ";
        for(int j=0; j<n.outNodes.getSize(); j++){
            out << n.outNodes[j] << " ";
        }
        out << "\n";
    }
}

void Graph::printSimilarity(){
    ofstream out;
    out.open("outgraph.txt", ios::app);
    for(int i=0; i<numNodes; i++){
        out << nodes[i].value << " " << nodes[i].similarityIndex << "\n";
    }
}

void Graph::collapse(){
    ofstream out;
    out.open("outgraph.txt", ios::app);
    vector<int> collVer;
    for(int i=0; i<numNodes; i++){
        int a = nodes[i].similarityIndex;
        if(a == -1){
            a = nodes[i].value;
        }
        collVer.insert(a);
    }
    out << "Collapsed graph:\n";
    out << collVer.getSize() << ":";
    for(int i=0; i<collVer.getSize(); i++){
        out << " " << collVer[i];
    }
    out << "\n";

    vector<string> collEdges;
    for(int i=0; i<numNodes; i++){
        int a = nodes[i].similarityIndex;
        for(int j=0; j<nodes[i].outNodes.getSize(); j++){
            int b = nodes[nodes[i].outNodes[j]-1].similarityIndex;
            if(a == -1){
                a = nodes[i].value;
            }
            if(b == -1){
                b = nodes[nodes[i].outNodes[j]-1].value;
            }
            if(a != b){
                // out << "Test: " << a << " " << b << "\n";
                collEdges.insert(to_string(a) + " " + to_string(b));
            }
        }
    }
    for(int i=0; i<collEdges.getSize(); i++){
        out << collEdges[i] << "\n";
    }
}

#endif