#include "historial.hpp"
#include <cstring>

// Constructor
HistorialMedico::HistorialMedico(int idHistorial, int idPaciente, int idDoctor, 
                                 const char* fecha, const char* diagnostico, 
                                 const char* tratamiento)
    : idHistorial(idHistorial), idPaciente(idPaciente), idDoctorTratante(idDoctor) {
    
    // Copia segura de cadenas (char arrays)
    strncpy(this->fechaRegistro, fecha, 10);
    this->fechaRegistro[10] = '\0';

    strncpy(this->diagnostico, diagnostico, 199);
    this->diagnostico[199] = '\0';

    strncpy(this->tratamiento, tratamiento, 199);
    this->tratamiento[199] = '\0';
}

//getters , metodo de acceso, lee o consulta
int HistorialMedico::getIdHistorial() const { return idHistorial; }
int HistorialMedico::getIdPaciente() const { return idPaciente; }
const char* HistorialMedico::getFechaRegistro() const { return fechaRegistro; }
const char* HistorialMedico::getDiagnostico() const { return diagnostico; }
const char* HistorialMedico::getTratamiento() const { return tratamiento; }
int HistorialMedico::getIdDoctorTratante() const { return idDoctorTratante; }

// Setters (Implementación), ESCRIBE
void HistorialMedico::setIdHistorial(int id) { this->idHistorial = id; }
void HistorialMedico::setIdPaciente(int id) { this->idPaciente = id; }
void HistorialMedico::setFechaRegistro(const char* nuevaFecha) {
    strncpy(this->fechaRegistro, nuevaFecha, 10);
    this->fechaRegistro[10] = '\0';
}
void HistorialMedico::setDiagnostico(const char* nuevoDiagnostico) {
    strncpy(this->diagnostico, nuevoDiagnostico, 199);
    this->diagnostico[199] = '\0';
}
void HistorialMedico::setTratamiento(const char* nuevoTratamiento) {
    strncpy(this->tratamiento, nuevoTratamiento, 199);
    this->tratamiento[199] = '\0';
}
void HistorialMedico::setIdDoctorTratante(int id) { this->idDoctorTratante = id; }
