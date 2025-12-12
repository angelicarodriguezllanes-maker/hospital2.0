#include "validaciones.hpp"
#include <iostream>
#include <limits> // Para numeric_limits
#include <cstring>
// Implementación de la validación de rango numérico
bool Validaciones::validarRangoEntero(int valor, int min, int max) {
    return valor >= min && valor <= max;
}

// Implementación de la validación de longitud de cadena
bool Validaciones::validarLongitudCadena(const string& cadena, size_t min, size_t max) {
    return cadena.length() >= min && cadena.length() <= max;
}

// Implementación de la validación de formato de fecha (simplificada)
bool Validaciones::validarFormatoFecha(const char* fecha) {
    // Revisa solo la longitud y que existan los caracteres de separación ('/')
    if (strlen(fecha) != 10) return false;
    if (fecha[2] != '/' || fecha[5] != '/') return false;
    
    // TODO: Implementar validación estricta de días, meses y años bisiestos.
    
    return true; 
}

// Implementación de la limpieza del buffer de entrada
void Validaciones::limpiarBufferEntrada() {
    // Verifica si la entrada falló (ej. ingresó letra en lugar de número)
    if (cin.fail()) {
        cin.clear(); // Limpia el indicador de error
        // Descarta el resto de la entrada hasta el fin de línea
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    } else {
        // Si no falló, solo descarta el resto de la línea (para evitar problemas con el próximo getline)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool Validaciones::validarFormatoHora(const char* hora) {
    // Revisa solo la longitud y que exista el separador (':')
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;
    
    // TODO: Implementar validación estricta de que las horas sean <= 23 y minutos <= 59.

    return true; 
}