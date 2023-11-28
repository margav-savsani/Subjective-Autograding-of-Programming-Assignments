#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include<chrono>

using namespace std;
// int getNum(vector<int>& v)
// {
 
//     // Size of the vector
//     int n = v.size();
 
//     // Generate a random number
//     srand(time(NULL));
 
//     // Make sure the number is within
//     // the index range
//     int index = rand() % n;
 
//     // Get random number from the vector
//     int num = v[index];
 
//     // Remove the number from the vector
//     swap(v[index], v[n - 1]);
//     v.pop_back();
 
//     // Return the removed number
//     return num;
// }
int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    //New Code
    // int choice;
    // cout<<"enter 1 for automatic, 0 for manual:";cin>>choice;
    SorterTree st(pivot_chooser,num_entries);
    // if(!choice){
    for(int i=0;i<num_entries;i++){
        // cout<<"Enter entry number "<<i<<" :";
        unsigned int jcode,price;cin>>jcode>>price;
        Journey jrny(jcode,price);
        st.insertElement(jrny);
        // cout<<"Here1"<<endl;
    }
    // }
    // else{
    //     vector<int> v(num_entries);
    //     for (int i = 0; i < num_entries; i++){v[i] = i + 1;}
    //     while(v.size()){
    //         unsigned int jcode,price;
    //         jcode=getNum(v);price=rand();
    //         Journey jrny(jcode,price);
    //         st.insertElement(jrny);
    //     }
        
    //     // for(int i=0;i<num_entries;i++){
    //     // unsigned int jcode,price;
    //     // jcode=rand()%10000000;price=rand()%10000000;
    //     // Journey jrny(jcode,price);
    //     // st.insertElement(jrny);}
    // }
    auto start=chrono::system_clock::now();
    st.Quicksort(0,num_entries-1);
    st.printArray();
    // cout<<"Here3"<<endl;
    // st.QuicksortWithBSTInsert(0,num_entries-1);
    // // st.printArray();
    // cout<<"Imbalance: "<<st.getTree()->getImbalance()<<endl;
    cout<<"Cost of comparisions is: "<<st.getComparisions()<<endl;
    auto end=chrono::system_clock::now();
    // st.getTree()->printBST("");
    cout<< "Time Elapsed "<< chrono::duration_cast<chrono::nanoseconds>(end-start).count()<<" nanoseconds"<<endl;
}
