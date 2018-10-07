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
    struct body *data;              // Body con información sobre siguiente conexión o null si no tiene
}vertex;

// Nodo "body" - Información sobre las adyacencias(conexiones). Uno por cada conexión de cada vértice
typedef struct v_data{
    int vertice;                    // Vértice al que se conecta
    struct v_data *sig;             // Body con información sobre siguiente conexión o null si no tiene
}v_data;


void generar_grafo(vertex *p);
void mostrar(vertex *p);
void mostrar_body(v_data *p);
void crear(vertex *p);
void crear_body(v_data *p);
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
        printf("1) Ingresar nodos\n");
        printf("2) Eliminar nodos\n");
        printf("3) Mostrar el grafo\n");
        printf("0) Salir\n");
        scanf("%d", &opcion);

        switch (opcion){
            case 1:
                crear(p);
                break;
            case 2:
                break;
            case 3:
                mostrar(p);
                printf("\n");
                system("pause");
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

void crear(vertex *p){
    printf("Ingrese el numero del vertice (0 para terminar):\n");
    scanf("%d", &p->vertice);

    // Esto es para terminar la carga
    if (p->vertice==0)
        p->sig=NULL;
    // Crea un nuevo vértice
    else{
        p->data=(v_data*) malloc(sizeof(v_data));
        crear_body(p->data);
        p->sig=(vertex*) malloc(sizeof(vertex));
        crear(p->sig);
    }
}

void crear_body(v_data *p){
    printf("Ingrese el numero del vertice al cual se conecta (0 para terminar):\n");
    scanf("%d", &p->vertice);

    // Esto es para terminar la carga
    if (p->vertice==0)
        p->sig=NULL;
    // Crea una nueva conexión
    else{
        p->sig=(v_data*) malloc(sizeof(v_data));
        crear_body(p->sig);
    }
}

void calcularMultiplicacion(int dim_x, int dim_y, int mat[][dim_y], int mat_m[][dim_x], int mat_r[][dim_y]){
    int i;
    int j;
    int k;

    printf("Calculando multiplicacion entre matrices\n");

    for (i=0; i<dim_y; i++){
        for (j=0; j<dim_x; j++){
            mat_r[i][j] = 0;
            for (k=0; k<dim_x; k++){
                mat_r[i][j] += mat[k][j] * mat_m[i][k];
            }
        }
    }
}

void generar_grafo(vertex *p){
    FILE *archivo;
    int limite = 0;
    int columna_actual = 0;
    int fila_actual = 0;
    int leido;
    char char_leido;
    vertex v_actual = NULL;
    vertex v_anterior = NULL;
    v_data vdata_actual = NULL;
    v_data vdata_anterior = NULL;

    // Leo hasta el final del archivo para obtener la cantidad de lineas = cantidad de columnas = cantidad de vertices a generar
    while((char_leido = fgetc(archivo)) != EOF)
        if (ch == '\n')
            limite++;

    rewind(archivo);

    // Leo el archivo int por int con ayuda de acumuladores de fila y columna
    while (!feof (archivo)){
        // Lee vertices adyacentes y los guarda
        vdata_actual = (v_data*) malloc(sizeof(v_data));
        fscanf(archivo, "%d", vdata_actual->vertice);

        // En cada inicio de línea genero un nuevo vertex
        if (columna_actual == 0){
            v_actual = (vertex*) malloc(sizeof(vertex));
            v_actual->vertice = fila_actual;
            v_actual->data = vdata_actual;
        }

        columna_actual++;

        // Maneja el final de columnas y filas
        if (columna_actual == limite){
            fila_actual++;
            columna_actual = 0;
            vdata_actual->vertice = NULL;

            if (fila_actual == limite)
                v_actual->vertice == NULL;
        }
    }
    
    fclose (archivo);
}