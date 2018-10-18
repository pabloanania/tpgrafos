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
#include <stdbool.h>

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


void pause_screen();
void generar_grafo(vertex *p);
void mostrar(vertex *p);
void mostrar_body(v_data *p);
int calcular_cantidad_vertices(vertex *p);
int calcular_cantidad_aristas(vertex *p);
int calcular_grados_vertice(vertex *v);
bool grafo_es_valido(vertex *p);
bool grafo_es_completo(vertex *p);
bool grafo_es_regular(vertex *p);
bool grafo_es_simple(vertex *p);
bool tiene_aristas_paralelas(vertex *p);
bool tiene_bucles(vertex *p);
void mostrar_grados_cada_vertice(vertex *p);
void selector_opcion(vertex *p);


int main()
{
    vertex *primero = NULL;
    primero = (vertex*) malloc(sizeof(vertex));

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
        printf("2) Obtener cantidad de vertices\n");
        printf("3) Obtener cantidad de aristas\n");
        printf("4) Mostrar los grados de cada vertice\n");
        printf("5) Determinar si el grafo es valido\n");
        printf("6) Determinar si el grafo es completo\n");
        printf("7) Determinar si el grafo es regular\n");
        printf("8) Determinar si el grafo es simple\n");
        printf("0) Salir\n");
        scanf("%d", &opcion);
        system("cls");

        switch (opcion){
            case 1:
                mostrar(p);
                pause_screen();
                break;
            case 2:
                printf("\nCantidad de vertices: %d\n", calcular_cantidad_vertices(p));
                pause_screen();
                break;
            case 3:
                printf("\nCantidad de aristas: %d\n", calcular_cantidad_aristas(p));
                pause_screen();
                break;
            case 4:
                mostrar_grados_cada_vertice(p);
                pause_screen();
                break;
            case 5:
                printf(grafo_es_valido(p) ? "El grafo es valido\n" : "El grafo NO es valido\n");
                pause_screen();
                break;
            case 6:
                printf(grafo_es_completo(p) ? "El grafo es completo\n" : "El grafo NO es completo\n");
                pause_screen();
                break;
            case 7:
                printf(grafo_es_regular(p) ? "El grafo es regular\n" : "El grafo NO es regular\n");
                pause_screen();
                break;
            case 8:
                printf(grafo_es_simple(p) ? "El grafo es simple\n" : "El grafo NO es simple\n");
                pause_screen();
                break;
        }
    }while(opcion != O_SALIR);
}

