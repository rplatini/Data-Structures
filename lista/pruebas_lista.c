#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


//PRUEBAS DE LA LISTA

void pruebas_lista_vacia(){
    printf("INICIO DE PRUEBAS DE CREAR LISTA\n");

    lista_t *lista = lista_crear();
    if(!lista) return;
    
    print_test("Prueba1: La lista fue creada", lista != NULL);
    print_test("Prueba2: La lista esta vacia", lista_esta_vacia(lista));
    print_test("Prueba4: No se puede ver primero en una lista vacia", !lista_ver_primero(lista));
    print_test("Prueba5: No se puede ver ultimo en una lista vacia", !lista_ver_primero(lista));
    print_test("Prueba6: No se puede borrar en una lista recien creada", !lista_borrar_primero(lista));

    lista_destruir(lista, free);
    printf("\n");
}


void pruebas_lista_algunos_elementos(){
    printf("INICIO DE PRUEBAS DE INSERTAR Y BORRAR ELEMENTOS\n");
    
    lista_t* lista = lista_crear();
    if(!lista) return;

    int numero = 10;
    char letra = 'A';
    char* cadena = "cadena de prueba";
    
    // pruebas de insertar elementos de distintos tipos de datos
    print_test("Prueba1: Se puede insertar un entero al principio de la lista", lista_insertar_primero(lista, &numero));
    print_test("Prueba2: El primer elemento de la lista es el insertado", lista_ver_primero(lista) == &numero);
    print_test("Prueba3: Se puede insertar un caracter al principio de la lista", lista_insertar_primero(lista, &letra));
    
    print_test("Prueba4: Se puede insertar una cadena al final de la lista", lista_insertar_ultimo(lista, cadena));
    print_test("Prueba5: El ultimo elemento de la lista es el insertado", lista_ver_ultimo(lista) == cadena);
    print_test("Prueba 6: El largo de la lista es correcto", lista_largo(lista) == 3);

    // pruebas de borrar elementos
    print_test("Prueba7: Se puede borrar el primer elemento de la lista", lista_borrar_primero(lista) == &letra);
    print_test("Prueba8: El largo de la lista es correcto luego de borrar", lista_largo(lista) == 2);
    
    lista_destruir(lista, NULL);
    printf("\n");   
}

// inserta tam elementos del vector en la lista, en la ultima posicion
void insertar_muchos_elementos(lista_t* lista, int arreglo[], int tam, bool* ok){
    *ok = true;
    for(int i = 0; i < tam; i++){
        arreglo[i] = i;
        bool auxiliar = lista_insertar_ultimo(lista, &arreglo[i]);
        if (!auxiliar){
            ok = false;
        }
    }
}

// elimina tam elementos de la lista
void borrar_muchos_elementos(lista_t* lista, int arreglo[], int tam, bool* ok){
    *ok = true;
    for(int i = 0; i < tam; i++){
        int *auxiliar = lista_borrar_primero(lista);
        if (*auxiliar != arreglo[i]){
            ok = false;
        }
    }
}

void pruebas_lista_volumen(){
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");
    lista_t *lista_vol = lista_crear();
    if(!lista_vol) return;

    int tam = 10000;
    int arreglo[10000];
    bool ok = true;

    // pruebas de insertar muchos elementos al final de la lista
    insertar_muchos_elementos(lista_vol, arreglo, tam, &ok);

    print_test("Prueba1: se pudieron insertar a lo ultimo todos los elementos", ok);
    print_test("Prueba2: El largo de la lista es el correcto luego de insertar muchos elementos", lista_largo(lista_vol) == (size_t)tam);

    // pruebas de borrar muchos elementos hasta que la lista queda vacia
    borrar_muchos_elementos(lista_vol, arreglo, tam, &ok);

    print_test("Prueba3: Se pudieron borrar todos los elementos", ok);
    print_test("Prueba4: La lista quedo vacia luego de borrar todos los elementos", lista_esta_vacia(lista_vol));
    print_test("Prueba5: El largo de la lista es 0 luego de borrar todos los elementos", lista_largo(lista_vol) ==  0);

    lista_destruir(lista_vol, free);
    printf("\n");
}


void pruebas_lista_destruccion_no_null(){
    printf("INICIO DE PRUEBAS DE DESTRUCCION NO NULL\n");
    lista_t *lista_destruccion = lista_crear();
    if(!lista_destruccion) return;


    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));

    // pruebas de insertar elementos dinamicos
    lista_insertar_primero(lista_destruccion, a);
    lista_insertar_primero(lista_destruccion, b);
    lista_insertar_primero(lista_destruccion, c);
    lista_insertar_primero(lista_destruccion, d);


    print_test("Prueba1: Se insertaron algunos elementos dinamicos", lista_largo(lista_destruccion) == 4);
    print_test("Prueba2: Se elimino elemento dinamico correctamente", lista_borrar_primero(lista_destruccion) == d);
    print_test("Prueba3: Se elimino elemento dinamico correctamente", lista_borrar_primero(lista_destruccion) == c);
    free(d);
    free(c);

    lista_destruir(lista_destruccion, free);
    printf("\n");
}


void pruebas_lista_destruccion_null(){
    printf("INICIO PRUEBAS DESTRUCCION\n");
    lista_t* lista = lista_crear();
    if(!lista) return;

    print_test("Prueba1: La lista fue creada", lista != NULL);
    print_test("Prueba2: La lista esta vacia", lista_esta_vacia(lista));

    // destruyo la lista
    lista_destruir(lista, NULL);
    printf("\n");
}


