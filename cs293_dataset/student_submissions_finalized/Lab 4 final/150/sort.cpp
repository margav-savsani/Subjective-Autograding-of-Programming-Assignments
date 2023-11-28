#include "sort.h"
#include <cmath>
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l)
{
     this->choice = choice;
     this->l = l;
     tree = new BST();
     capacity = 0;
     comparisons = 0;
     array = new Journey[l];
};
bool SorterTree::Quicksort(int start, int finish)
{
     // Call appropriate pivot function based on choice
     // Split into 2 parts based on pivot choice
     // Recursively keep sorting
     if (start == finish)
     {
          return true;
     }
     Journey *pivot;
     if (choice == 1)
     {
          pivot = choose_one(array, start, finish);
     }
     else if (choice == 2)
     {
          pivot = choose_two(array, start, finish);
     }
     else if (choice == 3)
     {
          pivot = choose_three(array, start, finish);
     }
     if (start >= finish)
     {
          return true;
     }
     int min = 0;
     for (int i = 0; i < l; i++)
     {
          if (abs(array[i].getJourneyCode() - pivot->getJourneyCode()) < abs(array[min].getJourneyCode() - pivot->getJourneyCode()))
          {
               min = i;
          }
     }
     pivot = &array[min];
     swap(*pivot, array[finish]);
     pivot = &array[finish];
     int i = start, j = finish;
     while (true)
     {
          while (*pivot < array[j])
          {
               j--;
               comparisons++;
          }
          comparisons++;
          while (array[i] < *pivot)
          {
               i++;
               comparisons++;
          }
          comparisons++;
          if (i < j)
          {
               swap(array[i], array[j]);
               continue;
               comparisons++;
          }
          else
          {
               break;
          }
     }
     if (j == finish)
     {
          Quicksort(start, finish - 1);
     }
     else
     {
          Quicksort(start, j);
          Quicksort(j + 1, finish);
     }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
     // Call appropriate pivot function based on choice
     // Split into 2 parts based on pivot choice
     // Recursively keep sorting
     // Insert chosen pivot into the tree appropriately
     Journey *pivot;
     if (choice == 1)
     {
          pivot = choose_one(array, start, finish);
          tree->insert(pivot->getJourneyCode(), pivot->getPrice());
     }
     else if (choice == 2)
     {
          pivot = choose_two(array, start, finish);
          tree->insert(pivot->getJourneyCode(), pivot->getPrice());
     }
     else if (choice == 3)
     {
          pivot = choose_three(array, start, finish);
          tree->insert(pivot->getJourneyCode(), pivot->getPrice());
     }

     if (start >= finish)
     {
          return true;
     }
     if (pivot == NULL){ return false;}
     int min = 0;
     for (int i = 0; i < l; i++)
     {
          if (abs(array[i].getJourneyCode() - pivot->getJourneyCode()) < abs(array[min].getJourneyCode() - pivot->getJourneyCode()))
          {
               min = i;
          }
     }
     pivot = &array[min]; 
     swap(*pivot, array[finish]);
     pivot = &array[finish];
     int i = start, j = finish;
     while (true)
     {
          while (*pivot < array[j])
          {
               j--;
               comparisons++;
          }
          comparisons++;
          while (array[i] < *pivot)
          {
               i++;
               comparisons++;
          }
          comparisons++;
          if (i < j)
          {
               swap(array[i], array[j]);
               continue;
          }
          else
               break;
     }
     if (j == finish)
     {
          QuicksortWithBSTInsert(start, j - 1);
          QuicksortWithBSTInsert(j, finish);
     }
     else
     {
          QuicksortWithBSTInsert(start, j);
          QuicksortWithBSTInsert(j + 1, finish);
     }
     return true;
}

BST *SorterTree::getTree()
{
     return tree;
};

bool SorterTree::printArray()
{
     for (int i = 0; i < l; i++)
     {
          std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
     }
}

bool SorterTree::insertJourney(int JourneyCode, int price)
{
     array[capacity].setJourneycode(JourneyCode);
     array[capacity].setprice(price);
     capacity++;
     return true;
}