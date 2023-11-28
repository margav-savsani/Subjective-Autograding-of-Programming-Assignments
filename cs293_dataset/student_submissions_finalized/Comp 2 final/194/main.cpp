#include "Graph.h"

using namespace std;

// class similar_nodes{
//     public:
//         similar_nodes(){
//             v1 = 0;
//             v2 = 0;
//             next = nullptr;
//         }
//         similar_nodes *next;
//         int v1,v2;

// };

bool func(int **s, Node *n, int i, int j);
void call_for_child(int **s, Node *n, int i, int j){
    Node *temp1 = n[i].outgoing_node;
    while(temp1!=nullptr){
        Node *temp2 = n[j].outgoing_node;
        while(temp2!=nullptr){
            if(func(s,n,temp1->value-1,temp2->value-1)==true && func(s,n,temp1->value-1,temp2->value-1)==true){
                s[temp1->value-1][temp2->value-1]=1;
                s[temp2->value-1][temp1->value-1]=1;
            }
            temp2 = temp2->outgoing_node;
        }
        temp1=temp1->outgoing_node;
    }
}
bool func(int **s, Node *n, int i, int j){

    //  if(i==j){
    //             return false;
    // }
            if(s[i][j]==0){
                bool b = false;
                Node *temp = n[i].incoming_node;
                while(temp!=nullptr){
                    
                    bool found = false;
                    Node *temp2 = n[j].incoming_node;
                    //cout<<i<<" "<<j<<" "<<temp->value<<" "<<temp2->value<<endl;
                    while(temp2!=nullptr){

                            //cout<<i<<" "<<j<<" "<<temp->value<<" "<<temp2->value<<endl;
                        if(s[temp->value-1][ temp2->value-1]==1){
                            found  = true;
                            break;
                        }
                        temp2 = temp2->incoming_node;
                    }
                    if(found == false){
                        b = true;
                        break;
                    }
                    temp = temp->incoming_node;
                }
                if(b==false && n[i].incoming_node!=nullptr){
                    //cout<<i<<"jhasjh"<<j<<endl;
                    // s[i][j] = 1;
                    // s[j][i] = 1;
                    call_for_child(s,n,i,j);
                    return true;
                }
            }
            return false;
}

void func2(int **s, Node* e,Node *t,bool *include, int i, int num){
    if(include[i]==true){
            return;
        }
    include[i]=true;
    Node *temp= t;
        for(int j=0;j<num;j++){
            //cout<<i<<" "<<j<<" "<<temp->value<<" "<<e->value<<endl;
            if(s[i][j]==1 || s[j][i]==1){
                //cout<<"jwq\n";
                // if(include[j]==true){
                //     continue;
                // }
                if(temp->eq==nullptr){
                    //cout<<include[j];
                    //cout<<j+1<<"jkerjk\n";
                    temp->eq = new Node(j+1);
                    //cout<<j+1<<"jsj"<<endl;
                    func2(s,e,t,include,j,num);
                }
                else{
                    Node *trav = temp->eq;
                    bool g = false;
                    if(temp->value==j+1){
                        g = true;
                    }
                    while(trav->eq!=nullptr){
                        //cout<<trav->value<<" jkjk"<<endl;
                        if(trav->value==j+1){
                            g=true;
                            //j=0;
                            break;
                        }
                        trav = trav->eq;
                        
                    }
                    if(g==false){ 
                       //include[i]=true;
                        //cout<<j+1<<"jkek\n";
                        trav->eq = new Node(j+1);
                        //cout<<j+1<<"ukuiq\n";
                        func2(s,e,t,include,j,num);
                    }
                }
                //Node *temp2  = temp;
   
            }  
        }
}

int search(int i,Node *e){
    Node *temp = e;
    int cnt = 0;
    while(temp!=nullptr){
        cnt++;
        if(temp->value==i){
            return cnt;
        }
        Node *temp2 = temp->eq;
        while (temp2!=nullptr)
        {
            if(temp2->value==i){
                return cnt;
            }
            temp2 = temp2->eq;
        }
        
        temp = temp->next;
    }
    
    return -1;
}


