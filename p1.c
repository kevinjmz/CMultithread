#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

long long sum;
int arraySize;
int * prepareArray (int numberOfIndices);
void *computeSum(int *A, int startIndex, int numberOfIndices);
int * splitArray();
int numberOfThreads=0;
int numberOfIndices=0;
static int *A;
static int *splits;
int global_index=0;
pthread_mutex_t mutex;


int main(int argc, char *argv[]){
  pthread_attr_t attr;

  if (argc != 3) {
    printf ("You must enter the number of indices in the array and the number of threads");
    return -1;
  }

  if (atoi(argv[1]) < 0) {
      fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
      return -1;
  }
  numberOfIndices = atoi(argv[1]);
  numberOfThreads = atoi(argv[2]);

  A = malloc(numberOfIndices * sizeof(*A));
  splits = malloc((numberOfThreads*2) * sizeof(*splits));
  
  prepareArray(numberOfIndices);
  splitArray();
  
  pthread_t tid[numberOfThreads];
  
    for(int i=0; i<numberOfThreads; i++){
      int x=splits[i]-1;
      int y=splits[i+1];

      printf("call computesum with...x=%d ,y= %d\n",x,y);
      pthread_create(&tid[i], NULL,computeSum(A,x,y),NULL);
     
    }

    for( int i=0; i<numberOfThreads; i++){
      pthread_join(tid[i],NULL);
    }
    long average = sum/numberOfIndices;

    printf("Average: %ld",average);
  
    
}

int * prepareArray(int NumberOfIndices){
  srand(time(NULL));

  
  for(int i=0; i<NumberOfIndices; i++){
    A[i]=rand()%20;
     printf("%i ***\n ", *(A+i));
  }
  return A;
}

void  *computeSum(int *A, int EndIndex,int startIndex){
  int i;
  int taken=-1;
  
  for(i=startIndex; i<EndIndex; i++){
    // printf("%d,%d\n",startIndex,EndIndex);
    while(taken==1);
    taken=1;
    pthread_mutex_lock(&mutex);
    sum+= A[i];
    printf("%d\n",A[i]);
    // printf("sum %d\n",sum);
    pthread_mutex_unlock(&mutex);
    taken=-1;
  }
}

int * splitArray(){
    for(int i=numberOfIndices,j=0; i>=0; i=i-numberOfThreads,j++){
      splits[j]=i;
      //   printf("split -> %d\n",splits[j]);
  }
    return splits;
}