void pause_screen(){
    printf("\n");
    system("pause");
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

int calcular_cantidad_vertices(vertex *p){
    int vertices = 0;

    while (p->sig != NULL){
        vertices++;
        p = p->sig;
    }

    return vertices;
}

int calcular_cantidad_aristas(vertex *p){
    int diagonal_actual = 0;
    int cantidad_aristas = 0;
    v_data *vdata_actual;

    while (p->sig != NULL){
        vdata_actual = p->data;
        while (vdata_actual->sig != NULL){
            if (vdata_actual->vertice >= diagonal_actual)
                cantidad_aristas++;

            vdata_actual = vdata_actual->sig;
        }
        p = p->sig;
        diagonal_actual++;
    }

    return cantidad_aristas;
}

void mostrar_grados_cada_vertice(vertex *p){
    int mayor = 0;
    int grados;

    while (p->sig != NULL){
        grados = calcular_grados_vertice(p);
        printf("Los grados del vertice %d son: %d\n", p->vertice, grados);

        if (grados > mayor)
            mayor = p->vertice;

        p = p->sig;
    }

    printf("El vertice de mayor grado es: %d\n", mayor);
}

int calcular_grados_vertice(vertex *v){
    int grados = 0;
    v_data *vdata_actual = v->data;

    while (vdata_actual->sig != NULL){
        grados++;
        vdata_actual = vdata_actual->sig;
    }

    return grados;
}

bool grafo_es_valido(vertex *p){
    int sum_grados = 0;
    int aristas = calcular_cantidad_aristas(p);

    while (p->sig != NULL){
        sum_grados+=calcular_grados_vertice(p);
        p=p->sig;
    }

    if (sum_grados == 2 * aristas)
        return true;
    else
        return false;
}

bool grafo_es_completo(vertex *p){
    int aristas = calcular_cantidad_aristas(p);
    int vertices = calcular_cantidad_vertices(p);
    int calculo = (vertices*(vertices-1))/2;

    if (aristas == calculo)
        return true;
    else
        return false;
}

bool grafo_es_regular(vertex *p){
    int grado = -1;
    bool regular = true;

    while (p->sig != NULL){
        if (grado == -1)
            grado = calcular_grados_vertice(p);
        else if (calcular_grados_vertice(p) != grado)
            regular = false;

        p = p->sig;
    }

    return regular;
}

bool grafo_es_simple(vertex *p){
    if (!tiene_aristas_paralelas(p) && !tiene_bucles(p))
        return true;
    else
        return false;
}

bool tiene_aristas_paralelas(vertex *p){
    bool paralelas = false;
    int vertice;
    v_data *vdata_actual;
    v_data *vdata_comparador;

    while (p->sig != NULL){
        vdata_actual = p->data;
        while (vdata_actual->sig != NULL){
            vdata_comparador = vdata_actual->sig;
            while (vdata_comparador->sig != NULL){
                if (vdata_actual->vertice == vdata_comparador->vertice)
                    paralelas = true;

                vdata_comparador = vdata_comparador->sig;
            }
            vdata_actual = vdata_actual->sig;
        }
        p = p->sig;
    }

    return paralelas;
}

bool tiene_bucles(vertex *p){
    bool bucles = false;
    int vertice;
    v_data *vdata_actual;

    while (p->sig != NULL){
        vertice = p->vertice;
        vdata_actual = p->data;
        
        while (vdata_actual->sig != NULL){
            if (vdata_actual->vertice == vertice)
                bucles = true;

            vdata_actual = vdata_actual->sig;
        }
        p = p->sig;
    }

    return bucles;
}

void grafo_es_bipartito(vertex *p){
    // Guarda con que vertices NO se conecta v0
    v_data *conjunto_inicial = (v_data*) malloc(sizeof(v_data));
    conjunto_inicial->vertice = p->vertice;
    // Guarda el primer vertice con el que se conecta v0 y que grupo generan los que no se conectan con este vertice
    v_data *conjunto_partito = (v_data*) malloc(sizeof(v_data));
    conjunto_partito->vertice = p->data->vertice;
}

void generar_no_conexiones(int vertice_inicial, vertex *p, v_data *nc){
    int cantidad_vertices = calcular_cantidad_vertices(p);
    v_data *nc_actual = nc;
    v_data *nc_anterior = NULL;
    v_data *nc_comparable = nc;
    v_data *vdata_actual;
    vertex *v_actual;
    int coincidencias = 0;

    // Genero una lista enlazada con todos los vertices que uso para guardar los que no tiene conexion
    for (int i=0; i<cantidad_vertices; i++){
        nc_actual->vertice = i;
        nc_actual->sig = (v_data*) malloc(sizeof(v_data));
        nc_actual = nc_actual->sig;
    }
    nc_actual->vertice = NULL;
    nc_actual->sig = -1;

    // "Rebobino" el vector
    nc_actual = nc;

    // Comparo con la lista con cuales no se conecta, si hay conexion los elimino de nc
    while (nc_actual->sig != NULL){
        // Me posiciono en el vertice actual
        while (v_actual->vertice != vertice_comparable)
            v_actual = v_actual->sig;
        
        // Compara por todos los vdata del vertice actual a ver si hay coincidencias
        vdata_actual = v_actual->data;
        while (vdata_actual->sig != NULL){
            if (vdata_actual->vertice == vertice_comparable)
                coincidencias++;
        }

        // Si hay alguna coincidencia elimina el vdata de la lista enlazada nc
        if (coincidencias > 0){
            nc_anterior->sig = nc_actual->sig;
        }
        
        // Avanzo
        nc_anterior = nc_actual;
        nc_actual = nc_actual->sig;
        vertice_comparable = nc_actual->vertice;
    }
}

void generar_grafo(vertex *p){
    FILE *archivo;
    int limite = 0;
    int columna_actual = 0;
    int fila_actual = 0;
    int leido;
    char char_leido;
    vertex *v_actual = NULL;

    // Leo hasta el final del archivo para obtener la cantidad de lineas = cantidad de columnas = cantidad de vertices a generar
    archivo = fopen("matriz.txt","r");
    while((char_leido = fgetc(archivo)) != EOF)
        if (char_leido == '\n')
            limite++;

    rewind(archivo);

    // Genero conexiones iniciales de punteros (lista enlazada)
    v_actual = p;
    v_data *vdata_actual;
    vdata_actual = (v_data*) malloc(sizeof(v_data));
    v_actual->data = vdata_actual;
    v_actual->vertice = 0;

    // Leo el archivo int por int con ayuda de acumuladores de fila y columna
    while (fila_actual != limite){
        // Avanza por cada columna (generación de v_data)
        if (columna_actual != limite){
            // Genera una struct por cada adyacencia
            fscanf(archivo, "%d", &leido);
            for (int i=0; i<leido; i++){
                vdata_actual->vertice = columna_actual;
                vdata_actual->sig = (v_data*) malloc(sizeof(v_data));
                vdata_actual = vdata_actual->sig;
            }
            columna_actual++;
        // Si finaliza la fila actual genera nuevos vertex
        }else{
            fila_actual++;
            columna_actual = 0;

            // Cierra lista enlazada de datos
            vdata_actual->sig = NULL;
            vdata_actual->vertice = -1;

            v_actual->sig = (vertex*) malloc(sizeof(vertex));
            v_actual = v_actual->sig;
            v_actual->vertice = fila_actual;
            vdata_actual = (v_data*) malloc(sizeof(v_data));
            v_actual->data = vdata_actual;
            
            // Finalizó la carga
            if (fila_actual == limite){
                v_actual->sig = NULL;
                v_actual->vertice = -1;
            }
        }
    }
    
    fclose (archivo);
}