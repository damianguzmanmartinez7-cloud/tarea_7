#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente
{
    int id;
    // arreglos de caracteres
    char nom[40];
    char mail[40];
};
/// @brief agrega al nuevo cliente al archivo de texto
void alta()
{
    struct Cliente c; // declara la variable local donde guardaremos los datos ingresados
    FILE *f;          // puntero direccionado al archivo donde se guardan los clientes

    f = fopen("clientes.txt", "a"); // abre el archivo para agregar datos al final
    if (f == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    // solicita los datos del cliente//
    printf("ID: ");
    scanf("%d", &c.id);
    getchar(); // limpia el salto de linea ppara que fgets lo lea correctamente

    printf("Nombre: ");
    fgets(c.nom, sizeof(c.nom), stdin);
    c.nom[strcspn(c.nom, "\n")] = '\0';

    printf("Correo: ");
    fgets(c.mail, sizeof(c.mail), stdin);
    c.mail[strcspn(c.mail, "\n")] = '\0';

    fprintf(f, "%d,%s,%s\n", c.id, c.nom, c.mail); // escribe la linea del archivo separando por comas (CSV)
    fclose(f);                                     // cierra el archivo, guardando los cambios

    printf("Cliente agregado: ID=%d, %s, %s\n", c.id, c.nom, c.mail);
}
// busqueda de los clientes por id//
void consulta()
{
    struct Cliente c;
    FILE *f;
    int idBus, ok = 0; // variable boleana, nos indica si el archivo se encontro

    f = fopen("clientes.txt", "r"); // abre el texto en modo lectura
    if (f == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    printf("ID a buscar: ");
    scanf("%d", &idBus); // busca el usuario por id

    // lee el entero, lee hasta 39 caracteres antes de una coma, lee hasta el fin de linea
    // se asegura de que los datos leidos sean 3
    while (fscanf(f, "%d,%39[^,],%39[^\n]\n", &c.id, c.nom, c.mail) == 3)
    {
        if (c.id == idBus)
        {
            // compara c.id con c,non y si coinciden imprime 1
            printf("Cliente encontrado: ID=%d, %s, %s\n", c.id, c.nom, c.mail);
            ok = 1;
            break; // dejamos de buscar
        }
    }

    if (!ok)
        printf("No se encontro el cliente con ID=%d\n", idBus);

    fclose(f); // ciera el archivo
}

// funcion para eliminar un cliente guardando a los demas en un archivo temporal
void eliminar()
{
    struct Cliente c;
    FILE *f, *temp;
    int idDel, elim = 0; // id que se desea eliminar
    // temp.txt sera el archivo temporal donde se guardan los datos que ya no se eliminan
    f = fopen("clientes.txt", "r");
    temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL)
    {
        printf("Error con los archivos\n");
        return;
    }
    // cuando compara los datos de id con idDel y resultan diferentes  los elimina
    printf("ID a eliminar: ");
    scanf("%d", &idDel);

    while (fscanf(f, "%d,%39[^,],%39[^\n]\n", &c.id, c.nom, c.mail) == 3)
    {
        if (c.id != idDel)
            // si el id no coincide con el que se quiere eliminar, lo copiamos
            fprintf(temp, "%d,%s,%s\n", c.id, c.nom, c.mail);
        else
            elim = 1; // el cliente fue eliminado
    }

    fclose(f);
    fclose(temp);
    // borramos el archivo anterior y renombramos el temporal
    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (elim)
        printf("Cliente eliminado: ID=%d\n", idDel);
    else
        printf("No se encontro el cliente con ese ID\n");
}
// muestra el menu y lee las elecciones del usuario
int main()
{
    int op;

    do
    {
        printf("\n MENU CLIENTE: \n");
        printf("1. Alta de cliente\n");
        printf("2. Consultar cliente\n");
        printf("3. Eliminar cliente\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);
        getchar();
        // segun la opcion elegida llamamos  a la funcion correspondiente
        switch (op)
        {
        case 1:
            alta();
            break;
        case 2:
            consulta();
            break;
        case 3:
            eliminar();
            break;
        case 4:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida\n");
        }
        // el menu se repite hasta que se elija 4
    } while (op != 4);

    return 0;
}
