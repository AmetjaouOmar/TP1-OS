/*  On a essayé d'exécuter le programme en utilisant le multithreading , 
on a constaté que le temps d'exécution de programme augmente proportionnellement avec le nombre de threading 
Dans ce cas: 
        1 thread => 111148 ns,
        2 thread => 173949 ns,
        4 thread => 247355 ns,
        100 thread => 12882363 ns,
     Donc l'utilisation d'un seule thread nous a donné le meilleur temps d'exécution
*/

#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>
#include <time.h>

#define size 4
#define thread_size 100

typedef unsigned int index;
typedef unsigned int length;

int tableau[size] = { 2, 27, 3, 49};
int longueur = sizeof(tableau) / sizeof(int);
int temp_val = 0;

void merge(index start, index middle, index final);
void merge_sort(index start, index final);

void merge_sort(index start, index final) {
  if(start < final) {
    index middle = floor((start + final) / 2);
    merge_sort(start, middle);
    merge_sort(middle+1, final);
    merge(start, middle, final);
  }
}

void merge(index start, index middle, index final) {
  length countL = middle - start + 1;
  int *arrayL = malloc(countL * sizeof(int));
  index currentL, currentR;
  for(currentL = 0; currentL < countL; currentL++)
    arrayL[currentL] = tableau[start + currentL];

  length countR = final - middle;
  int* arrayR = malloc(countR * sizeof(int));
  for(currentR = 0; currentR < countR; currentR++)
    arrayR[currentR] = tableau[middle + 1 + currentR];

  currentL = 0;
  currentR = 0;
  index current;
  for(current = start; current <= final && currentL < countL && currentR < countR; current++) {
    if(arrayL[currentL] <= arrayR[currentR]) {
      tableau[current] = arrayL[currentL];
      currentL++;
    } else { // arrayL[currentL] > arrayR[currentR]
      tableau[current] = arrayR[currentR];
      currentR++;
    }
  }

  // If <arrayL> was completely consumed, copy the remainder of <arrayR> over the remainder of <array>
  if(currentL >= countL)
    while(currentR < countR) {
      tableau[current] = arrayR[currentR];
      current++;
      currentR++;
    }

  // If <arrayR> was completely consumed, copy the remainder of <arrayL> over the remainder of <array>
  if(currentR >= countR)
    while(currentL < countL) {
      tableau[current] = arrayL[currentL];
      current++;
      currentL++;
    }

  free(arrayL);
  free(arrayR);
}

void* threading_sort(void* arg){
   int set_val = temp_val++;
   int start = set_val * floor(size / 4);
   int final = (set_val + 1) * floor(size / 4) - 1;
   index middle = start + floor((start + final) / 2);
   if (start < final) {
        merge_sort(start, middle);
        merge_sort(middle + 1, final);
        merge(start, middle, final);
   }
}

void show(int array[], length count) {
  for(index i = 0; i < count; i++)
    printf("%d ", array[i]);
  printf("\n");
}

long int nanos_between ( struct timespec *final , struct timespec *start ){
    time_t seconds = final->tv_sec - start->tv_sec ;
    long int nanoseconds = final->tv_nsec - start->tv_nsec ;
    return seconds * 1e9 + nanoseconds ;
}


int main(){
    struct timespec start , final;

    // Show the table before sorting
    show(tableau, longueur);

    // Get the start time
    clock_gettime(CLOCK_REALTIME , &start);

    // Creating a table of threads to use 
    pthread_t P_TH[thread_size];

    // Creating the threads and waiting them to finish
    for(int i = 0; i < thread_size; i++){
        pthread_create(&P_TH[i], NULL, threading_sort, (void*)NULL);
    }
    for(int i = 0; i < thread_size; i++){
        pthread_join(P_TH[i], NULL);
    }
    merge(0, (size / 2 - 1) / 2, size / 2 - 1);
    merge(size / 2, size/2 + (size-1-size/2)/2, size - 1);
    merge(0, (size - 1)/2, size - 1);

    // Get the final time
    clock_gettime(CLOCK_REALTIME , &final);

    // Show the number of threads using and the time execution
    printf("number of threads --> %d / time elapsed : %ld ns \n" , thread_size, nanos_between(&final , &start));
    
    // Show the table after sorting
    show(tableau, longueur);

    return 0;
}
