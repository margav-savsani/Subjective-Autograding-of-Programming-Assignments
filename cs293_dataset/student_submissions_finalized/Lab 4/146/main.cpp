#include<iostream>
#include "sort.cpp"

using namespace std;

int main(){
    int N;
    cin>>N;
    SorterTree T{5,1};
    T.array = new Journey[N];
    for(int i=0; i<N; i++){
        cin>>T.array[i].JourneyCode;
    }
    T.Quicksort(0,N-1);
    for(int i=0; i <N ; i++){
        cout<<T.array[i].JourneyCode<<" ";
    }
    cout<<endl;
    return 0;
}