#include "GestorArchivos.hpp" 
#include <fstream>      
#include <iostream>     
#include <typeinfo>     // Necesario para obtener el nombre del tipo (T)

using namespace std;

//dado un tipo de dato genera el nombre de un archivoo correspondiente
template <typename T> // plantikka generica que recibe cualquier tipo d edato 
string GestorArchivos::obtenerRutaArchivo() { //obtiene el nombre de la funcion 
    string nombreTipo = typeid(T).name();

    // 2. Construir la ruta completa
    return "datos/" + nombreTipo + ".bin";
}

// Guarda un objeto completo al final del archivo binario, como una secuencia aen bytes 
template <typename T>
bool GestorArchivos::guardar(const T& entidad) {
    // Obtiene la ruta del archivo usando el método auxiliar (el robin de batman)
    string ruta = obtenerRutaArchivo<T>();
    
    // 2. Abrir el archivo en modo binario y de salida (app/ate: para agregar al final)
    fstream archivo(ruta, std::ios::out | std::ios::binary | std::ios::app);
    
    if (!archivo.is_open()) { //validacion 
        std::cerr << "Error: No se pudo abrir el archivo para guardar en la ruta: " << ruta << std::endl;
        return false;
    }

    // 3. Escribir los datos del objeto (raw bytes , cmc almacena sin niguna interpretacion) y su tamano completo 
    archivo.write(reinterpret_cast<const char*>(&entidad), sizeof(T));
    
    archivo.close();
    
    return true;
}
 //Lee un objeto del archivo binario basado en su posición de registro.
template <typename T>
T GestorArchivos::leerPorPosicion(long posicion) {
    T entidadVacia = T(); // Objeto vacío para retornar si hay un error
    std::string ruta = obtenerRutaArchivo<T>();

    // 1. Abrir el archivo en modo binario y de entrada
    fstream archivo(ruta, std::ios::in | std::ios::binary);

    if (!archivo.is_open()) { //validacion de apertura 
        std::cerr << "Error: No se pudo abrir el archivo para leer en la ruta: " << ruta << std::endl;
        return entidadVacia;
    }

    long offset = posicion * sizeof(T); // calcual posicion en bytes
    
    archivo.seekg(offset); // mueve el puntero de lectura 

    if (archivo.fail()) { // valida posisicion 
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