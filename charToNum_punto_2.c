#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función que recibe un carácter numérico y retorna un número entero.
int charToNum(char c) {
    if (isdigit(c)) { // Valida que sea un dígito.
        return c - '0';  // Convierte el carácter numérico en su valor entero: En ASCII el 0 representa el 48 y todos los demás números son consecutivos por lo tanto si los restamos conseguimos el entero asociado.
    } else {
        printf("Error: '%c' no es un digito.\n", c);
        return -1;  // Retorna -1 en caso de error
    }
}

int main() {
    // Test de la función charToNum con varios caracteres.
    char testChars[] = {'5', '0', '9', 'a', '#', '7'};
    int numTests = sizeof(testChars) / sizeof(testChars[0]); // Calculamos la cantidad de elementos del array.

    for (int i = 0; i < numTests; i++) {
        char c = testChars[i];
        int resultado = charToNum(c);
        
        if (resultado != -1) {
            printf("El valor numerico del caracter '%c' es: %d\n", c, resultado);
        }
    }

    return 0; // Fin de programa.
}