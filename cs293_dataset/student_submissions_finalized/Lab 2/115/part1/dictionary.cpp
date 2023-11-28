#include<cmath>
double golden_ratio = (sqrt(5)-1)/2;
int Dictionary::hashValue(char key[])
{
    double polynomial_value=0;
    double factor=1;
    for(int i=0;i<32;i++)
    {
        if(key[i]=='\0')
        {
            break;
        }
        polynomial_value += factor*((key[i]+1)-1);
        factor = factor * 33;//because 33 is good value to decrease collisons 
    }//hash code is completed
    return floor(64*(polynomial_value*golden_ratio-floor(polynomial_value*golden_ratio)));
}
int Dictionary::findFreeIndex(char key[])
{
    int Hashval= hashValue(key);
    for(int i=Hashval;i<Hashval+64;i++)
    {
        if(Filled_or_not[i%64]=='\0')
        {
            return i%64;
        }
    }
    return -1;
}
struct Entry *Dictionary::get(char key[])
{
    int Hashval = hashValue(key);
    bool Same;
    for(int i=Hashval;i<Hashval+64;i++)
    {
        Same=true;
        if(Filled_or_not[i%64]=='f')
        {
            for(int j=0;j<31;j++)
            {
                if(key[j]!=(A[i%64].key)[j])
                {
                    Same=false;
                    break;
                }
            }
            if(Same)
            {
                return (&A[i%64]);
            }
        }
    }
    return NULL;
}
bool Dictionary::put(struct Entry e)
{
    int Hashval = hashValue(&e.key[0]);
    for(int i=Hashval;i<Hashval+64;i++)
    {
        if(Filled_or_not[i%64]=='f'||Filled_or_not[i%64]=='x')
        {
            continue;
        }
        if(Filled_or_not[i%64]=='\0')
        {
            A[i%64]=e;
            Filled_or_not[i%64]='f';
            return true;
        }
    }
    return false;
}
bool Dictionary::remove(char key[])
{
    int Hashval = hashValue(key);
    bool Same;
    for(int i=Hashval;i<Hashval+64;i++)
    {
        Same=true;
        if(Filled_or_not[i%64]=='f')
        {
            for(int j=0;j<32;j++)
            {
                if(key[j]!=(A[i%64].key)[j])
                {
                    break;
                    Same=false;
                }
            }
            if(Same)
            {
                Filled_or_not[i%64]='x';
                return true;
            }
        }
    }
    return false;
}