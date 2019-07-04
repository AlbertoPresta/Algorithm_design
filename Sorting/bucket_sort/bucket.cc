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

// create a vector for bucket sort
double* create_vect(int n){
	//srand(time(NULL));
	double* da{new double[n]};
	for (int i = 0; i<n; i++){
		da[i]=(double)(rand()%1000 +1)/1000;
	}
	return da;
} 


 void switch_el_double(double* A, size_t i, size_t j){
    double temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int* empty_vector(int n){
    int* A{new int[n]};
    for (int i=0;i<n;i++){A[i]=0;}
    return A;
}
 
 
void double_insertion_sort(double* A,size_t n){
    for (size_t i= 1 ; i < n;i++){
        size_t j = i;
        while(j>0 and A[j]<A[j-1]){
            switch_el_double(A,j-1,j);
            j = j-1;
        }
    }
}


 
 
 
 // funzione che mi restituisce il numero di elementi che ci sono in ogni bucket 
 // n è il numero di buckets
 int* division_bucket(double* A,size_t n){
	 int* ris = empty_vector(n);
     for(int j = 0; j<n;j++){
         int i = 0;
         //cout<<"++++++++++++++       "<<j<<endl;
         while(i<n){
             if(A[j]>(double)(n-1)/n){
                 ris[n-1]=ris[n-1]+1;
                 i = n+1;
             }
             else{
             double l = (double)(i)/n;
             double r = (double)(i+1)/n;
             if(l<A[j]<=r){
                  
                 ris[i-1]=ris[i-1]+1;
                 
                 i = n+1;
                 }
             else{
                 
                 i = i+1;}
            }
         }
     }
     return ris;
 }







void bucket_sort(double* A,size_t n){
    int* p = division_bucket(A,n); // serve per allocare meno memoria possibile--> questo è un array che contiene quanti elementi ha ogni bucket
    // temp rappresenta l'insieme dei bucket vero e proprio
    double **temp=(double **)malloc(sizeof(double**)*n);
    for (size_t i = 0; i<n;i++){temp[i] = (double *)malloc(sizeof(double*)*p[i]);}
    for(size_t i = 0; i<n; i++){
        for(size_t j = 0; j<p[i];j++){temp[i][j] = 0.0;}
    }
   int* indici = empty_vector(n); // array che mi serve per l'inserimento del bucket
    for (size_t i = 0; i<n; i++){
        size_t  k = (int)(A[i]*n);
        temp[k][indici[k]] = A[i];
        indici[k] = indici[k] + 1;
        
    }
    for (size_t i = 0; i<n; i++){double_insertion_sort(temp[i],p[i]);}
    // buttare tutto dentro A
    size_t i = 0;
    for(size_t j = 0; j<n; j++){
        for(size_t w = 0;w<p[j];w++){
            A[i] = temp[j][w];
            i = i+1;
           }
       }
    delete[] p;
    delete[] indici;
    delete[] temp;
}



int main(){
    string file_name="bucket_sort.txt";
    clock_t t1;
	std::fstream f{file_name,f.app};
    
    
	for(int i{10};i<105;i=i+5){
        double* da{new double[i]};
	    for (int j = 0; j<i; j++){da[j]=(double)(rand()%1000 +1)/1000;}
		t1 = clock();
        bucket_sort(da,i);
        t1=clock()-t1;
        f.open(file_name,f.app);
        f<<((float)t1)/CLOCKS_PER_SEC<<endl;
        f.close();
        cout<<i<<endl;
		delete[] da;
    }  
    
        


    return 0;
}