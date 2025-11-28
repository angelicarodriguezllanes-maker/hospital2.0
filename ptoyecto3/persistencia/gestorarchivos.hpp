// persistencia/GestorArchivos.hpp
#ifndef GESTOR_ARCHIVOS_HPP // Guarda de Inclusión para evitar redefiniciones
#define GESTOR_ARCHIVOS_HPP

#include <string>
#include <cstddef> // Para size_t

 * * Utiliza templates para ser genérica, permitiendo operar con cualquier
 * entidad (Paciente, Doctor, etc.) que tenga un tamaño fijo (sizeof()).
 */
class GestorArchivos {
private:
    /**
     * @brief Genera la ruta del archivo binario basada en el tipo de la entidad.
     * @tparam T Tipo de la entidad (e.g., Paciente).
     * @return std::string Ruta del archivo (e.g., "datos/Paciente.bin").
     */
    template <typename T>
    static std::string obtenerRutaArchivo(); 
    
public:
    /**
     * @brief Guarda un objeto completo al final del archivo binario.
     * @tparam T Tipo de la entidad a guardar.
     * @param entidad La entidad constante que se va a escribir.
     * @return bool Verdadero si la operación fue exitosa.
     */
    template <typename T>
    static bool guardar(const T& entidad); 

    /**
     * @brief Lee un objeto del archivo binario basado en su posición de registro.
     * @tparam T Tipo de la entidad a leer.
     * @param posicion La posición (índice 0-basado) del registro en el archivo.
     * @return T La entidad leída (o una entidad vacía si falla).
     */
    template <typename T>
    static T leerPorPosicion(long posicion); 

    // TODO: Aquí irán declarados los métodos 'listar', 'actualizar', 'eliminar', etc.
};

// =========================================================================
// INCLUSIÓN DE LA IMPLEMENTACIÓN (CRUCIAL PARA TEMPLATES)
// =========================================================================
// En C++, cuando se usan templates, la implementación debe ser visible para el 
// compilador en el momento de la llamada. Por convención, se incluye el .cpp 
// al final del .hpp.
#include "GestorArchivos.cpp" 

#endif // GESTOR_ARCHIVOS_HPP