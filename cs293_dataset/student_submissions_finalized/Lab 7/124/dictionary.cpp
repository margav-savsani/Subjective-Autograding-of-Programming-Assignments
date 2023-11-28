#include<iostream>
using namespace std;

 int Dictionary:: hashValue(char key[]){
const int p=89;
int m=41;
int hash_value;
long int hash_so_far=0;
long p_pow=1;
const int n=key.length();
for(int i=0;i<n;i++){
hash_so_far=(hash_so_far +(key[i]-'a'+97)*p_pow)%m;
p_pow=(p_pow*p)%m;
int hash_string(string s, int m) {
      int a=0; 
   for(int i=0;i<s.length();i++){
   a=a+(s[i]);
  }
  int b=a%m;
  return b;

}
hash_value=hash_so_far;
return hash_value;
}
 }
int Dictionary:: findFreeIndex(char key[]){

}