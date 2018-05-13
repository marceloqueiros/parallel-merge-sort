#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "omp.h" 

#define MAX_SIZE 10000 //number of elements

// function to generate an array
void generate_list(int * x, int n) {
  int i,j = MAX_SIZE;
   for (i = 0; i < n; i++){
      x[i] = j;
      j--;
   }
}

// merge function
void merge(int * X, int n, int * tmp) {
   int i = 0;
   int j = n/2;
   int ti = 0;

   while (i<n/2 && j<n) {
      if (X[i] < X[j]) {
         tmp[ti] = X[i];
         ti++; i++;
      } else {
         tmp[ti] = X[j];
         ti++; j++;
      }
   }
   while (i<n/2) { /* finish up lower half */
      tmp[ti] = X[i];
      ti++; i++;
   }
      while (j<n) { /* finish up upper half */
         tmp[ti] = X[j];
         ti++; j++;
   }
   memcpy(X, tmp, n*sizeof(int));

}


void mergeSortSeq(int arr[], int size, int temp[]){
    if (size < 2){ 
        return;
    }
        // Sort first and second halves
        mergeSortSeq(arr, size/2, temp);
        mergeSortSeq(arr+size/2, size-size/2, temp);
 
        merge(arr, size,temp);
    
} 


void printArray(int A[], int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
 
int main(int argc, char * argv[]){

    int *data = malloc(MAX_SIZE*sizeof(int));
    int *temp = malloc(MAX_SIZE*sizeof(int));
    int n = MAX_SIZE;

    double start,stop;

    printf("Given array is \n");
    generate_list(data, n);
    printArray(data, n);

    start = omp_get_wtime();
        mergeSortSeq(data, n, temp);    
    stop = omp_get_wtime();
    
    printf("\nSorted array is \n");
    printArray(data, n);
    printf("\nMergeSort Time: %f\n",(stop-start));
    free(temp);
    free(data);
    return 0;    

    
}