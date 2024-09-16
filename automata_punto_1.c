#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función para determinar si el caracter es un número decimal.
int esDecimal(const char *str) {
    int i = 0;

    if (str[0] == '+' || str[0] == '-') i++; // Permitimos el signo y avanzamos en una unidad.

    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0; // Si no es dígito, no es decimal.
    }
    return 1;
}

// Función para determinar si el caracter es un número octal.
int esOctal(const char *str) {
    if (str[0] != '0') return 0; // Los octales empiezan con 0 (Para diferenciarlos del hexadecimal).
    
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '7') return 0; // Verificamos si es dígito octal.
    }
    return 1;
}

// Función para determinar si el caracter es un número hexadecimal.
int esHexadecimal(const char *str) {
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) { // Si empieza con 0x o 0X es hexadecimal.
        for (int i = 2; str[i] != '\0'; i++) {
            if (!isxdigit(str[i])) return 0; // Verifica si es un dígito hexadecimal.
        }
        return 1;
    }
    return 0;
}

// Función principal para procesar la cadena.
void procesarCadena(const char *cadena) {
    int decimales = 0, octales = 0, hexadecimales = 0, errores = 0; // Inicializamos los contadores para devolver en el resumen final.
    char *token; // Variable para almacenar los caracteres a analizar en la iteración del while.
    char cadena_copia[256]; // Copiamos la cadena de entrada antes de modificarla.
    
    // Copia la cadena para usar strtok posteriormente. Esto lo hacemos ya que la función strtok modifica la cadena al dividirla en fragmentos.
    strncpy(cadena_copia, cadena, sizeof(cadena_copia));

    // Separamos la cadena por el delimitador #:
    token = strtok(cadena_copia, "#"); // Nos permite separar la cadena_copia en subcadenas tomando como separador el #.
    
    while (token != NULL) { // Mientras tengamos más caracteres para leer, continuamos analizando el token.
        if (esDecimal(token)) {
            printf("Decimal encontrado: %s\n", token); // Si el valor encontrado es un decimal, lo informamos por pantalla.
            decimales++; // Sumamos en el contador para el resumen.
        } else if (esOctal(token)) {
            printf("Octal encontrado: %s\n", token); // Si el valor encontrado es un octal, lo informamos por pantalla.
            octales++; // Sumamos en el contador para el resumen.
        } else if (esHexadecimal(token)) {
            printf("Hexadecimal encontrado: %s\n", token); // Si el valor encontrado es un hexadecimal, lo informamos por pantalla.
            hexadecimales++; // Sumamos en el contador para el resumen.
        } else {
            printf("Error lexico encontrado: %s\n", token); // Si el valor encontrado es un error, lo informamos por pantalla.
            errores++; // Sumamos en el contador para el resumen.
        }
        // Obtenemos el siguiente token.
        token = strtok(NULL, "#"); // Si pasamos NULL cómo parámetro le indicamos que continue por donde se quedó en la anterior llamada a la función strtok.
    }

    printf("Resumen:\n");
    printf("- Cantidad de decimales: %d\n", decimales);
    printf("- Cantidad de octales: %d\n", octales);
    printf("- Cantidad de hexadecimales: %d\n", hexadecimales);
    printf("- Cantidad de errores lexicos: %d\n", errores);
}

// Función que recibe un carácter numérico y retorna un número entero.
int charToNum(char c) {
    if (isdigit(c)) { // Valida que sea un dígito.
        return c - '0';  // Convierte el carácter numérico en su valor entero: En ASCII el 0 representa el 48 y todos los demás números son consecutivos por lo tanto si los restamos conseguimos el entero asociado.
    } else {
        printf("Error: '%c' no es un dígito.\n", c);
        return -1;  // Retorna -1 en caso de error
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) { // argc contiene la cantidad de argumentos pasados al programa por línea de comandos.
        printf("Debe ingresar una unica cadena por linea de comandos."); // Se deben pasar 2 parámetros, la ruta del .exe y la cadena a analizar con el autómata.
        return 1;
    }
    
    // Procesar la cadena ingresada por línea de comandos.
    procesarCadena(argv[1]);

    return 0; // Fin de programa.
}