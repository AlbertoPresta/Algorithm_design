#include<stdlib.h>
#include<iostream>
#include<cmath>

using namespace std;



// bisogna cotruire la classe min_heap 
template<typename T>
class min_heap{
    int dim_array; // size of the array
    int dim_heap;
    T* hp{new T[dim_array]};

public:
    void swap(int i ,int j){
        T temp = this->hp[i];
        this->hp[i] = this->hp[j];
        this->hp[j] = temp;
    }
        
 // funzioni che servono per costruire la heap 
    void  heapify(int i){
       
        int l = left(i);
        int r = right(i);
        int m=i;
        if(is_valid_node(l) and this->hp[l]<this->hp[m]){m = l;}
        
        if(is_valid_node(r) and this->hp[r]<this->hp[m]){m = r;};
        if(m!=i){
            swap(i,m);
            this->heapify(m);
        }
    }

    void build_heap(){
        int i = this->dim_array - 1;
        while(i>=0){
            heapify(i);
            i--;
        }
}

    
    
    
    
   // constructor: it receives in input an integer and an array of values
    
    
    min_heap(int dim,T* a):dim_array{dim},dim_heap{dim},hp{a} {
        // transform the array in a heap
        build_heap(); // function to be defined
    }

//  basic functions
    int get_dim(){return this->dim_heap;}
    int left(int i){return 2*i;}
    int right(int i){return 2*i +1;}
    int parent(int i){return i/2;}
    int length(){return this->dim_array;}
    T* get_array(){return this->hp;}
   
    
    bool is_valid_node(int i){return (this->dim_heap >i);}
    
    bool ver(){
        for(int i = 1;i<this->dim_heap;i++){
            if(this->hp[parent(i)]>this->hp[i]){return false;};
            }
        return true;
    }
    
    // this function is usefull to heapsort
    void decrease_hp(){this->dim_heap = this->dim_heap -1;}
    
    
    void print(){
        for(int i = 0; i < this->dim_heap; i++){
            cout<<this->hp[i]<<" ";
        }
        cout<<endl;
    }

    bool isempty(){
        if(dim_heap==0) return true;
        else return false;
    }

    T* extractmin(){
        if(!this->isempty()){
            T r = this->hp[0];
            this->swap(0,dim_heap -1);
            this->decrease_hp(); // delete last element
            this->heapify(0);
            T* p = &r;
            return p;
        }
        return NULL;
    }


    
    
// end of basics functions
    
/*
 heapify(i)-->it receives in input an array A and an index i and It transforms the sub-array with root i in a max(min) heap
 heapify receives as input our heap A, which at the beginning is simply an array
private or public--> I vote for private
*/
  

};



// now we have to create or class graph 

struct graph{
    // variabili di classe : un intero che rappresenta il numero di vertici 
    // 
    // matrice di adiacenza 
    
    int v;
    
    int* adj{new int[v*v]};

    graph(int n,int* mat): v{n}, adj{mat} {

    }

    void print_graph() {
        for(int i=0; i<this->v;i++){
            for(int j=0;j<this->v;j++){
                cout<<this->adj[i*v+j]<<" ";
            }
            cout<<endl;
        }
    }

    ~graph(){}



};


























int main(){
int n = 10;
int* a{new int[n]};
a[0]=12;
a[1]=2;
a[2]=1;

for(int i=3; i<n;i++){a[i]=rand()%100 +1;}

min_heap<int> a_hp{n,a};
a_hp.print();
int* minimo = a_hp.extractmin();
cout<<"ecco il minimo : "<<*minimo<<endl;
int* gr{new int[5*5]};

for(int j=0; j<25;j++){
    double random = (double)(rand()%100+1)/100;
    if(random>0.3){gr[j]=rand()%100+1;}
    else{gr[j]=0;}
}

graph g{5,gr};
g.print_graph();
return 0;
}
