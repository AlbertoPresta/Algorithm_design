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



struct matrix{
    size_t row;
    size_t col;
    double* index{new double[row*col]};
	
	// costruttori
    matrix( size_t n, size_t m):  row{n} , col{m} {
        this->index = new double [row*col]{};
    }
	
	// costruttore per matrici quadrate

    matrix(size_t n): row{n}, col{n}{
         this->index = new double [row*col]{};
}
	
	~matrix(){
        if(!(this->index))
        delete[] index;
	}
    
    void random_fill(size_t n){
        srand(time(NULL));
        for (size_t i = 0; i < this->row*this->col; i++){this->index[i] = rand()%n +1;}
        }
    
    // ocopy constructor
    matrix(matrix* M):  row{M->row}, col{M->col},index{M->index} {}
    
    //Add
    matrix add( matrix other) const {
        matrix temp = new matrix{this->row,this->col};
        
        for(size_t i{0};i<(this->row)*(this->col);i++) {temp.index[i] = (this->index)[i] + other.index[i];};
        return temp;
    }
    
    
    
    
    
    
    
    
    // fill
    void fill(){
        cout<<"insert the value of the matrix."<<endl;
        for (size_t i = 0; i < this->row; i++){
            for (size_t j = 0; j<this->col; j++){
                cin >> this->index[i*this->row + j];
                }
            }
    }
    
    void print(){
        for (size_t i = 0; i < this->row; i++){
            for (size_t j = 0; j<this->col; j++){
                cout << this->index[i*this->row + j]<<" ";
            }
            cout<<endl;
        }
    }
    
    bool null_matrix(){
        for (size_t i = 0; i < this->row*this->col; i++){
            if(this->index[i]!=0) {return false;}
            else{continue;}
        }
        return true;
    }
    

    
};



matrix* naive_multiplication(matrix* A, matrix*B){
    matrix* temp = new matrix{A->row,B->col};
    if (A->col != B->row){
        cout<<"impossible job! empy matrix is returned"<<endl;
        return temp;}
    else{
        for (size_t i = 0; i< A->row; i++){
            for (size_t j=0; j< B->col; j++){
                for (size_t k = 0; k< A->col; k++){
                    temp->index[i*A->row + j] += (A->index[i*A->row + k]*B->index[A->col*k + j]);
                }
            }
        }
        return temp;
    }
}

matrix operator*(matrix A, matrix B) {
    matrix* temp = naive_multiplication(&A, &B);
    return temp;
    
}




void matrix_chain_aux(int* a, matrix m , matrix s , size_t i, size_t j){
    size_t m_dim_row = m.row;
    size_t s_dim_row = s.row;
    m.index[i*m_dim_row + j ] = 10000000;
    for (size_t k = i; k < j;k++){
        size_t q = m.index[i*m_dim_row + k] + m.index[(k+1)*m_dim_row + j] + (a[i])*(a[k+1])*(a[j+1]);
        if(q < m.index[i*m_dim_row + j ] ){
            
            m.index[i*m_dim_row + j ] = q;
            s.index[i*s_dim_row + (j-1) ] = k+1;
        }
    }
}

// lavoro con array di matrici di lunghezza n
matrix* chain(int* a, size_t n){
    
    matrix *temp=(matrix *)malloc(sizeof(matrix*)*2);
    
    matrix m = new matrix{n};
    matrix s = new matrix{n-1};
    for (size_t l = 1; l<n; l++){
        for (size_t i = 0; i< n-l; i++){
            size_t j = i+l;
            matrix_chain_aux(a,m,s,i,j);
        }
    }
    temp[0] = m;
    temp[1] = s;
    return temp;
    
}

int conta(matrix* A){
    int cont = 0 ;
    int i = 0;
    while(A[i].null_matrix()==false){
        i = i+1;
        cont = cont + 1;
    }
    return cont;
}



void timer(){
    srand(time(NULL));
    clock_t t1;
    string file_name="test_data_iter.txt";
    std::fstream f{file_name,f.app};
    f<<"--------------------TIME IN SECONDS--------------------"<<endl<<endl;
    f<<"Chain dimension(vector)                    Execution time "<< endl;
    f.close();
    for (size_t q = 2; q <= 4096; q = q*2 ){
        int* da{new int[q]};
        for(size_t i = 0; i<q; i++){da[i]=rand()%10 +1;}
        t1 = clock();
        matrix *temp = chain(da,q-1);
        t1 = clock() - t1;
        f.open(file_name,f.app);
        f<<q<<"                                        "<<((float)t1)/CLOCKS_PER_SEC<<endl;
        f.close();
      
    }
}


int main(){
    
    matrix A = new matrix{4,3};
    matrix B = new matrix{3,6};
    matrix C = new matrix{6,5};
    matrix D = new matrix{5,4};
    matrix E = new matrix{5,4};
    A.random_fill(50);
    B.random_fill(50);
    C.random_fill(50);
    D.random_fill(50);
    E.random_fill(50);
    /*
    cout<<"somma:  "<<endl;
    matrix Z = D.add(E);
    Z.print();
    cout<<"fine riempimento automatico"<<endl;
    cout<<"MAtrice A: "<<endl;
    A.print();
    cout<<"Matrice B: "<<endl;
    B.print();
    
    cout<<"Matrice C"<<endl;
    C.print();
    cout<<"Matrice D"<<endl;
    D.print();
    
    cout<<"operator *"<<endl;
    matrix S = A*B;
    S.print();
    cout<<"fine operator *"<<endl;
    
   
    int x = conta(lista);
    cout<<x<<endl;
    */
    
    timer();
    
    return 0;
}
