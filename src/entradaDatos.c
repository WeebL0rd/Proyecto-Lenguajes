#include "../include/entradaDatos.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LINEA 256

typedef enum {
    LECTURA_FIN = 0,
    LECTURA_OK = 1,
    LECTURA_DEMASIADO_LARGA = 2
} EstadoLectura;

/* Funciones privadas: solo pertenecen al modulo de entrada. */
static EstadoLectura leerLinea(char texto[], size_t capacidad);
static void quitarEspaciosExtremos(char texto[]);
static int convertirAFloat(const char texto[], float *resultado);
static int leerNombrePais(char pais[], size_t capacidadPais);
static int leerQuintiles(float quintiles[CANTIDAD_QUINTILES]);
static int pedirPorcentajeAcumulado(int porcentajePoblacion,
                                    float minimoPermitido,
                                    int debeSerCien,
                                    float *porcentaje);

int leerDatosPais(char pais[], size_t capacidadPais,
                  float quintiles[CANTIDAD_QUINTILES])
{
    if (pais == NULL || capacidadPais == 0U || quintiles == NULL) {
        return 0;
    }

    if (!leerNombrePais(pais, capacidadPais)) {
        return 0;
    }

    return leerQuintiles(quintiles);
}

int preguntarContinuar(void)
{
    char linea[TAM_LINEA];

    for (;;) {
        EstadoLectura estado;

        printf("\nDesea ingresar otro pais? (S/N): ");
        estado = leerLinea(linea, sizeof linea);

        if (estado == LECTURA_FIN) {
            return 0;
        }

        if (estado == LECTURA_DEMASIADO_LARGA) {
            printf("Entrada demasiado larga. Escriba solamente S o N.\n");
            continue;
        }

        quitarEspaciosExtremos(linea);

        if (strlen(linea) == 1U) {
            char respuesta = (char)tolower((unsigned char)linea[0]);

            if (respuesta == 's') {
                return 1;
            }

            if (respuesta == 'n') {
                return 0;
            }
        }

        printf("Entrada invalida. Escriba S para continuar o N para terminar.\n");
    }
}

static int leerNombrePais(char pais[], size_t capacidadPais)
{
    for (;;) {
        EstadoLectura estado;

        printf("Ingrese el nombre del pais: ");
        estado = leerLinea(pais, capacidadPais);

        if (estado == LECTURA_FIN) {
            return 0;
        }

        if (estado == LECTURA_DEMASIADO_LARGA) {
            printf("El nombre es demasiado largo. Use menos de %zu caracteres.\n",
                   capacidadPais);
            continue;
        }

        quitarEspaciosExtremos(pais);

        if (pais[0] != '\0') {
            return 1;
        }

        printf("El nombre del pais no puede quedar vacio.\n");
    }
}

static int leerQuintiles(float quintiles[CANTIDAD_QUINTILES])
{
    int i;
    float minimoPermitido = 0.0f;

    printf("\nIngrese el porcentaje acumulado del ingreso total.\n");
    printf("Use valores entre 0 y 100; el modulo los convertira a decimales.\n");
    printf("Puede escribir decimales con punto o coma.\n\n");

    for (i = 0; i < CANTIDAD_QUINTILES; ++i) {
        int porcentajePoblacion = (i + 1) * 20;
        int debeSerCien = (i == CANTIDAD_QUINTILES - 1);
        float porcentaje;

        if (!pedirPorcentajeAcumulado(porcentajePoblacion,
                                      minimoPermitido,
                                      debeSerCien,
                                      &porcentaje)) {
            return 0;
        }

        /* El modulo de calculo recibe los datos en escala decimal 0.0 a 1.0. */
        quintiles[i] = porcentaje / 100.0f;
        minimoPermitido = porcentaje;
    }

    return 1;
}

static int pedirPorcentajeAcumulado(int porcentajePoblacion,
                                    float minimoPermitido,
                                    int debeSerCien,
                                    float *porcentaje)
{
    char linea[TAM_LINEA];

    if (porcentaje == NULL) {
        return 0;
    }

    for (;;) {
        EstadoLectura estado;
        float valor;

        printf("Ingreso acumulado para el %d%% de la poblacion (0 a 100): ",
               porcentajePoblacion);
        estado = leerLinea(linea, sizeof linea);

        if (estado == LECTURA_FIN) {
            return 0;
        }

        if (estado == LECTURA_DEMASIADO_LARGA) {
            printf("La entrada es demasiado larga. Intente nuevamente.\n");
            continue;
        }

        quitarEspaciosExtremos(linea);

        if (!convertirAFloat(linea, &valor)) {
            printf("Entrada invalida. Escriba un numero valido.\n");
            continue;
        }

        if (valor < 0.0f || valor > 100.0f) {
            printf("El porcentaje debe estar entre 0 y 100.\n");
            continue;
        }

        if (valor < minimoPermitido) {
            printf("Los porcentajes son acumulados: el valor no puede ser menor que %.4f.\n",
                   minimoPermitido);
            continue;
        }

        if (debeSerCien && valor != 100.0f) {
            printf("El ingreso acumulado para el 100%% de la poblacion debe ser 100.\n");
            continue;
        }

        *porcentaje = valor;
        return 1;
    }
}

static EstadoLectura leerLinea(char texto[], size_t capacidad)
{
    int caracter;

    if (texto == NULL || capacidad < 2U) {
        return LECTURA_FIN;
    }

    if (fgets(texto, (int)capacidad, stdin) == NULL) {
        return LECTURA_FIN;
    }

    if (strchr(texto, '\n') == NULL) {
        do {
            caracter = getchar();
        } while (caracter != '\n' && caracter != EOF);

        texto[0] = '\0';
        return LECTURA_DEMASIADO_LARGA;
    }

    texto[strcspn(texto, "\r\n")] = '\0';
    return LECTURA_OK;
}

static void quitarEspaciosExtremos(char texto[])
{
    size_t inicio = 0U;
    size_t fin;
    size_t longitud;

    if (texto == NULL) {
        return;
    }

    longitud = strlen(texto);

    while (inicio < longitud && isspace((unsigned char)texto[inicio])) {
        ++inicio;
    }

    fin = longitud;
    while (fin > inicio && isspace((unsigned char)texto[fin - 1U])) {
        --fin;
    }

    if (inicio > 0U && fin > inicio) {
        memmove(texto, texto + inicio, fin - inicio);
    }

    texto[fin - inicio] = '\0';
}

static int convertirAFloat(const char texto[], float *resultado)
{
    char copia[TAM_LINEA];
    char *finConversion;
    size_t i;
    int separadores = 0;
    float valor;

    if (texto == NULL || resultado == NULL || texto[0] == '\0') {
        return 0;
    }

    if (strlen(texto) >= sizeof copia) {
        return 0;
    }

    strcpy(copia, texto);

    for (i = 0U; copia[i] != '\0'; ++i) {
        if (copia[i] == '.' || copia[i] == ',') {
            ++separadores;
            if (copia[i] == ',') {
                copia[i] = '.';
            }
        }
    }

    if (separadores > 1) {
        return 0;
    }

    errno = 0;
    valor = strtof(copia, &finConversion);

    if (errno == ERANGE || finConversion == copia || !isfinite(valor)) {
        return 0;
    }

    while (*finConversion != '\0' && isspace((unsigned char)*finConversion)) {
        ++finConversion;
    }

    if (*finConversion != '\0') {
        return 0;
    }

    *resultado = valor;
    return 1;
}
