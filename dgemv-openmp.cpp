#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {
   #pragma omp parallel
   {
      int nthreads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
      printf("my_dgemv(): Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
      // need sum out here 
      for (int i = 0; i < n; i++){ // row
         int rowOffset = i * n; 
         double sum = 0.0;
         #pragma omp for reduction(+:sum)
         for (int j = 0; j < n; j++){ // column
            sum += A[rowOffset + j] * x[j];
         }
         y[i] += sum;
      }

      //printf("my_dgemv(): For actual timing runs, please comment out these printf() and omp_get_*() statements. \n");
   }

   // insert your dgemv code here. you may need to create additional parallel regions,
   // and you will want to comment out the above parallel code block that prints out
   // nthreads and thread_id so as to not taint your timings

   // parallel region = #pragma omp parallel {}
   // all code inside {} executes in parallel
   // each of the A[i] * x computations can be done seperately, in parallel

   // reduction clause can make summations on multiple threads more efficient
   // reduction (op: list)
   // pragma omp parallel for reduction (+:sum)
}

