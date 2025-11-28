#include "GestorArchivos.hpp" 
#include <fstream>      
#include <iostream>     
#include <typeinfo>     // Necesario para obtener el nombre del tipo (T)

// -----------------------------------------------------------------
// IMPLEMENTACIÓN DEL MÉTODO AUXILIAR PRIVADO (Plantilla)
// -----------------------------------------------------------------

/**
 * @brief Genera la ruta del archivo binario basada en el tipo de la entidad.
 * Este método es PRIVADO y auxiliar, usado solo por los métodos 'guardar' y 'leer'.
 * Por ejemplo: si T es Paciente, retorna "datos/Paciente.bin".
 */
template <typename T>
std::string GestorArchivos::obtenerRutaArchivo() {
    // 1. Obtener el nombre del tipo (ej: "Paciente")
    // Note: typeid(T).name() puede retornar nombres prefijados, pero
    // para un ejemplo simple asumimos que el nombre es utilizable.
    std::string nombreTipo = typeid(T).name();

    // 2. Construir la ruta completa
    // La convención es que el archivo se guarda en una carpeta 'datos'
    return "datos/" + nombreTipo + ".bin";
}

// -----------------------------------------------------------------
// IMPLEMENTACIÓN DEL MÉTODO PÚBLICO: guardar
// -----------------------------------------------------------------

/**
 * @brief Guarda un objeto completo al final del archivo binario.
 * La entidad se guarda como una secuencia de bytes.
 */
template <typename T>
bool GestorArchivos::guardar(const T& entidad) {
    // 1. Obtener la ruta del archivo usando el método auxiliar
    std::string ruta = obtenerRutaArchivo<T>();
    
    // 2. Abrir el archivo en modo binario y de salida (app/ate: para agregar al final)
    std::fstream archivo(ruta, std::ios::out | std::ios::binary | std::ios::app);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar en la ruta: " << ruta << std::endl;
        return false;
    }

    // 3. Escribir los datos del objeto (raw bytes)
    // El 'sizeof(T)' asegura que escribimos el tamaño exacto del objeto.
    archivo.write(reinterpret_cast<const char*>(&entidad), sizeof(T));
    
    // 4. Cerrar el archivo
    archivo.close();
    
    return true;
}

// -----------------------------------------------------------------
// IMPLEMENTACIÓN DEL MÉTODO PÚBLICO: leerPorPosicion
// -----------------------------------------------------------------

/**
 * @brief Lee un objeto del archivo binario basado en su posición de registro.
 */
template <typename T>
T GestorArchivos::leerPorPosicion(long posicion) {
    T entidadVacia = T(); // Objeto vacío para retornar si hay un error
    std::string ruta = obtenerRutaArchivo<T>();

    // 1. Abrir el archivo en modo binario y de entrada
    std::fstream archivo(ruta, std::ios::in | std::ios::binary);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para leer en la ruta: " << ruta << std::endl;
        return entidadVacia;
    }

    // 2. Calcular la posición exacta en bytes
    long offset = posicion * sizeof(T);
    
    // 3. Mover el puntero de lectura (seekg: seek get pointer)
    archivo.seekg(offset);

    if (archivo.fail()) {
        std::cerr << "Error: La posición " << posicion << " está fuera del rango del archivo." << std::endl;
        archivo.close();
        return entidadVacia;
    }

    // 4. Leer el bloque de bytes y reconstruir el objeto
    T entidadLeida;
    archivo.read(reinterpret_cast<char*>(&entidadLeida), sizeof(T));

    // 5. Cerrar el archivo
    archivo.close();
    
    return entidadLeida;
}