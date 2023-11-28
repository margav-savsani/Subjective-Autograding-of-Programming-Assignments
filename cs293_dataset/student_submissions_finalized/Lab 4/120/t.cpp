#include <iostream>
using namespace std;

int main(){
    int a;
    int c=2;
    int *b=&c;
    a=3;
    if(a>*b){
        cout<<1<<endl;
    }
}