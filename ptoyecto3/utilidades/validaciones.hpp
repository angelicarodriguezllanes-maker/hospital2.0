#ifndef VALIDACIONES_HPP
#define VALIDACIONES_HPP

#include <iostream>
#include <ctime> // Para funciones de tiempo si las necesitas

class validaciones {
public:
    // ------------------------------------------------------------------
    // Métodos para validación de datos de Doctor y Paciente (AÑADIR ESTO)
    // ------------------------------------------------------------------

    /**
     * @brief Valida el formato y la estructura de una cédula/DNI.
     * @param cedula Cadena de caracteres a validar.
     * @return true si es válida, false en caso contrario.
     */
    static bool validarCedula(const char* cedula);

    /**
     * @brief Valida el formato y la longitud de un número de teléfono.
     * @param telefono Cadena de caracteres a validar.
     * @return true si es válido, false en caso contrario.
     */
    static bool validarTelefono(const char* telefono);

    /**
     * @brief Valida el formato básico de una dirección de correo electrónico.
     * @param email Cadena de caracteres a validar.
     * @return true si es válido, false en caso contrario.
     */
    static bool validarEmail(const char* email);

    // ------------------------------------------------------------------
    // Otros métodos estáticos (Mantén si ya existían)
    // ------------------------------------------------------------------

    // Ejemplo: Si tienes validaciones de fecha/hora que mencionaste antes
    static bool validarFormatoFecha(const char* fecha);
    static bool validarFormatoHora(const char* hora);
    
    // Función genérica para leer enteros
    static int leerEntero(const char* mensaje);

    // Función genérica para leer flotantes
    static float leerFlotante(const char* mensaje);

    // Asegúrate de que todas tus validaciones genéricas estén aquí...
    
};

// ------------------------------------------------------------------
// Nota: La implementación (código real) de estas funciones 
// debe ir en utilidades/Validaciones.cpp
// ------------------------------------------------------------------

#endif // VALIDACIONES_HPP