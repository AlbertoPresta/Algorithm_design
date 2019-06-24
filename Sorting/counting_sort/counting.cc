#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<sstream>

#include<cmath>
#include<fstream>

using std::size_t;
using std::cout;
using std::endl;
using std::cin;
using std::string;

int* create_vect(int n){
	//srand(time(NULL));
	int* da{new int[n]};
	for (int i = 0; i<n; i++){
		da[i]=rand()%100 +1;
	}
	return da;
}

	

void counting_sort(int* A,int* B,int k,int n){
	int* C{new int[k]};
	
	for (size_t j = 0; j< k; j++){C[j]=0;}
	for (size_t i = 0; i<n; i++){C[A[i]-1] = C[A[i]-1] +1;}
	for (size_t j = 1; j< k; j++){C[j] = C[j] +  C[j-1];}
	for (size_t i = n-1; i>0;i= i-1){
		B[C[A[i]-1]-1] = A[i];
		C[A[i]-1] = C[A[i]-1] -1;
	  }
	  B[C[A[0]-1]-1] = A[0];
      for(size_t i = 0; i<n;i++){A[i]=B[i];}
	delete[] C;
}
 
 
 
 int find_max(int* A,int n){
 	int max = A[0];
 	for (size_t i = 1; i<n;i++){
 		if(A[i]>max){max = A[i];}
 	}
 	return max;
 } 
 
 int main(){
	 
	 string file_name="counting_sort.txt";
	 clock_t t1;
	 std::fstream f{file_name,f.app};
	 size_t size;
	 for(int i{1};i<7;i++){
        for(int h{1};h<10;h = h+1){
			//cout<<"ciao"<<endl;
            
            size =h*pow(10,i);
            int* a = create_vect(size);
			int* b{new int[size]};
			int max = find_max(a,size);
            t1 = clock();
            counting_sort(a,b,max,size);
            t1=clock()-t1;
            f.open(file_name,f.app);
            f<<size<<"         "<<((float)t1)/CLOCKS_PER_SEC<<endl;
            f.close();
			delete[] a;
			delete[] b;
                }
        }



	 return 0;
 }
 
 
