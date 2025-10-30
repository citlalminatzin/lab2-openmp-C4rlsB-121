#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

float** crearMatriz(int filasNum, int colNum);
void liberarMatriz(float** matriz, int filasNum);
void prodMatriz_Static(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR, int chunkSize);
void prodMatriz_Dynamic(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR, int chunkSize);
void prodMatriz_Guided(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR, int chunkSize);
void prodMatriz_Collapse(int n, int m, int l, float** matrizA, float** matrizB, float** matruzR);
void prodMatriz_Secuencial(int n, int m, int l, float** matrizA, float** matrizB, float** matruzR);
void printMatriz(int filasNum, int colNum, float** matriz);

int main(){
        // Declaración de variables
        float inicio;
        float final;
        int chunkSize = 1;
        int n = 121;
        int m = 3000;
        int l = 70;
        float** matrizA = crearMatriz(n, m);
        float** matrizB = crearMatriz(m, l);
        float** matrizR = crearMatriz(n, n);

        // Inicializacion matrices
	#pragma omp parallel for collapse(2)
        for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			matrizA[i][j] = i + j;
		}
	}
	#pragma omp parallel for collapse(2)
        for (int i = 0; i < m; i++){
		for (int j = 0; j < l; j++){
			matrizB[i][j] = -i-j;
		}
	}

        // Mostrar
        //printf("-------------------------------------\nA= \n");
        //printMatriz(n, m, matrizA);
        //printf("-------------------------------------\nB= \n");
        //printMatriz(m, l, matrizB);
        //printf("-------------------------------------\nAB= \n");

        // Static
        printf("Static ---------------\n");
        inicio = omp_get_wtime();
        prodMatriz_Static(n, m, l, matrizA, matrizB, matrizR, chunkSize);
        final = omp_get_wtime();
        //printMatriz(n, l, matrizR);
        printf("Tiempo: %.9f\n", final - inicio);

        // Dynamic
        printf("Dynamic ---------------\n");
        inicio = omp_get_wtime();
        prodMatriz_Dynamic(n, m, l, matrizA, matrizB, matrizR, chunkSize);
        final = omp_get_wtime();
        //printMatriz(n, l, matrizR);
        printf("Tiempo: %.9f\n", final - inicio);

        // Guided
        printf("Guided ---------------\n");
        inicio = omp_get_wtime();
        prodMatriz_Guided(n, m, l, matrizA, matrizB, matrizR, chunkSize);
        final = omp_get_wtime();
        //printMatriz(n, l, matrizR);
        printf("Tiempo: %.9f\n", final - inicio);


        // Collapse
        printf("Collapse ---------------\n");
        inicio = omp_get_wtime();
        prodMatriz_Collapse(n, m, l, matrizA, matrizB, matrizR);
        final = omp_get_wtime();
        //printMatriz(n, l, matrizR);
        printf("Tiempo: %.9f\n", final - inicio);


	// Secuencial
        printf("----------------------------------------------\n");
        printf("----------------Secuencial ---------------\n");
        inicio = omp_get_wtime();
        prodMatriz_Secuencial(n, m, l, matrizA, matrizB, matrizR);
        final = omp_get_wtime();
        //printMatriz(n, l, matrizR);
        printf("Tiempo: %.9f\n", final - inicio);




        liberarMatriz(matrizA, n);
        liberarMatriz(matrizB, m);
        liberarMatriz(matrizR, n);
}

float** crearMatriz(int filasNum, int colNum){
        float**  matriz = malloc(filasNum * sizeof(float*));
        for (int i = 0; i < filasNum; i++){
                matriz[i]  = malloc(colNum * sizeof(float));
        }
        return matriz;
}

void liberarMatriz(float** matriz, int filasNum){
        #pragma omp parallel for
        for (int i = 0; i < filasNum; i++){
                free(matriz[i]);
        }
        free(matriz);
}

void prodMatriz_Static(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR, int chunkSize){
        #pragma omp parallel for schedule(static, chunkSize)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        matrizR[i][j] = 0;
                }
        }

        #pragma omp parallel for schedule(static, chunkSize)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        for (int k = 0; k < m; k++){
                                matrizR[i][j] += matrizA[i][k] * matrizB[k][j];
                        }
                }
        }

}

void prodMatriz_Dynamic(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR, int chunkSize){
        #pragma omp parallel for schedule(dynamic, chunkSize)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        matrizR[i][j] = 0;
                }
        }

        #pragma omp parallel for schedule(dynamic, chunkSize)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        for (int k = 0; k < m; k++){
                                matrizR[i][j] += matrizA[i][k] * matrizB[k][j];
                        }
                }
        }

}

void prodMatriz_Guided(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR, int chunkSize){
        #pragma omp parallel for schedule(guided, chunkSize)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        matrizR[i][j] = 0;
                }
        }

        #pragma omp parallel for schedule(guided, chunkSize)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        for (int k = 0; k < m; k++){
                                matrizR[i][j] += matrizA[i][k] * matrizB[k][j];
                        }
                }
        }

}

void prodMatriz_Collapse(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR){
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        matrizR[i][j] = 0;
                }
        }

        #pragma omp parallel for collapse(2)
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        for (int k = 0; k < m; k++){
                                matrizR[i][j] += matrizA[i][k] * matrizB[k][j];
                        }
                }
        }

}

void prodMatriz_Secuencial(int n, int m, int l, float** matrizA, float** matrizB, float** matrizR){
        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        matrizR[i][j] = 0;
                }
        }

        for (int i = 0; i < n; i++){
                for (int j = 0; j < l; j++){
                        for (int k = 0; k < m; k++){
                                matrizR[i][j] += matrizA[i][k] * matrizB[k][j];
                        }
                }
        }

}


void printMatriz(int filasNum, int colNum, float** matriz){
        for (int i = 0; i < filasNum; i++){
                printf("        ");
                for (int  j = 0; j < colNum; j++){
                        printf("%6.2f ", matriz[i][j]);
                }
        printf("\n");
        }
}
