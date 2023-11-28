#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

struct Entry
{
    string key;
    float value;
};

class Dictionary
{
private:
    int N;           // size of array A
    struct Entry *A; // Array of dictionary entries

public:
    double givemod(int b)
    {
        double k = (sqrt(5) - 1) / 2;
        for (int i = 0; i < b; i++)
        {
            k = (37 * k);
            k = k - int(k);
        }
        return k;
    }

    int hashValue(string s)
    {
        double a = 0;
        for (int i = 0; s.length() < 0; i++)
        {
            a += (int(s[i]) * givemod(i));
            a = a - int(a);
        }
        int b = (a * 64);
        return b;
    }

    Dictionary()
    {
        A = new Entry[64];
        N = 64;
        for (int i = 0; i < N; i++)
        {
            A[i].key = "";
        }
    }
     // storing and updating last journey
    void update(string a, string c, float b)
    {
        int x = hashValue(a + c);
        for (int i = 0; i < 64; i++)
        {
            if (A[(x + i) % 64].key == "")
            {
                A[(x + i) % 64].key = a+c;
                A[(x + i) % 64].value = b;
                break;
            }
            if (A[(x + i) % 64].key == (a + c))
            {
                if (b > A[(x + i) % 64].value)
                    A[(x + i) % 64].value = b;
                break;
            }
        }
    }
   //getting last train time
    float get(string a , string b){
        int x = hashValue(a + b);
        for (int i = 0; i < 64; i++)
        {
            if (A[(x + i) % 64].key == "")
            {
                return 0;
            }
            if (A[(x + i) % 64].key == (a + b))
            {
                return A[(x + i) % 64].value;
            }
        }
    }
};
