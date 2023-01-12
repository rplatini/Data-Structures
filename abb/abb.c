#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include "pila.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// declaracion de estructuras

typedef struct abb_nodo {
    struct abb_nodo* izq;
    struct abb_nodo* der;
    void* dato;
    char* clave;
} abb_nodo_t;


struct abb {
    abb_nodo_t* raiz;
    size_t cantidad;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
};


struct abb_iter {
    abb_t* arbol;
    pila_t* pila;
};

// PRIMITIVAS NODO

abb_nodo_t* crear_nodo(const char *clave, void *dato){
    abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
    if (!nodo) return NULL;

    char* copia_clave = strdup(clave);
    if(!copia_clave){
        free(nodo);
        return NULL;
    }  
    nodo->clave = copia_clave;
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;

    return nodo;
}


void destruir_nodo(abb_nodo_t* nodo){
    free(nodo->clave);
    free(nodo);
}

//FUNCIONES AUXILIARES

// PRIMITIVAS ABB

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* arbol = malloc(sizeof(abb_t));
    if(!arbol) return NULL;

    arbol->raiz = NULL;
    arbol->cantidad = 0;
    arbol->cmp = cmp;
    arbol->destruir_dato = destruir_dato;

    return arbol;
}


abb_nodo_t* buscar_clave(abb_nodo_t* nodo, const char* clave, abb_comparar_clave_t cmp, abb_nodo_t** padre){
    if(!nodo) return NULL;

    if(cmp(clave, nodo->clave) == 0){
        return nodo;

    } else if(cmp(clave, nodo->clave) < 0){
        *padre = nodo;
        return buscar_clave(nodo->izq, clave, cmp, padre);

    } else {
        *padre = nodo;
        return buscar_clave(nodo->der, clave, cmp, padre);
    }
}


bool abb_guardar(abb_t* arbol, const char* clave, void* dato){
    // caso arbol vacio
    if(arbol->cantidad == 0){
        arbol->raiz = crear_nodo(clave, dato);
        if(!arbol->raiz) return false;
        arbol->cantidad++;
        return true;
    }

    abb_nodo_t* padre = arbol->raiz;
    abb_nodo_t* nodo_clave = buscar_clave(arbol->raiz, clave, arbol->cmp, &padre);

    // caso clave no existe y hay que crear nodo
    if(!nodo_clave){
        if(arbol->cmp(clave, padre->clave) > 0){
            padre->der = crear_nodo(clave, dato);
            if(!padre->der) return false;

        } else {
            padre->izq = crear_nodo(clave, dato);
            if(!padre->izq) return false;
        }
        arbol->cantidad++;

    // caso clave existe y hay que reemplazar dato
    } else {
        void* dato_viejo = nodo_clave->dato;
        nodo_clave->dato = dato;

        if(arbol->destruir_dato){
            arbol->destruir_dato(dato_viejo);
        }
    }
    return true;
}


void *abb_obtener(const abb_t *arbol, const char *clave){
    abb_nodo_t* padre = arbol->raiz;
    abb_nodo_t* nodo_clave = buscar_clave(arbol->raiz, clave, arbol->cmp, &padre);

    if(!nodo_clave) return NULL;
    return nodo_clave->dato;
}


bool abb_pertenece(const abb_t *arbol, const char *clave){
    abb_nodo_t* padre = arbol->raiz;
    abb_nodo_t* nodo_clave = buscar_clave(arbol->raiz, clave, arbol->cmp, &padre);

    if(!nodo_clave) return false;
    return true;
}

// funciones auxiliares de borrado

abb_nodo_t* buscar_reemplazante(abb_nodo_t* nodo, abb_nodo_t** padre){
    if(!nodo->izq) return nodo;
    *padre = nodo;
    return buscar_reemplazante(nodo->izq, padre);
}

bool no_tiene_hijo(abb_nodo_t* nodo){
    return (!nodo->izq && !nodo->der);
}

bool tiene_1_hijo(abb_nodo_t* nodo){
    return (!nodo->izq && nodo->der) || (nodo->izq && !nodo->der);
}

// intercambia las claves y los datos de 2 nodos
void swappear_datos(abb_nodo_t* nodo1, abb_nodo_t* nodo2, char* clave_aux, void* dato_aux){
    clave_aux = nodo1->clave;
    dato_aux = nodo1->dato;
    nodo1->clave = nodo2->clave;
    nodo1->dato = nodo2->dato;
    nodo2->clave = clave_aux;
    nodo2->dato = dato_aux;
}

// elimina un nodo del abb que no tiene hijos
void abb_borrar_sin_hijos(abb_nodo_t** raiz, abb_nodo_t* hijo, abb_nodo_t** padre){
    if(!*padre){
        destruir_nodo(*raiz);
        return;
    }

    if((*padre)->izq == hijo){
        (*padre)->izq = NULL;

    } else if((*padre)->der == hijo){
        (*padre)->der = NULL;
    }
    destruir_nodo(hijo);
}

