#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void  expression(){
    int n;
    cin>>n;
    long long arr[n];
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    
     sort(arr, arr + n);
    //  for (int i = 0; i < n; i++)
    //  {
    //     cout<<arr[i]<<" ";
    //  }
    
     for (int i = 0; i < n; i++) {
         long long temp;                        //   
         temp = gcd(arr[i],arr[n-1]);     //  temp gcdc is cgenerated 
        //  cout<<temp<<" ";                 //   
        //  cout<<endl;                      //    
         arr[n-i] = temp;                   //  
        //  cout<<endl;
     }
     long long sum=0;
     for (int i = 0; i < n; i++) {
         sum = sum + arr[i];
     }

    cout<<sum<<endl;
} 




int main() {
	int T;
	cin>>T;
	while(T--){
	    
	    expression();
	}
	return 0;
}
