
#define GRAPH_BST_CPP
#include <iostream>

#include <string>
#include <stdlib.h>

#include "Graph.h"

bool Graph::check_c2(int in,int out){


    if(is_checked[in][out]) return is_similar[in][out]; //if this pair is already checked directly returning the bool.
    
    if(issource[in] || issource[out]){
        is_checked[in][out]=true;
        is_similar[in][out]=false;
        return false;
    }
    
    listofnodes*m1=nodes[in].from,*m2=nodes[out].from;
    while(m1!=nullptr){ //checking for second condition

        bool found = false;
        m2=nodes[out].from;
        while(m2!=nullptr){

            
            if(check_c2(m1->index-1,m2->index-1) ){
                found=true;
                
                break;
            }
            else m2=m2->next;
        }

        if(!found){
            is_similar[in][out]=false;
            is_checked[in][out]=true;
            return false;

        }
        m1=m1->next;
    }
    m2=nodes[out].from;
    m1=nodes[in].from;
    while(m2!=nullptr){

        bool found = false;
        m1=nodes[in].from;
        while(m1!=nullptr){

            
            if(check_c2(m2->index-1,m1->index-1) ){
                found=true;
                
                break;
            }
            else m1=m1->next;
        }

        if(!found){
            is_similar[in][out]=false;
            is_checked[in][out]=true;
            return false;

        }
        m2=m2->next;
    }
    
        is_similar[in][out]=true;
        is_checked[in][out]=true;
        is_similar[out][in]=true;
        is_checked[out][in]=true;
        return true;
  

}


