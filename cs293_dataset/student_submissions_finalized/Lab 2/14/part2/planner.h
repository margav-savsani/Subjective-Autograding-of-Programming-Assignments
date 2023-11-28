/*
  Roll no: 210050098
  Name: Moningi Srija
*/

#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>

using namespace std;

struct dtuple //duplicate tuple
{
  float stime;
  float etime;
  char est[32];
};

struct station
{
  char sst[32];
  vector<dtuple> info;
  int status = 0; //status = 0  filled  =1 empty
};

class dictionary
{
  private:
    int N;
    station* s;
  
  public:
    dictionary()
    {
      N = 64;
      s = new station[N];
    }

    int hashValue(char key[])
    {
      int x = 39;
      double result=0;
      int i = 0;
      while(key[i]!='\0')
      {
        result = result*x + int(key[i]);
        result = int(result)%167;
        i++;
      }  
      result = result*0.618;
      result = result - floor(result);
      result = result*N;
      result = floor(result);
      return result;
    }

    int findFreeIndex(char key[])
    {
      int hash = hashValue(key);
      int filled = 0;
      
      for(int i=0; i<N; i++)
      {
        if(s[i].status == 1) filled++;
      }
      if(filled == N) return -1;
      
      int i=0;
      while(s[i].status == 1)
      {
        hash = (hash+1)%N;
      }
      return hash; 
    }

    bool put(struct station e)
    {
      int avbfreeindex = findFreeIndex(e.sst);
      if(avbfreeindex == -1)
      {
        return false;
      }
      else
      {
        s[avbfreeindex]=e;
        s[avbfreeindex].status = 1;
        return true;
      }  
    }

    int found(char stat[])
    {
      for(int i=0; i<N; i++)
      {
        if(strcmp(s[i].sst, stat)==0)
        {
          return i;
        }
      }
      return -1;
    }

    void querystation(float gtime, int index)
    {
      bool found = false;
      for(int i=0;i<(s[index].info).size();i++)
      {
        if((s[index].info)[i].stime >= gtime) //gtime -> given
        {
          cout << (s[index].info)[i].stime << " " << (s[index].info)[i].est << endl;
          found = true;
        }
      }
      if(!found)
      {
       cout <<"ERROR: NO TRAIN" << endl;
      }
    }

    void queryjourney(float gtime, int index, char f[])
    {
      float min1, min2;
      int final1, final2, minin, jmin, i=0;
      bool found1 = false, found2 = false;

      while(i<(s[index].info).size())
      {
        if((s[index].info)[i].stime >= gtime && strcmp((s[index].info)[i].est,f)==0)
        {
          if(!found1)
          {
            min1 = (s[index].info)[i].stime;
            final1 = i;
            found1 = true;
          }
          else
          {
            int x = min(min1, (s[index].info)[i].stime);
            if(x!=min1)
            {
              min1 = x;
              final1 = i;
            }
          }
        }

        else if((s[index].info)[i].stime >= gtime && strcmp((s[index].info)[i].est, f)!=0)
        {
          int intermediate = found((s[index].info)[i].est);
          if(intermediate != -1)
          {
            for(int j=0;j<(s[intermediate].info).size();j++)
            {
              if((s[index].info)[i].etime <= (s[intermediate].info)[j].stime)
              {
                if(strcmp((s[intermediate].info)[j].est,f)==0)
                {
                  if(!found2)
                  {
                    min2 = (s[index].info)[i].stime;
                    final2 = i;
                    minin = intermediate;
                    jmin = j;
                    found2 = true;
                  }
                  else
                  {
                    int x = min(min2, (s[index].info)[i].stime);
                    if(x != min2)
                    {
                      min2 = x;
                      final2 = i;
                      minin = intermediate;
                      jmin = j;
                    }
                  }
                }
              }
            }
          }
        }
        i++;
      }

      if(!found1 && !found2)
      {
        cout << "ERROR: NO SUCH PATH EXISTS" << endl;
      }
      else if(!found1 && found2)
      {
        cout << ((s[index].info)[final2]).stime << " " << ((s[index].info)[final2]).est << " " << (s[minin].info)[jmin].stime << endl;
      }
      else if(found1 && found2)
      {
        if(min1 <= min2)
        {
          cout << min1 << endl;
        }
        else
        {
          cout << (s[index].info)[final2].stime << " " << (s[index].info[final2]).est  << " " <<s[minin].info[jmin].stime << endl;
        }
      }
      else
      {
        cout << min1 << endl;
      }
    }
};

//not using these 

struct Journey {
  // define suitable fields here
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
};

#endif
