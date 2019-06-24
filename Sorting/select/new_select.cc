#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<fstream>
#include<sstream>
#include<cmath>

using std::size_t;
using std::cout;
using std::endl;
using std::cin;
using std::string;

int* create_vect(int n){
	
	int* da{new int[n]};
	for (int i = 0; i<n; i++){
		da[i]=rand()%100 +1;
	}
	return da;
}

void switch_el(int* A, size_t i, size_t j){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}


int partition(int* A,size_t l,size_t r){ // pivot= A[l]
	int pivot = A[l];
    size_t i = l+1;
	size_t j = r ;
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

void quicksort(int* A,int l,int r){
	if(l<r){
		int p = partition(A,l,r);
        quicksort(A,l,p-1);
		quicksort(A,p+1,r);
	}
}
	
int partition_select(int* A,size_t l,size_t r,int m){ // pivot= A[l]
    switch_el(A,l,m); // metto il pivot all'inizio e poi procedo normalmente con il partition
    int pivot = A[l];
    size_t i = l+1;
	size_t j = r ;
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

int best_pivot(int* A,int l,int r){ // N grande è la dimensione totale
	    
        int len = r-l;
        int chunks = len/10 + 1;
		
        // caso in cui ol nostro array sia più piccolo di 10
        if(len +1<=10){
            quicksort(A,l,r);
            return (l+r)/2;
        }
        // iteriamo in tutti i chunck e li riordiniamo
//        
        int counter = l + 9;
        while(counter < r -10){
            quicksort(A,counter-9,counter);
            if(counter+10>=r-10){counter=r;}
            else{counter+=10;}
        }
        // trovare la mediana su ogni chunk e spostarla all'inizio di ogni array
        int j = l+10;
        for(int i=l;i<chunks;i++){
            switch_el(A,i,(j+i*10)/2);
            if(j+10>=r){j=r;}
            else{j+=10;}
        }
        int res;
        // continuo finchè non rimane un solo chunck
        res = best_pivot(A,l,l+chunks);
        return res;
        
    }





int select(int* A,int i, int l,int r){
    int j = best_pivot(A,l,r);
    int k = partition_select(A,l,r,j);
	if(i==k+1){return A[k];};
	if(i<1+k){return select(A,i,l,k-1);};
    return select(A,i,k+1,r) ;
	
}



int main(){

     // tempistiche
    clock_t t1;
    for (int i = 10; i<=10000;i=i+10){
        
        int* pp = create_vect(i);
        t1 = clock();
        int p = select(pp,1,0,i);
        t1=clock()-t1;
        cout<<((float)t1)/CLOCKS_PER_SEC<<endl;
        
       
    }
    
    
    

	return 0;
}






