#include <stdio.h>
#include <string.h>

struct Fecha
{
    int dia, mes, anio;
};

struct Evento
{
    char titulo[40];
    struct Fecha fecha;
};

enum
{
    salir,
    ingresar,
    consultar,
};

void limpiar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    struct Evento eventos[100];
    struct Evento evento; // Arreglo para almacenar hasta 100 eventos
    int num_eventos = 0;  // Contador para el número de eventos
    int seleccion, continuar = 1;
    FILE *eventosArchivo;
    char linea[80];

    while (continuar)
    {
        printf("\n\t---Menú--- \n\t1. Ingresar evento\n\t2. Consultar eventos\n\t0. Salir\n\t   Elija su seleccion: ");

        if (scanf("%d", &seleccion) != 1)
        {
            seleccion = -1;
        }
        limpiar_buffer();

        switch (seleccion)
        {
        case ingresar:
            evento.fecha.dia = 0;
            evento.fecha.mes = 0;
            evento.fecha.anio = 0;

            printf("\n\t   Evento: ");
            fgets(evento.titulo, sizeof(evento.titulo), stdin);
            evento.titulo[strcspn(evento.titulo, "\n")] = 0; // quita el \n

            while (!(evento.fecha.dia >= 1 && evento.fecha.dia <= 31)) // Bucle de validación para el día
            {
                printf("\t   Día [dd]: ");
                scanf("%02i", &evento.fecha.dia);
                limpiar_buffer(); // Limpiar el búfer después de cada scanf
            }
            while (!(evento.fecha.mes >= 1 && evento.fecha.mes <= 12)) // Bucle de validación para el mes
            {
                printf("\t   Mes [mm]: ");
                scanf("%02i", &evento.fecha.mes);
                limpiar_buffer();
            }
            while (!(evento.fecha.anio >= 1900 && evento.fecha.anio <= 2100)) // Bucle de validación para el año
            {
                printf("\t   Año [aaaa]: ");
                scanf("%i", &evento.fecha.anio);
                limpiar_buffer();
            }
            printf("\n\t   ----------------------------➢\n\t   [%02i/%02i/%i] - %s\n\t   ----------------------------➢\n", evento.fecha.dia, evento.fecha.mes, evento.fecha.anio, evento.titulo);

            eventosArchivo = fopen("eventos.txt", "a");
            if (eventosArchivo != NULL)
            {
                fprintf(eventosArchivo, "\nEvento: %s\nFecha: %02i/%02i/%i", evento.titulo, evento.fecha.dia, evento.fecha.mes, evento.fecha.anio);
                fclose(eventosArchivo);
            }
            break;
        case consultar:
            struct Evento evento;

            eventosArchivo = fopen("eventos.txt", "r");
            if (eventosArchivo == NULL)
            {
                printf("No se pudo abrir el archivo");
                return 1;
            }
            printf("\n");
            while (fgets(linea, sizeof(linea), eventosArchivo) != NULL) // lectura por línea
            {
                if (strstr(linea, "Evento: ") != NULL)
                {
                    sscanf(linea, "Evento: %[^\n]", evento.titulo); // extraer el evento
                }
                else if (strstr(linea, "Fecha: ") != NULL)
                {
                    sscanf(linea, "Fecha: %02i/%02i/%04i", &evento.fecha.dia, &evento.fecha.mes, &evento.fecha.anio); // extraer la fecha

                    printf("\t   [%02i/%02i/%04i] - ", evento.fecha.dia, evento.fecha.mes, evento.fecha.anio); // impresión, se sobre escriben datos porque ya esxite el archivo
                    printf("%s\n", evento.titulo);
                }
            }

            fclose(eventosArchivo);

            break;
        case salir:
            printf("\n\t   ➤ Archivo generado: eventos.txt\n");
            printf("\n\t     Saliendo del programa\n");
            continuar = 0;
            break;
        default:
            printf("\n\t   Ingrese una opción válida del menú\n");
            break;
        }
    }

    return 0;
}
