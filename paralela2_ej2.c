#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 100

void inicializar_matriz(int n, int matriz[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand() % 10 + 1;
        }
    }
}

void imprimir_matriz(int n, int matriz[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 100;
    int A[n][n], B[n][n], C[n][n], D[n][n];

    srand(42);

    double start_time = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            inicializar_matriz(n, A);
        }
        #pragma omp section
        {
            inicializar_matriz(n, B);
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] = 0;
                    for (int k = 0; k < n; k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }

        #pragma omp section
        {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    D[i][j] = A[i][j] + B[i][j];
                }
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);
    return 0;
}
