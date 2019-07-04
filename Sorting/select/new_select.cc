#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<fstream>
#include<sstream>
#include<cmath>


int rep_partition_select(int* A,int l,int r,int m);

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
	
int partition_select(int* A,size_t l,size_t r,int m){ // pivot= A[m]
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

int best_pivot(int* A,int l,int r){ 
	    
        int len = r-l;
        int chunks = len/10 + 1;  // 10 chuncks 
		
        // caso in cui il nostro array sia più piccolo di 10
        if(len + 1<=10){
            quicksort(A,l,r);
            return (l+r)/2;
        }
        // iteriamo in tutti i chunck e li riordiniamo
//        
        int counter = l + 9;
        while(counter < r -10){
            quicksort(A,counter-9,counter); // riordiniamo la parte di array relativa ad un singolo chunk 
            if(counter+10>=r-10){counter=r;} // se l'ultimo chunck è più piccolo di 10--> allora lo settiamo ad r 
            else{counter+=10;}
        }
        // trovare la mediana su ogni chunk e la sposto sul primo chunk 
        int j = l+10;
        for(int i=l;i<chunks;i++){
            switch_el(A,i,(j+i*10)/2); 
            if(j+10>=r){j=r;}
            else{j+=10;}
        }
        int res;
        
        res = best_pivot(A,l,l+chunks); // trovo il best pivot sul primo chunk (la funzione finirà dentro il primo if)
        return res;
        
    }





int select(int* A,int i, int l,int r){
    int j = best_pivot(A,l,r);
    int k = partition_select(A,l,r,j);
	if(i==k+1){return A[k];};
	if(i<1+k){return select(A,i,l,k-1);};
    return select(A,i,k+1,r) ;
	
}



/*
************** DEALING WITH REPEATED VALUE *********************
Actually, select algorithm works with repeated value, but the performance decreases a lot, especially when 
there are values equal to the pivot--> it creates unbalancing  in partition.
How do resolve this problem? with a boolean flag jump:
    -if jump is true, then the equal value is positioned to the left of the pivot (we don't do the switch)
    -if jump is false, then th equal value is positine d to the right of the pivot (we DO the switch)
*/

int rep_partition_select(int* A,int l,int r,int m){
    switch_el(A,l,m); // metto il pivot all'inizio e poi procedo normalmente con il partition
    int pivot = A[l];
    size_t i = l+1;
	size_t j = r ;
    bool jump = true;  // if jump is true--> we put equal values on the left; otherwise on the right
	while(i<=j){
        if(A[i]==pivot){jump = !jump;};
		if(pivot<A[i] || (A[i]==pivot && jump==false)){
			switch_el(A,i,j);
			j = j-1;
		}
		else{i = i+1;}
	}
	switch_el(A,l,j);
	return j; // nuova posizione del pivot
}

int rep_select(int* A,int i, int l,int r){
    int j = best_pivot(A,l,r);
    int k = rep_partition_select(A,l,r,j);
	if(i==k+1){return A[k];};
	if(i<1+k){return rep_select(A,i,l,k-1);};
    return rep_select(A,i,k+1,r) ;
	
}



int main(){

    // verifica che il rep_select funzioni 
    int* alpha{new int[10]};
    for(int i = 0; i<5;i++){
        alpha[i]=rand()%100 + 1;
        alpha[9-i] = alpha[i];
    }
    for(int i = 0;i<10;i++){cout<<alpha[i]<<" ";}
    cout<<endl;
    for(int j = 1; j <=10;j++){
        int p = rep_select(alpha,j,0,10);
        cout<<"alla "<<j<<" posizione si trova"<<p<<endl;
    }


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






