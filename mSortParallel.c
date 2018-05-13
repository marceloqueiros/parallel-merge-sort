#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "omp.h" 

#define MAX_SIZE 10000//number of elements

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


void mergeSortPara(int arr[], int size, int temp[] , int threads){

    if (threads > 1){
        
        // Sort first and second halves
            #pragma omp task
            mergeSortPara(arr, size/2, temp, threads/2);

            #pragma omp task 
            mergeSortPara((arr+size/2), (size-size/2), (temp+size/2) , (threads-threads/2)); 
        
        #pragma omp taskwait
        merge(arr, size, temp);
    }else if (threads == 1){
        mergeSortSeq(arr,size,temp);
    }
}


void printArray(int A[], int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}


//function to check if array is sorted to be called after merge Sort
int isSorted(int a[], int size){
	int i,r = 0;

	for(i=0;i<size-1;i++){
		if(a[i]>a[i+1]){
			r = 1;
			printf("a[%d]=%d,a[%d]=%d \n",i,a[i],i+1,a[i+1]);
			break;
		}
	}
	return r;
}


int main(int argc , char * argv[]){

    int threads;

    int *data = malloc(MAX_SIZE*sizeof(int));
    int *temp = malloc(MAX_SIZE*sizeof(int));
    int n = MAX_SIZE;

    double start,stop;

    printf("Given array is \n");
    generate_list(data, n);
    printArray(data, n);

    start = omp_get_wtime();
        #pragma omp parallel
        {
        	threads = omp_get_num_threads();
            #pragma omp single
                mergeSortPara(data, n, temp ,threads);    
        } 
    stop = omp_get_wtime();
    
    printf("\nSorted array is \n");
    printArray(data, n);

    int r = isSorted(data,n);
    if(r != 0){
    	printf("O array não está ordenado");
    }

    printf("\nMergeSort Time: %f\n",(stop-start));
    free(temp);
    free(data);
    return 0;
}