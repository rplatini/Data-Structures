#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

typedef void (*pila_destruir_wrapper_t)(void*);

static void pruebas_crear_cola(){
    printf("INICIO DE PRUEBAS DE CREACION DE COLA\n");
    cola_t* cola = cola_crear();

    print_test("La cola fue creada", cola != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(cola));

    print_test("No se puede desencolar en una cola recien creada", !cola_desencolar(cola));
    print_test("No se puede ver el primer elemento en una cola recien creada", !cola_ver_primero(cola));
    printf("\n");

    cola_destruir(cola, NULL);
}

static void pruebas_elemento_nulo(){
    printf("PRUEBA CON ELEMENTO NULO\n");

    cola_t* cola = cola_crear();
    print_test("Encolar elemento NULL es valido", cola_encolar(cola, NULL));
    cola_destruir(cola, NULL);
    printf("\n");

}

static void pruebas_algunos_elementos(){
    printf("INCIO DE PRUEBAS DE ENCOLAR Y DESENCOLAR ALGUNOS ELEMENTOS ESTATICOS\n");

    cola_t* cola = cola_crear();

    int entero = 19;
    double decimal = 9.81;
    char cadena[50] = "texto de prueba";

    print_test("Se puede encolar entero de valor 19", cola_encolar(cola, &entero));
    print_test("Se puede encolar double de valor 9.81", cola_encolar(cola, &decimal));
    print_test("Se puede encolar cadena de caracteres", cola_encolar(cola, &cadena));

    print_test("Se puede desencolar elemento estatico y se cumple invariante de cola", cola_ver_primero(cola) == cola_desencolar(cola));

    cola_destruir(cola, NULL);
    printf("\n");
}

void pruebas_liberar_a_mano(){
    printf("INICIO DE PRUEBAS DE LIBERAR MEMORIA MANUALMENTE\n");

    cola_t* cola = cola_crear();

    void** elementos = malloc(sizeof(void*) * 3);
    if(!elementos) return;

    bool ok = cola_encolar(cola, &elementos[0]);
    bool ok_2 = cola_encolar(cola, &elementos[1]);
    bool ok_3 = cola_encolar(cola, &elementos[2]);

    print_test("Se puede encolar elementos dinamicos", ok && ok_2 && ok_3);
    print_test("Se puede desencolar elemento dinamico", cola_desencolar(cola));

    // destruyo la cola y libero los elementos a mano
    cola_destruir(cola, NULL);
    free(elementos);

    printf("\n");
}

void pruebas_liberar_con_funcion(){
    printf("INICIO DE PRUEBAS DE LIBERAR MEMORIA CON FUNCION\n");
    cola_t* cola = cola_crear();

    void* elemento_1 = malloc(sizeof(void*));
    if(!elemento_1) return;

    void* elemento_2 = malloc(sizeof(void*));
    if(!elemento_2) return;
    
    void* elemento_3 = malloc(sizeof(void*));
    if(!elemento_3) return;

    bool ok_1 = cola_encolar(cola, elemento_1);
    bool ok_2 = cola_encolar(cola, elemento_2);
    bool ok_3 = cola_encolar(cola, elemento_3);

    print_test("Se puede encolar elementos dinamicos", ok_1 && ok_2 && ok_3);

    // libero a mano porque desencole un elemento
    void* primero = cola_ver_primero(cola);
    void* desencolado = cola_desencolar(cola);

    print_test("Se puede desencolar elemento dinamico", primero == desencolado);
    free(desencolado);

    // destruyo la cola pasando free porque los elementos encolados son dinamicos
    cola_destruir(cola, free);
    printf("\n");
}

// PRE: el vector fue creado, n esta inicializado
// POST: inicializa el vector de enteros con n elementos
void cargar_vector(int vector[], size_t n){
    for(int i = 0; i < n; i++){
        vector[i] = i;
    }
}

void pila_destruir_wrapper(void* pila){
    pila_destruir(pila);
}

void pruebas_encolar_pilas(){
    printf("INICIO DE PRUEBAS DE ENCOLAR PILAS\n");

    cola_t* cola = cola_crear();
    pila_t* pila = pila_crear();
    pila_t* pila_2 = pila_crear();
    pila_t* pila_3 = pila_crear();

    bool ok = cola_encolar(cola, pila);
    bool ok_2 = cola_encolar(cola, pila_2);
    bool ok_3 = cola_encolar(cola, pila_3);

    print_test("Se puede encolar pilas en la cola", ok && ok_2 && ok_3);

    print_test("Se puede desencolar pilas en la cola y se cumple invariante de cola", cola_desencolar(cola) == pila);

    // destruyo la pila que desencole
    pila_destruir(pila);
    
    // destruyo la cola y todas las pilas que contiene
    cola_destruir(cola, pila_destruir_wrapper);
    printf("\n");

}

/* PRE: la cola fue creada, vector y tam estan inicializados
 * POST: encola enteros a la cola, la cantidad que encola es cant. Modifica el valor de ok si algun elemento no se encolo
 */
void encolar_muchos_elementos(cola_t* cola, int vector[], size_t cant, bool* ok){
    *ok = true;
    for(size_t i = 0; i < cant; i++){
        *ok = cola_encolar(cola, &vector[i]);
    }
}

/* PRE: cola fue creada
 * POST: desencola elementos hasta que la cola esta vacia
 */
void desencolar_muchos_elementos(cola_t* cola, bool* ok){
    *ok = true;
    while(!cola_esta_vacia(cola)){
        int* primero = cola_ver_primero(cola);
        int* desencolado = cola_desencolar(cola);
        if(primero != desencolado){
            *ok = false;
        }
    }
}


static void pruebas_volumen(){
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    cola_t* cola = cola_crear();

    int* vector = malloc(sizeof(int) * 20000);
    if(!vector) return;

    cargar_vector(vector, 20000);
    bool ok = true;

    // pruebas de encolar y desencolar un volumen grande de elementos
    encolar_muchos_elementos(cola, vector, 1000, &ok);
    print_test("Se pudieron encolar muchos elementos y se cumple el invariante de cola", ok);

    desencolar_muchos_elementos(cola, &ok);
    print_test("Se pudieron desencolar muchos elementos", cola_esta_vacia(cola));
    print_test("Se cumple el invariante de cola al desencolar muchos elementos", ok);

    // pruebas de encolar y desencolar un volumen muy grande de elementos
    encolar_muchos_elementos(cola, vector, 10000, &ok);
    print_test("Se pudieron encolar muchisimos elementos y se cumple el invariante de cola", ok);

    desencolar_muchos_elementos(cola, &ok);
    print_test("Se pudieron desencolar muchisimos elementos", cola_esta_vacia(cola));
    print_test("Se cumple el invariante de cola al desencolar muchisimos elementos", ok);

    print_test("No se puede desencolar en una cola que se encolo y desencolo hasta quedar vacia", !cola_desencolar(cola));
    print_test("No se puede ver el primer elemento de una cola que se encolo y desencolo hasta quedar vacia", !cola_ver_primero(cola));

    // destruyo la cola, y paso NULL porque los elementos encolados son estaticos
    cola_destruir(cola, NULL);
    free(vector);

    printf("\n");
}

void pruebas_cola_estudiante(void){
    pruebas_crear_cola();
    pruebas_elemento_nulo();
    pruebas_algunos_elementos();
    pruebas_liberar_a_mano();
    pruebas_liberar_con_funcion();
    pruebas_encolar_pilas();
    pruebas_volumen();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
