#include<iostream>
#include <vector>
using namespace std;

struct intpair{
    int n1; int n2;
};


struct node{
    int value;
    vector<int> incoming;
    vector<int> outgoing;
    vector<int> similarto;
    vector<int> closure;
    node(int value){
     this->value=value;
    }
    void addIncomingedge(int value){
     incoming.push_back(value);
    }
    void addOutgoingedge(int value){
     outgoing.push_back(value);
    } 
};

class graph{
    public:
    int num_nodes;
    vector<node> nodes;
    
        graph(int num_nodes){
            this->num_nodes = num_nodes;
            for (int i=0; i<num_nodes; i++){
                nodes.push_back(node(i+1)); 
            }
        }
        void addedge(int n1, int n2){
            nodes[n1].addOutgoingedge(n2);
            nodes[n2].addIncomingedge(n1);
        }
        void printSourceNodes(){
            cout << "source nodes: ";
            for (int i=0; i<num_nodes; i++){
                if (nodes[i].incoming.empty()) cout << nodes[i].value << " ";
            }
        }
        bool isSimilar(int n1, int n2){
            for (int i=0; i<nodes[n1].similarto.size(); i++){
                if (n2 == nodes[n1].similarto[i]) return true;
            }
            return false;
        }
        void addSimilarNodes(){

            while(true){
                int num_added =0;
                for(int i=0; i<num_nodes; i++){
                    for(int j=0; j<num_nodes; j++){
                        bool present = false;
                        for(int k=0; k<nodes[i].similarto.size(); k++){
                            if(nodes[i].similarto[k]==j) {present=true; break;}
                        }
                        if (!present){
                            if(nodes[i].incoming.size()==1 && nodes[i].incoming[0]==j){
                                nodes[i].similarto.push_back(j);
                                num_added++;
                                continue;
                            }
                            else{
                                bool paired = false;
                                for(int k=0; k<nodes[i].incoming.size(); k++){
                                    bool found = false;
                                    for (int l=0; l<nodes[j].incoming.size(); l++){
                                        if (isSimilar(nodes[i].incoming[k],nodes[j].incoming[l])){
                                            found = true;
                                            break;
                                        }
                                    }
                                    if(!found) {paired = false; break;}
                                    if (found && k==nodes[i].incoming.size()-1) {paired= true; break;}
                                }
                                if (paired){
                                paired = false;
                                for(int k=0; k<nodes[j].incoming.size(); k++){
                                    bool found = false;
                                    for (int l=0; l<nodes[i].incoming.size(); l++){
                                        if (isSimilar(nodes[j].incoming[k],nodes[i].incoming[l])){
                                            found = true;
                                            break;
                                        }
                                    }
                                    if(!found) {paired = false; break;}
                                    if (found && k==nodes[j].incoming.size()-1) {paired= true; break;}
                                }
                                }
                                if (paired){
                                    nodes[i].similarto.push_back(j);
                                    num_added++;
                                    continue;
                                }
                            }
                        }
                    }
                }
                if (num_added==0) break;
            }
        }
        void printSimilarNodes(){
            cout<< endl << "similar nodes: ";
            for (int i=0; i<num_nodes; i++){
                for(int j=0; j<nodes[i].similarto.size(); j++){
                    cout << "(" << nodes[i].value << ", " << nodes[nodes[i].similarto[j]].value << ") ";
                }
            }
        }

        bool edgepresent(int n1, int n2){
            for (int i=0; i<nodes[n1].closure.size(); i++){
                if (n2 == nodes[n1].closure[i]) return true;
            }
            return false;
        }

        
};


int main(){
    int n;
    cin >> n;
    graph g = graph(n);
    while (true){
        int n1,n2;
        cin >> n1 >> n2;
        if (n1==-1 && n2==-1) break;
        else{
            g.addedge(n1-1,n2-1);
        }
    }
    while (true){
        int n1,n2;
        cin >> n1 >> n2;
        if (n1==-1 && n2==-1) break;
        else{
            g.nodes[n1-1].similarto.push_back(n2-1);
        }
    }
    g.printSourceNodes();
    g.addSimilarNodes();
    g.printSimilarNodes();
}
