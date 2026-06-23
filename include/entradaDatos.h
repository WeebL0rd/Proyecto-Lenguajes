#ifndef ENTRADA_DATOS_H
#define ENTRADA_DATOS_H

#include <stddef.h>

/*
 * Constantes de la entrada. Son constantes de compilacion, no variables
 * globales, por lo que no almacenan estado compartido entre modulos.
 */
enum {
    CANTIDAD_QUINTILES = 5,
    TAM_NOMBRE_PAIS = 100
};

/*
 * Solicita y valida los datos de un pais.
 *
 * Parametros de salida:
 * - pais: nombre no vacio del pais.
 * - quintiles: cinco valores acumulados en escala decimal 0.0 a 1.0.
 *
 * Ejemplo de entrada del usuario: 3.1, 11.3, 25.2, 47.8, 100.
 * Resultado almacenado:          0.031, 0.113, 0.252, 0.478, 1.0.
 *
 * Retorna 1 si los datos se leyeron correctamente y 0 si la entrada
 * estandar finalizo antes de completar la lectura.
 */
int leerDatosPais(char pais[], size_t capacidadPais,
                  float quintiles[CANTIDAD_QUINTILES]);

/*
 * Pregunta si se desea procesar otro pais.
 * Retorna 1 para continuar y 0 para terminar.
 */
int preguntarContinuar(void);

#endif
