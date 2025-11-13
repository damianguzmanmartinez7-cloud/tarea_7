#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *numeros;
    numeros = fopen("numeros.txt", "r");

    if (numeros == NULL)
    {
        printf("No se pudo abrir el documento\n");
        return 1;
    }

    float *arrNumeros = NULL, leido, suma = 0.0, max, min;
    int capacidad = 0, i = 0;

    if (fscanf(numeros, "%f", &leido) == 1) // primer número para inicar min, max y arrNumeros
    {
        arrNumeros = (float *)malloc(sizeof(float)); // tamaño de [0]
        if (arrNumeros == NULL)
        {
            printf("No se asignó la memoria\n");
            fclose(numeros);
            return 1;
        }
        arrNumeros[0] = leido;
        min = leido;
        max = leido;
        suma = leido;
        i++;
        capacidad = 1;
    }
    else
    {
        printf("El archivo está vacío o no contiene numeros.\n");
        fclose(numeros);
        return 0;
    }

    while (fscanf(numeros, "%f", &leido) == 1) // leer los siguientes números
    {
        if (i >= capacidad)
        {
            capacidad *= 2; // aumentar la capacidad de arrNumeros
            float *temp = (float *)realloc(arrNumeros, capacidad * sizeof(float));

            if (temp == NULL)
            {
                printf("No se asignó la memoria\n");
                free(arrNumeros);
                fclose(numeros);
                return 1;
            }
            arrNumeros = temp;
        }

        arrNumeros[i] = leido; // guaradar números del txt en arrNumeros

        if (leido > max) // Encontrar mínumo y máximo
        {
            max = leido;
        }
        else if (leido < min)
        {
            min = leido;
        }

        suma += leido;
        i++;
    }

    printf("Archivo: numeros.txt → ");
    for (int j = 0; j < i; j++)
    {
        printf(" %.1f ", arrNumeros[j]);
    }
    printf("\nTotal de numeros = %d\n", i);
    printf("Promedio = %.1f, Minimo = %.1f, Maximo = %.1f \n", suma / i, min, max);

    free(arrNumeros);
    fclose(numeros);

    return 0;
}
