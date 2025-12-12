#include "pacientes.hpp" // Incluye la declaración de la clase
#include <iostream> 
#include <cstring>  
#include <cctype>
#include <cstddef>

using namespace std; 

// Devuelve el tamaño exacto del objeto en bytes, ayuda al gestor de archivos 
size_t Paciente::obtenerTamano() {
    return sizeof(Paciente);
}

// Constructor por Defecto, (binarios)
Paciente::Paciente() : id(0), edad(0), sexo(' ') {
    strcpy(nombre, ""); 
    strcpy(apellido, ""); 
    strcpy(cedula, ""); 
    strcpy(tipoSangre, ""); 
    strcpy(telefono, ""); 
    strcpy(direccion, ""); 
    strcpy(email, "");
}

// Constructor con P setters para asignar y validar
Paciente::Paciente(int id, const char* n, const char* a, const char* c, int e, 
                   char s, const char* ts, const char* t, const char* d, const char* em) {
    // La asignación a través de setters garantiza que los datos se validen al ser creados
    setID(id);
    setNombre(n);
    setApellido(a);
    setCedula(c);
    setEdad(e);
    setSexo(s);
    setTipoSangre(ts);
    setTelefono(t);
    setDireccion(d);
    setEmail(em);
}


// GETTERS (Métodos de Lectura)
int Paciente::getID() const { return id; } 
const char* Paciente::getNombre() const { return nombre; }
const char* Paciente::getApellido() const { return apellido; }
const char* Paciente::getCedula() const { return cedula; }
int Paciente::getEdad() const { return edad; }
char Paciente::getSexo() const { return sexo; }
const char* Paciente::getTipoSangre() const { return tipoSangre; }
const char* Paciente::getTelefono() const { return telefono; }
const char* Paciente::getDireccion() const { return direccion; }
const char* Paciente::getEmail() const { return email; }

// SETTERS (Métodos de Escritura y Validación)

void Paciente::setID(int nuevoID) {
    if (nuevoID > 0) {
        id = nuevoID;
    } else {
        cerr << "Error de validación: ID debe ser un valor positivo." << endl;
    }
}

// SETTERS PARA CHAR[]: Validan longitud (para evitar overflow)
void Paciente::setNombre(const char* nuevoNombre) { // portero de seguridad 

    if (std::strlen(nuevoNombre) < sizeof(nombre)) { // valias tamano
        std::strcpy(nombre, nuevoNombre); // mide
    } else {
        cerr << "Error: Nombre demasiado largo. No asignado." << endl;
    }
}

void Paciente::setApellido(const char* nuevoApellido) {
    if (std::strlen(nuevoApellido) < sizeof(apellido)) {
        std::strcpy(apellido, nuevoApellido);
    } else {
        cerr << "Error: Apellido demasiado largo. No asignado." << endl;
    }
}

void Paciente::setCedula(const char* nuevaCedula) {
    if (std::strlen(nuevaCedula) < sizeof(cedula)) {
        // TODO: En el módulo 'Utilidades' se pueden agregar validaciones más complejas de formato.
        std::strcpy(cedula, nuevaCedula);
    } else {
        cerr << "Error: Cédula demasiado larga. No asignada." << endl;
    }
}

void Paciente::setTipoSangre(const char* nuevoTipoSangre) {
    if (std::strlen(nuevoTipoSangre) < sizeof(tipoSangre)) {
        // TODO: Validar que sea un tipo de sangre válido (A+, O-, etc.)
        std::strcpy(tipoSangre, nuevoTipoSangre);
    } else {
        cerr << "Error: Tipo de Sangre demasiado largo. No asignado." << endl;
    }
}

void Paciente::setTelefono(const char* nuevoTelefono) {
    if (std::strlen(nuevoTelefono) < sizeof(telefono)) {
        // TODO: Validar que solo contenga dígitos.
        std::strcpy(telefono, nuevoTelefono);
    } else {
        cerr << "Error: Teléfono demasiado largo. No asignado." << endl;
    }
}

void Paciente::setDireccion(const char* nuevaDireccion) {
    if (std::strlen(nuevaDireccion) < sizeof(direccion)) {
        std::strcpy(direccion, nuevaDireccion);
    } else {
        cerr << "Error: Dirección demasiado larga. No asignada." << endl;
    }
}

void Paciente::setEmail(const char* nuevoEmail) { //mide lo qeu entra ey el espacio 
    if (std::strlen(nuevoEmail) < sizeof(email)) {
        // TODO: Validar formato de email (@, .)
        std::strcpy(email, nuevoEmail);
    } else {
        cerr << "Error: Email demasiado largo. No asignado." << endl;
    }
}


void Paciente::setEdad(int nuevaEdad) {
    // Validación de rango lógico
    if (nuevaEdad >= 0 && nuevaEdad <= 120) {
        edad = nuevaEdad;
    } else {
        cerr << "Error de validación: Edad inválida (0-120). No asignada." << endl;
    }
}

void Paciente::setSexo(char nuevoSexo) {
    // Estandarizar a mayúscula para simplificar
    char s = std::toupper(nuevoSexo);
    if (s == 'M' || s == 'F') {
        sexo = s;
    } else {
        cerr << "Error de validación: Sexo inválido. Debe ser 'M' o 'F'. No asignado." << endl;
    }
}