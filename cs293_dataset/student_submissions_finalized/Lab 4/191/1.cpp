#include<iostream>
using namespace std;

void Sorter(int *arr,int start ,int finish){
	
	if(start >= finish)
		return;
	
	int pivot = rand()%(finish-start+1);
	int value = arr[pivot+start];
	int s = start-1;
	int f = finish+1;
	int mid;
	
	while(true){
		do{
			s++;
		}while(arr[s]<value && s<=f);
		
		do{
			f--;
		}while(arr[f]>value && f>=s);
		
		if(f>s){
			int temp;
			temp = arr[s];
			arr[s] = arr[f];
			arr[f] = temp;
		}else{
			break;
		}
	}
	
	Sorter(arr, start, f);
	Sorter(arr, f+1, finish);
	
}


int main(){
	int *arr;
	srand(time(0));
	arr = new int[10];
	for(int i=0;i<10;i++){
		arr[i]=rand()%1000;
	}
	Sorter(arr, 0, 10);
	for(int i=0;i<10;i++){
		cout<<arr[i]<<endl;
	}
	
}
