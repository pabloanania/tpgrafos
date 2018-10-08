/*
MULTILISTA PARA REPRESENTAR GRAFOS
p->***->a
    |
    d
    |
   ...
*/

#include <stdio.h>
#include <stdlib.h>

#define O_SALIR     0

// Nodo "header" - Uno por cada vértice
typedef struct vertex{
    int vertice;                    // Nombre del vertice
    struct vertex *sig;             // Vertice siguiente. Orden en que yo quiera poner a los vértices del grafo (ej. A-B-C-D)
    struct v_data *data;              // Body con información sobre siguiente conexión o null si no tiene
}vertex;

// Nodo "body" - Información sobre las adyacencias(conexiones). Uno por cada conexión de cada vértice
typedef struct v_data{
    int vertice;                    // Vértice al que se conecta
    struct v_data *sig;             // Body con información sobre siguiente conexión o null si no tiene
}v_data;


void generar_grafo(vertex *p);
void mostrar(vertex *p);
void mostrar_body(v_data *p);
void selector_opcion(vertex *p);


int main()
{
    vertex *primero = NULL;

    generar_grafo(primero);
    selector_opcion(primero);

    return 0;
}

void selector_opcion(vertex *p){
    int opcion;

    do{
        system("cls");
        printf("Seleccione una opcion:\n");
        printf("1) Mostrar el grafo \n");
        printf("2) Validar el grafo\n");
        printf("0) Salir\n");
        scanf("%d", &opcion);

        switch (opcion){
            case 1:
                mostrar(p);
                break;
            case 2:
                break;
            case 3:
                break;
        }
    }while(opcion != O_SALIR);
}

void mostrar(vertex *p){
    printf("\nVertice #%d se conecta a nodos:\n", p->vertice);
    mostrar_body(p->data);
    // Debe ver si el siguiente no tiene más data que mostrar...
    if (p->sig->sig != NULL)
        mostrar(p->sig);
}

void mostrar_body(v_data *p){
    printf("%d\t", p->vertice);
    if (p->sig->sig != NULL)
        mostrar_body(p->sig);
}

void generar_grafo(vertex *p){
    FILE *archivo;
    int limite = 0;
    int columna_actual = 0;
    int fila_actual = 0;
    int leido;
    char char_leido;
    vertex *v_actual;
    v_actual = (vertex*) malloc(sizeof(vertex));
    v_data *vdata_actual;
    vdata_actual = (v_data*) malloc(sizeof(v_data));
    v_actual->vertice = 0;

    // Leo hasta el final del archivo para obtener la cantidad de lineas = cantidad de columnas = cantidad de vertices a generar
    archivo = fopen("matriz.txt","r");
    printf("Archivo abierto \n");
    while((char_leido = fgetc(archivo)) != EOF)
        if (char_leido == '\n')
            limite++;

    rewind(archivo);

    // Genero conexiones de punteros iniciales
    v_actual->data = vdata_actual;
    p = v_actual;

    // Leo el archivo int por int con ayuda de acumuladores de fila y columna
    while (!feof (archivo)){
        // Avanza por cada columna (generación de v_data)
        if (columna_actual != limite){
            // Lee vertices adyacentes y los guarda
            fscanf(archivo, "%d", &vdata_actual->vertice);
            vdata_actual->sig = (v_data*) malloc(sizeof(v_data));
            vdata_actual = vdata_actual->sig;
        // Si finaliza la fila actual genera nuevos vertex
        }else{
            fila_actual++;
            columna_actual = 0;
            vdata_actual->sig = NULL;
            vdata_actual->vertice = -1;

            // Genera nuevo vertex
            if (fila_actual != limite){
                v_actual->sig = (vertex*) malloc(sizeof(vertex));
                v_actual = v_actual->sig;
                v_actual->vertice = fila_actual;
            // Finalizó la carga
            }else{
                v_actual->sig = NULL;
                v_actual->vertice = -1;
            }
        }

        columna_actual++;
    }
    
    fclose (archivo);
}