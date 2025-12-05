#ifndef HISTORIAL_MEDICO_HPP
#define HISTORIAL_MEDICO_HPP

#include <string>

using namespace std;

class HistorialMedico {
private:
    // Atributos privados (Encapsulamiento)
    int idHistorial;
    int idPaciente; // Clave foránea al Paciente
    char fechaRegistro[11]; // "DD/MM/AAAA\0"
    char diagnostico[200];
    char tratamiento[200];
    int idDoctorTratante; // Quién hizo la anotación

public:
    // Constructor
    HistorialMedico(int idHistorial = 0, int idPaciente = 0, int idDoctor = 0, 
                    const char* fecha = "", const char* diagnostico = "", 
                    const char* tratamiento = "");

    // Getters
    int getIdHistorial() const;
    int getIdPaciente() const;
    const char* getFechaRegistro() const;
    const char* getDiagnostico() const;
    const char* getTratamiento() const;
    int getIdDoctorTratante() const;

    // Setters
    void setIdHistorial(int id);
    void setIdPaciente(int id);
    void setFechaRegistro(const char* nuevaFecha);
    void setDiagnostico(const char* nuevoDiagnostico);
    void setTratamiento(const char* nuevoTratamiento);
    void setIdDoctorTratante(int id);
};

#endif // HISTORIAL_MEDICO_HPP