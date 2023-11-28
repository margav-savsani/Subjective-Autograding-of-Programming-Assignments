#ifndef PLANNER_H
#define PLANNER_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <iostream>
#include <cmath>
using namespace std;
struct Journey 
{
  string start;     //store the starting station name
  string end;       //store the destination station name
  float st;         //start time
  float et;         //end time
  bool filled;      //to check the entry is filled or not
  Journey()
  {
    filled=false;
  }
};
int minval(int arr[],int num)   //to find index of min value
{
  int k=0;
  for(int i=0;i<num;i++)
  {
    if (arr[k]>=arr[i])
      k=i;
  }
  return k;
}
class Planner 
{
  int N;            //max size
  Journey *data;    //storing the data
  public:
  Planner()
  {
    data=new Journey[64];
    N=64;
  }
  int hashValue(string key)
  {
    int p=33;             //value of x in polynomial
    double m=64;          //max size of list
    double a=(sqrt(5)-1)/2;     //fibanoci constant
    int i=0,hash;               //to check 1 loop is completed or not and hash value
    double k=(key[key.length()-1]*a);        //we need only fractional part of a*f(p)
    for(int j=key.length()-2;j>=0;j--)     //evaluating fractional part of a*f(p)
    {
        k=key[j]*a+p*k;
        int lowval=k;
        k=k-lowval;
    }
    hash=m*k;                   //hash value
    return hash;
  }
  int FindFreeIndex(string key)
  {
    int k1=hashValue(key);       //starting with hash value
    //to check a loop
    for(int i=0;i<N;i++)                 //we should add value if it not filled
    {
        if(data[k1].filled==false)
            return k1;
        else 
            k1=(k1+1)%N;
    }
    return -1;        //if fill return -1
  }
  bool addtrain(string s,float t1,string e,float t2)
  {
    int k2=FindFreeIndex(s);
    if (k2==-1)
      return false;
    else            //add at free index
    {
      data[k2].start=s;
      data[k2].end=e;
      data[k2].st=t1;
      data[k2].et=t2;
      data[k2].filled=true;
      return true;
    }
  }
  bool QueryStation(string s,float t)
  {
    int k3=hashValue(s);  //calculate the hash value and check from there 
    int check=0;          //to check some are added or not 
    for(int i=0;i<N;i++)
    {
      if (data[k3].filled)
      {                 //printing the required stations
        if((s.compare(data[k3].start)==0) && (data[k3].st>=t))
        {
          cout<<data[k3].st<<" "<<data[k3].end<<endl;
          check++;
          k3=(k3+1)%N;
        }
        else
          k3=(k3+1)%64;
      }                 //after reaching null break the loop
      else
        break;
    }
    if (check==0)       //error
      return false;
    else
      return true;
  }
  bool QueryJourney(string stat1,float t,string stat2)
  {
    int k=hashValue(stat1);     //start checking from hash
    int num=0;                  //to get the entries 
    int time[N];
    Journey dummy[N];
    for(int i=0;i<N;i++)
    {               //check if filled else break the loop
      if (data[k].filled)
      {
        if(stat1.compare(data[k].start)==0 && t<=data[k].st)//if same compare the end else incr k 
        {
          if(stat2.compare(data[k].end)==0)     //if end is same then add time
          {
            time[num]=data[k].st;
            num++;
            k=(k+1)%64;
          }
          else              //else check for the link
          {
            int k1=hashValue(data[k].end);//same as above
            string s=data[k].end;
            for(int j=0;j<N;j++)
            {
              if(data[k1].filled)
              { //we are checking only for 1 link
                if(s.compare(data[k1].start)==0 && data[k].et<=data[k1].st && stat2.compare(data[k1].end)==0)
                {
                  time[num]=data[k].st;
                  dummy[num].start=data[k1].start;
                  dummy[num].st=data[k1].st;
                  dummy[num].filled=true;
                  num++;
                  k1=(k1+1)%64;
                }
                else
                  k1=(k1+1)%64;
              }
              else
                break;
            }
            k=(k+1)%64;
          }
        }
        else
          k=(k+1)%64;
      }
      else 
        break;
    }
    if(num==0)      //if num=0 it will return 0 which means no train
      return false;
    else
    {             //else it will return true with the least start time with or without link
      int f=minval(time,num);
      if (dummy[f].filled)
      {
        cout<<time[f]<<" "<<dummy[f].start<<" "<<dummy[f].st<<endl;
        return true;
      }
      else 
      {
        cout<<time[f]<<endl;
        return true;
      }
    }
  }
};
#endif      //by saran 210050036