int main(){
    int numNodes;
    cin >> numNodes;
    
    ofstream graphfile("outgraph.txt");
    Node *nodes = new Node[numNodes];
    //bool in_collapsed[numNodes];
    //Node *collapsed_nodes=nullptr;
    //cout<<collapsed_nodes;
    int **similar = new int*[numNodes];
    for(int i=0; i<numNodes; i++){
        similar[i]= new int[numNodes];
        //in_collapsed[i] = true;
    }

    for(int i=0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            similar[i][j] = 0;
        }  
    }

    //Node *with_same_incoming = new Node[numNodes];
    
    //bool source[numNodes];
    //similar_nodes S;

    for(int i=0;i<numNodes;i++){
        nodes[i].value = i+1;
        //with_same_incoming[i].value = -1;
        //source[i] = false;
    }
    while(true){
        int n1,n2;
        cin>>n1>>n2;
        if(n1==-1){
            break;
        }
        
        //source[n2-1] = true;
        
        Node *temp = &nodes[n1-1];
        while(temp->outgoing_node!=nullptr){
            temp = temp->outgoing_node;
        }
        temp->outgoing_node = new Node(n2);
        Node *var = &nodes[n2-1];
        while (var->incoming_node!=nullptr){
            var = var->incoming_node;
        }
        var->incoming_node = new Node(n1);
        nodes[n2-1].inc_cnt++;
    }

    while(true){
        int s1,s2;
        cin>>s1>>s2;
        //cout<<s1<<s2<<"\n";
        if(s1==-1){
            break;
        }
        similar[s1-1][s2-1]=1;

    }

    while(true){
        for(int i=0;i<numNodes;i++){
            if(nodes[i].inc_cnt==1){
                Node *temp = nodes[i].incoming_node;
                similar[i][temp->value-1]=1;
            }
        }
        break;
    }

    for(int i=0;i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            if(func(similar,nodes,i,j)==true && func(similar,nodes,j,i)==true){
                similar[i][j]=1;
                similar[j][i]=1;
            }
        }
    }



    bool is_included[numNodes];
    for(int i=0;i<numNodes;i++){
        is_included[i] = false;
    }
    Node *equival = new Node(-1);
    //is_included[0] = true;
    //int c=1;
    for(int i=0;i<numNodes;i++){
        if(is_included[i]==false){
        Node *temp = equival;
        if(temp->value==-1){
            //cout<<"jhsd";
            temp->value = 1;
        }
        else{ 
            while(temp->next!=nullptr){
                temp = temp->next;
            }
        
            temp->next = new Node(i+1);
            temp = temp->next;
        }
        func2(similar,equival,temp,is_included,i,numNodes);}

        
    }

    graphfile<<"Source nodes:";
    for(int i=0;i<numNodes;i++){
        if(nodes[i].inc_cnt==0){
            graphfile<<" "<<i+1;
        }
    }
    graphfile<<"\n\nSimilar node pairs: ";
    
    for(int i=0; i<numNodes; i++){
        for(int j=0; j<numNodes; j++){
            if(similar[i][j]==1){
                graphfile<<"("<<i+1<<", "<<j+1<<") ";
            }
        }
    }

    graphfile<<"\n\nCollapsed graph:\n\n";

    Node * r = equival;
    Node *new_nodes = new Node(-1);
    int cnt =0;
    while(r!=nullptr){
        cnt++;
        Node *x = new_nodes;
        if(new_nodes->value==-1){
            new_nodes->value = r->value;
            x = new_nodes;
        }
        else{
            while(x->next!=nullptr){
                x = x->next;
            }
            x->next = new Node(-1);
            x = x->next;
        }
        if(x->value < r->value){
            x->value = r->value;
        }
        Node *w = r->eq;
        while(w!=nullptr){
            if(w->value>x->value){
                x->value = w->value;
            }
            w = w->eq;
        }
        r = r->next;
    }
    
    graphfile<<cnt<<": ";
    Node *ui = new_nodes;
    while(ui!=nullptr){
        graphfile<<ui->value<<" ";
        ui = ui->next;
    }
    graphfile<<"\n";


    bool printed[numNodes][numNodes];
    for(int i=0; i<numNodes;i++){
        for(int j=0;j<numNodes;j++){
            printed[i][j]=false;
        }
    }
    
    Node * a = nodes;
    for(int i=0;i<numNodes;i++){
        Node * b = &a[i];
        Node *in = a[i].incoming_node;
        int cmp1,cmp2;
        while(in!=nullptr){
            cmp2 = search(b->value,equival);
            int cmp2_cp = cmp2;
            cmp1 = search(in->value,equival);
            int cmp1_cp = cmp1;
            if(cmp1==cmp2){
                in = in->incoming_node;
                continue;
            }
            int max1,max2;
            Node *e = new_nodes;
            while(true){
                cmp1_cp--;
                if(cmp1_cp==0){
                    max1 = e->value;
                    break;
                }
                e = e->next;
            }
            Node *f =new_nodes;
            while(true){
                cmp2_cp--;
                if(cmp2_cp==0){
                    max2 = f->value;
                    break;
                }
                f = f->next;
            }
            if(printed[max1][max2]==false){
                graphfile<<max1<<" "<<max2<<endl;
                printed[max1][max2]=true;
            }
            in = in->incoming_node;
        }
    }
    graphfile.close();
}
    

        // if(S.v1==0){
        //     S.v1 = s1;
        //     //cout<<S.v1<<"dsj\n";
        //     S.v2 = s2;
        // }
        // else{
        //     similar_nodes *temp = &S;
        //     while(temp->next!=nullptr){
        //         temp = temp->next;
        //     }
        //     temp->next = new similar_nodes();
        //     temp->next->v1 =s1;
        //     temp->next->v2 =s2;
        // }
    // Node *shubham = equival;
    // int cnt = 0;

    // while(shubham!=nullptr){
    //     cnt++;
    //     shubham = shubham->next;
    // }
    //     cout<<cnt<<":";
        // Node *te = new Node(-1);
        // Node * k = equival;
        // while(k!=nullptr){
        //     cout<<k->value;
        //     Node *w = te;
        //     if(te->value==-1){
        //         w->value = k->value;
        //     }
        //     else{
        //         while(w->next!=nullptr){
        //             w = w->next;
        //         }
        //         w->next = new Node(-1);
        //         w=w->next;
        //     }
        //     Node *u = k->eq;
        //     while(u!=nullptr){
        //         if(u->value>w->value){
        //             w->value = u->value;
        //         }
        //         cout<<u->value<<" - ";
        //         u = u->eq;
        //     }
        //     cout<<"\n";
        //     k=k->next;
        // }
        // cout<<endl;
        // Node *y = te;
        // while(y!=nullptr){
        //     cout<<y->value<<" ";
        //     y = y->next;
        // }
    //ifstream readfile;
    
    // readfile.open("graphFile.txt");
    // if(readfile.is_open()){
        
    // }
    // similar_nodes *t = &S;
    // //cout<<S.v1;
    // while(t!=nullptr){
    //     cout<<"( "<<t->v1<<","<<t->v2<<" ) ";
    //     t= t->next;
    // }
    // cout<<endl;
            // if(i==j){
            //     continue;
            // }
            // if(similar[i][j]==0){
            //     bool b = false;
            //     Node *temp = nodes[i].incoming_node;
            //     while(temp!=nullptr){
                    
            //         bool found = false;
            //         Node *temp2 = nodes[j].incoming_node;
            //         //cout<<i<<" "<<j<<" "<<temp->value<<" "<<temp2->value<<endl;
            //         while(temp2!=nullptr){

            //                 cout<<i<<" "<<j<<" "<<temp->value<<" "<<temp2->value<<endl;
            //             if(similar[temp->value-1][ temp2->value-1]==1){
            //                 found  = true;
            //                 break;
            //             }
            //             temp2 = temp2->incoming_node;
            //         }
            //         if(found == false){
            //             b = true;
            //             break;
            //         }
            //         temp = temp->incoming_node;
            //     }
            //     if(b==false && nodes[i].incoming_node!=nullptr){
            //         cout<<i<<"jhasjh"<<j<<endl;
            //         similar[i][j] = 1;
            //         similar[j][i] = 1;
            //     }
            // }
                
                // Node *temp1 = nodes[i].outgoing_node;
                // while(temp1!=nullptr){
                //     Node *temp2 = nodes[j].outgoing_node;
                //     while(temp2!=nullptr){
                //         if(func(similar,nodes,temp1->value-1,temp2->value-1)==true && func(similar,nodes,temp1->value-1,temp2->value-1)==true){
                //             similar[temp1->value-1][temp2->value-1]=1;
                //             similar[temp2->value-1][temp1->value-1]=1;
                //         }
                //         temp2 = temp2->outgoing_node;
                //     }
                //     temp1=temp1->outgoing_node;
                // }
    // for(int i=0; i<numNodes; i++){
    //     for(int j=0; j<numNodes; j++){
    //         if(similar[i][j]==1){
    //             cout<<i+1<<" "<<j+1<<" ";
    //         }
    //     }
    // }
    // cout<<endl;
        //similar_nodes *temp = &S;
        // Node * temp2 = &with_same_incoming[1];
        // // while(temp->next!=nullptr){
        // //     temp = temp->next;
        // // }
        // while(temp2!=nullptr){
        //     // temp->next = new similar_nodes();
        //     // temp->next->v1 = temp2->value;
        //     // temp->next->v2 = nodes[temp2->value-1].incoming_node->value;
        //     cout<<temp2->value<<endl;
        //     similar[temp2->value-1][nodes[temp2->value-1].incoming_node->value -1]=1;
        //     //temp = temp->next;
        //     temp2 = temp2->next;
        // }
    // for(int i=0; i<numNodes; i++){
    //     int x = nodes[i].inc_cnt;
    //     if(with_same_incoming[x].value==-1){
    //         with_same_incoming[x].value = i+1;
    //     }
    //     else{
    //         Node *temp = &with_same_incoming[x];
    //         while(temp->next!=nullptr){
    //             temp = temp->next;
    //         }
    //         temp->next = new Node(i+1);
    //     }
    // }

    // for(int i=0;i<numNodes;i++){
    //     Node *temp = &with_same_incoming[i];

    //     cout<<i<<" "<<with_same_incoming[i].value;
    //     while(temp->next!=nullptr){
    //         cout<<" "<<temp->next->value;
    //         temp =temp->next;
    //     }
    //     cout<<"\n";
    // }
        //similar_nodes *q = &S;
    //cout<<S.v1<<q->v1;
    // while(q!=nullptr){
    //     cout<<"( "<<q->v1<<","<<q->v2<<" ) ";
    //     q= q->next;
    // }
    // cout<<"\n";
        // Node *temp = &nodes[s1-1];
        // while(temp->similar_node!=nullptr){
        //     temp = temp->similar_node;
        // }
        // temp->similar_node = new Node(s2+1);
        
        //similar_nodes *t = &S;
    //cout<<S.v1;
    // while(t!=nullptr){
    //     cout<<"( "<<t->v1<<","<<t->v2<<" ) ";
    //     t= t->next;
    // }
    // cout<<"\n";
    
    //cout<<1;
    //cout<<numNodes;
    // for(int i=0;i<999999999;i++){

    // }
    // for(int i=0;i<999999999;i++){
    //     cout<<"jewk";
    // }
