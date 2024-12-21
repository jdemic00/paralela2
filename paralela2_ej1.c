#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void inicializar_matriz(int n, int *matriz) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i * n + j] = rand() % 10 + 1;
        }
    }
}

void imprimir_matriz(int n, int *matriz) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i * n + j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 100;
    int *A = (int *)malloc(n * n * sizeof(int));
    int *B = (int *)malloc(n * n * sizeof(int));
    int *C = (int *)malloc(n * n * sizeof(int));
    int *D = (int *)malloc(n * n * sizeof(int));

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
                    C[i * n + j] = 0;
                    for (int k = 0; k < n; k++) {
                        C[i * n + j] += A[i * n + k] * B[k * n + j];
                    }
                }
            }
        }

        #pragma omp section
        {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    D[i * n + j] = A[i * n + j] + B[i * n + j];
                }
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);

    free(A);
    free(B);
    free(C);
    free(D);

    return 0;
}
