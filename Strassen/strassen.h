#ifndef __STRASSEN__

#include <stdlib.h>
void strassen_w(float **C, float **A, float **B, const size_t n);
void strassen(float **C, float **A, float **B, const size_t n);
void strassen_base(float **C, float **A, float **B, const size_t n);
#endif // __STRASSEN__
