#include <iostream>
#include <iostream>
#include<vector>


void print(double* p, int n);
// algoritmo naive: riceve in input le due matrici ed esegue l'algoritmo naive



template<typename T>
T*  naive(T* A, T* B, size_t n){
    T* C = new T[n*n]{};
	for (int i = 0; i< n; i++){
		for (int j=0; j< n; j++){
			for (int k = 0; k< n; k++){
				C[i*n + j] += (A[i*n + k]*B[n*k + j]);
			}
		}
	}
	return C;
}


//  CREAZIONE DEI BLOCCHI! per ogni matrice creo i quattro blocchi + i quattro blocchi del risultato
// output vettore di matrici  T* a {new T[n]};
template<typename T>
std::vector<T*>  create_blocks(T* A,  size_t n ){
	size_t q = (int) n/2; // dimensione lineare dei blocchi 
	
	std::vector<T*> blocco;
	T* A1 = new T[q*q]{}; // blocco 1
	T* A2 = new T[q*q]{};
	T* A3 = new T[q*q]{};
	T* A4 = new T[q*q]{};
	//A1
	for (int i = 0 ; i < q; i++ ){
		for (int j = 0; j < q; j++){
			int indice = i*q + j;
            if(indice< q)
                A1[i*q + j] = A[i*q + j];
            else{
               
                
                int r = 2;
                while(indice*r < n){
                    std::cout<<"i am in "<<std::endl;
                    if( q*(r-1)< indice <q*r - 1){
                        A1[i*q + j] = A[i*q + j + (r-1)*q];
                        break;
                    }
                    else{
                        r = r+1;
                    }
                }
            }
        }
    }
	//A2
	for (int i = 0 ; i < q; i++ ){
		for (int j = 0; j < q; j++){
			int indice = i*q + j;
			if(indice<q){A2[i*q + j] = A[(i)*q + j + q];}
			else{A2[i*q + j] = A[(i)*q + j + q + q ];}
			
		}
	}
	//A3
	for (int i = 0 ; i < q; i++ ){
		for (int j = 0; j < q; j++){
			int indice = i*q + j;
			if(indice<q){
				A3[i*q + j ] = A[i*q + j + q*n];}
			else{A3[i*q + j] = A[(i)*q + j +  q*(n+1) ];}
			
		}
	}
	//A4
	for (int i = 0 ; i < q; i++ ){
		for (int j = 0; j < q; j++){
			int indice = i*q + j;
			if(indice<q){
				A4[i*q + j ] = A[i*q + j + q*n + q ];}
			else{A4[i*q + j] = A[(i)*q + j +  q*(n+1) + q ];}
			
		}
	}
	
	blocco.push_back(A1);
	blocco.push_back(A2);
	blocco.push_back(A3);
	blocco.push_back(A4);
	
	return blocco;
}





template<typename T>
T* sum(T* A, T* B, int n){
    T* S = new T[n*n]{};
    for (int i = 0; i< n; i++){
        for (int j = 0; j< n; j++){
            S[i * n + j] = A[i * n + j] + B[i * n + j];
        }
        
    }
    return S;
}















void print(double* p, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << p[i * n + j] << " ";
        std::cout << std::endl;
    }
}

template<typename T>
std::vector<T*> blocks(T* A,  T*B, size_t n){
	size_t q = (int) n/2;
	std::vector<T*> S ;
	std::vector<T*> G ;
	S = create_blocks(A,4);
	G = create_blocks(B,4);
	std::vector<double*> C;
   
    
    T* A0B0 = naive(S[0],G[0], q); // manca da fare i blocchi
    T* A0B1 = naive(S[0],G[1], q);
	T* A1B2 = naive(S[1],G[2], q);
    T* A1B3 = naive(S[1],G[3],q);
	T* A1B0 = naive(S[1],G[0], q);
    T* A2B0 = naive(S[2],G[0], q);
    T* A3B2 = naive(S[3],G[2], q);
    T* A2B1 = naive(S[2],G[1], q);
    T* A3B3 = naive(S[3],G[3], q);
    T* C0 = sum(A0B0,A1B2, q);
    T* C1 = sum(A0B1,A1B3,q);
    T* C2 = sum(A2B0,A3B2,q);
    T* C3 = sum(A2B1,A3B3,q);
    C.push_back(C0);
    C.push_back(C1);
    C.push_back(C2);
    C.push_back(C3);
    return C;
    
    
}







int main(){
	
	double* A = new double[8*8]{};
    int cont = 1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j){
            A[i * 8 + j] = cont;
        cont = cont +1;
        }
    }



	double* B = new double[4*4]{};
	//std::cout<<"Ppppppp"<<std::endl;
	B[0] = 0;
	B[1] = 1;
	B[2] = 0;
	B[3] = 0;
	
	B[4] = 2;
	B[5] = 1;
	B[6] = 0;
	B[7] = 0;
	
	B[8] = 0;
	B[9] = 1;
	B[10] = 2;
	B[11] = 0;
	
	B[12] = 4;
	B[13] = 1;
	B[14] = 0;
	B[15] = 1;
	print(A,8);
	std::cout<<"Matrix B"<<std::endl;
	print(B,4);
	
	std::cout<<"NAIVE VERSION"<<std::endl;
	double* c = naive(A,B,4);
	print(c,4);
	
	std::vector<double*> S ; 
	std::vector<double*> T ; 
	//S = create_blocks(A,8);
    //std::cout<<"VERIFICA"<<std::endl;
    //print(S[0],4);
    
	T = create_blocks(B,4);
    std::vector<double*> Q ;
    Q = blocks(A,B,4);
    std::cout<<"BLOCKS VERSION"<<std::endl;
    print(Q[0],2);
	std::cout<<std::endl;
	print(Q[1],2);
	std::cout<<std::endl;
    print(Q[2],2);
	std::cout<<std::endl;
    print(Q[3],2);
	
	
	
}
