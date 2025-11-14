#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanoPalabra 100

int compare(const void *a, const void *b)
{
    const char **strA = (const char **)a;
    const char **strB = (const char **)b;
    return strcmp(*strA, *strB); // compara cadenas
}

int main()
{
    char **arrPalabras = NULL;       // arreglo palabras totales
    char tempPalabra[tamanoPalabra]; // arreglo de palabras en ingreso
    int capacidad = 0, numeroNombres = 0;

    printf("Entrada, (finalice con 0):\n");

    while (scanf("%s", tempPalabra) == 1 && strcmp(tempPalabra, "0") != 0)
    {
        if (numeroNombres >= capacidad)
        {
            capacidad = (capacidad == 0) ? 1 : capacidad * 2;
            char **tempArr = realloc(arrPalabras, capacidad * sizeof(char *)); // redimensión del la matriz de punteros

            if (tempArr == NULL)
            {
                printf("No se pudo reasignar memoria para las arrPalabras.\n");
                for (int j = 0; j < numeroNombres; j++)
                {
                    free(arrPalabras[j]);
                }
                free(arrPalabras); // liberar memoria
                return 1;
            }
            arrPalabras = tempArr;
        }

        arrPalabras[numeroNombres] = malloc(strlen(tempPalabra) + 1); // agregar espacio para la nueva palabra
        if (arrPalabras[numeroNombres] == NULL)
        {
            printf("No se pudo asignar memoria para una palabra.\n");
            for (int j = 0; j < numeroNombres; j++)
            {
                free(arrPalabras[j]);
            }
            free(arrPalabras);
            return 1;
        }
        strcpy(arrPalabras[numeroNombres], tempPalabra); // copiar nombre al arrPalabras
        numeroNombres++;
    }

    qsort(arrPalabras, numeroNombres, sizeof(char *), compare); // ordenar las arrPalabras alfabéticamente con Quicksort

    printf("\nSalida → nombres.txt:\n");
    for (int j = 0; j < numeroNombres; j++)
    {
        printf("%s \n", arrPalabras[j]);
    }
    printf("\n");

    FILE *nombresArchivo;
    nombresArchivo = fopen("nombres.txt", "w");
    if (nombresArchivo != NULL)
    {
        for (int j = 0; j < numeroNombres; j++)
        {
            fprintf(nombresArchivo, "%s\n", arrPalabras[j]); // transcribir el arrPalabras en el txt,
        }
        fclose(nombresArchivo);
    }

    for (int j = 0; j < numeroNombres; j++) // liberar la memoria
    {
        free(arrPalabras[j]);
    }
    free(arrPalabras);

    return 0;
}
