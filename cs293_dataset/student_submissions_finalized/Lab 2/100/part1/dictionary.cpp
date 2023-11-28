#include"dictionary.h"
#include<math.h>
#include <string.h>

Dictionary::Dictionary()
{
	N=64;
    A=new Entry[N];
    for(int i=0;i<N;i++)A[i].key[0]='\0';
};

int Dictionary::hashValue(char key[])
{
    long long int sum=0;
    int power=0,value;
    double x=37,a=(sqrt(5)-1)/2;
    for (int i=0;(int)key[i]!=0;i++)
    {
        sum+=((int)key[i])*(pow(x,power));
    }
    value=(int)(N*((sum*a)-(int)(sum*a)));
    return value;
};

int Dictionary::findFreeIndex(char key[])
{
    int hvalue=hashValue( key);
    for(int i=0;i<N;i++)
    {
        if(A[(hvalue+i)%N].key[0]!='\0' && A[(hvalue+i)%N].key[0]!=(char)3)continue;
        else return((i+hvalue)%N);
    }
    return -1;
};

Entry* Dictionary::get(char key[])
{
    int hvalue=hashValue(key);
    for(int i=0;i<N;i++)
    {
        if(strcmp(A[(hvalue+i)%N].key,key)==0)return (A+(hvalue+i)%N);
        else if(A[(hvalue+i)%N].key[0]=='\0')return NULL;
    }
    return NULL;
};

bool Dictionary::put(Entry e)
{
    int pos=findFreeIndex(e.key);
    if(pos>=0)
    {
        A[pos]=e;
        return true;
    }
    else return false;
};

bool Dictionary::remove(char key[])
{
    if(get(key)!=NULL){
        get(key)->key[0]=(char)3;
        return true;
    }
    else return false;

};
