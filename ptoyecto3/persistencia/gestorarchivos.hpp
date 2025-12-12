#ifndef GESTOR_ARCHIVOS_HPP // Guarda de Inclusión para evitar redefiniciones
#define GESTOR_ARCHIVOS_HPP

#include <string>
#include <cstddef> // Para size_t

class GestorArchivos {
private:
    template <typename T> // plantilla para generar una funcion par a cualquier tipo dedato 
    static std::string obtenerRutaArchivo(); //sea generico (funciona con cualquier dato0)
    
public:
  //toma cualquier objeto determina su archivo y y escribe al final del archivo 
    template <typename T>n// formula para funciones qeu guarda lo que sea 
    static bool guardar(const T& entidad); 

    template <typename T>
    static T leerPorPosicion(long posicion); 
};


//#include "GestorArchivos.cpp"  // se incluye popr el uso de plantillas

#endif 