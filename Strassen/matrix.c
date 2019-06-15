#include <stdlib.h>
#include <stdio.h>
int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols)
{
  if (A_cols != B_rows) {
     return -1;
  }

  // for all rows in A
  for (size_t i=0; i<A_rows; i++) {

     // for all cols in B
     for (size_t j=0; j<B_cols; j++) {

       // reset C[i][j]
       C[i][j] = 0.0;

       // sum all the element mults
       for (size_t k=0; k<A_cols; k++) {
        C[i][j] += (A[i][k]*B[k][j]);
       }
     }
  }

  return 0;
}

float **allocate_matrix(const size_t rows,
                        const size_t cols)
{
   float **A=(float **)malloc(sizeof(float *)*rows);

   for (size_t i=0; i<rows; i++) {
     A[i]=(float *)malloc(sizeof(float)*cols);
   }

   return A;
}

void deallocate_matrix(float **A, const size_t rows)
{
  for (size_t i=0; i<rows; i++) {
    free(A[i]);
  }

  free(A);
}

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols)
{
   if ((A_rows != B_rows) || (A_cols != B_cols)) {
     return 0;
   }
   int counter=0;
   _Bool uguali=1;
   for (size_t i=0; i<A_rows; i++) {
     for (size_t j=0; j<A_cols; j++) {
        if ((A[i][j] - B[i][j]>0.0001)||(A[i][j] - B[i][j]<-0.0001)) {

          counter++;
	        uguali=0;
        }
     }
   }
   if(counter>0){
     printf(" diverse per %d elementi",counter);
   };
   return uguali;
}


void print_mat(float **C,
               const size_t C_f_row,
               const size_t C_f_col,
               const size_t n)
               {
                 for (int i=0;i<n;i++){
                   if(i==n/2){printf("\n" );};
                   for (int j=0;j<n;j++) {
                     if(j==n/2){
                       printf(" %f ",C[C_f_row+i][C_f_col+j] );
                     }
                     else{
                       printf("%f ",C[C_f_row+i][C_f_col+j] );
                     };
                   }
                   printf("\n");
                 }
                 printf("\n");
               }
