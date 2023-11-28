#include<iostream>
#include<fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class Graph {
    int N;    //number of vertices
    bool *array;
    fstream file;
    vector<int> from;   //from entries
    vector<int> to;      //to entries
    vector<int> source;  //source nodes
    vector<int> nonsource;   //non source nodes
    vector<vector<int> > collapse_graph; //collapsed graph representation
    vector<pair<int, int> > input;     //set of similar pairs given in the input
    set<pair<int, int> > similar;    //set of similar edges
    set<pair<int, int> > collapse_edges;    //collapsed edges

    public:
        Graph(int n, string name){   //constructor
            N = n;
            array = new bool[N];
            for (int i = 0; i < N; i++){
                array[i] = true;
            }
            file.open(name, ios::out);
            if (!file.is_open()) {
                cerr << "Couldn't open graph file " << name << ". Aborting ..." << endl;
                exit(-1);
                }
        }
        
        void update(int v1, int v2){   //updates the edges in the to and from vectors
            from.push_back(v1);
            to.push_back(v2);
        }

        void print_source_nodes(){     //it prints all the source nodes
            updatesourcenodes();
            file << "Source nodes:";
            for (int i = 0; i < source.size(); i++){
                file << " "<<source[i];
            }
            file << endl << endl;
        }

        void updatesourcenodes(){       //it checks all the nodes in 'to' vertex to see if they are source nodes or not, if yes then adds them to source vector
            for (int i = 1; i <= N; i++){
                vector<int>::iterator it = find(to.begin(), to.end(), i);
                if(it == to.end()){
                    source.push_back(i);
                }
            }
        }

        void givensimilar(int v1, int v2){     //updates the similar pairs given to us in the input vector
            pair<int, int> p = make_pair(v1,v2);
            input.push_back(p);
        }
       
        bool related(int n1, int n2){         //checks if two nodes are similar
            updatesourcenodes();
            pair<int, int> p = make_pair(n1,n2);
            vector<pair<int, int> >::iterator it = find(input.begin(), input.end(), p);
            if (!(it == input.end())){   //CASE 1
                return true;
            }
            if(count(to.begin(), to.end(), n1) == 1) {    //CASE 3
                vector<int>::iterator itt = find(to.begin(), to.end(), n1);
                if(from[itt - to.begin()] == n2){
                    return true;
                } 
            }
            vector<int>::iterator it1 = find(source.begin(), source.end(), n1);  //CASE2
            vector<int>::iterator it2 = find(source.begin(), source.end(), n2);
            if(it1 == source.end() && it2 == source.end()){
                for (int i = 0; i < to.size(); i++){
                    if(to[i] == n1){
                        int m1 = from[i];
                        int count = 0;
                        for (int i = 0; i < to.size(); i++)
                        {
                            if(to[i] == n2 && related(m1, from[i])) count++;
                        }
                        if(count == 0) return false; 
                    }
                    if(to[i] == n2){
                        int m2 = from[i];
                        int count = 0;
                        for (int i = 0; i < to.size(); i++)
                        {
                            if(to[i] == n1 && related(m2, from[i])) count++;
                        }
                        if(count == 0) return false;
                    }
                }
                return true;
            }
            return false;
        }

        void updatesimilar(){             //loops through all pairs of nodes and updates them in similar set if they are related
            for (int i = 1; i <= N; i++){
                 for (int j = 1; j <= N; j++){
                     if(related(i,j)){
                          similar.insert(make_pair(i,j));
                      }
                 }
            }
            
        }
       
        void printsimilarpairs(){         //prints all the similar pairs of nodes in the required way
            updatesimilar();
            file <<"Similar node pairs:";
            set<pair<int, int> >::iterator itr;
            for(itr = similar.begin(); itr != similar.end(); itr++){
                int f = itr->first;
                int s = itr->second;
                
                file <<" ("<<f<<","<<s<<")";
            }
            file << endl << endl; 
        }
        void collapse(){              //This function collapses the graph and prints the edges as well as nodes in collapsed graph
             set<pair<int, int> >::iterator itr;
             for(itr = similar.begin(); itr != similar.end(); itr++){    //adding all symmetric pairs
                int f = itr->first;
                int s = itr->second;
                pair<int, int> p = make_pair(s,f);
                similar.insert(p);
             }

             for(itr = similar.begin(); itr != similar.end(); itr++){    //adding all transitive pairs
                int a = itr->first;
                int b = itr->second;
                set<pair<int, int> >::iterator temp;
                for(temp = similar.begin(); temp != similar.end(); temp++){
                    if(temp->first == b){
                        int c = temp->second;
                        pair<int, int> transitive = make_pair(a,c);
                        similar.insert(transitive);
                    }
                }  
            }

            int t = N-1;
            while(t != -1){                                  //collapsing all the related pairs of vectors into one single vector denoted by the highest node in it 
                if(array[t]){
                    int n = t+1;
                    vector<int> v ;
                    v.push_back(n);
                    set<pair<int, int> >::iterator itr;
                    for(itr = similar.begin(); itr != similar.end(); itr++){
                        int f = itr->first;
                        int s = itr->second;
                        if(f == n){
                            array[s-1] = false;
                            v.push_back(s);
                        }
                    }
                    collapse_graph.push_back(v);
                }
                t--;
            }
            reverse(collapse_graph.begin(), collapse_graph.end());
            //printing the required things
            file <<"Collapsed graph:"<<endl;
           
            file <<collapse_graph.size()<<":";
            for (int i = 0; i < collapse_graph.size(); i++)
            {
                file<<" "<<collapse_graph[i][0];
            }
            file << endl;

            //checking the remaining edges after collapsing and adding them to collapsed graph   
            for (int i = 0; i < to.size(); i++){
                    int f = from[i];
                    int s = to[i];
                    pair<int, int> p = make_pair(f,s);
                    int ff, ss;
                    set<pair<int, int> >::iterator ii = find(similar.begin(), similar.end(), p);
                    if(ii == similar.end()){
                        for (int i = 0; i < collapse_graph.size(); i++)
                        {
                            for (int j = 0; j < collapse_graph[i].size(); j++)
                            {
                                if(collapse_graph[i][j] == f) ff = i;
                                if(collapse_graph[i][j] == s) ss = i;
                            }
                        }
                        if(ff != ss){
                            collapse_edges.insert(make_pair(collapse_graph[ff][0], collapse_graph[ss][0]));
                        }
                    }
            }
            //printing edges in collapsed graph
            set<pair<int, int> >::iterator tempo;
                for(tempo = collapse_edges.begin(); tempo != collapse_edges.end(); tempo++){
                    int f = tempo->first;
                    int s = tempo->second;

                    file <<f<<" "<<s<<endl;
                }
                file << endl<< endl;
                
        }        
};

int main(){
    int N; cin>>N;   //number of nodes
    Graph* g;
    g = new Graph(N, "outgraph.txt");
    int count = 0;

    while(true){     //taking in values and updating them suitably
        int v1, v2;
        cin>>v1>>v2;
        if(v1 == -1 && v2 == -1){
            count++;
            if(count == 1) continue;
            else break;
        }
        if(count == 0) g->update(v1,v2);
        if(count == 1) g->givensimilar(v1,v2);
    }
   
    g->print_source_nodes();
    g->printsimilarpairs();
    g->collapse();
    return 0;
}