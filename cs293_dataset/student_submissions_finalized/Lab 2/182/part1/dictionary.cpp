#include"dictionary.h"
#include<cmath>

Dictionary ::Dictionary(){
  N=64;
  A = new Entry[N];
}
int Dictionary ::hashValue(char key[]){
  int size=0;
  int q=37;
  while(true){
        if(key[size]=='\0')
        break;
        size++;
    }
  int value=0;
  for(int i=0;i<size;i++){
    value = (value + key[i])%q;
  }
  return value;
}
int Dictionary ::findFreeIndex(char key[]){
  double fibonacci=(pow(5,0.5)-1)/2;
  double hashvalue=hashValue(key);
  int index;
  index=int(N*(hashvalue*fibonacci)-int(N*(hashvalue*fibonacci)));
  int free=index;
  for(int j=index;j<index+64;j++){
    if(strcmp(A[j].key,"\0")==0) return free;
    else free=(free+1)%N;
  }
  return -1;
}
struct Entry* Dictionary :: get(char key[]){
  for(int i=0;i<N;i++){
    if(strcmp(A[i].key,key)==0) return &(A[i]);
  }
  return NULL;
}

bool Dictionary :: put(struct Entry e){
  int index = findFreeIndex(e.key);
  if(index==(-1)) return false ;
  else{
    A[index] = e;
    return true;
  }

}
bool Dictionary ::remove(char key[]){
  Entry* ptr =get(key);
  if(ptr == NULL) return false;
  else{
    strcpy(ptr->key,"DELETED");
    ptr-> value = -1;
    return true;
  }
}