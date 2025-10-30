#include <omp.h>
#include <stdio.h>

int main(void){
        float INICIO, FIN, tiempof;
        int numThreads;

        INICIO = omp_get_wtime();
        #pragma omp parallel
        {
        int thread = omp_get_thread_num();
        printf("Wnas mundo, desde el hilo: %d\n", thread);
                #pragma omp master
                {
                numThreads = omp_get_num_threads();
                }
        }
        FIN = omp_get_wtime();
        tiempof = FIN - INICIO;
        printf("Tiempo de ejecucion con %d hilos: %.12f.\n", numThreads, tiempof);
        return 0;
}
