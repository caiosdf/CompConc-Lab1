#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  2
#define N 10000

//declaração do vetor
int vec[N];
//função executada pelas threads auxiliares
void *Incrementa(void *arg){
    int val = * (int*)arg;
    for(int x = val; x < N; x += NTHREADS){
        vec[x]++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid_sistema[NTHREADS];
    int thread;
    int tid_local[NTHREADS];
    //inicialização do vetor
    printf("vetor inicial -> ");
    for(int x = 0; x < N; x++){
        vec[x] = x;
        printf("%d ", vec[x]);
    }
    printf("\n\n\n");
    //criação das threads
    for(thread = 0; thread < NTHREADS; thread++){
        tid_local[thread] = thread;
        if(pthread_create(&tid_sistema[thread], NULL, Incrementa, (void*) &tid_local[thread])){
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }
    //o fluxo principal aguarda pelo termino de execução das threads auxiliares
    for (thread=0; thread<NTHREADS; thread++) {
        if (pthread_join(tid_sistema[thread], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        } 
    }
    printf("vetor incrementado -> ");
    for(int x = 0; x < N; x++){
        printf("%d ", vec[x]);
    }
    pthread_exit(NULL);
}