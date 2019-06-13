#include<stdlib.h>
#include<iostream>
#include<ctime>
#include"sort.h"
#include<sstream>

using std::size_t;
using std::cout;
using std::endl;
using std::cin;
using std::string;



void print(int*A,size_t n){
    for(size_t i = 0;i<n; i++){cout<<A[i]<< " ";}
    cout<<endl;
}


int find_max(int* A,int n){
    int max = A[0];
    for (size_t i = 1; i<n;i++){
        if(A[i]>max){max = A[i];}
    }
    return max;
}



int* rad_create_vect(int n){
    //srand(time(NULL));
    int* da{new int[n]};
    for (int i = 0; i<n; i++){da[i]=rand()%100000;}
    return da;
}

void rad_counting_sort(int* A, size_t n,size_t exp){
    /*
     this Algorithm is counting sort,taking into account that we have to move the entire number and not only the digit
     output = array in which I will move element of A according to the "digit-sorting"
     count = array necessary for counting sort---> it is of length of 10 because digit goes from 0 to 9
     */
    
    
    int* output{new int[n]};
    for (size_t j = 0; j< n; j++){output[j]=0;}
    int* count{new int[10]};
    for (size_t j = 1; j< 10; j++){count[j]=0;}
    //filling count
    for(size_t i = 0; i<n;i++){count[(A[i]/exp)%10]++;}
    
    // comulative count
    for(size_t i=1;i<10;i++){count[i]+=count[i-1];}
    
    int i = n-1;
    // counting sort
    while(i>=0){
        
        output[count[(A[i]/exp)%10] - 1] = A[i];
        count[(A[i] / exp) % 10]--;
        i--;
    }
    // copy output in A
    for (size_t i = 0; i < n; i++){A[i] = output[i];}
    delete[] output;
    delete[] count;
    
}

void radix_sort(int* A, size_t n){
    int m = find_max(A,n);
    size_t exp;
    for(exp = 1; (int)m/exp>0; exp*=10){rad_counting_sort(A,n,exp);}
    }


int main(){
    
    clock_t t1,t2;
    string file_name="radix.txt";
    std::fstream f{file_name,f.app};
    f.close();
    size_t size;
    for(int i{0};i<8;i++){
        f.open(file_name,f.app);
        f<<"potenza:  "<<pow(10,i)<<endl;
        f.close();
        for(int h{1};h<10;h = h+1){
            
            size = h*pow(10,i);
            int* prova = rad_create_vect(size);
            t1 = clock();
            radix_sort(prova,size);
            t2 = clock() -t1;
            f.open(file_name,f.app);
            f<<((float)t2)/CLOCKS_PER_SEC<<endl;
            f.close();
        }
    }
            
    return 0;
}
