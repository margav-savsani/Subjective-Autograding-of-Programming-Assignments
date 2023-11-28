#include "main.h"
#include <fstream>
#include <string>
#include<algorithm>
struct compare
{
    int key;
    compare(int const &i): key(i) {}
 
    bool operator()(int const &i) {
        return (i == key);
    }
    // this is used for comparing
};
struct map{
    int start;
    int finish;
    map(int s,int f){
        start = s;
        finish = f;
    }
    //this takes care of the direction  
};
int main(int argc, char **argv){
    vector<int> data;
    vector<int> fakesourceNodes;
    vector<int> sourceNodes;
    vector<int> nonsourceNodes;
    vector<map> maps;
    vector<int> similarNodes1;
    vector<int> similarNodes2;
    int c;
    cin>>c;
    data.push_back(c);
    while(true){
        int a,b;
        cin>>a>>b;
        data.push_back(a);
        data.push_back(b);
        if(a == -1 && b == -1) break;
    }
    while(true){
        int a,b;
        cin>>a>>b;
        data.push_back(a);
        data.push_back(b);
        if(a == -1 && b == -1) break;
    }
    node* nodes;
    nodes = new node[data[0]];
    for(int g = 0; g < data[0];g++){
        nodes[g].value = g+1;
        fakesourceNodes.push_back(g+1);
    }
    int k = 1;
    while(k < data.size()){
        if(data[k] != -1){
            nodes[data[k]-1].addoutgoing(data[k+1]-1);
            nodes[data[k]-1].adjacentnodes.push_back(data[k+1]-1);//data has taken all the digits in the respective text file
            nodes[data[k+1]-1].addincoming(data[k]-1);//this takes care of the pointing the nodes 
            nodes[data[k+1]-1].adjacentnodes.push_back(data[k]-1);
            k = k + 2;
        }
        else
            break;
    }
    k = k+2;
    while(k < data.size()){
        if(data[k] != -1){
            map y = map(data[k],data[k+1]);
            maps.push_back(y);
            similarNodes1.push_back(data[k]);
            similarNodes2.push_back(data[k+1]);//this takes care of the second part after -1,-1
            k = k + 2;
        }
        else
            break;
    }
    for(int g = 0; g < data[0];g++){
        if(nodes[g].outgoingnodes.size() != 0){
            for (auto & element : nodes[g].outgoingnodes) {
                vector<int> check;
                check = fakesourceNodes;
                if (find_if(check.begin(), check.end(), compare(element+1)) != check.end()) {
                    fakesourceNodes[element] = 0;
                }
            };
        }
        else
            continue;
    }
    cout<<"Source Nodes: ";
    int t = 0;
    for(auto & element : fakesourceNodes){
        if(element != 0){
            cout<<element<<" ";
            sourceNodes.push_back(element);//this has all the source nodes,non source nodes
        }
        else
            nonsourceNodes.push_back(t+1);
        t++;
    }
    cout<<endl;
    
    for(auto & element1 : nonsourceNodes){
        for(auto & element2 : nonsourceNodes){
            if(element1 != element2){
                bool similars1[nodes[element1-1].adjacentnodes.size()];
                bool similars2[nodes[element2-1].adjacentnodes.size()];
                for(auto & a : nodes[element1-1].adjacentnodes){
                    int o = 0;
                    for(auto & m : maps){
                        similars1[o] = false;// i have updated the mappings of similar nodes but there is a major fault
                        if(m.start-1 == a){// which i have recognised at the end that the even the map gets updated but some pf the cases may be possible
                        //after updating the mapping which i have considered error.
                            vector<int> check;
                            check = nodes[element2-1].adjacentnodes;
                            similars1[o] = (find_if(check.begin(), check.end(), compare(m.finish-1)) != check.end());
                            if(similars1[o]) break;
                        }
                    }
                    o++;
                }
                for(auto & a : nodes[element2-1].adjacentnodes){
                    int o = 0;
                    for(auto & m : maps){
                        similars2[o] = false;
                        if(m.start-1 == a){
                            vector<int> check;
                            check = nodes[element1-1].adjacentnodes;
                            similars2[o] = (find_if(check.begin(), check.end(), compare(m.finish-1)) != check.end());
                            if(similars2[o]) break;
                        }
                    }
                    o++;
                }
                bool q = true;
                bool p = true;
                for(int i = 0;i<sizeof(similars2)/sizeof(similars2[0]);i++){
                    if(similars2[i] == 0){
                        q = false;
                        break;
                    }
                }
                for(int i = 0;i<sizeof(similars1)/sizeof(similars1[0]);i++){
                    if(similars1[i] == 0){
                        p = false;
                        break;
                    }
                }
                if(p && q){
                    map y = map(element1,element2);
                    maps.push_back(y);
                    similarNodes1.push_back(element1);
                    similarNodes2.push_back(element2);
                }
            }
        }
    }
    for(int g = 0; g < data[0];g++){
        for (auto & element : nodes[g].outgoingnodes){
            if(nodes[element].incomingnodes.size() == 1){
                map y = map(element+1,nodes[g].value);
                maps.push_back(y);
                similarNodes2.push_back(nodes[g].value);
                similarNodes1.push_back(element+1);
            }
        }
    }
    cout<<"Similar Node pairs: ";
    for(int i = 0;i < similarNodes1.size();i++){
            cout<<"("<<similarNodes1[i]<<", "<<similarNodes2[i]<<") ";
    }
    cout<<endl;
}