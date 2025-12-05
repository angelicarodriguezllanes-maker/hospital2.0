#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <string> // Necesario para std::string si se usara, pero buena práctica

class Hospital {
private: //identificacion
    char nombre[100];
    char direccion[200];
    char telefono[20];
    
    // contadores para ids
    int proximoIDPaciente;
    int proximoIDDoctor;
    int proximoIDCita;
    int proximoIDConsulta; 
    
    // estadisticas
    int pacientesRegistrados; 
    int doctoresRegistrados;
    int citasAgendadas;
    int consultasRealizadas; 

public:
    //constructores
    Hospital();
    Hospital(const char* nombre, const char* direccion, const char* telefono);
    
    // Getters para datos fijos
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const; 

    // Getters para los próximos IDs
    int getProximoIDPaciente() const;
    int getProximoIDDoctor() const;
    int getProximoIDCita() const; 
    int getProximoIDConsulta() const; 

    // Getters para las estadísticas (Totales)
    int getPacientesRegistrados() const; 
    int getDoctoresRegistrados() const;
    int getCitasAgendadas() const;
    int getConsultasRealizadas() const; 
    
    // MÉTODOS GENERADORES 
    int generarNuevoIDPaciente(); 
    int generarNuevoIDDoctor();
    int generarNuevoIDCita(); 
    int generarNuevoIDConsulta(); 
    
    //SETTERS, para modificar los datos fijos del hospital
    void setNombre(const char* nuevoNombre);
    void setDireccion(const char* nuevaDireccion); 
    void setTelefono(const char* nuevoTelefono); 

    //metodos de incrementacion totales
    void incrementarPacientesRegistrados(); 
    void incrementarDoctoresRegistrados(); 
    void incrementarCitasAgendadas(); 
    void incrementarConsultasRealizadas(); 
};

#endif 