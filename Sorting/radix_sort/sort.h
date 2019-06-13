#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<cmath>
#include<sstream>
#include<fstream>




#ifndef __sort__
#define __sort__

// general method, useful for testing or for general purpose
int* create_vect(int n);
int find_max(int* A,int n);
int find_min(int* A,int n);

int* empty_vector(int n);
void switch_el(int* A, size_t i, size_t j);
void print(int*A,size_t n);
double* unif(int n);
void switch_el_double(double* A, size_t i, size_t j);

// radix sort algorithm 
void rad_counting_sort(int* A, size_t n,size_t exp);
void radix_sort(int* A, size_t n);
int* rad_create_vect(int n);

// insertion sort
void insertion_sort(int* A,int n);

//quicksort (with partition)
int partition(int* A,int l,int r);
void quicksort(int* A,int l,int r);

//counting_sort
void counting_sort(int* A, int* B,int k,int n);


//bucket sort (with division bucket)
void double_insertion_sort(double* A,size_t n);
int* division_bucket(double* A,size_t n);
void bucket_sort(double* A,size_t n);

//void timer_quickstort()
#endif
