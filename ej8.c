#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 100

int compare(const void *a, const void *b)
{
    const char **strA = (const char **)a;
    const char **strB = (const char **)b;
    return strcmp(*strA, *strB);
}

int main()
{
    char **palabras = NULL; // Arreglo de punteros a cadenas
    int capacidad = 0;      // Capacidad del arreglo de punteros
    int num_palabras = 0;   // Número de palabras leídas

    printf("Ingrese los nombres, finalice con 0 (seguido de Enter):\n");

    char temp_word[MAX_WORD_SIZE];
    while (scanf("%s", temp_word) == 1 && strcmp(temp_word, "0") != 0)
    {
        // Redimensionar el arreglo de punteros si es necesario
        if (num_palabras >= capacidad)
        {
            capacidad = (capacidad == 0) ? 1 : capacidad * 2;
            char **temp_arr = realloc(palabras, capacidad * sizeof(char *));

            if (temp_arr == NULL)
            {
                printf("Error: No se pudo reasignar memoria para las palabras.\n");
                // Liberar toda la memoria asignada hasta el momento
                for (int j = 0; j < num_palabras; j++)
                {
                    free(palabras[j]);
                }
                free(palabras);
                return 1;
            }
            palabras = temp_arr;
        }

        // Asignar memoria para la nueva palabra y copiarla
        palabras[num_palabras] = malloc(strlen(temp_word) + 1);
        if (palabras[num_palabras] == NULL)
        {
            printf("Error: No se pudo asignar memoria para una palabra.\n");
            // Liberar toda la memoria asignada hasta el momento
            for (int j = 0; j < num_palabras; j++)
            {
                free(palabras[j]);
            }
            free(palabras);
            return 1;
        }
        strcpy(palabras[num_palabras], temp_word);
        num_palabras++;
    }

    printf("\nPalabras ingresadas:\n");
    for (int j = 0; j < num_palabras; j++)
    {
        printf("%s ", palabras[j]);
    }
    printf("\n");

    // Ordenar las palabras usando qsort
    qsort(palabras, num_palabras, sizeof(char *), compare);

    printf("\nPalabras ordenadas alfabéticamente:\n");
    for (int j = 0; j < num_palabras; j++)
    {
        printf("%s ", palabras[j]);
    }
    printf("\n");

    // Escribir en un archivo (opcional)
    FILE *nombres_file;
    nombres_file = fopen("nombres.txt", "w");
    if (nombres_file != NULL)
    {
        for (int j = 0; j < num_palabras; j++)
        {
            fprintf(nombres_file, "%s\n", palabras[j]);
        }
        fclose(nombres_file);
        printf("\nLas palabras se han guardado en 'nombres.txt'.\n");
    }

    // Liberar toda la memoria asignada
    for (int j = 0; j < num_palabras; j++)
    {
        free(palabras[j]);
    }
    free(palabras);

    return 0;
}
