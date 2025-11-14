#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "inventario.txt"

typedef struct
{
    int id;
    char nombre[40];
    float precio;
    int stock;
} Producto;

void guardarInventario(Producto *inventario, int cantidad);
Producto *cargarInventario(Producto *inventario, int *cantidad);
void agregarProducto(Producto **inventario, int *cantidad);
void buscarProducto(Producto *inventario, int cantidad);
void mostrarInventario(Producto *inventario, int cantidad);

int main()
{
    Producto *inventario = NULL;
    int cantidad = 0;
    int opcion;

    inventario = cargarInventario(inventario, &cantidad);

    do
    {
        printf("\n---Menu INVENTARIO---\n");
        printf("1) Agregar producto\n");
        printf("2) Buscar producto\n");
        printf("3) Mostrar inventario\n");
        printf("4) Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            agregarProducto(&inventario, &cantidad);
            guardarInventario(inventario, cantidad);
            break;
        case 2:
            buscarProducto(inventario, cantidad);
            break;
        case 3:
            mostrarInventario(inventario, cantidad);
            break;
        case 4:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida, vuelva a intentarlo.\n");
        }

    } while (opcion != 4);

    free(inventario);
    return 0;
}

void agregarProducto(Producto **inventario, int *cantidad)
{
    *inventario = realloc(*inventario, (*cantidad + 1) * sizeof(Producto));
    if (*inventario == NULL)
    {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    Producto *nuevo = &(*inventario)[*cantidad];

    printf("Ingrese ID del producto: ");
    scanf("%d", &nuevo->id);
    getchar();

    printf("Ingrese nombre del producto: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0;

    printf("Ingrese precio:$");
    scanf("%f", &nuevo->precio);

    printf("Ingrese stock: ");
    scanf("%d", &nuevo->stock);

    (*cantidad)++;

    printf("Producto guardado: ID= %d | %s | $%.2f\n",
           nuevo->id, nuevo->nombre, nuevo->precio);
}

void buscarProducto(Producto *inventario, int cantidad)
{
    if (cantidad == 0)
    {
        printf("No hay ese producto.\n");
        return;
    }

    int opcion;
    printf("Buscar por:\n1)ID\n2)Nombre:\nIngrese 1 o 2: ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 1)
    {
        int id;
        printf("Ingrese ID: ");
        scanf("%d", &id);
        for (int i = 0; i < cantidad; i++)
        {
            if (inventario[i].id == id)
            {
                printf("Encontrado: ID= %d | %s | $%.2f | stock= %d\n",
                       inventario[i].id, inventario[i].nombre,
                       inventario[i].precio, inventario[i].stock);
                return;
            }
        }
    }
    else if (opcion == 2)
    {
        char nombre[40];
        printf("Ingrese nombre del producto: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = 0;
        for (int i = 0; i < cantidad; i++)
        {
            if (strcasecmp(inventario[i].nombre, nombre) == 0)
            {
                printf("Producto encontrado: ID= %d, %s, $%.2f, stock= %d\n",
                       inventario[i].id, inventario[i].nombre,
                       inventario[i].precio, inventario[i].stock);
                return;
            }
        }
    }

    printf("Producto no encontrado.\n");
}

void mostrarInventario(Producto *inventario, int cantidad)
{
    if (cantidad == 0)
    {
        printf("Inventario vacío.\n");
        return;
    }

    printf("\n--- Inventario ---\n");
    for (int i = 0; i < cantidad; i++)
    {
        printf("ID= %d | %-20s | $%.2f | Stock= %d\n",
               inventario[i].id, inventario[i].nombre,
               inventario[i].precio, inventario[i].stock);
    }
}

void guardarInventario(Producto *inventario, int cantidad)
{
    FILE *f = fopen(ARCHIVO, "w");
    if (f == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++)
    {
        fprintf(f, "ID: %d | Nombre del producto: %s | Precio:$%.2f | Stock: %d\n",
                inventario[i].id, inventario[i].nombre,
                inventario[i].precio, inventario[i].stock);
    }

    fclose(f);
}

Producto *cargarInventario(Producto *inventario, int *cantidad)
{
    FILE *f = fopen(ARCHIVO, "r");
    if (f == NULL)
        return inventario;

    Producto temp;
    while (fscanf(f, "ID: %d | Nombre del producto: %s | Precio: %.2f | Stock: %d\n",
                  &temp.id, temp.nombre, &temp.precio, &temp.stock) == 4)
    {
        inventario = realloc(inventario, (*cantidad + 1) * sizeof(Producto));
        inventario[*cantidad] = temp;
        (*cantidad)++;
    }

    fclose(f);
    return inventario;
}