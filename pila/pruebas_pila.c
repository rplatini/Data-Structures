#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void prueba_pila_vacia(void) {
    printf("INICIO DE PRUEBAS DE CREAR PILA\n");

    pila_t *pila = pila_crear();
    print_test("La pila fue creada", pila != NULL);
    print_test("La pila esta vacia", pila_esta_vacia(pila));

    print_test("No se puede desapilar en una pila recien creada", !pila_desapilar(pila));
    print_test("No se puede ver el tope en una pila recien creada", !pila_ver_tope(pila));
    printf("\n");

    // destruyo la pila
    pila_destruir(pila);
}

static void pruebas_elemento_nulo(){
    printf("INICIO DE PRUEBAS DE APILAR Y DESAPILAR ELEMENTO NULO\n");

    pila_t *pila = pila_crear();
    print_test("Apilar elemento NULL es valido", pila_apilar(pila, NULL));
    print_test("El valor de tope es NULL", pila_ver_tope(pila) == NULL);
    print_test("Desapilar elemento NULL devuelve NULL", pila_desapilar(pila) == NULL);
    printf("\n");

    pila_destruir(pila);
}

static void pruebas_algunos_elementos(){
    printf("INICIO DE PRUEBAS DE APILAR Y DESAPILAR DISTINTOS TIPOS DE DATOS\n");

    pila_t *pila = pila_crear();

    int numero = 5;
    double pi = 3.14159;
    char caracter = 'a';
    char cadena[50] = "cadena de prueba";


    // pruebas de apilar y desapilar un entero
    print_test("Se puede apilar entero de valor 5", pila_apilar(pila, &numero));
    print_test("El valor de tope es 5", pila_ver_tope(pila) == &numero);
    print_test("Desapilar entero de valor 5", pila_desapilar(pila) == &numero);

    // pruebas de apilar y desapilar un double
    print_test("Se puede apilar double de valor 3,14159", pila_apilar(pila, &pi));
    print_test("El valor de tope es 3,14159", pila_ver_tope(pila) == &pi);
    print_test("Desapilar double de valor 3,14159", pila_desapilar(pila) == &pi);

    // pruebas de apilar y desapilar un caracter
    print_test("Se puede apilar caracter de valor 'a'", pila_apilar(pila, &caracter));
    print_test("El valor de tope es 'a'", pila_ver_tope(pila) == &caracter);
    print_test("Desapilar caracter de valor 'a'", pila_desapilar(pila) == &caracter);

    // pruebas de apilar y desapilar una cadena de caracteres
    print_test("Se puede apilar cadena de caracteres 'cadena de prueba'", pila_apilar(pila, &cadena));
    print_test("El valor del tope es 'cadena de prueba'", pila_ver_tope(pila) == &cadena);
    print_test("Desapilar cadena de caracteres", pila_desapilar(pila) == &cadena);
    printf("\n");


    pila_destruir(pila);
}

/* PRE: el vector fue creado
 * POST: inicializa el vector con enteros del 0 al 20000.
 */
void cargar_vector(int vector[]){
    for(int i = 0; i < 20000; i++){
        vector[i] = i;
    }
}

/* PRE: la pila fue creada, tam y vector estan inicializados
 * POST: apila muchos elementos(tam) y retorna true si el tope es el correcto en cada caso, false en caso contrario.
 */
void apilar_muchos_elementos(pila_t* pila, int vector[20000], size_t tam, bool* tope_correcto){
    *tope_correcto = true;
    for(size_t i = 0; i < tam; i++){
        pila_apilar(pila, &vector[i]);

        // si algun elemento no se apilo correctamente, tope_correcto sera false
        if(pila_ver_tope(pila) != &vector[i]){
            tope_correcto = false;
        }
    }
}

/* PRE: la pila fue creada, tam esta inicializado
 * POST: desapila muchos elementos(tam) y retorna true si el tope es el correcto en cada caso, false en caso contrario.
 */
void desapilar_muchos_elementos(pila_t* pila, size_t tam, bool* tope_correcto){
    *tope_correcto = true;
    int* tope_actual;
    int* desapilado;

    for(size_t i = 0; i < tam; i++){
        tope_actual = pila_ver_tope(pila);
        desapilado = pila_desapilar(pila);

        // si el tope actual no coincide con el valor del ultimo desapilado, tope_correcto sera false
        if(tope_actual != desapilado){
            tope_correcto = false;
        }
    }
}

static void pruebas_volumen(){
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    pila_t* pila = pila_crear();

    int* vector = malloc(20000 * sizeof(int));
    if(vector == NULL){
        return;
    }

    cargar_vector(vector);
    vector[1000] = 10;
    vector[10000] = 6;
    bool tope_correcto;

    // pruebas apilar y desapilar un volumen grande de elementos
    apilar_muchos_elementos(pila, vector, 1000, &tope_correcto);

    print_test("Se apilaron muchos elementos", pila_apilar(pila, &vector[1000]));
    print_test("El tope toma los valores correctos al apilar muchos elementos", tope_correcto);
    print_test("Elemento en la posicion tope es 10", pila_ver_tope(pila) == &vector[1000]);
    print_test("Se desapilo entero de valor 10 en la posicion 1000", pila_desapilar(pila) == &vector[1000]);


    desapilar_muchos_elementos(pila, 1000, &tope_correcto);

    print_test("Se desapilaron muchos elementos", pila_desapilar(pila) == NULL);
    print_test("El tope toma los valores correctos al desapilar muchos elementos", tope_correcto);

    // pruebas de apilar y desapilar un volumen muy grande de elementos
    apilar_muchos_elementos(pila, vector, 10000, &tope_correcto);

    print_test("Se apilaron muchisimos elementos", pila_apilar(pila, &vector[10000]));
    print_test("El tope toma los valores correctos al apilar muchisimos elementos", tope_correcto);
    print_test("Elemento en la posicion tope es 6", pila_ver_tope(pila) == &vector[10000]);
    print_test("Se desapilo entero de valor 6 en la posicion 10000", pila_desapilar(pila) == &vector[10000]);


    desapilar_muchos_elementos(pila, 10000, &tope_correcto);

    print_test("Se desapilaron muchisimos elementos", pila_desapilar(pila) == NULL);
    print_test("El tope toma los valores correctos al desapilar muchisimos elementos", tope_correcto);

    // pruebas de desapilar y ver tope en una pila que se apilo y desapilo hasta quedar vacia
    print_test("Se desapilaron todos los elementos, la pila se comporta como recien creada", pila_esta_vacia(pila));
    print_test("No se puede desapilar en una pila que quedo vacia", !pila_desapilar(pila));
    print_test("No se puede ver el tope de una pila que quedo vacia", !pila_ver_tope(pila));
    printf("\n");

    free(vector);
    pila_destruir(pila);
}


void pruebas_pila_estudiante(){
    prueba_pila_vacia();
    pruebas_elemento_nulo();
    pruebas_algunos_elementos();
    pruebas_volumen();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
