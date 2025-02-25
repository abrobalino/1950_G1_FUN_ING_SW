#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void menu();
// Estructura para los productos
struct Producto {
    char product[50];
    int cantidad;
};

// Arreglo de productos
struct Producto producto[100];
int prod = 8;


// Cargar productos iniciales
void cargarproductos() {
    strcpy(producto[0].product, "001.Pimiento"); producto[0].cantidad = 50;
    strcpy(producto[1].product, "002.Cebolla"); producto[1].cantidad = 30;
    strcpy(producto[2].product, "003.Ajo"); producto[2].cantidad = 20;
    strcpy(producto[3].product, "004.Pepino"); producto[3].cantidad = 40;
    strcpy(producto[4].product, "005.Fideos Don Vitorio"); producto[4].cantidad = 100;
    strcpy(producto[5].product, "006.lb Arroz(Super Extra)"); producto[5].cantidad = 200;
    strcpy(producto[6].product, "007.lb Harina"); producto[6].cantidad = 150;
    strcpy(producto[7].product, "008.lb Azucar"); producto[7].cantidad = 90;
}

// Funci�n para la lista de productos

void lista_productos() {
    for (int i = 0; i < prod; i++) {
        printf(" %d: [Producto: %s] (Cantidad: %d)\n", i + 1, producto[i].product, producto[i].cantidad);
    }
}


// Funci�n para agregar productos
void agregar_producto() {
    if (prod < 100) {
        char nuevo_producto[50];
        char confirmar;

        printf("Ingrese el nombre del nuevo producto: ");

        fgets(nuevo_producto, 50, stdin);

        nuevo_producto[strcspn(nuevo_producto, "\n")] = '\0';


        for (int i = 0; nuevo_producto[i] != '\0'; i++) {
            if (isdigit(nuevo_producto[i])) {
                printf("Error: El nombre del producto no puede contener numeros.\n");
                return;
            }
        }

        printf("Esta seguro de que desea agregar el producto '%s' (V/F): ", nuevo_producto);
        scanf(" %c", &confirmar);
        confirmar = toupper(confirmar);

        if (confirmar == 'V') {
            sprintf(producto[prod].product, "%03d.%s", prod + 1, nuevo_producto);
            prod++;
            printf("Producto agregado exitosamente.\n");
        } else if (confirmar == 'F') {
            printf("No se agrego el producto.\n");
        } else {
            printf("Accion no valida. \n");
        }
    } else {
        printf("No se pueden agregar mas productos. Capacidad maxima alcanzada.\n");
    }
}


// Funci�n para buscar productos
void buscar_producto() {
    char termino[50];
    int encontrado = 0;

    printf("Ingrese el nombre o fragmento del producto a buscar: ");
    getchar();
    fgets(termino, 50, stdin);

    termino[strcspn(termino, "\n")] = '\0';

    printf("\nResultados de busqueda:\n");
    for (int i = 0; i < prod; i++) {
        if (strstr(producto[i].product, termino) != NULL) {
            printf(" %d: [Producto: %s] (Cantidad: %d)\n", i + 1, producto[i].product, producto[i].cantidad);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontraron productos que coincidan con '%s'.\n", termino);
    }
}


// Funci�n para entrada de productos
void entrada_producto() {
    char termino[50];
    int cantidad;
    int encontrado = 0;
    char confirmar;

    printf("Ingrese el codigo o nombre del producto para aumentar su cantidad: ");
    getchar();
    fgets(termino, 50, stdin);
    termino[strcspn(termino, "\n")] = '\0';

    if (strlen(termino) == 0) {
        printf("Error: No ingreso ningun valor. Intente nuevamente.\n");
        return;
    }

    for (int i = 0; i < prod; i++) {
        if (strstr(producto[i].product, termino) != NULL) {
            printf("\nProducto encontrado: %s (Cantidad actual: %d)\n", producto[i].product, producto[i].cantidad);
            printf("Ingrese la cantidad a agregar: ");
            if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                printf("Error: Cantidad invalida. Solo se aceptan numeros positivos.\n");
                while (getchar() != '\n');
                return;
            }

            printf("Esta seguro de que desea agregar %d a '%s' (V/F): ", cantidad, producto[i].product);
            scanf(" %c", &confirmar);
            confirmar = toupper(confirmar);

            if (confirmar == 'V') {
                producto[i].cantidad += cantidad;
                printf("\nCantidad actualizada. Nueva cantidad: %d\n", producto[i].cantidad);
            } else if (confirmar == 'F') {
                printf("\n No se realizo ningun cambio.\n");
            } else {
                printf("\nOpcion no valida..\n");
            }

            encontrado = 1;
            break;
        }}if (!encontrado) {
        printf("\nNo se encontro el producto con el codigo o nombre '%s'.\n", termino);
    }
}


