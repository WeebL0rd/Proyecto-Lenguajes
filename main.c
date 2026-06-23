#include <stdio.h>
#include "include/indexCalculation.h"

int main(void) {
    //Test del cálculo de la fórmula de Gini
    float quintilesUS[] = {0.031, .113, 0.252, 0.478, 1};
    float gini = calculoGini(quintilesUS, 5);
    printf("Indice: %f\n", gini);
    return 0;
}
