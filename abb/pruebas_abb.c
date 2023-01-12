#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

void prueba_crear_abb(){
    printf("PRUEBAS CREAR ABB VACIO\n");
    abb_t* arbol = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear", arbol);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(arbol, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(arbol, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(arbol, "A"));

    abb_destruir(arbol);
    printf("\n");
}

void prueba_iterar_abb_vacio(){
    printf("PRUEBAS ABB ITERAR VACIO\n");

    abb_t* arbol = abb_crear(strcmp ,NULL);
    abb_iter_t* iter = abb_iter_in_crear(arbol);

    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(arbol);

    printf("\n");
}

void prueba_abb_insertar(){
    printf("PRUEBAS ABB INSERTAR\n");
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    //Inserta 1 valor y luego lo borra
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);

    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(arbol, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    // Inserta otros 2 valores y no los borra (se destruyen con el abb)
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(arbol, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(arbol, clave3));

    abb_destruir(arbol);
    printf("\n");

}

void prueba_abb_reemplazar(){
    printf("PRUEBAS ARBOL REEMPLAZAR\n");
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    // Inserta 2 valores y luego los reemplaza
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    abb_destruir(arbol);
    printf("\n");

}

void prueba_abb_reemplazar_con_destruir(){
    printf("PRUEBAS ABB REEMPLAZAR CON DESTRUIR\n");
    abb_t* arbol = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    // Pide memoria para 4 valores
    //valor0 = malloc(10 * sizeof(char));
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));


    // Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza)
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    // Se destruye el abb (se debe liberar lo que quedó dentro)
    abb_destruir(arbol);
    printf("\n");
}

void prueba_abb_borrar(){
    printf("PRUEBAS ABB BORRAR\n");
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    // Inserta 3 valores y luego los borra
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(arbol) == 3);

    // Al borrar cada elemento comprueba que ya no está pero los otros sí. 
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(arbol, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(arbol, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(arbol, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(arbol, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(arbol, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(arbol, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(arbol, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(arbol, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(arbol, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(arbol, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(arbol, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(arbol, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(arbol, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(arbol, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
    printf("\n");

}

void prueba_abb_clave_vacia(){
    printf("PRUEBAS ABB CLAVE VACIA\n");
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(arbol, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(arbol, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(arbol, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(arbol, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
    printf("\n");

}

void prueba_abb_valor_null(){
    printf("PRUEBAS ABB VALOR NULL\n");
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    // Inserta 1 valor y luego lo borra
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(arbol, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(arbol, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(arbol, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(arbol, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
    printf("\n");
}


static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

void prueba_iterar_abb(){
    printf("PRUEBAS ABB ITERAR\n");
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    // Inserta 3 valores
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(arbol, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(arbol);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    // Primer valor
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));

    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    // Segundo valor
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));

    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    // Tercer valor
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));

    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    // Vuelve a tratar de avanzar, por las dudas
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(arbol);
    printf("\n");
}

bool sumar_valores(const char* clave, void* dato, void* extra){
    *(int*)extra += *(int*)dato;
    return true;
}

// suma todos los elementos pares de la lista
bool sumar_valores_pares(const char* clave, void* dato, void* extra){
    if ((*(int*)dato % 2) == 0){
        *(int*)extra += *(int*)dato;
    }
    return true;
}

bool multiplicar(const char *clave, void *dato, void *extra){
    if (*(int*)extra == 2){
        return false;
    }
    (*(int*)extra)++;
    (*(int*)dato) *= 2;
    return true;
}

void prueba_abb_iterador_interno(){
    printf("PRUEBAS ITERADOR INTERNO\n");
    abb_t *arbol = abb_crear(strcmp, NULL);
    int valores[] = {4, 1, 2, 3};
    const char *claves[] = {"Lemon Pie", "Torta Oreo", "Marquise", "Cheesecake"};
    int suma = 10;
    int suma_pares = 6;
    int extra_suma = 0;
    int extra_pares = 0;
    int extra = 0;

    abb_guardar(arbol, claves[0], &valores[0]);
    abb_guardar(arbol, claves[1], &valores[1]);
    abb_guardar(arbol, claves[2], &valores[2]);
    abb_guardar(arbol, claves[3], &valores[3]);

    abb_in_order(arbol, sumar_valores, &extra_suma);
    print_test("Se pudo iterar todo el abb utilizando iterador interno", extra_suma == suma);

    abb_in_order(arbol, sumar_valores_pares, &extra_pares);
    print_test("Se pueden sumar todos los elementos pares del abb utilizando iterador interno", extra_pares == suma_pares);

    // pruebas de iterar con condicion de corte
    abb_in_order(arbol, multiplicar, &extra);
    print_test("Se itero la lista sin llegar al final", extra == 2);

    abb_destruir(arbol);
    printf("\n");
}


char* generar_clave(size_t largo_clave){
    // diccionario de caracteres
    char diccionario[] = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    /*
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
        'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X', 'Y', 'Z',
    */

    srand((unsigned)time(NULL));  // se genera una semilla para tener un numero random
    char* clave = malloc(sizeof(char)*largo_clave); 
    if(!clave) return NULL;

    int len = (int)strlen(diccionario);

    for(int i = 0; i < largo_clave; i++){
        clave[i] = diccionario[rand() % len]; // se genera la clave aleatoria
    }
    clave[largo_clave-1] = '\0';
    return clave;
}

void prueba_abb_volumen(size_t largo){
    printf("PRUEBAS ABB VOLUMEN\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 3;
    char* claves[largo];
    unsigned* valores[largo];

    for(unsigned i = 0; i < largo; i++){
        claves[i] = generar_clave(largo_clave);
        valores[i] = malloc(sizeof(int));
        *valores[i] = i;
    }

    bool ok = true;
    for (unsigned i = 0; i < largo; i++){
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    print_test("Prueba abb almacenar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for(size_t i = 0; i < largo; i++){
        ok = abb_pertenece(abb, claves[i]);
        if(!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if(!ok) break;
    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++){
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if(!ok)break;
    }

    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    printf("\n");
}

void prueba_abb_iterar_volumen(size_t largo){
    printf("PRUEBAS ABB ITERADOR EXTERNO VOLUMEN\n");

    abb_t *abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    char *claves[largo];
    size_t valores[largo];

    for (unsigned i = 0; i < largo; i++){
        claves[i] = generar_clave(largo_clave);
        valores[i] = i;
    }
    bool ok = true;
    for (unsigned i = 0; i < largo; i++){
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok)break;
    }
    abb_iter_t *iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++){
        if (abb_iter_in_al_final(iter)){
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if (!clave){
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if (!valor){
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++){
        if (valores[i] != largo){
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    for (size_t j = 0; j < largo; j++){
        free(claves[j]);
    }
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n ~~ FIN DE PRUEBAS ~~\n");
    printf("\n");
}

void pruebas_abb_estudiante(){
    // ejecuta todas las pruebas unitarias

    prueba_crear_abb();
    prueba_abb_insertar();
    prueba_iterar_abb_vacio();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_iterar_abb();
    prueba_abb_iterador_interno();
    prueba_abb_volumen(5);
    prueba_abb_iterar_volumen(5);
}


