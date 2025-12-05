#ifndef CITA_HPP
#define CITA_HPP

#include <string>

using namespace std;

class Cita {
private:
    // Atributos privados (Encapsulamiento)
    int idCita;
    int idPaciente; // Clave foránea para relacionar con Paciente
    int idDoctor;   // Clave foránea para relacionar con Doctor
    char fecha[11]; // Formato "DD/MM/AAAA\0"
    char hora[6];   // Formato "HH:MM\0"
    char motivo[100];
    bool cancelada; // Para marcar si la cita fue cancelada/eliminada

public:
    // Constructor
    Cita(int idCita = 0, int idPaciente = 0, int idDoctor = 0, 
         const char* fecha = "", const char* hora = "", 
         const char* motivo = "", bool cancelada = false);

    // Getters (Métodos de Acceso)
    int getIdCita() const;
    int getIdPaciente() const;
    int getIdDoctor() const;
    const char* getFecha() const;
    const char* getHora() const;
    const char* getMotivo() const;
    bool estaCancelada() const;

    // Setters (Métodos de Modificación)
    void setIdCita(int id);
    void setIdPaciente(int id);
    void setIdDoctor(int id);
    void setFecha(const char* nuevaFecha);
    void setHora(const char* nuevaHora);
    void setMotivo(const char* nuevoMotivo);
    void setCancelada(bool estado);

    // Método de Negocio (Opcional, puede ir en OperacionesCitas)
    // bool validarDatos() const; 
};

#endif // CITA_HPP