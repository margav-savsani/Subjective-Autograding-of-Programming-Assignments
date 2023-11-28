#include<iostream>
#include<string.h>
#include"dictionary.h"
#include<math.h>
using namespace std;
const float M=(sqrt(5)-1)/2;
Dictionary::Dictionary(){
    N=64;
   A=new Entry[64];
   for (int i=0;i<64;i++)
   {
        A[i].filled=0;
   }

}
int Dictionary::hashValue(char* key){
    float k=0,l;
    for (int i=0;i<32;i++ )
    {
        if (key[i]=='\0')
        {
           break;
        }
        
       k=k+(key[i])*(pow(33,i));

    }
   float a= modf((k*M),&l)*64;
   float b=modf(a,&l);
   return a-b;
}
int Dictionary::findFreeIndex(char *key){
    int a=hashValue(key);
    for (int i = a; i <64 ; i++)
    {
        if((A[i].filled)==0)
        return i;
    }
    
}
Entry* Dictionary::get(char keys[]){
    int a=hashValue(keys);
    for (int i = a; i < 64; i++)
    {   bool b=true;
        for(int j=0;i<32;j++)
        {
            if(A[i].key[j]!=keys[j])
            b= false;
        }
       if(b)
       {return &A[i];}
    }
    return NULL;
}

bool Dictionary::put(Entry e){
    int a=findFreeIndex(e.key);
    A[a]=e;
     A[a].filled=1;
    return true;
   
}
bool Dictionary::remove(char key[]){
    Entry* e=get(key);
    if(e==NULL)
    {return false;}
    else {
        
        return true;}
}