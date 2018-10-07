# To do:
* Ingresar la matriz de adyacencia por archivo
    * Probarlo
* Pasar la data de la matriz de adyacencia a la struct generada (vértices y adyacencias)
* Calcular la cantidad de vértices
* Calcular la cantidad de aristas
* Calcular los grados de un vertice
* Determinar si el grafo es válido
* Informar cuál es el vértice de mayor grado
* Determinar si es un grafo completo
    * aristas=(verticesx(vertices-1))/2
* Determinar si es un grafo bipartito
    * Verificar desde el vertex 0 con cuales no se conecta:
        * Generar una nueva lista enlazada (conjunto) de v_data, una por cada vertice
        * Variable ultimo_recorrido guarda el index del recorrido actualmente
        * Tomo el primer vertex del grafo y recorro su v_data, en cada conexión elimino del conjunto incial el v_data con el int vertice correspondiente
        * Al finalizar, busco en el conjunto el siguiente a recorrer (el primero que sea distinto a ultimo_recorrido)
        * Repito la operacion de eliminar nodos del conjunto hasta que el nodo recorrido sea el ultimo del conjunto
        * El resultado es una lista enlazada de v_data con los vertices con los cuales no se conecta vertex 0 (conjunto)
    * Verificar desde el primer vertex con el cual tiene conexion vertex 0 con cuales no se conecta (partir desde el primer v_data de vertex 0)
        * Repetir el algoritmo de vertex 0 pero con el primero conectado
        * El resultado es el conjunto 2
    * Comparar las listas enlazadas con dos for verificando cuantas coincidencias hay de int vertice recorriendo los v_data
        * Si hay al menos una coincidencia -> NO ES BIPARTITO
        * Si no hay coincidencias -> ES BIPARTITO
* Determinar si es grafo regular (todos los v el mismo gr)
    * Recorrer uno por uno los vértices y aplicar funcion calculo de gr
    * Guardar resultado en variable
    * Repetir con el siguiente vértice, si es distinto -> FAILED
    * Si termina y no hay diferencias -> OK
* Determinar si es un grafo plano
    * Leyenda "Asumiendo que el grafo es conexo..."
    * Chequea si la cantidad de vertices es de al menos 3
    * Verifica con la función anterior si es bipartito
        * Si lo es aplica: aristas<=2xvertices-4
        * Si no lo es aplica: aristas<=3xvertices-6
* Determinar si es un grafo simple
    * Función verificadora de aristas paralelas:
        * Guarda el int vertice al que se conecta el primer v_data
        * Recorre los v_data del vértice comparando el int guardado en el anterior
        * Si el int no coincide en ningun caso continúa con el v_data siguiente y así hasta terminar el vértice
        * Repite esto con cada vértice, si no hay coincidencias -> OK
        * A la primer coincidencia -> FAILED
    * Función verificadora de bucles:
        * Guarda el int vertice del struct vertex y lo compara con el int vertice de cada v_data que posee
        * Si hay alguna coincidencia -> FAILED
        * De lo contrario sigue con todos los vertices, si no hubo coincidencias -> OK
