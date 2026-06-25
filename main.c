#include <stdio.h>
#include "include/entradaDatos.h"
#include "include/indexCalculation.h"
#include "include/giniClasification.h"

int main(void)
{
    char pais[TAM_NOMBRE_PAIS];
    float quintiles[CANTIDAD_QUINTILES];
    float gini;
    int continuar;

    printf("==============================================\n");
    printf("   Calculadora del Indice de Gini\n");
    printf("   Proyecto Lenguajes de Programacion\n");
    printf("==============================================\n\n");

    do {
        if (!leerDatosPais(pais, TAM_NOMBRE_PAIS, quintiles)) {
            break;
        }

        gini = calculoGini(quintiles, CANTIDAD_QUINTILES);

        printf("\n----------------------------------------------\n");
        printf("Pais: %s\n", pais);
        printf("Indice de Gini: %.4f\n", gini);
        clasificarGini(gini);
        printf("----------------------------------------------\n");

        continuar = preguntarContinuar();

    } while (continuar);

    printf("\nSe cerrará la calculadora del Indice de Gini.\n");

    return 0;
}
