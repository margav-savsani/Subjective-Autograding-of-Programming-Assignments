#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    
    SorterTree *s1=new SorterTree(pivot_chooser,num_entries);
    int i=0;
    cout<<"INSERT "<<num_entries<<" VALUES"<<endl;
    while(true){
        char input[32];
        cout << ">>>" ;
        cin>>input;
        //Quit
        if(strcmp(input,"EXIT")==0){
            break;
        }
        //INSERT
        else if(strcmp(input,"ADD")==0){
            int journey;
            cin>>journey;
            int price;
            cin>>price;
            s1->Insertjour(journey,price);
            i++;
            cout<<"SUCCESSFULLY INSERTED!!"<<endl;
            cout<<endl;
        }
        //SORT
        else if(strcmp(input,"SORT")==0){
            if(i==0){
                cout<<"NO ELEMENTS!!"<<endl;
                cout<<endl;
            }
            else{
            cout<<"SUCCESSFULLY SORTED!!"<<endl;
            cout<<endl;
            s1->Quicksort(0,i-1);
            cout<<"This is sorted array:"<<endl;
            cout<<endl;
            s1->printArray();
            cout<<endl;
            cout<<"These are the number of comparisions:"<<endl;
            cout<<s1->comparisons<<endl;
            cout<<endl;
            }
        }
        //SORTBST
         else if(strcmp(input,"SORTBST")==0){
            if(i==0){
                cout<<"NO ELEMENTS"<<endl;
                cout<<endl;
            }
            else{
            cout<<"SUCCESSFULLY SORTED"<<endl;
            cout<<endl;
            s1->QuicksortWithBSTInsert(0,i-1);
            cout<<"This is sorted array:"<<endl;
            cout<<endl;
            s1->printArray();
            cout<<endl;
            cout<<"These are the number of comparisions:"<<endl;
            cout<<endl;
            cout<<s1->comparisons<<endl;
            cout<<endl;
            cout<<"This is the tree of pivots:"<<endl;
            cout<<endl;
            s1->tree->printBST("");
            cout<<endl;
            cout<<"This is the value of Imbalance:"<<endl;
            cout<<endl;
            cout<<s1->tree->getImbalance()<<endl;
            cout<<endl;
            }
        }
        else{
            cout<<"ENTER A VALID COMMAND"<<endl;
            cout<<endl;
        }
    }

}
