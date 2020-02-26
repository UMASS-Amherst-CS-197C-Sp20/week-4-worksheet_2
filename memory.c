#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_arr(int *arr, int n);
int** build_2darr(int n);
void print_2darr(int** arr, int n);

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "cs197c");
   printf("String = %s,  Address = %u\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, "computer science 197c");
   printf("String = %s,  Address = %u\n", str, str);

   int* arr;

   // malloc() allocate the memory for 5 integers
   // containing garbage values
   arr = (int*)malloc(5 * sizeof(int)); // 5*4bytes = 20 bytes
   print_arr(arr, 5);
   // calloc() allocate the memory for 5 integers and
   // set 0 to all of them
   arr = (int*)calloc(5, sizeof(int));
   print_arr(arr, 5);


   /* Deallocate allocated memory */
   free(str);
   free(arr);

   //TODO: remove the comment below after finished the functions
   /*
   int** arr_2d = build_2darr(5);
   print_2darr(arr_2d);
   */

   return(0);
}

void print_arr(int *arr, int n){
   for(int i=0; i<n; i++){
      printf("%d\n", *(arr+i));
   }
}

// using memory allocation function to build a 2d arr
// that the length of each subarray is its index+1
// and fill the subarray with its index
// for example for n = 3
/*
   [[0]
    [1,1]
    [2,2,2]
   ]
*/
int** build_2darr(int n){
   //TODO
  // Int *arr is a pointer to int array (which is the memory address)
//*(arr) is the actual value of the first element in the int array
//*(arr+1) is the actual value of the second element in the array
  int** arr = (int**) malloc(n * sizeof(int*)); 
  for (int i = 0; i < n; i++){
    *(arr+i) = createID(i);
    
  }

 
   	
  return arr;	
}

 int* createID(int n){       //makes a 1D int array, fills that array in with n - 1 (n =size of array);
  int* arr = (int*) malloc((n+1) * sizeof(int));
  for (int i = 0; i < n; i++){
    *(arr+i) = n;
    
  }
  return arr;
 }      
// print the 2d array you build previously
void print_2darr(int** arr, int n){
   //TODO
  
	
}
