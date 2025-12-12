// En utilidades/Validaciones.cpp

#include "validaciones.hpp" 
#include <iostream>
#include <cstring> // Necesario para usar strlen()
#include <limits>  // Necesario para std::numeric_limits

using namespace std; // Para usar cout, cin, endl sin std::

// ------------------------------------------------------------------
// Implementación de Validaciones de Datos
// ------------------------------------------------------------------

bool Validaciones::validarCedula(const char* cedula) {
    if (strlen(cedula) != 10) {
        return false;
    }
    // Lógica avanzada de validación de cédula (ej. dígitos, algoritmo) iría aquí.
    // Por simplicidad, solo verificamos que sean dígitos (puedes expandir esta lógica).
    for (size_t i = 0; i < strlen(cedula); ++i) {
        if (!isdigit(cedula[i])) {
            return false;
        }
    }
    return true;
}

bool Validaciones::validarTelefono(const char* telefono) {
    if (strlen(telefono) < 8 || strlen(telefono) > 15) {
        return false;
    }
    // Lógica de validación de teléfono.
    for (size_t i = 0; i < strlen(telefono); ++i) {
        if (!isdigit(telefono[i])) {
            return false;
        }
    }
    return true;
}

bool Validaciones::validarEmail(const char* email) {
    // Validación de formato básica: debe contener '@' y '.'
    const char* at = strchr(email, '@');
    if (at == nullptr || strchr(at, '.') == nullptr) {
        return false;
    }
    return true;
}

// ------------------------------------------------------------------
// Implementación de Validaciones de Formato
// ------------------------------------------------------------------

bool Validaciones::validarFormatoFecha(const char* fecha) {
    if (strlen(fecha) != 10) return false;
    // Verifica formato DD/MM/AAAA (ejemplo básico)
    if (fecha[2] != '/' || fecha[5] != '/') return false;
    return true;
}

bool Validaciones::validarFormatoHora(const char* hora) {
    if (strlen(hora) != 5) return false;
    // Verifica formato HH:MM (ejemplo básico)
    if (hora[2] != ':') return false;
    return true;
}


// ------------------------------------------------------------------
// Implementación de Utilidades de Lectura Segura
// ------------------------------------------------------------------

int Validaciones::leerEntero(const char* mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cout << "Entrada inválida. Por favor, ingrese un número entero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return valor;
}

float Validaciones::leerFlotante(const char* mensaje) {
    float valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cout << "Entrada inválida. Por favor, ingrese un número (float): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return valor;
}

int Validaciones::leerOpcionMenu(int limiteInferior, int limiteSuperior) {
    int opcion;
    do {
        opcion = leerEntero("Seleccione una opción: ");
        if (opcion < limiteInferior || opcion > limiteSuperior) {
            cout << "Opción no válida. Ingrese un número entre " 
                 << limiteInferior << " y " << limiteSuperior << "." << endl;
        }
    } while (opcion < limiteInferior || opcion > limiteSuperior);
    return opcion;
}

bool Validaciones::validarFormatoHora(const char* hora) {
    // Revisa solo la longitud y que exista el separador (':')
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;
    
    // TODO: Implementar validación estricta de que las horas sean <= 23 y minutos <= 59.

    return true; 
}