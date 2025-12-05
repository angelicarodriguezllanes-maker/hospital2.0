#include "Cita.hpp"
#include <cstring> // Necesario para funciones como strncpy

// Constructor (Inicializa todos los atributos)
Cita::Cita(int idCita, int idPaciente, int idDoctor, 
           const char* fecha, const char* hora, 
           const char* motivo, bool cancelada) 
    : idCita(idCita), idPaciente(idPaciente), idDoctor(idDoctor), cancelada(cancelada) {
    
    // Usamos strncpy para copiar cadenas de caracteres (char arrays) de forma segura
    // Fecha (11 bytes: 10 caracteres + '\0')
    strncpy(this->fecha, fecha, 10);
    this->fecha[10] = '\0';

    // Hora (6 bytes: 5 caracteres + '\0')
    strncpy(this->hora, hora, 5);
    this->hora[5] = '\0';

    // Motivo (100 bytes)
    strncpy(this->motivo, motivo, 99);
    this->motivo[99] = '\0';
}

// ------------------------------------
// Getters (Solo devuelven el valor del atributo)
// ------------------------------------

int Cita::getIdCita() const {
    return idCita;
}

int Cita::getIdPaciente() const {
    return idPaciente;
}

int Cita::getIdDoctor() const {
    return idDoctor;
}

const char* Cita::getFecha() const {
    return fecha;
}

const char* Cita::getHora() const {
    return hora;
}

const char* Cita::getMotivo() const {
    return motivo;
}

bool Cita::estaCancelada() const {
    return cancelada;
}

// ------------------------------------
// Setters (Permiten modificar el valor del atributo de forma controlada)
// ------------------------------------

void Cita::setIdCita(int id) {
    this->idCita = id;
}

void Cita::setIdPaciente(int id) {
    this->idPaciente = id;
}

void Cita::setIdDoctor(int id) {
    this->idDoctor = id;
}

void Cita::setFecha(const char* nuevaFecha) {
    strncpy(this->fecha, nuevaFecha, 10);
    this->fecha[10] = '\0';
}

void Cita::setHora(const char* nuevaHora) {
    strncpy(this->hora, nuevaHora, 5);
    this->hora[5] = '\0';
}

void Cita::setMotivo(const char* nuevoMotivo) {
    strncpy(this->motivo, nuevoMotivo, 99);
    this->motivo[99] = '\0';
}

void Cita::setCancelada(bool estado) {
    this->cancelada = estado;
}