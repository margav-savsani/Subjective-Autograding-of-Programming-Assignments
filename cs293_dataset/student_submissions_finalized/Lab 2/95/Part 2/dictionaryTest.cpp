#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;
int main()
{
  
  Planner p;
 char  a[32]="Berlin"; 
char  b[32]="Munich";
char  c[32]="Gottingen";
char  d[32]="Hannover";
char  e[32]="Frankfurt";

  p.add_root(a, 1300 ,b, 1700);
    p.add_root(c ,1000 ,d, 1100);
  p.add_root(d ,900 ,a, 1100);
  p.add_root( b ,1400 ,e, 1800);
  p.add_root(e, 800, c, 955);
  p.add_root(b ,1200, a, 1600);
  p.add_root(c ,1200, b, 1600);
  p.add_root(c, 1000 ,a, 1200);
  p.QUERY_JOURNEY(c, 900 ,b);
  p.QUERY_JOURNEY(c, 1100 ,b);
  p.QUERY_JOURNEY(e ,700, b);
  p.Query_Staion(d ,500);
  p.Query_Staion(b ,500);
  p.QUERY_JOURNEY(a ,1000, c);


  
  return 0;
}
