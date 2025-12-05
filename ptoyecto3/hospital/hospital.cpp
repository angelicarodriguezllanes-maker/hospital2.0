#include "Hospital.hpp"
#include <cstring>
#include <iostream>

// Constructor por defecto
Hospital::Hospital() : proximoIDPaciente(1), proximoIDDoctor(1), proximoIDCita(1), proximoIDConsulta(1),
                       pacientesRegistrados(0), doctoresRegistrados(0) {
    std::strcpy(nombre, "Sin Nombre");
    std::strcpy(direccion, "Sin Dirección");
    std::strcpy(telefono, "N/A");
}

// Genera un nuevo ID y lo incrementa
int Hospital::generarNuevoIDPaciente() {
    return proximoIDPaciente++;
}

// Implementación del método de incremento de estadísticas
void Hospital::incrementarPacientesRegistrados() {
    pacientesRegistrados++;
}

// Getter de ejemplo
const char* Hospital::getNombre() const {
    return nombre;
}

// ... Implementación de todos los demás métodos
