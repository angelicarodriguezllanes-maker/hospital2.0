#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <cstring>  // Para strcpy ,  strlen    ( caracteres de ubicaion y calculalongitud de la posiscion de la cadena ) 
#include <ctime>    // Para time_t, time()

// Constantes para gestión de arrays fijos
const int MAX_PACIENTES_ASIGNADOS = 50; // Capacidad máxima de pacientes fijos por registro
const int MAX_CITAS_AGENDADAS = 10;     // Capacidad máxima de citas fijas por registro

class Doctor {
private:
    int id;
    char nombre[50]; 
    char apellido[50]; 
    char cedula[20];
    char especialidad[50];
    int aniosDeExperiencia;
    float costoDeLaConsulta;
    char horarioAtencion[50]; 
    char email[50];
    char telefono[15];

    //arrays fijos vs ids
    int pacientesIDs[MAX_PACIENTES_ASIGNADOS];
    int cantidadPacientes;
    
    int citasIDs[MAX_CITAS_AGENDADAS];
    int cantidadCitas;
    
    bool disponible;
    
    // datos para control 
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    Doctor(); // Constructor 
    // Constructor con parámetros principales 
    Doctor(int _id, const char* _nombre, const char* _apellido, const char* _cedula);

    // GETTERS (SIEMPRE const) 
    int getId() const { return id; }
    const char* getNombre() const { return nombre; }
    const char* getApellido() const { return apellido; }
    const char* getCedula() const { return cedula; }
    const char* getEspecialidad() const { return especialidad; }
    int getAniosDeExperiencia() const { return aniosDeExperiencia; }
    float getCostoDeLaConsulta() const { return costoDeLaConsulta; }
    const char* getHorarioAtencion() const { return horarioAtencion; }
    const char* getTelefono() const { return telefono; }
    const char* getEmail() const { return email; }
    bool estaDisponible() const { return disponible; }
    int getCantidadPacientes() const { return cantidadPacientes; }
    int getCantidadCitas() const { return cantidadCitas; }
    int getPacienteID(int indice) const; // getter para obtener un id de paciente por indice
    int getCitaID(int indice) const; 

    time_t getFechaCreacion() const { return fechaCreacion; }
    time_t getFechaModificacion() const { return fechaModificacion; }


    // SETTERS 
    void setId(int nuevoId);
    void setNombre(const char* nuevoNombre);
    void setApellido(const char* nuevoApellido);
    void setCedula(const char* nuevaCedula);
    void setEspecialidad(const char* nuevaEspecialidad);
    void setAniosDeExperiencia(int anios); // Validación: anios >= 0
    void setCostoDeLaConsulta(float costo); [cite_start]// Validación: rango razonable [cite: 99]
    void setHorarioAtencion(const char* horario);
    void setTelefono(const char* telefono);
    void setEmail(const char* email); [cite_start]// Validación: formato válido de email [cite: 94]
    void setDisponible(bool estado);

    void setFechaCreacion(time_t fecha);
    void setFechaModificacion(time_t fecha);

    // MÉTODOS DE VALIDACIÓN ESPECÍFICOS
    bool validarDatos() const; // Verifica que todos los datos sean correctos
    bool especialidadEsValida() const;// Verifica lista de especialidades válidas 
    bool cedulaProfesionalValida() const; // Puede llamar a Validaciones
    
    // GESTIÓN DE RELACIONES 
    bool agregarPacienteID(int pacienteID);
    bool eliminarPacienteID(int pacienteID);
    bool agregarCitaID(int citaID);
    bool eliminarCitaID(int citaID);

    // MÉTODOS DE PRESENTACIÓN 
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    //metodo para obtener el tamano del doctor
    static size_t obtenerTamano() { return sizeof(Doctor); }
};

#endif // DOCTOR_HPP