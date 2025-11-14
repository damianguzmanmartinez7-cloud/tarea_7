#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[40];
    float calificaciones[3];
    float promedio;
} Alumno;

float calculopromedio(float calificaciones[], int n)
{
    float suma = 0;
    for (int i = 0; i < n; i++)
        suma += calificaciones[i];
    return suma / n;
}

int main()
{
    Alumno *alumnos = NULL;
    int cantidad = 0;
    char continuar;

    do
    {
        cantidad++;
        alumnos = realloc(alumnos, cantidad * sizeof(Alumno));
        if (alumnos == NULL)
        {
            printf("Error al asignar memoria\n");
            return 1;
        }

        Alumno *actual = &alumnos[cantidad - 1];

        printf("\nNombre del alumno: ");
        getchar();
        fgets(actual->nombre, sizeof(actual->nombre), stdin);
        actual->nombre[strcspn(actual->nombre, "\n")] = '\0';

        printf("Calificaciones (3): \n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f", &actual->calificaciones[i]);
        }

        actual->promedio = calculopromedio(actual->calificaciones, 3);

        FILE *archivo = fopen("alumnos.txt", "a");
        if (archivo == NULL)
        {
            printf("Error al abrir el archivo\n");
            free(alumnos);
            return 1;
        }

        fprintf(archivo, "Nombre: %s\n", actual->nombre);
        fprintf(archivo, "Calificaciones: %.2f %.2f %.2f\n",
                actual->calificaciones[0],
                actual->calificaciones[1],
                actual->calificaciones[2]);
        fprintf(archivo, "Promedio: %.2f\n\n", actual->promedio);
        fclose(archivo);

        printf("[Guardado en alumnos.txt]\n");

        printf("¿Desea agregar otro alumno? (s/n): ");
        getchar();
        scanf("%c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    printf("\nLista de alumnos\n");
    for (int i = 0; i < cantidad; i++)
    {
        printf("Nombre del alumno: %s\n", alumnos[i].nombre);
        printf("Calificaciones: %.2f %.2f %.2f\n",
               alumnos[i].calificaciones[0],
               alumnos[i].calificaciones[1],
               alumnos[i].calificaciones[2]);
        printf("Promedio: %.2f\n\n", alumnos[i].promedio);
    }

    free(alumnos);
    return 0;
}
