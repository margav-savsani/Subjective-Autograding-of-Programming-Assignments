#ifndef GRAPH_CPP
#define GRAPH_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_H
#include "graph.h"
#endif

void Graph::sourceNodes(){
    //function to print all the source nodes
    listOfObjects<int> *srcNodes = nullptr;
    for(int i = 0; i<numNodes; i++)
    {
        if(nodes[i].source)
        {
            if(srcNodes == nullptr) //initialising a new srcnodes list if it is empty
            {
                srcNodes = new listOfObjects<int>(nodes[i].value);
            }
            else        //else adding nodes to the list
            {
                listOfObjects<int> *sn = srcNodes;
                while(sn->next != nullptr)
                {
                    sn = sn->next;
                }
                sn->next = new listOfObjects<int>(nodes[i].value);
            }
        }
    }
    listOfObjects<int> *sn = srcNodes;
    cout<<"Source nodes: ";
    while(sn != nullptr)
    {
        cout<<sn->object<<" ";
        sn = sn->next;
    }
    cout<<endl;
}

void Graph::printSimilar(){
    //function to print similar nodes
    cout<<"Similar node pairs:";
    for(int i=0; i<numNodes; i++)
    {
        for(int j=0; j<numNodes; j++)
        {
            if(similar1[i][j])
            {
                cout<<" ("<<nodes[i].value<<","<<nodes[j].value<<")";
            }
        }
    }
    cout<<endl;
}

void Graph::similarInput(){
    //function to take similar nodes input from the user
    while(true)
    {
        int n1,n2;
        cin>>n1>>n2;

        if(n1 == -1 && n2 == -1)
        {
            break;
        }

        n1 = n1-1;
        n2 = n2-1;

        similar1[n1][n2] = true;
    }
}

void Graph::computeSimilar(){
    //function to compute similar nodes
    for(int i = 0; i<numNodes; i++)     //checking the similarity relation defined by the 3rd criteria(if the node is a single child of the parent node).
    {
        if(nodes[i].parent != nullptr)
        {
            if(nodes[i].parent->next == nullptr)
            {
                similar1[i][nodes[i].parent->object] = true;
            }
        }
    }
    for(int i=0; i<numNodes; i++)       //computing the similarity relation defined by the 2nd criteria with the help of BFS.
    {
        if(nodes[i].source)     //performing BFS over all the source nodes.
        {
            BFS(i);
        }
    }
}

void Graph::BFS(int v){
    //function to compute BFS
    bool visited[numNodes];     //array to store if a node has been visited
    listOfObjects<int> *queue = nullptr;        //queue to add all the edges
    for(int i=0; i<numNodes; i++)
    {
        visited[i] = false;
    }
    visited[v] = true;
    queue = new listOfObjects<int>(v);
    while(queue != nullptr)     //iterating while queue becomes empty
    {
        int s = queue->object;      //popping the first element out
        if(nodes[s].parent != nullptr)      //checking the 2nd criteria
        {
            for(int i=0; i<numNodes; i++)
            {
                if(nodes[i].source)
                {
                    continue;
                }
                if(!similar1[s][i])
                {
                    bool isSimilar1 = true;
                    listOfObjects<int> *p1 = nodes[s].parent;
                    while(p1 != nullptr)        //checking if for every parent element of the given node, there is a similar parent node of a node i. If so relate the current node to i and i to the current node.
                    {
                        listOfObjects<int> *p2 = nodes[i].parent;
                        bool isSimilar3 = false;
                        while(p2 != nullptr)        
                        {
                            if(similar1[p1->object][p2->object])
                            {
                                isSimilar3 = true;
                                break;
                            }
                            p2 = p2->next;
                        }
                        if(!isSimilar3)
                        {
                            isSimilar1 = false;
                            break;
                        }
                        p1 = p1->next;
                    }
                    bool isSimilar2 = true;
                    p1 = nodes[i].parent;
                    while(p1 != nullptr)
                    {
                        listOfObjects<int> *p2 = nodes[s].parent;
                        bool isSimilar3 = false;
                        while(p2 != nullptr)
                        {
                            if(similar1[p1->object][p2->object])
                            {
                                isSimilar3 = true;
                                break;
                            }
                            p2 = p2->next;
                        }
                        if(!isSimilar3)
                        {
                            isSimilar2  = false;
                            break;
                        }
                        p1 = p1->next;
                    }
                    if(isSimilar1 && isSimilar2)
                    {
                        similar1[s][i] = true;
                        similar1[i][s] = true;
                    }
                }
            }
        }
        listOfObjects<int> *a = nodes[s].adj;
        while(a != nullptr)     //adding the non visited adjacent elements in the queue. 
        {
            if(!visited[a->object])
            {
                visited[a->object] = true;
                listOfObjects<int> *q = queue;
                while(q->next != nullptr)
                {
                    q = q->next;
                }
                q->next = new listOfObjects<int>(a->object);
            }
            a = a->next;
        }
        queue = queue->next;
    }
}