// elimina un nodo del abb que tiene 1 solo hijo
void abb_borrar_un_hijo(abb_nodo_t** raiz, abb_nodo_t* hijo, abb_nodo_t** padre){
    if(!*padre){ // si el elemento a borrar es la raiz del abb
        abb_nodo_t* raiz_vieja = *raiz;
        if((*raiz)->izq){
            *raiz = (*raiz)->izq;
        } else {
            *raiz = (*raiz)->der;
        }
        destruir_nodo(raiz_vieja);
        return;
    }

    if((*padre)->izq == hijo && hijo->der){
        (*padre)->izq = hijo->der;

    } else if((*padre)->izq == hijo && hijo->izq){
        (*padre)->izq = hijo->izq;

    } else if((*padre)->der == hijo && hijo->izq){
        (*padre)->der = hijo->izq;

    } else {
        (*padre)->der = hijo->der;
    }
    destruir_nodo(hijo);
}

// elimina un nodo del abb que tiene 2 hijos
void abb_borrar_2_hijos(abb_nodo_t** raiz, abb_nodo_t* hijo){
    abb_nodo_t* reemplazante;
    abb_nodo_t* padre_reemplazante = *raiz;
    char* clave_aux = hijo->clave;
    void* dato_aux = hijo->dato;

    if(hijo == *raiz){
        reemplazante = buscar_reemplazante((*raiz)->der, &padre_reemplazante);
        swappear_datos(*raiz, reemplazante, clave_aux, dato_aux); // hacemos un swap de los datos de la raiz con el reemplazante

    } else {
        reemplazante = buscar_reemplazante(hijo->der, &padre_reemplazante);
        swappear_datos(hijo, reemplazante, clave_aux, dato_aux); // hacemos un swap de los datos del hijo y el reemplazante
    }

    if(no_tiene_hijo(reemplazante)){
        abb_borrar_sin_hijos(raiz, reemplazante, &padre_reemplazante);

    } else {
        abb_borrar_un_hijo(raiz, reemplazante, &padre_reemplazante);
    }
}


void *abb_borrar(abb_t *arbol, const char *clave){
    abb_nodo_t* nodo_clave;
    abb_nodo_t* padre = NULL;

    nodo_clave = buscar_clave(arbol->raiz, clave, arbol->cmp, &padre);
    if(!nodo_clave) return NULL;

    void* dato_borrado = nodo_clave->dato;

    if(no_tiene_hijo(nodo_clave)){
        abb_borrar_sin_hijos(&arbol->raiz, nodo_clave, &padre);

    } else if(tiene_1_hijo(nodo_clave)){
        abb_borrar_un_hijo(&arbol->raiz, nodo_clave, &padre);

    } else {
        abb_borrar_2_hijos(&arbol->raiz, nodo_clave);
    }

    arbol->cantidad--;
    if(arbol->cantidad == 0) arbol->raiz = NULL;
    return dato_borrado;
}


size_t abb_cantidad(const abb_t *arbol){
    return arbol->cantidad;
}


void _abb_destruir(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato){
    if(!nodo) return;

    _abb_destruir(nodo->izq, destruir_dato);
    _abb_destruir(nodo->der, destruir_dato);

    if(destruir_dato){
        destruir_dato(nodo->dato);
    }
    destruir_nodo(nodo);
}


void abb_destruir(abb_t *arbol){
    _abb_destruir(arbol->raiz, arbol->destruir_dato);
    free(arbol);
}


// primitivas iterador interno

void _abb_in_order(abb_nodo_t *nodo, bool visitar(const char *, void *, void *), void *extra){
    if(!nodo) return;

    _abb_in_order(nodo->izq, visitar, extra);

    visitar(nodo->clave, nodo->dato, extra);
    
    _abb_in_order(nodo->der, visitar, extra); 
}


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    _abb_in_order(arbol->raiz, visitar, extra);
}


// PRIMITIVAS ITERADOR EXTERNO

void apilar_izquierdos(pila_t* pila, abb_nodo_t* nodo){
    if(!nodo) return;
    pila_apilar(pila, nodo);
    apilar_izquierdos(pila, nodo->izq);
}


abb_iter_t* abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t *iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;

    pila_t *pila = pila_crear();
    if (!pila){
        free(iter);
        return NULL;
    }
    iter->pila = pila;
    apilar_izquierdos(iter->pila, arbol->raiz);
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return false;

    abb_nodo_t* desapilado = pila_desapilar(iter->pila);
    if(desapilado->der){
        pila_apilar(iter->pila, desapilado->der);
        apilar_izquierdos(iter->pila, desapilado->der->izq);
    }
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return NULL;

    abb_nodo_t* actual = pila_ver_tope(iter->pila);
    return actual->clave;
}


bool abb_iter_in_al_final(const abb_iter_t *iter){
    if(pila_esta_vacia(iter->pila)) return true;
    return false;
}


void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}