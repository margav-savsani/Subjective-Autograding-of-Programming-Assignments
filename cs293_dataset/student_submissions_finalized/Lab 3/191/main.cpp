#include<iostream>
using namespace std;
#include "BST.cpp"

int main(){
	BST a;
	a.insert(1,120);
	a.insert(2,240);
	a.insert(3,40);
	a.traverse(2);
	cout<<a.getMinimum()<<endl;
}
