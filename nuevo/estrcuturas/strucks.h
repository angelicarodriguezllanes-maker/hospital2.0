#include <ctime>
#include <cstddef> // Para el uso de size_t si es necesario (aunque no directamente en estas structs)

struct ArchivoHeader { // indice del libro
    int cantidadRegistros = 0;      // conteo de registros
    int proximoID = 1;              
    int registrosActivos = 0;      
    int version = 2;                // Versión del formato del archivo para saber como se va a abrir 
};
//hospital.bin
struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];

    // Contadores de IDs 
    int siguienteIDPaciente;
    int siguienteIDDoctor;
    int siguienteIDCita;
    int siguienteIDConsulta;

    //totales 
    int totalPacientesRegistrados;
    int totalDoctoresRegistrados;
    int totalCitasAgendadas;
    int totalConsultasRealizadas;
};

// pacientes.bin
struct Paciente {
    int id; 
    char nombre[50];
    char apellido[50];
    char cedula[20]; 
    int edad;
    char sexo; 
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    char alergias[500];
    char observaciones[500];

    // Índice para Historial Médico
    int cantidadConsultas;  
    int primerConsultaID; 

    // Índice Citas
    int citasIDs[20];       
    int cantidadCitas;     

    //egistro
    bool activo; 
    bool eliminado;       
    time_t fechaCreacion;   // guarda la fecha y la hora de su creacion
    time_t fechaModificacion; // guarda la fecha y la hora de la modificacion
};

//doctores.bin
struct Doctor {
    int id;
    char nombre[50]; 
    char apellido[50]; 
    char cedulaProfesional[20]; 
    char especialidad[50];
    int aniosExperiencia;       
    float costoConsulta;       
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    bool disponible;

    int pacientesIDs[50];   // Array FIJO de IDs de pacientes asignados (máx 50) [cite: 63]
    int cantidadPacientes;
    
    int citasIDs[30];       // Array FIJO de IDs de citas agendadas
    int cantidadCitas;

    // Metadata de registro
    bool eliminado;         // borrado logico, etiqueta ignorar
    time_t fechaCreacion; // guarda fecha y hora exacta (modificacion)
    time_t fechaModificacion; 
};
//citas.bin
struct Cita {
    int id; 
    int pacienteID; 
    int doctorID; 
    char fecha[11]; 
    char hora[6]; 
    char motivo[150]; 
    char estado[20];       
    char observaciones[200];
    bool atendida;
    
    int consultaID;         
    bool eliminado;         //data del registro

    time_t fechaCreacion; //guarda fecha y modificacion 
    time_t fechaModificacion; 
};

//historial.bin
struct HistorialMedico {
    int id;                
    int pacienteID;         
    char fecha[11]; 
    char hora[6]; 
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int doctorID;
    float costo;
    
    // Índice de navegación
    int siguienteConsultaID; 

    // data de registro
    bool eliminado;        //borrado logico con etiqueta ignorar
    time_t fechaRegistro; //guarda fecha del registro
};
