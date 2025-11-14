#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// constantes
#define MAX 100
#define MAXG 10

// variables para los datos del grupo
typedef struct
{
    char letra; // grupo
    int suma;   // de calificaciones
    int cant;   // alumnos
} Grupo;

int main()
{
    // apertura del archivo.txt
    FILE *f;
    f = fopen("grupos.txt", "r");
    /// r es la funcion de fopen para solo leer el archivo
    if (f == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return 1;
        // comprobamos que el archivo exista y el programa lo pueda leer
    }

    Grupo g[MAXG];
    int ng = 0; // ng representa el numero de grupos
    char linea[MAX];
    // lee cada linea del archivo (hasta la última)
    while (fgets(linea, MAX, f))
    {
        linea[strcspn(linea, "\n")] = '\0'; // quitamos el salto de linea para marcar el fin de la cadena

        // se descompone en tokens por cada coma en la línea //

        char *p = strtok(linea, ","); // retorna un puntero al inicio del primer token dentro de linea
        if (p == NULL)
            continue; // primer token letra
        char grupo = p[0];

        p = strtok(NULL, ","); // cuando la cadena no contiene tokens válidos
        if (p == NULL)
            continue;
        char *nombre = p; // segundo token alumno

        p = strtok(NULL, ","); // tercer token calificación
        if (p == NULL)
            continue;
        int nota = atoi(p); // atoi es la funcion que convierte la cadena p a entero

        int enc = 0; // variable para saber si el grupo ya existe
        for (int i = 0; i < ng; i++)
        { // ng es el contador de datos que hay en el arreglo
            if (g[i].letra == grupo)
            {
                g[i].suma += nota; // acumular la nota
                g[i].cant++;       // aumentar canidad de alumnos
                enc = 1;           // el grupo fue encontrado
                break;             // sale del bucle
            }
        }
        // si el grupo no existe, crea un nuevo registro
        if (enc == 0 && ng < MAXG)
        { /// uso de variables boleanas
            g[ng].letra = grupo;
            g[ng].suma = nota;
            g[ng].cant = 1;
            ng++;
        }
    }

    fclose(f);

    // recorre todos los grupos registrados en el arreglo g[]
    for (int i = 0; i < ng; i++)
    { /// ng indica los grupos diferentes ya registrados
        float prom = (float)g[i].suma / g[i].cant;
        printf("Grupo %c -> Promedio %.1f\n", g[i].letra, prom);
    }

    return 0;
}