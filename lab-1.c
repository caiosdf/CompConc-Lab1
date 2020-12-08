#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  2
#define N 20

//declaração do vetor
int vec[N];
//função executada pelas threads auxiliares
void *Incrementa(void *arg){
    int x;
    int val = * (int*)arg;
    int inicio = val*N/NTHREADS;
    int fim = (val + 1)*N/NTHREADS;
    for(x = inicio; x < fim; x++){
        vec[x]++;
        printf("%d\n", vec[x]);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid_sistema[NTHREADS];
    int thread;
    int x;
    int tid_local[NTHREADS];
    //inicialização do vetor
    for(x = 0; x < N; x++){
        vec[x] = x;
        printf("start -> %d\n", vec[x]);
    }
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
    pthread_exit(NULL);
}