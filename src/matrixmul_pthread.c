#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

sem_t semaphore;
int N,**A,**B,**C,numberOfThread;
struct workRange{
    int start;
    int finish;
};
void* matrixmul(void* x);
void creatematrix();



//main
int main(int a, char *b[])
{
    struct timeval begin1, end1;
    pthread_t* thread_array;
    struct workRange* range;
    
    numberOfThread =atoi(b[1]);
    N=atoi(b[2]);
    creatematrix();
    
    gettimeofday(&begin1, 0);

    thread_array = (pthread_t*) malloc (numberOfThread*sizeof(pthread_t));
    range = (struct workRange*) malloc (numberOfThread*sizeof(struct workRange));
    int initial=0,i;
    int times=N/numberOfThread;
    for(i=0;i<numberOfThread;i++){
        range[i].start=initial;
        range[i].finish=initial+times;
        initial+=times;
    }

    for (i = 0; i < numberOfThread; i++)  
      pthread_create(&thread_array[i], NULL,
         matrixmul, &range[i]); 
          
    for (i= 0; i < numberOfThread; i++) 
     pthread_join(thread_array[i], NULL);

    gettimeofday(&end1,0);

    long seconds1 = end1.tv_sec - begin1.tv_sec;
    long microseconds1 = end1.tv_usec - begin1.tv_usec;
    double totalTime1 = seconds1 + microseconds1*1e-6;
    printf("Time taken by Matrix Multiplication: %.3f seconds.\n", totalTime1);

    return 0;
}

//define matrices
void creatematrix(){
    int i,j;
    A = (int **)malloc(N * sizeof(int *));
    B= (int **)malloc(N * sizeof(int *));
    C= (int **)malloc(N * sizeof(int *));

    for (i=0; i<N; i++){
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }
           
    for(i=0;i<N;i++)
     for(j=0;j<N;j++)
      { 
        A[i][j]=rand();
        B[i][j]=rand();
        C[i][j]=0;
      }
}

//multiply matrices
void* matrixmul(void* x)
{
    struct workRange* t=(struct workRange*)x;
    int i, j, k,temp=0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k =t->start ; k < t->finish; k++)
            {temp += A[i][k] * B[k][j];}
         sem_wait(&semaphore);
         C[i][j]+= temp;
         sem_post(&semaphore);    
        }
      }
  return NULL;
}

