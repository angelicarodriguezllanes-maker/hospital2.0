#include "Doctor.hpp"
#include <iostream>
#include <algorithm> // tiene funciones y procesa datos  Para std::remove
#include <cmath> 

// llama a las demas bibliotecas para utilizar sus funciones 
#include "../utilidades/Validaciones.hpp"  //hoja de ruta en el mismo codigo 

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
    for (int i = 0; i < MAX_PACIENTES_ASIGNADOS; ++i) pacientesIDs[i] = 0;
    for (int i = 0; i < MAX_CITAS_AGENDADAS; ++i) citasIDs[i] = 0;
}

Doctor::Doctor(int _id, const char* _nombre, const char* _apellido, const char* _cedula)
    : Doctor() // Llamar al constructor  para inicializar todo
{
    // Usar setters para aplicar validaciones si es necesario
    setId(_id);
    setNombre(_nombre);
    setApellido(_apellido);
    setCedula(_cedula);
    // El resto se inicializa por defecto y se puede modificar después
}

int Doctor::getPacienteID(int indice) const {
    if (indice >= 0 && indice < cantidadPacientes) {
        return pacientesIDs[indice];
    }
    return -1; // Retorna -1 si el índice es inválido
}

// ===========================================
//              2. SETTERS CON VALIDACIÓN
// ===========================================

void Doctor::setId(int nuevoId) {
    if (nuevoId > 0) {
        id = nuevoId;
        // Nota: Generalmente el ID no actualiza la fecha de modificación
    } else {
        cerr << "Error (Doctor): ID inválido. Debe ser positivo." << endl;
    }
}

void Doctor::setNombre(const char* nuevoNombre) {
    if (nuevoNombre && strlen(nuevoNombre) > 0 && strlen(nuevoNombre) < sizeof(nombre)) {
        // Validación de negocio simple: solo letras (se asume Validaciones::contieneSoloLetras)
        // if (Validaciones::contieneSoloLetras(nuevoNombre)) {
            strcpy(nombre, nuevoNombre);
            fechaModificacion = time(nullptr);
        // } else {
        //     cerr << "Error (Doctor): El nombre solo debe contener letras." << endl;
        // }
    } else {
        cerr << "Error (Doctor): Nombre inválido o muy largo." << endl;
    }
}

void Doctor::setApellido(const char* nuevoApellido) {
    if (nuevoApellido && strlen(nuevoApellido) > 0 && strlen(nuevoApellido) < sizeof(apellido)) {
        strcpy(apellido, nuevoApellido);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Apellido inválido o muy largo." << endl;
    }
}

void Doctor::setCedula(const char* nuevaCedula) {
    if (Validaciones::validarCedula(nuevaCedula) && strlen(nuevaCedula) < sizeof(cedula)) {
        strcpy(cedula, nuevaCedula);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Cédula inválida o muy larga (max " << sizeof(cedula) - 1 << ")." << endl;
    }
}

void Doctor::setEspecialidad(const char* nuevaEspecialidad) {
    if (nuevaEspecialidad && strlen(nuevaEspecialidad) > 0 && strlen(nuevaEspecialidad) < sizeof(especialidad)) {
        strcpy(especialidad, nuevaEspecialidad);
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Especialidad inválida o muy larga." << endl;
    }
}

void Doctor::setAniosDeExperiencia(int anios) {
    if (anios >= 0 && anios <= 70) { 
        aniosDeExperiencia = anios;
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): Años de experiencia deben ser entre 0 y 70." << endl;
    }
}

void Doctor::setCostoDeLaConsulta(float costo) {
    // Se asume que el costo de la consulta debe ser positivo.
    if (costo >= 0.0f) { 
        costoDeLaConsulta = costo;
        fechaModificacion = time(nullptr);
    } else {
        cerr << "Error (Doctor): El costo de la consulta no puede ser negativo." << endl;
    }
}

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


// ===========================================
//          3. MÉTODOS DE VALIDACIÓN
// ===========================================

bool Doctor::especialidadEsValida() const {
    // Lógica más allá del largo: verificar que la especialidad esté en un catálogo
    if (strlen(especialidad) == 0) return false;
    // Se asume una función de utilidad que verifica si la especialidad existe en la lista maestra.
    // return Validaciones::verificarEspecialidad(especialidad); 
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

// ===========================================
//          4. GESTIÓN DE RELACIONES
// ===========================================

bool Doctor::agregarPacienteID(int pacienteID) {
    if (cantidadPacientes < MAX_PACIENTES_ASIGNADOS && pacienteID > 0) {
        // Evitar duplicados antes de agregar (opcional)
        // for (int i = 0; i < cantidadPacientes; ++i) { if (pacientesIDs[i] == pacienteID) return false; }
        
        pacientesIDs[cantidadPacientes++] = pacienteID;
        fechaModificacion = time(nullptr);
        return true;
    }
    return false;
}

bool Doctor::eliminarPacienteID(int pacienteID) {
    int* inicio = pacientesIDs;
    int* fin = pacientesIDs + cantidadPacientes;
    
    // std::remove mueve el elemento a eliminar al final y retorna el nuevo final lógico
    int* nuevo_fin = remove(inicio, fin, pacienteID);

    if (nuevo_fin != fin) { // Si algo fue removido
        cantidadPacientes = nuevo_fin - inicio;
        fechaModificacion = time(nullptr);
        return true;
    }
    return false;
}

bool Doctor::agregarCitaID(int citaID) {
    if (cantidadCitas < MAX_CITAS_AGENDADAS && citaID > 0) {
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

// ===========================================
//          5. MÉTODOS DE PRESENTACIÓN
// ===========================================

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
    // cout << " - Última Modificación: " << Formatos::formatearFecha(fechaModificacion) << endl;
}