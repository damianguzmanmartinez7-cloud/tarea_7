#include <stdio.h>
#include <stdlib.h> //libreria para el uso de malloc

int main()
{
    int n, m;

    printf("Ingrese cantidad de filas: ");
    scanf("%d", &n);
    printf("Ingrese cantidad de columnas: ");
    scanf("%d", &m);

    // reservamos memoria para asignar la memoria dinámica
    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **S = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        A[i] = (int *)malloc(m * sizeof(int));
        B[i] = (int *)malloc(m * sizeof(int));
        S[i] = (int *)malloc(m * sizeof(int));
    }

    // Valores de la matriz A
    printf("\n--- MATRIZ A ---\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    // valores de la matriz B
    printf("\n--- MATRIZ B ---\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    // suma de las matrices
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            S[i][j] = A[i][j] + B[i][j];
        }
    }

    // Guardar en archivo
    FILE *archivo = fopen("matriz_suma.txt", "w"); // abre el archivo, y w es la funcion para la escritura
    fprintf(archivo, "Suma de las matrices:\n");   // fprintf escribe el resultado pero en el archivo
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fprintf(archivo, "%d ", S[i][j]);
        }
        fprintf(archivo, "\n");
    }
    // cerramos el archivo, para evitar la pérdida de información.
    fclose(archivo);

    printf("\n Resultado -> matriz_suma.txt :)\n");

    // Liberación de memoria con free
    for (int i = 0; i < n; i++)
    {
        // liberamos las filas de todas las matrices
        free(A[i]);
        free(B[i]);
        free(S[i]);
    }
    // liberamos los punteros
    free(A);
    free(B);
    free(S);

    return 0;
}
