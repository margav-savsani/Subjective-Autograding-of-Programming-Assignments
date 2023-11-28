#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <vector>
#include <stack>
#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void BST::printBST(const string& prefix, bool isLeft){
    if( root != nullptr ){
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        IntNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

bool BST::insert(int value){
    IntNode* node = new IntNode(value);
    if (root == nullptr){
        root =node;
        root->parent = nullptr;
        return true;
    }
    IntNode* n = root;
    bool i = 0;
    while (i == 0){
        if(n->value<node->value){
            if (n->right== nullptr){
                n->right = node;
                node->parent = n;
                i=1;
            }
            else n = n->right;
        }
        else{
            if (n->left == nullptr){
                n->left = node;
                node->parent = n;
                i=1;
            }
            else n = n->left;
        }
    }
    return i;
}

bool Graph::modifiedDFS1(int n,BST& bst_tree, int prev_node) {
    // cout<<n<<endl;
    bst_tree.insert(n);
    if(!visited[n-1][0]){
        visited[n-1][0]= true;
    }
    else if(!visited[n-1][1]){
        listOfObjects<dir_node*>* d=nodes[prev_node-1].adj;
        while(d!=nullptr){
            if(d->object->value==n){
                if(d->object->direction)visited[n-1][1]=true;
            }
            d=d->next;
        }
    }
 
    // Recur for all the vertices adjacent to this vertex
    listOfObjects<dir_node*>* a =nodes[n-1].adj;

    int found=0,return_value=false;
    while(a!=nullptr){
        if(!visited[a->object->value-1][0] || !visited[a->object->value-1][1] && a->object->direction){
            found=1;
            a->object->direction=true;
            listOfObjects<dir_node*>* c=nodes[a->object->value-1].adj;
            while(c!=nullptr){
                if(c->object->value==n)c->object->direction=false;
                c=c->next;
            }
            if(modifiedDFS1(a->object->value, bst_tree, nodes[n-1].value))return_value=true;
        }
        a=a->next;
    }
    if(found==0 || return_value==false){
        a=nodes[n-1].adj;
        while(a!=nullptr){
            if(a->object->value==prev_node) a->object->direction=true;
            a=a->next;
        }
        listOfObjects<dir_node*>* b=nodes[prev_node-1].adj;
        while(b!=nullptr){
            if(b->object->value==n) b->object->direction=false;
            b=b->next;
        }
        return false;
    }
    return true;
}

void Graph::modifiedDFS() {
    for(int i=0; i<numNodes;i++){
        if(!visited[i][0]){
            start_vertex=i;
            BST a;
            modifiedDFS1(start_vertex+1, a, -1);
            if(connected_components==0)bst_trees=new listOfObjects<BST>(a);
            else{
                listOfObjects<BST>* b=bst_trees;
                while(b->next!=nullptr){
                    b=b->next;
                }
                b->next=new listOfObjects<BST>(a);
            }
            connected_components++;
        }
    }
    return;
}

void Graph::printResults() {
    for (int i=0; i<numNodes; i++){
        if(visited[i][0] && visited[i][1]){
            visited_twice++;
            cout<<"visited twice:"<<i+1<<endl;
        }
        else if(visited[i][0] && !visited[i][1]){
            visited_once++;
            cout<<"visited once:"<<i+1<<endl;
        }
    }
    cout<<"No. of connected components:"<<connected_components<<endl;
    cout<<"No. of nodes visited once:"<<visited_once<<endl;
    cout<<"No. of nodes visited twice:"<<visited_twice<<endl;
    cout<<"No. of nodes in a cycle:"<<visited_twice<<endl;
    while(bst_trees!=nullptr){
        bst_trees->object.printBST("",false);
        bst_trees=bst_trees->next;
    }
}

#endif