// Funci�n para salida de productos
void salida_producto() {
    char termino[50];
    int cantidad;
    int encontrado = 0;
    char confirmar;

    printf("Ingrese el codigo o nombre del producto para disminuir su cantidad: ");
    getchar();
    fgets(termino, 50, stdin);
    termino[strcspn(termino, "\n")] = '\0';

    for (int i = 0; i < prod; i++) {
        if (strstr(producto[i].product, termino) != NULL) {
            printf("\nProducto encontrado: %s (Cantidad actual: %d)\n", producto[i].product, producto[i].cantidad);
            printf("Ingrese la cantidad a retirar: ");
            if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                printf("Error: Cantidad invalida.\n");
                while (getchar() != '\n');
                return;
            }

            printf("Esta seguro de que desea retirar %d de '%s' (V/F): ", cantidad, producto[i].product);
            scanf(" %c", &confirmar);
            confirmar = toupper(confirmar);

            if (confirmar == 'V') {
                if (cantidad <= producto[i].cantidad) {
                    producto[i].cantidad -= cantidad;
                    printf("\nCantidad actualizada. Nueva cantidad: %d\n", producto[i].cantidad);
                } else {
                    printf("\nCantidad insuficiente en inventario.\n");
                }
            } else if (confirmar == 'F') {
                printf("\nNo se realizo ningun cambio.\n");
            } else {
                printf("\nOpcion no valida.\n");
            }

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNo se encontro el producto con el codigo o nombre '%s'.\n", termino);
    }
}

// Funci�n para eliminar productos
void eliminar_producto() {
    char termino[50];
    int encontrado = -1;
    char confirmar;

    printf("Ingrese el nombre o codigo del producto a eliminar: ");
    getchar();
    fgets(termino, 50, stdin);
    termino[strcspn(termino, "\n")] = 0;

    for (int i = 0; i < prod; i++) {
        if (strstr(producto[i].product, termino) != NULL) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        // Preguntar si est� seguro de eliminar el producto
        printf("Producto encontrado: %s. Esta seguro de que desea eliminarlo (V/F): ", producto[encontrado].product);
        scanf(" %c", &confirmar);
        confirmar = toupper(confirmar);

        if (confirmar == 'V') {
            printf("Producto eliminado: %s\n", producto[encontrado].product);
            for (int i = encontrado; i < prod - 1; i++) {
                strcpy(producto[i].product, producto[i + 1].product);
                producto[i].cantidad = producto[i + 1].cantidad;
            }
            prod--;
        } else if (confirmar == 'F') {
            printf("Accion cancelada. No se elimino ningun producto.\n");
        } else {
            printf("Accion no valida.\n");
        }
    } else {
        printf("No se encontr� un producto que coincida con '%s'.\n", termino);
    }
}

//Funcion para guardar el archivo

void guardar() {
    // Abre el archivo en modo escritura
    FILE *archivo = fopen("productos.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < prod; i++) {
        fprintf(archivo, "%d: [Producto: %s] [Cantidad: %d]\n", i + 1, producto[i].product, producto[i].cantidad);
    }
    fclose(archivo);

    printf("Lista de productos guardada exitosamente en 'productos.txt'.\n");
}


//Funcion para regresar al menu
void regresar_menu() {
    char opcion;
    do {
        printf("\nDesea volver al menu principal (V/F): ");
        scanf(" %c", &opcion);
        opcion = toupper(opcion);

        if (opcion == 'V') {
            menu();
            break;
        } else if (opcion == 'F') {
            printf("Saliendo del programa. �Hasta luego!\n");
            exit(0);
        } else {
            printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while (1);
}
void menu() {
    int opc = 0;
    char buffer[256];
    int valid_input;

    // Cargar productos iniciales
    cargarproductos();

    do {
        // Men� principal
        printf("\n***** Seleccione una opcion: *****\n");
        printf("1. Visualizar la lista de productos disponibles\n");
        printf("2. Agregar productos\n");
        printf("3. Busqueda de productos\n");
        printf("4. Entrada de productos\n");
        printf("5. Salida de productos\n");
        printf("6. Eliminar productos\n");
        printf("7. Generar reporte\n");
        printf("8. Salir\n");
        printf("Ingrese su opcion: ");

        // Limpiar el buffer antes de leer
        fflush(stdin);

        // Leer la entrada como string
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Intentar convertir la entrada a n�mero
            valid_input = sscanf(buffer, "%d", &opc);

            // Verificar si la entrada es v�lida y est� en el rango correcto
            if (valid_input != 1 || opc < 1 || opc > 8) {
                printf("\nOpcion no valida. Por favor, ingrese un numero del 1 al 8.\n");
                continue;  // Volver al inicio del ciclo
            }

            // Manejo de opciones del menu
            switch (opc) {
                case 1:
                    lista_productos();
                    regresar_menu();
                    break;
                case 2:
                    agregar_producto();
                    break;
                case 3:
                    buscar_producto();
                    break;
                case 4:
                    entrada_producto();
                    break;
                case 5:
                    salida_producto();
                    break;
                case 6:
                    eliminar_producto();
                    break;
                case 7:
                    guardar();
                    regresar_menu();
                    break;
                case 8:
                    printf("Saliendo del programa. �Hasta luego!\n");
                    break;
            }
        } else {
            printf("\nError al leer la entrada. Por favor, intente nuevamente.\n");
            continue;
        }
    } while (opc != 8);
}


// Men� principal
int main() {
menu();
    return 0;
}

