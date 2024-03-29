
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

//srand(time(NULL));

void switch_el(int* A, size_t i, size_t j){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void insertion_sort(int* A,int n){
	for (size_t i= 1 ; i < n;i++){
		size_t j = i;
		while(j>0 and A[j]<A[j-1]){
			switch_el(A,j-1,j);
			j = j-1;
		}
	}
}

int* create_vect(int n){
	//srand(time(NULL));
	int* da{new int[n]};
	for (int i = 0; i<n; i++){
		da[i]=rand()%100 +1;
	}
	return da;
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


void print(int*A,size_t n){
	for(size_t i = 0;i<n; i++){cout<<A[i]<< " ";}
    cout<<endl;
}





int best_pivot(int* A,int l,int r){ 
	    
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



int best_partition(int* A,size_t l,size_t r){ 
	int pivot = A[(l+r)/2];
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


void best_quicksort(int* A,int l,int r){
	if(l<r){
		int p = best_partition(A,l,r);
        best_quicksort(A,l,p-1);
		best_quicksort(A,p+1,r);
	}
}




int main(){
    // test nel caso random
    clock_t t1;
    string file_name="quicksort_worst_case.txt";
    string second_file = "quicksort_normale_case.txt";
    string insertion = "insertion_sort.txt";
    string insertion_random = "random_insertion_sort.txt";
    string best = "best_quicksort.txt";
    string best_insertion = "best_insertion_sort.txt";

    //std::fstream ff{second_file,ff.app};
    //ff.close();
    std::fstream f{file_name,f.app};
    f.close();
    int size;
  
    for(int i{1};i<5;i++){
        for(int h{1};h<10;h = h+1){
            //cout<<"size:   "<<h*pow(10,i)<<endl;
            size =h*pow(10,i);
            
            int* b = create_vect(size);
            t1 = clock();
            quicksort(b,0,size);
            t1=clock()-t1;
            f.open(second_file,f.app);
            f<<((float)t1)/CLOCKS_PER_SEC<<endl;
            f.close();
                }
        }
    
    // analisi di quick sort nel caso peggiore

for(int i{1};i<5;i++){
        for(int h{1};h<10;h = h+1){
            //cout<<"size:   "<<h*pow(10,i)<<endl;
            size =h*pow(10,i);
            int* b{new int[size]};
            for(int i = 0; i<size;i++){b[i]= size - i;}
            t1 = clock();
            quicksort(b,0,size);
            t1=clock()-t1;
            f.open(file_name,f.app);
            f<<((float)t1)/CLOCKS_PER_SEC<<endl;
            f.close();
                }
        }
    
    // analisi di insertion sort nel caso peggiore 
    
    for(int i{1};i<5;i++){
        for(int h{1};h<10;h = h+1){
            //cout<<"size:   "<<h*pow(10,i)<<endl;
            size =h*pow(10,i);
            int* b{new int[size]};
            for(int i = 0; i<size;i++){b[i]= size - i;}
            t1 = clock();
            insertion_sort(b,size);
            t1=clock()-t1;
            f.open(insertion,f.app);
            f<<((float)t1)/CLOCKS_PER_SEC<<endl;
            f.close();
                }
        }

    cout<<"RANDOM INSERTION"<<endl;
    // analisi di insertion sort nel caso random
    for(int i{1};i<5;i++){
        for(int h{1};h<10;h = h+1){
            //cout<<"size:   "<<h*pow(10,i)<<endl;
            size =h*pow(10,i);
            int* b =  create_vect(size);
            t1 = clock();
            insertion_sort(b,size);
            t1=clock()-t1;
            f.open(insertion_random,f.app);
            f<<((float)t1)/CLOCKS_PER_SEC<<endl;
            f.close();
                }
        }
   
    
   

    cout<<"best insertion sort"<<endl;
    for(int i{1};i<5;i++){
        for(int h{1};h<10;h = h+1){
            size =h*pow(10,i);
            int* b{new int[size]};
            for(int q =0; q<size;q++){b[i]=i;}
            t1 = clock();
            insertion_sort(b,size);
            t1=clock()-t1;
            f.open(best_insertion,f.app);
            f<<((float)t1)/CLOCKS_PER_SEC<<endl;
            f.close();
                }
        }


	return 0;
	
}
