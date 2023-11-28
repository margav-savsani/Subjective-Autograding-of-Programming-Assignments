#include<iostream>
#include<string.h>
#include<cmath>
#include<vector>
// Can change this value for debugging
const int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
  string key;
  float start;
  string end;
  float finish;
  Entry(){}
  Entry(string s1,float t1,string s2,float t2){
    key=s1;
    end=s2;
    start=t1;
    finish=t2;
  }
};

class Dictionary {

 private:

  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Default constructor
  Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
    for(int i=0;i<N;i++){
      A[i].key="NULL"; //represents that the entry is empty(but not after deletion, TOMBSTONE is used to denote an entry which becomes empty after deletion of a key)
      A[i].start=0;
    }
  }

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key){
    //Polynomial accumulation scheme is used to convert strings to integers
    int n=key.length();
    const int m=23,x=31;
    int s=key[n-1];
    for(int i=n-2;i>=0;i--){
      s=key[i]+s*x;
    }
    //Now, the fibonacci hashing scheme is used on the above obtained integers to get the hash value.
    const double a=(sqrt(5)-1)/2;
    return floor(N*(s*a-floor(s*a)));
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key){

    //checks if the array is full
    bool isFull=true;
    for(int i=0;i<N;i++){
      if(A[i].key=="NULL" || A[i].key=="TOMBSTONE") isFull=false;     //checks if the entry is empty
    }
    if(isFull) return -1;

    //searches for free index if array is not full using the linear probing scheme
    int i=hashValue(key);
    while(A[i].key!="NULL" && A[i].key!="TOMBSTONE"){     //terminates when we find an empty entry
      i=(i+1)%N;
    }
    return i;
  }
  

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e){
    int index=findFreeIndex(e.key);
    if(index==-1) return false; //checks whether the array is full
    else{
      A[index]=e;
      return true;
    }
  }

  void add(string s1,float t1,string s2,float t2){
    put(Entry(s1,t1,s2,t2));
  }
  void station(string s,float t){
    vector<pair <float,int> > v;
    for(int i=0;i<N;i++){
        if(A[i].key==s && A[i].start>=t) v.push_back(make_pair(A[i].start,i));
    }
    sort(v.begin(), v.end());
    for(int i=0;i<v.size();i++){
        cout<<A[v[i].second].start<<" "<<A[v[i].second].end<<endl;
    }
    if(v.size()==0) cout<<"ERROR"<<endl;
  }
  struct Entry* directpath(string s1,float t,string s2){
    float x=2400;
    int y;
    for(int i=0;i<N;i++){
      if(A[i].key==s1 && A[i].end==s2&& A[i].start>=t){
        if(A[i].start<x){
            x=A[i].start;
            y=i;
        }
      }
    }
    if(x==2400) return NULL;
    else return &A[y];
  }
  struct Entry* stoppath(string s1,float t,string s2){
    float x=2400;
    int y;
    for(int i=0;i<N;i++){
      if(A[i].key==s1 && A[i].end!=s2 && A[i].start>=t){
        if(directpath(A[i].end,A[i].finish,s2)!=NULL){
          if(A[i].start<x){
            x=A[i].start;
            y=i;
          }
        }
      }
    }
    if(x==2400) return NULL;
    else return &A[y];
  }
  void journey(string s1,float t,string s2){
    if(stoppath(s1,t,s2)==NULL){
      if(directpath(s1,t,s2)==NULL) cout<<"ERROR"<<endl;
      else cout<<directpath(s1,t,s2)->start<<endl;
    }
    else{
      string inter;
      inter=stoppath(s1,t,s2)->end;
      if(directpath(s1,t,s2)==NULL) cout<<stoppath(s1,t,s2)->start<<" "<<inter<<" "<<directpath(inter,directpath(s1,t,inter)->finish,s2)->start<<endl;
      else{
        if(directpath(s1,t,s2)->start <= stoppath(s1,t,s2)->start) cout<<directpath(s1,t,s2)->start<<endl;
        else cout<<stoppath(s1,t,s2)->start<<" "<<inter<<" "<<directpath(inter,directpath(s1,t,inter)->finish,s2)->start<<endl;
      }
    }
    
  }
};

