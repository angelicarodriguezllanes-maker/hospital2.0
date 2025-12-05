#ifndef VALIDACIONES_HPP
#define VALIDACIONES_HPP

#include <string>

using namespace std;

class Validaciones {
public:
    // 1. Validación de rangos numéricos genéricos
    static bool validarRangoEntero(int valor, int min, int max);

    // 2. Validación de longitud de cadenas (Ej: nombre, cedula)
    static bool validarLongitudCadena(const string& cadena, size_t min, size_t max);

    // 3. Validación específica de formato (Ej: fechas, horas)
    static bool validarFormatoFecha(const char* fecha); // DD/MM/AAAA
    static bool validarFormatoHora(const char* hora);   // HH:MM

    // 4. Utilidad para limpiar el buffer de entrada (común en C++)
    static void limpiarBufferEntrada();
    
private:
    // Clase estática, el constructor es privado/eliminado
    Validaciones() = delete; 
};

#endif // VALIDACIONES_HPP