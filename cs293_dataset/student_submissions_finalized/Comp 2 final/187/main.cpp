#include "Graph.cpp"
using namespace std;
int main(int argc, char *argv[]){
    string d;
     Graph *g;
    getline(cin,d);
    if(getline(cin,d)){
        int num = stoi(d);
        g = new Graph(num,"outgraph.txt");
    }
    while(getline(cin,d)){
        if(d == "-1 -1"){
            break;
        }
        else{
        stringstream s(d);
        string l;
        int a,b;
        if(s >> l){
            a = stoi(l);
        }
        if(s >> l){
            b = stoi(l);    
        }
        g->insert(a-1,b-1);
    }
}
    while(getline(cin,d)){
        if(d == "-1 -1"){
            break;
        }
        else{
            stringstream s(d);
            string l;
            int a,b;
            if(s >> l){
                a = stoi(l);
            }
            if(s >> l){
                b = stoi(l);    
            }
            g->setsimilar(a-1,b-1);
        }
    }
    g->sourceNodes();
    g->similarNodes();
}