#include<vector>
#include<bits/stdc++.h>
#include<tuple>
#include<fstream>

class ListObj{
  public:
    int Value;
    ListObj *next;

    ListObj(int val){
      Value = val;
      next = nullptr;
    }

    ~ListObj() {;}
};

class ListTup{
    public:
    tuple<int, int> sim;
    ListTup *next;

    ListTup(int a, int b){
        sim = make_tuple(a, b);
        next = nullptr;
    }

    ~ListTup() {;}
};

class Node{
 public:
  int value;
  bool source=false;
  ListObj *froms;
  ListObj *tos;
  ListObj *adjcol;
};

int* man(string str){
    int *arr;
    arr = new int[2];
    string word = "";
    for (auto x:str){
        if (x == ' '){
            arr[0] = stoi(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    arr[1] = stoi(word);
    return arr;
}

class Graph{
    int numNodes;
    int numEdges;
    Node *nodes;
    ListObj *E1, *E2, *SNodes;
    ListTup *UsNodes;

    public:
    ListTup *SimNodes;
    ofstream gf;
    int *visited;
    int connCom=0;

    Graph(){
        int i=0;
        string text;
        ListObj *a, *b;
        while (getline(cin, text)){
            if (i==0){ numNodes = stoi(text);}
            else{
                int *aa = man(text);
                if (aa[0] == -1){ break; }
                if (E1 == nullptr){
                    E1 = new ListObj(aa[0]);
                    a = E1;
                }
                else{
                    a->next = new ListObj(aa[0]);
                    a = a->next;
                }
                if (E2 == nullptr){
                    E2 = new ListObj(aa[1]);
                    b = E2;
                }
                else{
                    b->next = new ListObj(aa[1]);
                    b = b->next;
                }   
            }
            i++;
        }
        numEdges = i-1;
        visited = new int[numNodes];
        ListObj *fi;
        ListObj *sn;
        nodes = new Node[numNodes];
        for (int i=0; i<numNodes; i++){
            nodes[i].value = i+1;
            visited[i]=0;
        }
        for (int i=1; i<=numNodes; i++){
            fi = E2;
            bool present = false;
            while (fi != nullptr){
                if (fi->Value == i){
                    present = true;
                }
                fi = fi->next;
            }
            if (!present){
                if (SNodes == nullptr){
                    SNodes = new ListObj(i);
                    nodes[i-1].source = true;
                    sn = SNodes;
                }
                else {
                    sn->next = new ListObj(i);
                    nodes[i-1].source = true;
                    sn = sn->next;
                }
            }
        }
        gf.open("al.txt");
        gf << "Source node: ";
        for (int i=0; i<numNodes; i++){if(nodes[i].source){gf << i+1 << " ";}}
        gf << "\n" << endl;
        ListObj *e_1[numNodes], *e_2[numNodes];
        ListObj *e1=E1, *e2=E2;
        while (e1 != nullptr){
            if (nodes[e1->Value-1].tos == nullptr){
                nodes[e1->Value-1].tos = new ListObj(e2->Value);
                e_1[e1->Value-1] = nodes[e1->Value-1].tos;
            }
            else {
                e_1[e1->Value-1]->next = new ListObj(e2->Value);
                e_1[e1->Value-1] = e_1[e1->Value-1]->next;
            }
            if (nodes[e2->Value-1].froms == nullptr){
                nodes[e2->Value-1].froms = new ListObj(e1->Value);
                e_2[e2->Value-1] = nodes[e2->Value-1].froms;
            }
            else {
                e_2[e2->Value-1]->next = new ListObj(e1->Value);
                e_2[e2->Value-1] = e_2[e2->Value-1]->next;
            }
            e1 = e1->next;
            e2 = e2->next;
        }
        string text2;
        ListTup *a1, *b1;
        while (getline(cin, text2)){
            int *aa1 = man(text2);
            if (aa1[0] == -1){ break; }
            if(UsNodes == nullptr){
                UsNodes = new ListTup(aa1[0], aa1[1]);
                a1 = UsNodes;
            }
            else {
                a1->next = new ListTup(aa1[0], aa1[1]);
                a1 = a1->next;
            }
        }
        ListTup *t1 = UsNodes;
        ListTup *f2;
        while(t1 != nullptr){
            ListObj *s1 = SNodes;
            bool b1 = false, b2 = false;
            b1 = nodes[get<0>(t1->sim)-1].source;
            b2 = nodes[get<1>(t1->sim)-1].source;
            if (b1 && b2){
                if (SimNodes == nullptr){
                    SimNodes = new ListTup(get<0>(t1->sim), get<1>(t1->sim));
                    f2 = SimNodes;
                }
                else{
                    f2->next = new ListTup(get<0>(t1->sim), get<1>(t1->sim));
                    f2 = f2->next;
                }
            }
            t1 = t1->next; 
        }
        ListTup *t2 = SimNodes;
        ListTup *t3;
        while(t2 != nullptr){
            t3 = t2;
            t2 = t2->next;
        }
        for (int i=0; i<numNodes; i++){
            ListObj *a1 = nodes[i].froms;
            if (a1 != nullptr && a1->next == nullptr){
                
                if (SimNodes == nullptr){
                    SimNodes = new ListTup(i+1, a1->Value);
                    t3 = SimNodes;
                }
                else{
                    t3->next = new ListTup(i+1, a1->Value);
                    t3 = t3->next;
                }
            }
        }
        ListTup *M = SimNodes;
        gf << "Similar Node pairs: "; 
        while(M != nullptr){
            if (nodes[get<0>(M->sim)].source || nodes[get<1>(M->sim)].source){
            gf << "(" << get<0>(M->sim) << ", " << get<1>(M->sim) << ") ";
            }
            M = M->next;
        }
        ListTup *t4 = SimNodes;
        ListTup *t5;
        while(t4 != nullptr){
            t5 = t4;
            t4 = t4->next;
        }
        for (int i=0; i<numNodes; i++){
            if(!nodes[i].source){
                for(int j=0; j<numNodes; j++){
                    if(!nodes[j].source){
                        bool a = Similar(nodes[i],nodes[j],SimNodes);
                        if(a){ 
                            gf <<"(" << i+1 << ", " << j+1 << ") ";
                            if (SimNodes == nullptr){
                                cout << "iehseuksk" << endl;
                                SimNodes = new ListTup(i+1, j+1);
                                t5 = SimNodes;
                            }
                            else{
                                t5->next = new ListTup(i+1, j+1);
                                t5 = t5->next;
                            }
                            }
                    }
                }
            }
        }
        gf << "\n" << endl;
        gf << "Collapsed graph:\n" << endl;
        collapAdj();
        connComp();
        gf << connCom << ":" << nodes[connCom].value+1<< endl;
    }
    
    bool Similar(Node n1, Node n2, ListTup *SimNodes){
        ListTup *sns = SimNodes;
        while(sns!=nullptr){
            if(n1.value == get<0>(sns->sim) && n2.value == get<1>(sns->sim)){
                return true;
            }
            sns=sns->next;
        }
        if (n1.froms==nullptr || n2.froms==nullptr || n1.source || n2.source){return false;}
        ListObj *l1=n1.froms;
        bool sims2 = true;
        while(l1!=nullptr){
            ListObj *l2=n2.froms;
            bool sims = false;
            while(l2!=nullptr){
                if(Similar(nodes[l1->Value-1], nodes[l2->Value-1], SimNodes)){
                    sims = true;
                    break;
                }
                l2 = l2->next;
            }
            l1 = l1->next;
            sims2=sims2 && sims;
        }
        ListObj *l3=n2.froms;
        bool sims4 = true;
        while(l3!=nullptr){
            ListObj *l4=n1.froms;
            bool sims3 = false;
            while(l4!=nullptr){
                if(Similar(nodes[l3->Value-1], nodes[l4->Value-1], SimNodes)){
                    sims3 = true;
                    break;
                }
                l4 = l4->next;
            }
            l3 = l3->next;
            sims4=sims4 && sims3;
        }
        return sims4 && sims2;
    }

    void collapAdj(){
        ListObj *adc[numNodes];
        ListTup *iter = SimNodes;
        while(iter != nullptr){
            if (nodes[get<0>(iter->sim)-1].adjcol == nullptr){
                nodes[get<0>(iter->sim)-1].adjcol = new ListObj(get<1>(iter->sim));
                adc[get<0>(iter->sim)-1] = nodes[get<0>(iter->sim)-1].adjcol;
            }
            else{
                adc[get<0>(iter->sim)-1]->next = new ListObj(get<1>(iter->sim));
                adc[get<0>(iter->sim)-1] = adc[get<0>(iter->sim)-1]->next;
            }
            if (nodes[get<1>(iter->sim)-1].adjcol == nullptr){
                nodes[get<1>(iter->sim)-1].adjcol = new ListObj(get<0>(iter->sim));
                adc[get<1>(iter->sim)-1] = nodes[get<1>(iter->sim)-1].adjcol;
            }
            else{
                adc[get<1>(iter->sim)-1]->next = new ListObj(get<0>(iter->sim));
                adc[get<1>(iter->sim)-1] = adc[get<1>(iter->sim)-1]->next;
            }
            iter = iter->next;
        }
    }

    void connComp(){
        for (int i=0; i<numNodes; i++){
            if(visited[i]==0){
                DFS(i);
                connCom++;
            }
        }
    }

    void DFS(int i){
        visited[i] = 1;
        for(ListObj *ad=nodes[i].adjcol; ad!=nullptr; ad=ad->next){
            if(visited[ad->Value]==0){
                DFS(ad->Value);
            }
        }
    }

};

