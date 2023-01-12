#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


void pruebas_abb_estudiante(void);

#ifndef CORRECTOR
#define CORRECTOR
int main() {

    printf("\n~~~ PRUEBAS ESTUDIANTES ~~~\n");
    pruebas_abb_estudiante();

    return failure_count() > 0;
}
#endif // CORRECTOR