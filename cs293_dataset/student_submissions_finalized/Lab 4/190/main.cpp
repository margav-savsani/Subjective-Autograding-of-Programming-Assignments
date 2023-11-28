#include <iostream>
#include "roughsort.cpp"

using namespace std;

int main(){
    SorterTree s(0, 11);
    
    s.printArray();

    s.Quicksort(-1,11);

    s.printArray();
}