//         if(is_included[i]==true){
//             continue;
//         }
//         Node *temp= equival;
//         if(temp->value==-1){
//             temp->value = 1;
//         }
//         else{ 
//         while(temp->next!=nullptr){
//             temp = temp->next;
//         }
//         //if(c!=1){
//             temp->next = new Node(i+1);
//             temp = temp->next;
//         }
//         //}
//         //else{
//           //  c=0;
//         //}
//         for(int j=0;j<numNodes;j++){
//             if(similar[i][j]==1 || similar[j][i]==1){
//                 if(temp->eq==nullptr){
//                     is_included[j]=true;
//                     temp->eq = new Node(j+1);
//                 }
//                 else{
//                     Node *trav = temp->eq;
//                     bool g = false;
//                     while(trav->eq!=nullptr){
//                         cout<<trav->value<<" jkjk"<<endl;
//                         if(trav->value==j+1){
//                             g=true;
//                             //j=0;
//                             break;
//                         }
//                         trav = trav->eq;
                        
//                     }
//                     if(g==false){ 
//                         is_included[j]=true;
                        
//                         trav->eq = new Node(j+1);
//                     }
//                 }
//                 //Node *temp2  = temp;
   
//             }  
//         }
// Node * k = equival;
//         while(k!=nullptr){
//             cout<<k->value<<" ";
//             k=k->next;
//         }
//         cout<<endl;
    // for(int i=0;i<numNodes;i++){
    //     for(int j=numNodes-1;j>i;j--){
    //         if(similar[i][j]==1 || similar[j][i]==1){
    //             in_collapsed[i] = false;
    //         }
    //     }
    // }
    
    // for(int i=0;i<numNodes;i++){
    //     if(in_collapsed[i]==true){
    //         cout<<i+1<<" "<<endl;
    //     }
    // }
    // cout<<endl;
