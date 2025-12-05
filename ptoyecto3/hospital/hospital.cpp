#include "Hospital.hpp"
#include <cstring> // Para strncpy y strlen
#include <iostream>

using namespace std;

// 1. Constructor por Defecto
Hospital::Hospital() { // Inicialización de datos fijos (Usando los valores de tu struct)
    
    strncpy(nombre, "Hospital San Jose St. Bonaventure", 99);
    nombre[99] = '\0';  //lee y copia el nombre (lector de precios)
    
    strncpy(direccion, "San Jose, California", 199);
    direccion[199] = '\0';

    strncpy(telefono, "0414-7348227", 19); //copiq los caracters

    telefono[19] = '\0';

    // Inicialización de IDs y Estadísticas
    proximoIDPaciente = 1;
    proximoIDDoctor = 1;
    proximoIDCita = 1;
    proximoIDConsulta = 1;
    pacientesRegistrados = 0;
    doctoresRegistrados = 0;
    citasAgendadas = 0;
    consultasRealizadas = 0;
}

// 2. Constructor con Parámetros
Hospital::Hospital(const char* nombre, const char* direccion, const char* telefono) {
    strncpy(this->nombre, nombre, 99); //copia segura de cadenas garantizando que termine correctamente
    this->nombre[99] = '\0';
    
    strncpy(this->direccion, direccion, 199);
    this->direccion[199] = '\0';

    strncpy(this->telefono, telefono, 19);
    this->telefono[19] = '\0';

    // Se inicializan los contadores a los valores por defecto
    proximoIDPaciente = 1;
    proximoIDDoctor = 1;
    proximoIDCita = 1;
    proximoIDConsulta = 1;
    pacientesRegistrados = 0;
    doctoresRegistrados = 0;
    citasAgendadas = 0;
    consultasRealizadas = 0;
}

// Los getters devuelven los valores de los miembros privados
const char* Hospital::getNombre() const { return nombre; }
const char* Hospital::getDireccion() const { return direccion; }
const char* Hospital::getTelefono() const { return telefono; }

int Hospital::getProximoIDPaciente() const { return proximoIDPaciente; }
int Hospital::getProximoIDDoctor() const { return proximoIDDoctor; }
int Hospital::getProximoIDCita() const { return proximoIDCita; }
int Hospital::getProximoIDConsulta() const { return proximoIDConsulta; }

int Hospital::getPacientesRegistrados() const { return pacientesRegistrados; }
int Hospital::getDoctoresRegistrados() const { return doctoresRegistrados; }
int Hospital::getCitasAgendadas() const { return citasAgendadas; }
int Hospital::getConsultasRealizadas() const { return consultasRealizadas; }

/// setters 
void Hospital::setNombre(const char* nuevoNombre) { //cambia el nombre 
    std::strncpy(nombre, nuevoNombre, 99);
    nombre[99] = '\0';
}

void Hospital::setDireccion(const char* nuevaDireccion) { //cambia la direccion
    std::strncpy(direccion, nuevaDireccion, 199);
    direccion[199] = '\0';
}

void Hospital::setTelefono(const char* nuevoTelefono) { //cambia el telefono    
    std::strncpy(telefono, nuevoTelefono, 19);
    telefono[19] = '\0';
}

//generadores de ids 
// Retorna el valor actual y luego lo incrementa 
int Hospital::generarNuevoIDPaciente() { return proximoIDPaciente++; }
int Hospital::generarNuevoIDDoctor() { return proximoIDDoctor++; }
int Hospital::generarNuevoIDCita() { return proximoIDCita++; }
int Hospital::generarNuevoIDConsulta() { return proximoIDConsulta++; }

//meetodo para incrementar los totales
void Hospital::incrementarPacientesRegistrados() { pacientesRegistrados++; }
void Hospital::incrementarDoctoresRegistrados() { doctoresRegistrados++; }
void Hospital::incrementarCitasAgendadas() { citasAgendadas++; }
void Hospital::incrementarConsultasRealizadas() { consultasRealizadas++; }