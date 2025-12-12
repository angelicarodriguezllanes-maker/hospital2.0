#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP
#include <string>

#include <string> 

class Hospital {
private:
    // Datos de Identificación (Miembros Privados) 
   
    char nombre[100];
    char direccion[200]; 
    char telefono[20];
    
    // Contadores de IDs (Próximos IDs) 
    int proximoIDPaciente;
    int proximoIDDoctor;
    int proximoIDCita;
    int proximoIDConsulta; 
    
    //Estadísticas (Totales registrados)
    int pacientesRegistrados; 
    int doctoresRegistrados;
    int citasAgendadas;
    int consultasRealizadas; 

public:
    // CONSTRUCTORES 
    // 1. Constructor usa los valores preestablecidos
    Hospital();
    // 2. Constructor con parámetros, permite inicializar con otros valores
    Hospital(const char* nombre, const char* direccion, const char* telefono);
    void mostrarEstadisticas();
    // GETTERS (Métodos de Lectura const)
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const;

    int getProximoIDPaciente() const;
    int getProximoIDDoctor() const;
    int getProximoIDCita() const;
    int getProximoIDConsulta() const;

    int getPacientesRegistrados() const; 
    int getDoctoresRegistrados() const;
    int getCitasAgendadas() const;
    int getConsultasRealizadas() const;
    
    // SETTERS (Métodos de Escritura)
    void setNombre(const char* nuevoNombre);
    void setDireccion(const char* nuevaDireccion);
    void setTelefono(const char* nuevoTelefono);

    
    // Generadores de ID (obtienen el ID actual y lo incrementan)
    int generarNuevoIDPaciente(); 
    int generarNuevoIDDoctor();
    int generarNuevoIDCita();
    int generarNuevoIDConsulta();
    
    // Incrementadores de Totales
    void incrementarPacientesRegistrados();
    void incrementarDoctoresRegistrados();
    void incrementarCitasAgendadas();
    void incrementarConsultasRealizadas();
};

#endif // HOSPITAL_HPP