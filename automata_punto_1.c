#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Declaro los prototipos de las funciones.
int verifica(char* s);  
int esPalabra(char* s, int* decimales, int* octales, int* hexadecimales);
int columna(int c);

int main(int argc, char *argv[]) {
    // Verificamos si se pasó la cadena como argumento por CLI.
    if (argc < 2) {
        printf("Por favor ingrese la cadena a analizar como argumento.\n");
        return 1;
    }

    char* cadena = argv[1];  // Tomamos la cadena de entrada desde la consola.

    // Verificamos si la cadena contiene caracteres inválidos (alfabeto incorrecto).
    if (verifica(cadena)) {
        printf("Hay caracteres que no pertenecen al alfabeto.\n");
        return 1;
    }

    // Contadores para cada grupo de constantes inicializadas en 0.
    int decimales = 0, octales = 0, hexadecimales = 0;

    // Verificamos si la cadena pertenece al lenguaje, contando cada tipo de constante durante la detección.
    if (esPalabra(cadena, &decimales, &octales, &hexadecimales)) {
        printf("Es palabra del lenguaje.\n");
        printf("Cantidad de constantes decimales: %d\n", decimales);
        printf("Cantidad de constantes octales: %d\n", octales);
        printf("Cantidad de constantes hexadecimales: %d\n", hexadecimales);
    }
    else {
        printf("No pertenece al lenguaje.\n");
    }

    return 0; // Fin de programa.
}

// Función que verifica si la cadena tiene caracteres no permitidos.
int verifica(char* cadena) {
    int i;

    // Recorremos cada carácter de la cadena.
    for (i = 0; cadena[i]; i++) {
        // Verificamos si el carácter no es '+', '-', '#', un dígito (Del 0 al 9) o un carácter válido para hexadecimales (A-F o a-f o x,X).
        if (!(cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '#' || isdigit(cadena[i]) || (cadena[i] >= 'A' && cadena[i] <= 'F') ||
              (cadena[i] >= 'a' && cadena[i] <= 'f') || cadena[i] == 'x' || cadena[i] == 'X')) {
            return 1;  // Retornamos 1 si hay caracteres inválidos.
        }
    }

    return 0;  // Retornamos 0 si no hay caracteres inválidos.
}

// Función que implementa el autómata y valida la cadena, además de contar los tipos de constantes.
int esPalabra(char* cadena, int* decimales, int* octales, int* hexadecimales) {
    // Tabla de transiciones del autómata.
    static int tt[7][8] = {
    //   '+'  '-'  '#'  '0'  [1-7] [1-9] [A-Fa-f] 'x,X'
        { 1,   1,   0,   2,    3,     3,    6,   6 },  // Estado A (inicial) 0
        { 6,   6,   6,   6,    3,     3,    6,   6 },  // Estado B (después de un signo) 1
        { 6,   6,   6,   4,    4,     6,    6,   5 },  // Estado D (después de un '0') 2
        { 6,   6,   0,   3,    3,     3,    6,   6 },  // Estado C (número decimal) 3
        { 6,   6,   0,   4,    4,     6,    6,   6 },  // Estado F (número octal) 4
        { 6,   6,   0,   6,    5,     5,    5,   6 },  // Estado E (número hexadecimal) 5
        { 6,   6,   6,   6,    6,     6,    6,   6 }   // Estado G (rechazo) 6
    };

    int estado = 0;  // Estado inicial (A). Se va a ir actualizando dentro del while.
    int i = 0;       // Índice para recorrer la cadena.
    int c = cadena[0];  // Primer carácter de la cadena.
    int actualTipo = -1;  // Para contar el tipo actual de constante (-1 si no hay constante actual).

    // Recorremos la cadena mientras no lleguemos al final,
    while (c != '\0') {
        // Actualizamos el estado del autómata usando la tabla de transiciones.
        estado = tt[estado][columna(c)];

        // Si llegamos al final de una constante (al leer '#'), aumentamos el contador adecuado.
        if (c == '#') {
            if (actualTipo == 3) (*decimales)++;      // Si era decimal.
            else if (actualTipo == 4) (*octales)++;   // Si era octal.
            else if (actualTipo == 5) (*hexadecimales)++;  // Si era hexadecimal.
            
            actualTipo = -1;  // Reiniciamos el tipo actual de constante.
        }
        else {
            actualTipo = estado;  // Guardamos el tipo de la constante actual.
        }

        c = cadena[++i];  // Avanzamos al siguiente carácter.
    }

    // Verificamos si terminamos en un estado de aceptación (3: decimal, 4: octal, 5: hexadecimal).
    if (estado == 3 || estado == 4 || estado == 5) {
        // Contamos la última constante en caso de no haber otro '#'.
        if (actualTipo == 3) (*decimales)++;
        else if (actualTipo == 4) (*octales)++;
        else if (actualTipo == 5) (*hexadecimales)++;
        return 1;  // La cadena es válida.
    }
    else {
        return 0;  // La cadena no es válida.
    }
}

// Función que asigna la columna correspondiente en la tabla de transiciones.
int columna(int c) {
    // Identificamos la columna de la tabla según el carácter,
    if (c == '+') return 0;   // Columna para '+'.
    if (c == '-') return 1;   // Columna para '-'.
    if (c == '#') return 2;   // Columna para '#'.
    if (c == '0') return 3;   // Columna para '0'.
    if (c >= '1' && c <= '7') return 4;  // Columna para dígitos [0-7].
    if (c >= '1' && c <= '9') return 5;  // Columna para dígitos octales [1-9].
    if ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) return 6;  // Columna para hexadecimales.
    if (c == 'x' || c == 'X') return 7;  // Columna para 'x' o 'X' (hexadecimal).

    return -1;  // Si el carácter no pertenece al alfabeto, retornamos -1.
}