#include "Tree.h"

#ifndef BST_H
#include "BST.cpp"
#endif

#ifndef AVL_H
#include "AVL.cpp"
#endif

#include <iostream>
#include <stdlib.h>
#include <fstream>

int main(int argc, char** argv) {
    AVLTree* treeAVL;
    BST* treeBST;
    std::ofstream statFile;
    int choice = -1;
    std::string cmd;

    if (argc == 1) {
        statFile.open((choice == 0) ? "BST.out" : "AVL.out");
    }
    else {
        std::cout.setstate(ios_base::failbit);
        statFile.open(argv[1]);
    }

    std::cout << "0. BST\n1. AVL\nChoose type of tree : ";
    std::cin >> choice;

    int perComparisonCost, perParentChildUpdateCost;
    
    std::cout << "Enter per comparison cost (non-negative integer): ";
    std::cin >> perComparisonCost;
    std::cout << "Enter per parent-child update cost (non-negative integer): ";
    std::cin >> perParentChildUpdateCost;

    if (perComparisonCost <= 0) {
        std::cout << "Invalid per comparison cost.  Defaulting to 1" << endl;
        perComparisonCost = 1;
    }
    if (perParentChildUpdateCost <= 0) {
        std::cout << "Invalid per parent-child update cost.  Defaulting to 1" << endl;
        perParentChildUpdateCost = 1;
    }
	
    if (choice == 0) {
        treeBST = new BST(perComparisonCost, perParentChildUpdateCost);
    }
    else if (choice == 1) {
        treeAVL = new AVLTree(perComparisonCost, perParentChildUpdateCost);
    }
    else {
        std::cout << "Invalid Choice" << endl;
        return 0;
    }
    

    std::cout << ">>";
    while (std::cin >> cmd) {
        if (cmd == "ADD") {
	        int jCode, price;
            std::cin >> jCode >> price;

            if (((choice == 0) ? treeBST->insert(jCode, price):treeAVL->insert(jCode, price))) {
                std::cout << "SUCCESSFULLY ADDED" << endl;
            }
            else {
                std::cout << "INSERT FAILED" << endl;
            }
            statFile << ((choice == 0)? treeBST->getComparisonCost():treeAVL->getComparisonCost()) << ' ' << ((choice == 0)? treeBST->getParentChildUpdateCost():treeAVL->getParentChildUpdateCost()) << '\n';
        }
        else if (cmd == "DEL") {
            int jCode;
            std::cin >> jCode;

            if ((choice == 0)? treeBST->remove(jCode):treeAVL->remove(jCode)) {
                std::cout << "SUCCESSFULLY DELETED" << endl;
            } else {
                std::cout << "DELETION FAILED" << endl;
            }
            statFile << ((choice == 0)? treeBST->getComparisonCost():treeAVL->getComparisonCost()) << " " << ((choice == 0)? treeBST->getParentChildUpdateCost():treeAVL->getParentChildUpdateCost()) << endl;
        } else if (cmd == "FIND") {
            int jCode;
            std::cin >> jCode;

	    int price = ((choice == 0) ? treeBST->find(jCode):treeAVL->find(jCode));
            if (price >= 0) {
                std::cout << "FOUND" << endl;
            } else {
                std::cout << "NOT FOUND" << endl;
            }
            statFile << ((choice == 0)? treeBST->getComparisonCost():treeAVL->getComparisonCost()) << " " << ((choice == 0)? treeBST->getParentChildUpdateCost():treeAVL->getParentChildUpdateCost()) << endl;
        } else if (cmd == "PRINT") {
	  if (choice == 0) {
	    treeBST->print();
	  }
	  else {
	    treeAVL->print();
	  }
        } else if (cmd == "EXIT") {
            break;
        }
        std::cout << ">>";
    }
    statFile.close();
    if (choice == 0) {
      delete treeBST;
    }
    else {
      delete treeAVL;
    }

    return 0;
}
