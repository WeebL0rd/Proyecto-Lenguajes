#include <stdio.h>
#include "../include/giniClasification.h"

void clasificar_gini(float gini) {
    printf("Clasificacion de la distribución del ingreso: ");

    if (gini < 0.30) {
        printf("Muy buena distribucion del ingreso\n");
    } else if (gini < 0.35) {
        printf("Buena distribucion del ingreso\n");
    } else if (gini < 0.40) {
        printf("Distribucion regular del ingreso\n");
    } else if (gini < 0.45) {
        printf("Distribucion desigual del ingreso\n");
    } else if (gini < 0.50) {
        printf("Mala distribucion del ingreso\n");
    } else {
        printf("Enorme desigualdad del ingreso\n");
    }
}