void pruebas_lista_elemento_null(){
    printf("INICIO DE PRUEBAS DE INSERTAR Y BORRAR ELEMENTO NULO\n");

    lista_t* lista = lista_crear();
    print_test("Prueba 1: Insertar elemento NULL al principio de la lista es valido", lista_insertar_primero(lista, NULL));
    print_test("Prueba 2: El primer elemento de la lista es NULL", lista_ver_primero(lista) == NULL);
    print_test("Prueba 3: Insertar elemento NULL al final de la lista es valido",lista_insertar_ultimo(lista, NULL));
    print_test("Borrar elemento NULL devuelve NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, free);
    printf("\n");
}


//PRUEBAS ITERADOR INTERNO

// suma todos los elementos de la lista
bool sumar_numeros(void* dato, void* extra){
    *(int*)extra += *(int*)dato;
    return true;
}

// suma todos los elementos pares de la lista
bool sumar_pares(void* dato, void* extra){
    if((*(int*)dato % 2) == 0){
        *(int*)extra += *(int*)dato;
    }
    return true;
}

#define CANTIDAD 5
#define MULTIPLICADOR 2
// multiplica por 2 los primeros 5 elementos de la lista
bool multiplicar(void* dato, void*extra){
    if(*(int*)extra == CANTIDAD){
        return false;
    } 
    (*(int*)extra)++;
    (*(int*)dato) *= MULTIPLICADOR;
    return true;
}


void pruebas_iterador_interno(){
    printf("INICIO DE PRUEBAS CON ITERADOR INTERNO\n");

    lista_t* lista = lista_crear();
    if(!lista) return;
    
    int arreglo[] = {4, 3, 12, 27, 6, 5, 40};
    int suma = 97;
    int suma_pares = 62;
    int extra_suma = 0;
    int extra_pares = 0;
    int extra = 0;

    lista_insertar_ultimo(lista, &arreglo[0]);
    lista_insertar_ultimo(lista, &arreglo[1]);
    lista_insertar_ultimo(lista, &arreglo[2]);
    lista_insertar_ultimo(lista, &arreglo[3]);
    lista_insertar_ultimo(lista, &arreglo[4]);
    lista_insertar_ultimo(lista, &arreglo[5]);
    lista_insertar_ultimo(lista, &arreglo[6]);


    // pruebas de iterar sin condicion de corte
    lista_iterar(lista, sumar_numeros, &extra_suma);
    print_test("Prueba1: Se puede iterar toda lista utilizando iterador interno", extra_suma == suma);

    lista_iterar(lista, sumar_pares, &extra_pares);
    print_test("Prueba2: Se pueden sumar todos los elementos pares de la lista utilizando iterador interno", extra_pares == suma_pares);

    // pruebas de iterar con condicion de corte
    lista_iterar(lista, multiplicar, &extra);
    print_test("Prueba3: Se itero la lista usando condicion de corte", extra == CANTIDAD);

    lista_destruir(lista, NULL);
    printf("\n");
}


//PRUEBAS ITERADOR EXTERNO

void pruebas_iterador_externo(){
    printf("INICIO DE PRUEBAS CON ITERADOR EXTERNO\n");
    lista_t *lista = lista_crear();
    if(!lista) return;
    lista_iter_t *iter = lista_iter_crear(lista);
    if(!iter) return;

    char *tortas[] = {"Lemon Pie", "Chocotorta", "Marquise", "Key Lime Pie", "Selva Negra"};

    // pruebas de creacion de iter
    print_test("Prueba1: Se creó correctamente el iterador y la lista", lista != NULL && iter != NULL);
    print_test("Prueba2: La lista esta vacia", lista_esta_vacia(lista));

    // prueba de insertar al principio de la lista
    print_test("Prueba3: Se puede insertar valor al principio de la lista", lista_iter_insertar(iter, &tortas[0]));
    lista_iter_avanzar(iter);
    print_test("Prueba4: El iterador esta en el final de la lista", lista_iter_al_final(iter));
    lista_iter_insertar(iter, &tortas[1]);

    // prueba de insertar  y borrar en el medio de la lista
    lista_iter_avanzar(iter);
    print_test("Prueba6: Se puede insertar un valor en el medio de la lista", lista_iter_insertar(iter, &tortas[3]));
    print_test("Prueba7: El elemento actual es el recién agregado", lista_iter_ver_actual(iter) == &tortas[3]);
    print_test("Prueba8: Se puede borrar elemento del medio", lista_iter_borrar(iter) == &tortas[3]);
    print_test("Prueba9: Iterador avanza hasta el final", lista_iter_al_final(iter));

    // prueba de insertar al final
    print_test("Prueba10: Se puede insertar valor al final de la lista", lista_iter_insertar(iter, &tortas[4]));
    print_test("Prueba11: El elemento actual es el último de la lista", lista_ver_ultimo(lista) == lista_iter_ver_actual(iter));
    
    // prueba de borrar elementos
    print_test("Prueba12: Se puede borrar un valor insertado", lista_iter_borrar(iter) == &tortas[4]);
    print_test("Prueba13: No se puede avanzar si el iterador esta al final", !lista_iter_avanzar(iter));
    print_test("Prueba14: No se puede borrar si el iterador esta al final", !lista_iter_borrar(iter));

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf("\n");
}

void pruebas_lista_estudiante(){
    pruebas_lista_vacia();
    pruebas_lista_algunos_elementos();
    pruebas_lista_volumen();
    pruebas_lista_destruccion_no_null(); 
    pruebas_lista_elemento_null();
    pruebas_iterador_interno();
    pruebas_iterador_externo();   
}


#ifndef CORRECTOR

int main(){
    pruebas_lista_estudiante();
    return failure_count() > 0;
}

#endif // CORRECTOR