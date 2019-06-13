#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<fstream>
#include<sstream>


using std::size_t;
using std::cout;
using std::endl;
using std::cin;
using std::string;


/////////////////////////// parte relativa a radix sort///////////////////////////

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
	
	
	
	/////////////////////////////////




void switch_el(int* A, int i, int j){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void insertion_sort(int* A,int n){
	for (int i= 1 ; i < n;i++){
		int j = i;
		while(j>0 and A[j]<A[j-1]){
			switch_el(A,j-1,j);
			j = j-1;
		}
	}
}



int partition(int* A,int l,int r,int jj){ // pivot= A[l]
	switch_el(A,0,jj);
	int pivot = A[0];
    
	int i = l+1;
	int j = r ;
	while(i<=j){
		if(pivot<A[i]){
			switch_el(A,i,j);
			j = j-1;
		}
		else{i = i+1;}
	}
	switch_el(A,l,j);
	return j; // nuova posizione del pivot
}



int look_for_value(int* A,int conf,int N){
    int res;
    for(int i= 0; i<N;i++){
        if(A[i]==conf){
            res = i;
            return res;
        }
    }
    return 0;
}



int median(int* A,int start,int end,int N){
	int n = end-start;
	int* temp{new int[n]};
	for(int i=0; i<n;i++){temp[i]=A[start+i];}
    //insertion_sort(temp,n);
	radix_sort(temp,n);
    int conf = temp[n/2];
    int res = look_for_value(A,conf,N);
    return res;
}
	


int best_pivot(int* A,int l,int r,int N){ // N grande è la dimensione totale
	    int len = r-l;
        int n;
		if(len%10==0) { n = len/10;}
        else { n=len/10+1;}
        int* index{new int[n]};
        for(int i{0};i<n;i++) index[i]=median(A,i*10,i*10 + 10,N);
        int* index_values{new int[n]};
        for(int i{0};i<n;i++) index_values[i]=A[index[i]];
        int ris = median(index_values,0,n,N);
        return median(index_values,0,n,N);
    }



int select(int* A,int i, int l,int r,int N){
    int* AA{new int[N]};
    for(int i=0; i<N;i++){AA[i]=A[i];}
    int j = best_pivot(AA,l,r,N);
    int k = partition(AA,l,r,j);
	if(i==k){return A[k];};
	if(i<k){return select(A,i,l,k-1,N);};
    return select(A,i,k+1,r,N) ;
	
}


int main(){

    // prova se funziona 
    int* pp{new int[10]};
    pp[0]=2;
    pp[1]=1;
    pp[2]=4;
    pp[3]=3;
    pp[4]=7;
    pp[5]=6;
    pp[6]=33;
    pp[7]=8;
    pp[8]=11;
    pp[9]=5;
    
    //for (int i = 0;i<10;i++){pp[i]=i;}
    for (int i = 0;i<10;i++){cout<<pp[i]<<" ";}
    cout<<endl;
    int prova = select(pp,4,0,10,10);
    cout<<prova<<endl;
    clock_t t1,t2;
    int* A{new int[1000]};
	for(int i=0;i<1000;i++){A[i]= i;}
	for(int i = 0; i<1000;i=i+100){
        t1 = clock();
        int y = select(A,i,0,1000,1000);
        t2 = clock() -t1;
        //cout<<y<<endl;
        cout<<"time for algorithm for searching "<<i<<":  "<<((float)t2)/CLOCKS_PER_SEC<<endl;
    }
	

	return 0;
}






