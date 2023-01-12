#include "cola.h"
#include <stdlib.h>


typedef struct nodo {
    void* dato;
    struct nodo* siguiente;
} nodo_t;

struct cola {
    nodo_t* ultimo;
    nodo_t* primero;
};

cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));
    if(cola == NULL) return NULL;

    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

void cola_destruir(cola_t* cola, void(*destruir_dato)(void*)){
    while(!cola_esta_vacia(cola)){

        if(destruir_dato != NULL) destruir_dato(cola_desencolar(cola));
        else cola_desencolar(cola);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return (cola->primero == NULL);
}

/* crea un nodo.
 POST: devuelve un nodo vacio. En caso de que no se haya creado devuelve NULL.
 */
nodo_t* nodo_crear(){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL) return NULL;
    return nodo;
}

bool cola_encolar(cola_t* cola, void* valor){
    nodo_t* nodo = nodo_crear();

    if(cola_esta_vacia(cola)){
        cola->primero = nodo;
    } else {
        cola->ultimo->siguiente = nodo;
    }
    cola->ultimo = nodo;
    nodo->dato = valor;
    nodo->siguiente = NULL;

    return true;
}

void *cola_ver_primero(const cola_t *cola){
    if(cola_esta_vacia(cola)) return NULL;

    return cola->primero->dato;
}

void *cola_desencolar(cola_t *cola){
    if(cola_esta_vacia(cola)){
        cola->ultimo = NULL;
        return NULL;
    } 

    void* dato_desencolado = cola_ver_primero(cola);
    void* siguiente = cola->primero->siguiente;
    free(cola->primero);

    cola->primero = siguiente;
    return dato_desencolado;
}
