#ifndef CITA_HPP
#define CITA_HPP

#include <string>

using namespace std;

class Cita {
private://pepa del agucate, el usario no puede cambiar lo qeu esta adentro
    int idCita;
    int idPaciente; 
    int idDoctor;   
    char fecha[11]; 
    char hora[6];   
    char motivo[100];
    bool cancelada; //  cita  cancelada/eliminada

public: //el la concha, el usuario la puede cambiar directamente sin las reglas de la clase
    // Constructor, prepara al objeto, despues de ser creador dandole alores parra utilizarlo
    Cita(int idCita = 0, int idPaciente = 0, int idDoctor = 0, 
         const char* fecha = "", const char* hora = "", 
         const char* motivo = "", bool cancelada = false);

    // Getters (Métodos de Acceso), obtiene o recupera el alor de una vriable privada
    int getIdCita() const;
    int getIdPaciente() const;
    int getIdDoctor() const;
    const char* getFecha() const;
    const char* getHora() const;
    const char* getMotivo() const;
    bool estaCancelada() const;

    // Setters (Métodos de Modificación)solamente modifica la ariable priada
    void setIdCita(int id);
    void setIdPaciente(int id);
    void setIdDoctor(int id);
    void setFecha(const char* nuevaFecha);
    void setHora(const char* nuevaHora);
    void setMotivo(const char* nuevoMotivo);
    void setCancelada(bool estado)
};

#endif 