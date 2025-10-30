#include<omp.h>
#include<stdio.h>

float aproxIntegral(float a, float b, int n, float (*f)(float));
float f(float x){ return 4 / (1 + x*x);}

int main(){
        float aproxPi = aproxIntegral(0, 1, 1000000, f);
        printf("Aproximación de Pi:%f\n", aproxPi);
        return 0;
}

float aproxIntegral(float a, float b, int n, float (*f)(float)){
        float suma = 0, h = (b-a)/n, INICIO, FINAL;
        INICIO  = omp_get_wtime();
        #pragma omp parallel for reduction(+:suma)
        for (int i = 0; i < n; i++){
                suma += f(a + i*h + h/2); // Punto medio
        }
        FINAL = omp_get_wtime();
        printf("Tiempo: %f\n", FINAL - INICIO);
        return suma * h;
}
