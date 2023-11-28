#include<iostream>
#include<string.h>
#include<math.h>
#include"planner.h"

using namespace std;

char key[13];

char* Planner :: makekey(Journey path)
{
    int i;
    i=path.start.id/10;
    key[0]=i;
    i=path.start.id;
    key[1]=i%10;
    i = path.st;
    key[2]=i/1000;
    key[3]=(i/100)%10;
    key[4]=(i/10)%10;
    key[5]=(i)%10;

    i=path.end.id/10;
    key[0]=i;
    i=path.end.id;
    key[1]=i%10;
    i = path.ft;
    key[2]=i/1000;
    key[3]=(i/100)%10;
    key[4]=(i/10)%10;
    key[5]=(i)%10;

    return key;
}

int Planner :: com1(char *key,Journey path)
{
    int id1 = key[0]*10 +key[1];
    int st = key[2]*1000 +key[3]*100 +key[4]*10+key[5];
    int id2 = key[6]*10 +key[7];
    int ft = key[8]*1000 +key[9]*100 +key[10]*10+key[11];

    if(id1 == path.start.id && path.st>=st)
    return id2*pow(10,4)+ft;
    return -1;
}
