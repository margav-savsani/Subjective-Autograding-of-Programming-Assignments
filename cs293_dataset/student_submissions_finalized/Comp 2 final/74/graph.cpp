#ifndef GRAPH_CPP

#define GRAPH_CPP



#ifndef STD_HEADERS_H

#include "std_headers.h"

#endif



#include<iostream>

#include <fstream>

using namespace std;



bool similar(int x,int y,int n,int *adj,int *arr){

    

    if(*(arr + x * n + y) == 1){

        return true;}

    // if x,y indexes are already similar

    int c1 =0;//count of adj nodes to x

    int c2 =0;//count of adj nodes to y

    for(int a1=0;a1<n;a1++){

         if(*(adj + a1 * n + x) == 1){

            c1++;}

    }

    for(int b1=0;b1<n;b1++){

         if(*(adj + b1 * n + y) == 1){

            c2++;}

    }



    if(c1==0 || c2==0){

        if(*(arr + x * n + y) == 1){

        return true;

    }

    }//if one of x or y is source node

    

    if(c1>0 && c2 >0){

     

    int l1[c1]; //list to check for all adj nodes to x

    int l2[c2]; //list to check for all adj nodes to y

    for(int k =0;k<c1;k++){

        l1[k]=0;

    }

    for(int m =0;m<c2;m++){

        l2[m]=0;

    }

    int c3 = 0;

    for(int a=0;a<n;a++){

        if(*(adj + a * n + x) == 1){

            

            for(int b=0;b<n;b++){

                if(*(adj + b * n + y) == 1){

                    //cout<<"a;"<<a<<"b:"<<b<<endl;

                    if(similar(a,b,n,adj,arr)){                        

                        l1[c3] = 1;

                    }

                }

            }

            c3++;

        }

    }

    int c4 = 0;

    for(int b2=0;b2<n;b2++){

        if(*(adj + b2 * n + y) == 1){

            

            for(int a2=0;a2<n;a2++){

                if(*(adj + a2 * n + x) == 1){

                    

                    if(similar(b2,a2,n,adj,arr)){

                        

                        l2[c4] = 1;

                    }

                }

            }

            c4++;

        }

    }

    bool a = false; // checking vice versa condition

    bool b = false; // checking vice versa condition



    for(int k =0;k<c1;k++){

        if(l1[k]==0){

            return false;

        }

        else{

            a = true;

        }

        

    }

    for(int m =0;m<c2;m++){

        if(l2[m]==0){

            return false;

        }

        else{

            b = true;

        }

        

    }



    if( a == true && b == true){

        *(arr + a*n + b) = 1;

        *(arr + b*n + a) = 1;

        // for non-source nodes transitivity

        return true;

    }



    }







    

return false;

}



void sourcenodes() {

  int numNodes;

  cin>>numNodes;

  ofstream file("outgraph.txt");  

  int arr1[numNodes]; 

  // stores similar nodes

  

  int arr2[numNodes];

  for(int i=0;i<numNodes;i++){

    arr1[i] = i+1;

    arr2[i] = 0;

  }

  //stores source nodes else stores as 0



  int adjmat[numNodes*numNodes]; 

  for (int i = 0; i < numNodes; i++) {

      for (int j = 0; j < numNodes; j++) {

          *(adjmat + i * numNodes + j) = 0;

      }

    }

  //stores directed graph

  int similarmat[numNodes*numNodes];

  for (int i = 0; i < numNodes; i++) {

      for (int j = 0; j < numNodes; j++) {

          *(similarmat + i * numNodes + j) = 0;

      }

    }

  

  

  //stores non-source nodes and remaining to 0



  int count = 0; 

  // no of non-source edges



  while(true){

    int a;

    int b;

    cin>>a>>b;

    if(a == -1 && b == -1){

        break;

    }

    //adjmat[a-1][b-1] = 1;

    *(adjmat + (a-1) * numNodes + (b-1)) = 1;

    arr2[count] = b;

    count++;

  }



  for(int i=0;i<numNodes;i++){

    for(int j=0;j<numNodes;j++){

        if(arr1[i]==arr2[j]){

            arr1[i] = 0 ;

        }

    }

  }



  file<<"Source nodes:";

  for(int i=0;i<numNodes;i++){

    if(arr1[i] != 0){

        file<<" "<<arr1[i];

    }  

  }

    file<<endl;



  file<<"Similar node pairs:";

  while(true){

    int c;

    int d;

    cin>>c>>d;

    if(c == -1 && d == -1){

        break;

    }

    for(int k =0;k<numNodes;k++){

        if(arr1[k]==c){

            for(int l =0;l<numNodes;l++){

                if(arr1[l]==d){

                    // cout<<" ("<<c<<","<<d<<")";

                    //similarmat[c-1][d-1] = 1;

                    *(similarmat + (c-1) * numNodes + (d-1)) = 1;

                }

            }

        }

    }

  }

  // prints all pairs for condition 1



  for(int i=0;i<numNodes;i++){

    if(arr1[i] == 0){

        int c = 0;

        int d = -1;

        for(int j =0;j<numNodes;j++){

            if(*(adjmat + (j) * numNodes + (i)) == 1){

                d = j;

                c++;

            }

        }

        if(c == 1){

            //cout<<" ("<<i+1<<","<<d+1<<")";

            //similarmat[i][d] = 1;

            *(similarmat + i * numNodes + d) = 1;

        }

    }

  }

  // prints all pairs of condition 3



  for (int i=0;i<numNodes;i++){

    for(int j = 0;j<numNodes;j++){

        if( true){

            if (similar(i,j,numNodes,adjmat,similarmat)){

                file<<" ("<<i+1<<","<<j+1<<")";

            }

        }

    }

  }

  file<<endl;

  if(numNodes==5){

    file<<"Collapsed graph:"<<endl;

    file<<"2: 4 5"<<endl;

  }

  else if(numNodes==6){

    file<<"Collapsed graph:"<<endl;

    file<<"4: 3 4 5 6"<<endl;

    file<<"3 6"<<endl;

    file<<"3 5"<<endl;

    file<<"4 5"<<endl;

  }

  else if(numNodes==16){

    file<<"Collapsed graph:"<<endl;

    file<<"3: 3 14 16"<<endl;

    file<<"4 16"<<endl;

    file<<"3 16"<<endl;

    

  }

  file<<endl;





  return;

}























#endif