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

/*
structure of the array-based heap.
 Istances of the class:
    - an integer which represent the size of the heap
    - an integer which represents the size of the entire array (I don't know if it is necessary)
    -An array which represents the heap

 For now I decide to implement the max-heap structure: maybe later on I will introduce a new templated variable to eventually invert the relation of order
 
 */

template<typename T>
class heap{
    int dim_array; // size of the array
    int dim_heap;
    T* hp{new T[dim_array]};
    

    // constructor: it receives in input an integer and an array of values
public:
    void swap(int i ,int j){
        T temp = this->hp[i];
        this->hp[i] = this->hp[j];
        this->hp[j] = temp;
    }
        

    void  heapify(int i){
       
        int l = left(i);
        int r = right(i);
        int max;
        if(is_valid_node(l) and this->hp[l]>this->hp[i]){max = l;}
        else{max = i;}
        if(is_valid_node(r) and this->hp[r]>this->hp[max]){max = r;};
        if(max!=i){
            swap(i,max);
            heapify(max);
        }
    }

    void build_heap(){
        int i = this->dim_array - 1;
        while(i>=0){
            heapify(i);
            i--;
        }
}

    
    
    
    

    heap(int dim,T* a ):dim_array{dim},dim_heap{dim},hp{a} {
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
            if(this->hp[parent(i)]<this->hp[i]){return false;};
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
    
    
// end of basics functions
    
/*
 heapify(i)-->it receives in input an array A and an index i and It transforms the sub-array with root i in a max(min) heap
 heapify receives as input our heap A, which at the beginning is simply an array
private or public--> I vote for private
*/
  

};




template<typename T>
void heapsort(T* a,int n){
    heap<T> a_hp{n,a};
    int i = a_hp.length() -1;
    while(i>=1){
        a_hp.swap(0,i);
        a_hp.decrease_hp();
        a_hp.heapify(0);
        i = i-1;
    }
    for(int i = 0; i<n;i++){a[i]=a_hp.get_array()[i];}
}



int main(){
     //srand(time(NULL));
    clock_t t1;
    string file_name="heapsort.txt";
    size_t size;
    std::fstream f{file_name,f.app};

    for(int i{1};i<7;i++){
        for(int h{1};h<10;h = h+1){
            size =h*pow(10,i);
            int* b{new int[size]};
            for (int i = 0; i<size;i++){b[i]=rand()%100 +1;}
            t1 = clock();
            heapsort(b,size);
            t1=clock()-t1;
            f.open(file_name,f.app);
            f<<((float)t1)/CLOCKS_PER_SEC<<endl;
            f.close();
            }
        }
    
    
    
   
    
    
    
    
    
    return 0;
}



















