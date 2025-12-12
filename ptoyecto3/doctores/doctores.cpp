#include "doctores.hpp"
#include <iostream>
#include <algorithm> // tiene funciones y procesa datos  Para std::remove
#include <cmath> 

// llama a las demas bibliotecas para utilizar sus funciones 
#include "../utilidades/Validaciones.hpp"  //llama a las validaciones del mismo codigo para utilizarlas

using namespace std;

//constructores
Doctor::Doctor() : id(0), aniosDeExperiencia(0), costoDeLaConsulta(0.0f), // lidts fr inicilizacion, da valores a los atributos 
                   cantidadPacientes(0), cantidadCitas(0), disponible(true) {
    // Inicializar todos los strings en vacío
    nombre[0] = '\0'; apellido[0] = '\0'; cedula[0] = '\0'; especialidad[0] = '\0';
    horarioAtencion[0] = '\0'; telefono[0] = '\0'; email[0] = '\0';
    
    // Inicializar fechas
    fechaCreacion = time(nullptr);
    fechaModificacion = fechaCreacion;

    // Inicializar arrays de IDs a 0
    for (int i = 0; i < MAX_PACIENTES_ASIGNADOS; ++i) pacientesIDs[i] = 0;//garantiza que al iniciar el programa toas las listas de id esten en 0
    for (int i = 0; i < MAX_CITAS_AGENDADAS; ++i) citasIDs[i] = 0;
}
Doctor::Doctor(int _
    id, const char* _nombre, const char* _apellido, const char* _cedula)
    : Doctor() // Llamar al constructor (doctor)  para inicializar todo
{
    // stters para validar si es necesario 
    setId(_id);
    setNombre(_nombre);
    setApellido(_apellido);
    setCedula(_cedula);
    // El resto se inicializa por defecto y se puede modificar después (predefinidos)
}
//validacion del indice 
int Doctor::getPacienteID(int indice) const {
    if (indice >= 0 && indice < cantidadPacientes) {
        return pacientesIDs[indice];
    }
    return -1; // Retorna -1 si el índice es inválido
}

 //SETTERS CON VALIDACIONES 
//validacion de id 
void Doctor::setId(int nuevoId) {
    if (nuevoId > 0) {
        id = nuevoId;
        // Nota: Generalmente el ID no actualiza la fecha de modificación
    } else {
        cerr << "Error (Doctor): ID inválido. Debe ser positivo." << endl;
    }
}
// Validacion y asignacion del nombre
void Doctor::setNombre(const char* nuevoNombre) {
    if (nuevoNombre && strlen(nuevoNombre) > 0 && strlen(nuevoNombre) < sizeof(nombre)) { //verfica que solaemten tenga letras y no sea mas largp que el espacio
            strcpy(nombre, nuevoNombre); //copia cadenas en el nuevo nombre 
            fechaModificacion = time(nullptr);//anota las flechas y la hora actual
    } else {
        cerr << "Error (Doctor): Nombre inválido o muy largo." << endl;//se utiliza para imprimir errores
    }
}

void Doctor::setApellido(const char* nuevoApellido) { //si el nuevo aprellido es valido, se guarda y se registra la hora de modificacion
    if (nuevoApellido && strlen(nuevoApellido) > 0 && strlen(nuevoApellido) < sizeof(apellido)) {
        strcpy(apellido, nuevoApellido);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Apellido inválido o muy largo." << endl;
    }
}

void Doctor::setCedula(const char* nuevaCedula) { //hace lo mismo pero con cedula 
    if (Validaciones::validarCedula(nuevaCedula) && strlen(nuevaCedula) < sizeof(cedula)) {
        strcpy(cedula, nuevaCedula);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Cédula inválida o muy larga (max " << sizeof(cedula) - 1 << ")." << endl;
    }
}

void Doctor::setEspecialidad(const char* nuevaEspecialidad) {//hace lo mismo con la especialidad
    if (nuevaEspecialidad && strlen(nuevaEspecialidad) > 0 && strlen(nuevaEspecialidad) < sizeof(especialidad)) {
        strcpy(especialidad, nuevaEspecialidad);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Especialidad inválida o muy larga." << endl;
    }
}
void Doctor::setAniosDeExperiencia(int anios) { //hace lo mismo con la experiencia
    if (anios >= 0 && anios <= 70) { 
        aniosDeExperiencia = anios;
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Años de experiencia deben ser entre 0 y 70." << endl;
    }
}

void Doctor::setCostoDeLaConsulta(float costo) { //hace lo mismo con el costo de la consulta
    // Se asume que el costo de la consulta debe ser positivo.
    if (costo >= 0.0f) { 
        costoDeLaConsulta = costo;
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): El costo de la consulta no puede ser negativo." << endl;
    }
}
//starlen cuenta la cant de caracteres 
void Doctor::setHorarioAtencion(const char* horario) {
    if (horario && strlen(horario) > 0 && strlen(horario) < sizeof(horarioAtencion)) {
        strcpy(horarioAtencion, horario);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Horario inválido o muy largo." << endl;
    }
}

