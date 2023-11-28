#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;


template <typename T> class listOfObjects {
  public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  listOfObjects(){
    next = prev = nullptr;
  }

  listOfObjects(T val){
    object = val;
    next = prev = nullptr;
  }

  ~listOfObjects(){;}
};

//listOfObjects<int> ** 
void read_process(string filename){
    ifstream file;
    file.open(filename);

    
    ofstream output_file;
    output_file.open("outgraph.txt");
    

    string s;
    int n=-1;
    int n1,n2;
    int num_change = 0;
    bool *arr;

    // listOfObjects<listOfObjects<int>> *L1;
    // listOfObjects<listOfObjects<int>> *L2;
    listOfObjects<int> **arr1;
    listOfObjects<int> **arr2;
    listOfObjects<int> *l1;
    listOfObjects<int> *l2;
    listOfObjects<int> *l3;

    if(file.is_open()){
      while(getline(file, s)){
        istringstream iss(s);
        if(n == -1){
          iss >> n;
          
          arr1 = new listOfObjects<int>*[n];  // array of list of 
          arr2 = new listOfObjects<int>*[n];
          arr = new bool[n];

        }
        else{
          if(!(iss >> n1 >> n2)){
            break;
          }
          
          if(n1 == -1){
            num_change++;
            continue;
          }
          
          if(num_change == 0){
            l1 = nullptr;
            l1 = arr1[n1-1];
            if(arr1[n1-1] == nullptr){
              arr1[n1-1] = new listOfObjects<int>(n2);
            }
            else{
              while(l1 != nullptr){
                l2 = nullptr;
                l2 = l1;
                l1 = l1->next;
              }
              l2->next = new listOfObjects<int>(n2);
            }
          }

          else if(num_change == 1){

            //for n1
            l1 = nullptr;
            l1 = arr2[n1-1];
            if(arr2[n1-1] == nullptr){
              arr2[n1-1] = new listOfObjects<int>(n2);
            }
            else{
              while(l1 != nullptr){
                l2 = nullptr;
                l2 = l1;
                l1 = l1->next;
              }
              l2->next = new listOfObjects<int>(n2);
            }

          }

          else {
            break;
          }
          
        }
      }
      
      //Source node part
      output_file << "Source nodes: ";
      
      for(int i = 0; i<n; i++){
        arr[i] = true;
      }


      // similar node pair part starts here
      for(int i = 0; i<n; i++){
        l1 = nullptr;
        l1 = arr1[i];
        int j = 0;
        bool exist = false;
        
        while(l1 != nullptr){
          arr[l1->object-1] = false;
          l1 = l1->next;
          j++;
        }
        if(j == 1){
          l2 = nullptr;
          l2 = arr2[arr1[i]->object-1];

          exist = false;
          while(l2 != nullptr){
            if(i+1 == l2->object){
              exist = true;
            }
            l2 = l2->next;
          }
          if(!exist){
            l2 = nullptr;
            l2 = arr2[arr1[i]->object-1];

            if(arr2[arr1[i]->object-1] == nullptr){
              arr2[arr1[i]->object-1] = new listOfObjects<int>(i+1);
            }

            else {
              while(l2 != nullptr){
                l3 = nullptr;
                l3 = l2;
                l2 = l2->next;
              }
            l3->next = new listOfObjects<int>(i+1);
            }
          }

        }
      }
      for(int i = 0 ; i<n; i++){
        if(arr[i]){
          output_file << i+1 << " ";
        }
      }
      output_file << endl << endl;
    

      output_file << "Similar node pairs: ";
      for(int i = 0; i<n; i++){
        l1 = nullptr;
        l1 = arr2[i];

        while(l1 != nullptr){
          
          // first condition of similarity
          output_file << "(" << i+1 << ", " << l1->object << ")";
          l1 = l1->next;

          // second condition of similarity
            
        }

      }
      output_file << endl;

    }
  file.close();
}

int main(int argc, char **argv){
    
    string filename;
    filename = argv[1];
    read_process(filename);
    
}
