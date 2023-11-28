#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <typename T> class listNode{
    public:
    T  object;
    listNode *next;
    listNode(){
        object=nullptr;
        next=nullptr;
    }
    listNode(T ob){
        object=ob;
        next=nullptr;
    }
};

class node{
    public: 
    int name;
    int visited;
    int level;
    int group;
    listNode<node *> *inNeighbours;
    listNode<node *> *outNeighbours;
    listNode<node *> *similar;
    listNode<node *> *closure;

    node(){
        name =-1;
        visited=0;
        level=0;
        group=0;
        inNeighbours=nullptr;
        outNeighbours=nullptr;
        similar=nullptr;
        closure = nullptr;
    }
    bool insertInNeigh(node *x){
        listNode<node *> *curr=inNeighbours;
        if(curr==nullptr){
            inNeighbours=new listNode<node *>(x);
            return true;
        }
        else{
            if(curr->object->name == x->name){
                return false;
            }
            while(curr->next!=nullptr){
                if(curr->object->name == x->name){
                    return false;
                }
                curr=curr->next;
            }
            curr->next=new listNode<node *>(x);
            return true;
        }
    }

    bool insertOutNeigh(node *x){
        listNode<node *> *curr=outNeighbours;
        if(curr==nullptr){
            outNeighbours=new listNode<node *>(x);
            return true;
        }
        else{
            if(curr->object->name == x->name){
                return false;
            }
            while(curr->next!=nullptr){
                if(curr->object->name == x->name){
                    return false;
                }
                curr=curr->next;
            }
            curr->next=new listNode<node *>(x);
            return true;
        }
    }

    bool insertSimilar(node *x){
        listNode<node *> *curr=similar;
        if(curr==nullptr){
            similar=new listNode<node *>(x);
        }
        else{
            if(curr->object->name == x->name){
                return false;
            }
            while(curr->next!=nullptr){
                if(curr->object->name == x->name){
                    return false;
                }
                curr=curr->next;
            }
            curr->next=new listNode<node *>(x);
        }
    }
    bool insertClosure(node *x){
        listNode<node *> *curr=closure;
        if(curr==nullptr){
            closure=new listNode<node *>(x);
        }
        else{
            if(curr->object->name == x->name){
                return false;
            }
            while(curr->next!=nullptr){
                if(curr->object->name == x->name){
                    return false;
                }
                curr=curr->next;
            }
            curr->next=new listNode<node *>(x);
        }
    }

    bool findIn(int x){
        listNode<node *> *curr = inNeighbours;
        while(curr!=nullptr){
            if(curr->object->name == x){
                return true;
            }
            curr=curr->next;
        }
        return false;
    }

    bool findOut(int x){
        listNode<node *> *curr = outNeighbours;
        while(curr!=nullptr){
            if(curr->object->name == x){
                return true;
            }
            curr=curr->next;
        }
        return false;
    }

    bool findSim(int x){
        listNode<node *> *curr = similar;
        while(curr!=nullptr){
            if(curr->object->name == x){
                return true;
            }
            curr=curr->next;
        }
        return false;
    }

    bool findClosure(int x){
        listNode<node *> *curr = closure;
        while(curr!=nullptr){
            if(curr->object->name == x){
                return true;
            }
            curr=curr->next;
        }
        return false;
    }
};
#endif 