//cout<<collapsed_nodes<<endl;
    // for(int i=0;i<numNodes;i++){
    //             bool f = false;
    //     for(int j=numNodes-1;j>i;j--){
    //         if(f==true){
    //             break;
    //         }
    //         if(similar[i][j]==1 || similar[j][i]==1){
    //             cout<<i+1<< " " <<j+1<<endl;
    //             if(collapsed_nodes==nullptr){
    //                 collapsed_nodes = new Node(j+1);
    //                 break;
    //             }
    //             else{
    
    //                 Node *temp = collapsed_nodes;
    //                 while(temp->next!=nullptr){
    //                     if(temp->value == j+1){
    //                         f = true;
    //                         break;
    //                     }
    //                     if(temp->value == i+1){
    //                         temp->value = j+1;
    //                         f = true;
    //                         break;
    //                     }
    //                     temp = temp->next;
    //                 }
    //                 if(temp->value != j+1){
    //                     f = true;
    //                     temp -> next = new Node(j+1);
    //                 }
                    
    //             }
    //         }
    //     }
    // }
    // Node *temp = collapsed_nodes;
    // while(temp!=nullptr){
    //     cout<<temp->value<<" ";
    //     temp = temp->next;
    // }
        // if(temp->value==-1){
        //     //cout<<"jhsd";
        //     temp->value = 1;
        // }
        // else{ 
        //     while(temp->next!=nullptr){
        //         temp = temp->next;
        //     }
        // //if(c!=1){
        //     cout<<"jkjkjkjkjkjkk\n";
        //     temp->next = new Node(i+1);
        //     temp = temp->next;
        // }
        //}
        //else{
          //  c=0;
        //}