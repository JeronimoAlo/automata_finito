#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Función que recibe un carácter numérico y retorna un número entero.
int charToNum(char c) {
    if (isdigit(c)) { // Valida que sea un dígito.
        return c - '0';  // Convierte el carácter numérico en su valor entero: En ASCII el 0 representa el 48 y todos los demás números son consecutivos por lo tanto si los restamos conseguimos el entero asociado.
    } else {
        printf("Error: '%c' no es un digito.\n", c);
        return -1;  // Retorna -1 en caso de error.
    }
}

// Función para evaluar una expresión con +, -, *, /
int evaluarExpresion(const char* expresion) {
    int resultado = 0;
    int valorActual = 0;
    char operacion = '+';  // Comienza con una suma.

    for (int i = 0; expresion[i] != '\0'; i++) {
        char c = expresion[i];

        // Si es un dígito, lo convertimos a número.
        if (isdigit(c)) {
            valorActual = valorActual * 10 + charToNum(c);  // Para manejar números de más de 1 dígito.
        }

        // Si encontramos un operador o es el final de la cadena, ejecutamos la operación.
        if (!isdigit(c) && !isspace(c) || expresion[i + 1] == '\0') {
            switch (operacion) {
                case '+': resultado += valorActual; break;
                case '-': resultado -= valorActual; break;
                case '*': resultado *= valorActual; break;
                case '/': resultado /= valorActual; break;
            }
            operacion = c;  // Guardamos el siguiente operador.
            valorActual = 0;  // Reiniciamos el valor para el próximo número.
        }
    }

    return resultado;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <expresión>\n", argv[0]);
        return 1;
    }

    // Obtenemos la expresión de la línea de comandos.
    char* expresion = argv[1];

    // Evaluamos la expresión.
    int resultado = evaluarExpresion(expresion);

    // Mostramos el resultado.
    printf("El resultado de la expresión '%s' es: %d\n", expresion, resultado);

    return 0;
}
