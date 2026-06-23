#include <stdio.h>
#include "../include/indexCalculation.h"


// Evaluación de la integral definida de 0 a 1 con la regla del trapecio
float calculoIntegral(float bases[], int size){

    float res = 0;
    float altura = 1.0f /size;
    float baseMenor = 0;
    float baseMayor;

    for (int i=0; i < size; i++) {
        baseMayor = bases[i];

        res += ((baseMenor + baseMayor) * altura) / 2;

        // printf("Area: %f\n", (((baseMenor + baseMayor) * altura) / 2));

        baseMenor = bases[i];
    }

    return res;
}

float calculoGini(float grupos[], int size) {
    float index = 1 - 2 * calculoIntegral(grupos, size);

    return index;
}