void Doctor::setTelefono(const char* nuevoTelefono) {
    if (Validaciones::validarTelefono(nuevoTelefono) && strlen(nuevoTelefono) < sizeof(telefono)) {
        strcpy(telefono, nuevoTelefono);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Teléfono inválido o muy largo." << endl;
    }
}

void Doctor::setEmail(const char* nuevoEmail) {
    if (Validaciones::validarEmail(nuevoEmail) && strlen(nuevoEmail) < sizeof(email)) {
        strcpy(email, nuevoEmail);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Formato de email inválido o muy largo." << endl;
    }
}

void Doctor::setDisponible(bool estado) {
    disponible = estado;
    fechaModificacion = time(nullptr);
}

//validacion de datos 
//strlen cuanta cuantos caracterees tiene una cadena de texto
//valida especialidad
bool Doctor::especialidadEsValida() const {
    if (strlen(especialidad) == 0) return false; // Se asume una función de utilidad que verifica si la especialidad existe en la lista maestra.
    return true; 
}

bool Doctor::validarDatos() const {
    // Llama a todos los métodos de validación de la clase
    return (id > 0 &&
            strlen(nombre) > 0 &&
            strlen(apellido) > 0 &&
            cedulaEsValida() && 
            especialidadEsValida() &&
            costoDeLaConsulta >= 0.0f);
}


bool Doctor::agregarPacienteID(int pacienteID) {
    if (cantidadPacientes < MAX_PACIENTES_ASIGNADOS && pacienteID > 0) { //verofoca e; espacio disponible
        // Evitar duplicados antes de agregar (opcional)
        
        pacientesIDs[cantidadPacientes++] = pacienteID;
        fechaModificacion = time(nullptr);
        return true;
    }///verfica si tiene cupo pero si no tiene cupo no se agrega 
    return false;
}

bool Doctor::eliminarPacienteID(int pacienteID) {
    int* inicio = pacientesIDs;//define los limites
    int* fin = pacientesIDs + cantidadPacientes;
    
    //remove mueve el elemento a eliminar al final y retorna el nuevo final lógico
    int* nuevo_fin = remove(inicio, fin, pacienteID);

    if (nuevo_fin != fin) { // berifica Si algo fue removido
        cantidadPacientes = nuevo_fin - inicio; //se ajustan los datos del doctro
        fechaModificacion = time(nullptr);
        return true;
    }
    return false;
}

bool Doctor::agregarCitaID(int citaID) {
    if (cantidadCitas < MAX_CITAS_AGENDADAS && citaID > 0) { //verifica el cupo en la agenda y si el id es valido
        citasIDs[cantidadCitas++] = citaID;
        fechaModificacion = time(nullptr);
        return true;
    }
    return false;
}

bool Doctor::eliminarCitaID(int citaID) {
    int* inicio = citasIDs;
    int* fin = citasIDs + cantidadCitas;
    
    // std::remove mueve el elemento a eliminar al final y retorna el nuevo final lógico
    int* nuevo_fin = remove(inicio, fin, citaID);

    if (nuevo_fin != fin) { // Si algo fue removido
        cantidadCitas = nuevo_fin - inicio;
        fechaModificacion = time(nullptr);
        return true;
    }
    return false;
}

void Doctor::mostrarInformacionBasica() const {
    cout << "ID: " << id
         << " | Nombre: " << nombre << " " << apellido
         << " | Especialidad: " << especialidad
         << " | Costo Consulta: $" << fixed << setprecision(2) << costoDeLaConsulta 
         << (disponible ? " (DISPONIBLE)" : " (NO DISPONIBLE)") << endl;
}

void Doctor::mostrarInformacionCompleta() const {
    mostrarInformacionBasica();
    cout << " - Cédula Profesional: " << cedula << endl;
    cout << " - Años de Experiencia: " << aniosDeExperiencia << endl;
    cout << " - Horario de Atención: " << horarioAtencion << endl;
    cout << " - Contacto: Teléfono: " << telefono << " | Email: " << email << endl;
    cout << " - Pacientes Asignados: " << cantidadPacientes << "/" << MAX_PACIENTES_ASIGNADOS << endl;
    cout << " - Citas Agendadas: " << cantidadCitas << "/" << MAX_CITAS_AGENDADAS << endl;
    // TODO: Si implementaste Formatos::formatearFecha, úsalo aquí
    cout << " - Última Modificación: " << Formatos::formatearFecha(fechaModificacion) << endl;
}