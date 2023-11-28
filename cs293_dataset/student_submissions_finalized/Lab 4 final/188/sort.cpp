#include "sort.h"
#include <iostream>
// unsigned int counts = 0;
//  Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    this->comparisons = 0;
    this->array = new Journey[l];
    this->tree = new BST();
    for (int i = 0; i < l; i++)
    {
        cout << "Journey: ";
        int c, p;
        cin >> c >> p;
        Journey j = Journey(c, p);
        array[i] = j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int i = start;
    int j = finish;
    Journey temp;
    Journey *q;
    if (choice == 1)
    {
        q = choose_one(array, start, finish);
    }
    else if (choice == 2)
    {
        q = choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        q = choose_three(array, start, finish);
    }
    if (q == nullptr)
        return false;

    temp = array[finish];
    array[finish] = *q;
    *q = temp;
    // //cout<<i<<" "<<j<<endl;
    Journey x = array[finish];
    //cout << x.getJourneyCode() << endl;
    while (true)
    {
        //cout << "while loop started" << endl;
        while (x < array[j])
        {
            //cout << "Searching smaller" << endl;
            //printArray();
            j = j - 1;
            comparisons++;
        }
        while (array[i] < x)
        {
            //cout << "Searching larger" << endl;
            //printArray();
            // //cout<<i<<" ";
            i = i + 1;
            comparisons++;
            //cout << i << endl;
        }
        if (i < j)
        {
            //cout << "if" << endl;
            // //cout<<i<<" "<<j<<endl;
            Journey temp2 = array[i];
            array[i] = array[j];
            array[j] = temp2;
        }
        else
        {
            //cout << "else" << endl;
            break;
        }
    }

    //cout << "while loop borken" << endl;
    // QuickSort Code
    int partition = j;
    //cout << "partition" << endl;
    //cout << partition << endl;
    if (!(partition >= start && partition <= finish))
    {
        return false;
    }
    if (start >= finish)
    {
        //cout << "hit" << endl;
        return true;
    }
    else
    {
        if(partition == finish) { 
            //cout << start << " " << partition << endl;
            Quicksort(start, partition - 1);
            //cout << "q1" << endl;
            Quicksort(partition, finish);
            //cout << "q2" << endl;
        }
        else{
            //cout << start << " " << partition << endl;
            Quicksort(start, partition);
            //cout << "q1" << endl;
            Quicksort(partition + 1, finish);
            //cout << "q2" << endl;
        }
    }
    // //cout<<"No. of Counts "<<comparisons<<endl;

    return true;
}
bool SorterTree::insertPivot(int JourneyCode, int price)
{
    //Journey j(JourneyCode,price);
    //cout<<tree<<endl;
    tree->insert(JourneyCode, price);
    //cout<<"pivot inserted"<<endl;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    int i = start;
    int j = finish;
    Journey temp;
    Journey *q;
    if (choice == 1)
    {
        q = choose_one(array, start, finish);
    }
    else if (choice == 2)
    {
        q = choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        q = choose_three(array, start, finish);
    }
    if (q == nullptr) return false;
    //cout<<q<<endl;
    //cout<<"Shasmith"<<endl;
    int c = q->getJourneyCode();
    int p = q->getPrice();
    insertPivot(c, p);

    temp = array[finish];
    array[finish] = *q;
    *q = temp;
    //cout<<i<<" "<<j<<endl;
    Journey x = array[finish];
    //cout << x.getJourneyCode() << endl;
    while (true)
    {
        //cout << "while loop started" << endl;
        while (x < array[j])
        {
            //cout << "Searching smaller" << endl;
            //printArray();
            j = j - 1;
            comparisons++;
        }
        while (array[i] <= x)
        {
            //cout << "Searching larger" << endl;
            //printArray();
            // //cout<<i<<" ";
            i = i + 1;
            comparisons++;
            //cout << i << endl;
        }
        if (i < j)
        {
            //cout << "if" << endl;
            // //cout<<i<<" "<<j<<endl;
            Journey temp2 = array[i];
            array[i] = array[j];
            array[j] = temp2;
        }
        else
        {
            //cout << "else" << endl;
            break;
        }
    }

    //cout << "while loop borken" << endl;
    // QuickSort Code
    int partition = j;
    //cout << "partition" << endl;
    //cout << partition << endl;
    if (!(partition >= start && partition <= finish))
    {
        return false;
    }
    if (start >= finish)
    {
        //cout << "hit" << endl;
        return true;
    }
    else
    {
        if(partition == finish) { 
            //cout << start << " " << partition << endl;
            QuicksortWithBSTInsert(start, partition - 1);
            //cout << "q1" << endl;
            QuicksortWithBSTInsert(partition, finish);
            //cout << "q2" << endl;
        }
        else{
            //cout << start << " " << partition << endl;
            QuicksortWithBSTInsert(start, partition);
            //cout << "q1" << endl;
            QuicksortWithBSTInsert(partition + 1, finish);
            //cout << "q2" << endl;
        }
    }
    // //cout<<"No. of Counts "<<comparisons<<endl;

    return true;
}
BST *SorterTree::getTree()
{
    return tree;
}

bool SorterTree::printArray()
{
    cout<<"Number of Comparisons: "<<comparisons<<endl;
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}