void Graph::collapsedNodes(){
    //function to compute and print collapsed nodes
    bool visited[numNodes];     //array to store if a node has been visited or not
    for(int i=0; i<numNodes; i++)
    {
        visited[i] = false;
    }
    for(int i=0; i<numNodes; i++)       //making the similar array symmetric
    {
        for(int j=0; j<numNodes; j++)
        {
            if(similar1[i][j])
            {
                similar1[j][i] = true;
            }
        }
    }
    for(int i=0; i<numNodes; i++)       //computing the collapsed nodes with the help of DFS
    {
        if(!visited[i])
        {
            visited[i] = true;
            collapsedDFS(i,visited);
        }
    }

    cout<<"Collapsed graph:"<<endl<<endl;       //printing the collapsed nodes
    listOfObjects<listOfObjects<int> *> *c = classes;
    int length=0;
    while(c != nullptr)     //computing the number of equivalence classes
    {
        length++;
        c = c->next;
    }
    cout<<length<<": ";
    c = classes;
    while(c != nullptr)     //printing the max nodes
    {
        int node = findMax(c->object);
        cout<<nodes[node].value<<" ";
        c = c->next;
    }
    cout<<endl;
}

void Graph::collapsedDFS(int v, bool *visited){
    //function to compute equivalence classes of the similar relations using DFS
    static listOfObjects<int> *eqClass = nullptr;       
    static int reccLevel = -1;
    if(eqClass == nullptr)      //adding the node to the equivalence class if not already present
    {
        eqClass = new listOfObjects<int>(v);
    }
    else
    {
        listOfObjects<int> *ec = eqClass;
        if(ec->object == v)
        {
            return;
        }
        while(ec->next != nullptr)
        {
            if(ec->next->object == v)
            {
                return;
            }
            ec = ec->next;
        }
        ec->next = new listOfObjects<int>(v);
    }
    reccLevel++;
    for(int i=0; i<numNodes; i++)       //reccursively calling DFS over the nodes which are similar to the current node
    {
        if(similar1[v][i])
        {
            visited[i] = true;
            collapsedDFS(i,visited);
        }
    }
    reccLevel--;
    if(reccLevel == -1)
    {
        if(classes == nullptr)      //adding the equivalence class to set of classes
        {
            classes = new listOfObjects<listOfObjects<int> *>(eqClass);
        }
        else
        {
            listOfObjects<listOfObjects<int> *> *c = classes;
            while(c->next != nullptr)
            {
                c = c->next;
            }
            c->next = new listOfObjects<listOfObjects<int> *>(eqClass);
        }
        eqClass = nullptr;
    }
}

int Graph::findMax(listOfObjects<int> *nums){
    //function to find the max element in a list
    int max = 0;
    listOfObjects<int> *n = nums;
    while(n != nullptr)
    {
        if(max < n->object)
        {
            max = n->object;
        }
        n = n->next;
    }
    return max;
}

void Graph::printCollapsedEdges(){
    //function to print collapsed edges
    listOfObjects<listOfObjects<int> *> *c = classes;
    bool collapsedEdges[numNodes][numNodes];        //creating a matrix to store the collapsed edges information
    for(int i=0; i<numNodes; i++)
    {
        for(int j=0; j<numNodes; j++)
        {
            collapsedEdges[i][j] = false;
        }
    }
    while(c != nullptr)     //iterating over all equivalence classes
    {
        listOfObjects<int> *node = c->object;  
        int collapsedNode = findMax(node);      //finding the collapsed node of the the equivalence class
        while(node != nullptr)      //iterating over all the nodes of an equivalence class
        {
            listOfObjects<int> *a = nodes[node->object].adj;
            while(a != nullptr)     //iterating over all the adjacent nodes
            {
                if(!isPresent(a->object, c->object))        //checking if the edge is within an eqivalence class
                {
                    if(!collapsedEdges[collapsedNode][classOfNode(a->object)])      //adding the collapsed edge if not already present
                    {
                        collapsedEdges[collapsedNode][classOfNode(a->object)] = true;
                    }
                }
                a = a->next;
            }
            node = node->next;
        }
        c = c->next; 
    }
    for(int i = 0; i<numNodes; i++)     //printing the collapsed edges
    {
        for(int j=0; j<numNodes; j++)
        {
            if(collapsedEdges[i][j])
            {
                cout<<nodes[i].value<<" "<<nodes[j].value<<endl;
            }
        }
    } 
}

bool Graph::isPresent(int n, listOfObjects<int> *numbers){
    //function to check if an element is present in the list
    listOfObjects<int> *nums = numbers;
    while(nums != nullptr)
    {
        if(n == nums->object)
        {
            return true;
        }
        nums = nums->next;
    }
    return false;
}

int Graph::classOfNode(int n){
    //function to return the collapsed edge of the equivalence class n is present in
    listOfObjects<listOfObjects<int> *> *c = classes;
    while(c != nullptr)
    {
        if(isPresent(n,c->object))
        {
            return findMax(c->object);
        }
        c = c->next;
    }
}

void Graph::printEqClass(){
    //function to print the equivalence class
    listOfObjects<listOfObjects<int> *> *c = classes;
    while(c != nullptr)
    {
        listOfObjects<int> *nums = c->object;
        while(nums != nullptr)
        {
            nums = nums->next;
        }
        c = c->next;
    }
}

#endif