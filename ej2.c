#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUMNOS 100
#define MAX_NOMBRE 100

typedef struct
{
    char nombre[MAX_NOMBRE];
    float promedio;
} Alumno;

int main()
{
    FILE *archivo;
    Alumno alumnos[MAX_ALUMNOS];
    int count = 0;
    char linea[200];

    archivo = fopen("alumnos.txt", "r");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo))
    {
        if (strncmp(linea, "Nombre:", 7) == 0)
        {
            // Leer nombre
            strcpy(alumnos[count].nombre, linea + 8);
            // Eliminar salto de línea final
            alumnos[count].nombre[strcspn(alumnos[count].nombre, "\n")] = '\0';
        }
        else if (strncmp(linea, "Promedio:", 9) == 0)
        {
            // Leer promedio
            sscanf(linea + 10, "%f", &alumnos[count].promedio);
            count++;
        }
    }

    fclose(archivo);

    float suma = 0.0;
    float maxPromedio = 0.0;
    char mejorAlumno[MAX_NOMBRE] = "";

    printf("Nombre de los alumnos y sus promedios:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s -> %.2f\n", alumnos[i].nombre, alumnos[i].promedio);
        suma += alumnos[i].promedio;
        if (alumnos[i].promedio > maxPromedio)
        {
            maxPromedio = alumnos[i].promedio;
            strcpy(mejorAlumno, alumnos[i].nombre);
        }
    }

    float promedioGeneral = suma / count;

    printf("\nPromedio del grupo: %.2f\n", promedioGeneral);
    printf("Mejor alumno: %s\n", mejorAlumno);

    return 0;
}