#include<iostream>
#include"dictionary.h"

void strcpy(char a[32], char b[32]){
	for(int i=0; b[i]!=NULL; i++)
	a[i]=b[i];
}

int strcmp(char a[32], char b[]){
	if(a=="QUIT" && b=="QUIT") return 0;
	if(a=="INS" && b=="INS") return 0;
	if(a=="DEL" && b=="DEL") return 0;
	if(a=="FIND" && b=="FIND") return 0;
}
