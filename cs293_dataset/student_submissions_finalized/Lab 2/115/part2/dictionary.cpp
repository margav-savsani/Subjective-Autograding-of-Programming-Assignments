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
    return floor(DICT_SIZE*(polynomial_value*golden_ratio-floor(polynomial_value*golden_ratio)));
}
int Dictionary::findFreeIndex(char key[])
{
    int Hashval= hashValue(key);
    for(int i=Hashval;i<Hashval+DICT_SIZE;i++)
    {
        if(Filled_or_not[i%DICT_SIZE]=='\0')
        {
            return i%DICT_SIZE;
        }
    }
    return -1;
}
struct Entry *Dictionary::get(char key[])
{
    int Hashval = hashValue(key);
    bool Same;
    int m=0;
    for(m=0;m<32;m++)
    {
        if(key[m]=='\0')
        {
            break;
        }
    }
    for(int i=Hashval;i<Hashval+DICT_SIZE;i++)
    {
        if(Filled_or_not[i%DICT_SIZE]!='f')
        {
            continue;
        }
        Same=true;
        int z=0;
        for(z=0;z<32;z++)
        {
            if((A[i%DICT_SIZE].key)[z]=='\0')
            {
                break;
            }
        }
        if(m!=z)
        {
            continue;
        }
        for(int j=0;j<m;j++)
        {
            if(key[j]!=(A[i%DICT_SIZE].key)[j])
            {
                Same=false;
                break;
            }
        }
        if(Same)
        {
            return (&A[i%DICT_SIZE]);
        }
    }
    return NULL;
}
bool Dictionary::put(struct Entry e)
{
    int Hashval = hashValue(e.key);
    for(int i=Hashval;i<Hashval+DICT_SIZE;i++)
    {
        if(Filled_or_not[i%DICT_SIZE]=='f')
        {
            continue;
        }
        else
        {
            A[i%DICT_SIZE]=e;
            Filled_or_not[i%DICT_SIZE]='f';
            return true;
        }
    }
    return false;
}
bool Dictionary::remove(char key[])
{
    int Hashval = hashValue(key);
    bool Same;
    int m=0;
    for(m=0;m<32;m++)
    {
        if(key[m]=='\0')
        {
            break;
        }
    }
    for(int i=Hashval;i<Hashval+DICT_SIZE;i++)
    {
        if(Filled_or_not[i%DICT_SIZE]!='f')
        {
            continue;
        }
        Same=true;
        int z=0;
        for(z=0;z<32;z++)
        {
            if((A[i%DICT_SIZE].key)[z]=='\0')
            {
                break;
            }
        }
        if(m!=z)
        {
            continue;
        }
        for(int j=0;j<m;j++)
        {
            if(key[j]!=(A[i%DICT_SIZE].key)[j])
            {
                Same=false;
                break;
            }
        }
        if(Same)
        {
            Filled_or_not[i%DICT_SIZE]='x';
            return true;
        }
    }
    return false;
}