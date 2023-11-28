#include <iostream>
#include "dictionary.h"
using namespace std;

int Dictionary::hashValue(char key[])
{
    int i = 0;
    int x = 37;
    int a = 0;
    while(key[i] != '\0'){
        a = a*x + int(key[i]); 
    }
}
