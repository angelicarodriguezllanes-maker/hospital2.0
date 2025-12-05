#include "OperadorPacientes.hpp" // "" para buscar adentro de los archivos 
#include <iostream>
#include <cstring>
#include <cmath> // Para floor

using namespace std; 

//constructor
OperadorPacientes::OperadorPacientes() 
    capacidadMaxima_(TAMANO_INICIAL), 
    cantidadActual_(0), 
    ultimoIDAsignado_(0) 
{
    // Asignación de memoria para el array inicial
    listaPacientes_ = new Paciente[capacidadMaxima_];
}

//libera memoria
OperadorPacientes::~OperadorPacientes() {
    delete[] listaPacientes_; 
}

// Verifica si el array está lleno y lo expande
void OperadorPacientes::verificarYExpandir() {
    // Si la cantidad actual es igual o mayor a la capacidad máxima, expandimos.
    if (cantidadActual_ >= capacidadMaxima_) {
        // 1. Calcula la nueva capacidad (ej: 10 * 1.5 = 15)
        int nuevaCapacidad = static_cast<int>(floor(capacidadMaxima_ * FACTOR_CRECIMIENTO));
        
        // 2. Asigna un nuevo bloque de memoria más grande
        Paciente* nuevoArray = new Paciente[nuevaCapacidad];

        // 3. Copia los elementos antiguos al nuevo array
        for (int i = 0; i < cantidadActual_; ++i) {
            // Se usa la sobrecarga de operador de asignación de struct (copia bit a bit)
            nuevoArray[i] = listaPacientes_[i]; 
        }

        // 4. Libera la memoria del array antiguo
        delete[] listaPacientes_;

        // 5. Actualiza el puntero y la capacidad
        listaPacientes_ = nuevoArray;
        capacidadMaxima_ = nuevaCapacidad;
        
        cout << "📢 Array de pacientes expandido a " << nuevaCapacidad << " de capacidad." << endl;
    }
}

// --------------------------------------------------------------------------------
// Auxiliar: Genera el siguiente ID secuencial
// --------------------------------------------------------------------------------
int OperadorPacientes::getSiguienteID() {
    return ++ultimoIDAsignado_;
}

// --------------------------------------------------------------------------------
// CRUD: Agregar un Paciente
// --------------------------------------------------------------------------------
bool OperadorPacientes::agregarPaciente(const Paciente& nuevoPaciente) {
    
    // 1. Verifica y expande la capacidad si es necesario
    verificarYExpandir();
    
    // 2. Trabajamos con una copia mutable
    Paciente p = nuevoPaciente;
    
    // 3. Asignar ID y fechas
    if (p.id == -1) {
        p.id = getSiguienteID();
    } // Se asume que el manejo de ID preexistente está bien si no es -1
    
    time_t now = time(0);
    p.fechaCreacion = now;
    p.fechaModificacion = now;

    // 4. Añadir al array dinámico y aumentar el contador
    listaPacientes_[cantidadActual_] = p;
    cantidadActual_++;
    
    cout << "✅ Paciente '" << p.nombre << " " << p.apellido 
         << "' agregado con ID: " << p.id << endl;
         
    return true;
}

// --------------------------------------------------------------------------------
// CRUD: Buscar Paciente por ID
// --------------------------------------------------------------------------------
Paciente* OperadorPacientes::buscarPacientePorID(int id) {
    
    for (int i = 0; i < cantidadActual_; ++i) {
        if (listaPacientes_[i].id == id) {
            // Devolvemos un puntero al elemento en el array
            return &listaPacientes_[i];
        }
    }
    return nullptr; 
}

// --------------------------------------------------------------------------------
// CRUD: Actualizar Paciente
// --------------------------------------------------------------------------------
bool OperadorPacientes::actualizarPaciente(const Paciente& pacienteModificado) {
    
    Paciente* pExistente = buscarPacientePorID(pacienteModificado.id);
    
    if (pExistente != nullptr) {
        time_t fechaCreacionOriginal = pExistente->fechaCreacion;
        
        // Copia todos los campos del struct
        *pExistente = pacienteModificado; 
        
        // Actualiza metadatos
        pExistente->fechaCreacion = fechaCreacionOriginal;
        pExistente->fechaModificacion = time(0);
        
        cout << "🔄 Paciente ID " << pExistente->id << " actualizado correctamente." << endl;
        return true;
    }
    
    cout << "❌ Error: No se puede actualizar. Paciente ID " << pacienteModificado.id << " no encontrado." << endl;
    return false;
}

// --------------------------------------------------------------------------------
// CRUD: Eliminar Paciente (Soft Delete)
// --------------------------------------------------------------------------------
bool OperadorPacientes::eliminarPaciente(int id) {
    
    Paciente* p = buscarPacientePorID(id);
    
    if (p != nullptr) {
        if (p->activo) {
            // Eliminación lógica
            p->activo = false;
            p->eliminado = true;
            p->fechaModificacion = time(0);
            
            cout << "🗑️ Paciente ID " << id << " eliminado (Soft Delete)." << endl;
            return true;
        } else {
            cout << "⚠️ Advertencia: Paciente ID " << id << " ya estaba inactivo." << endl;
            return false;
        }
    }
    
    cout << "❌ Error: Paciente ID " << id << " no encontrado para eliminar." << endl;
    return false;
}

// --------------------------------------------------------------------------------
// Auxiliar: Listar todos los pacientes activos
// --------------------------------------------------------------------------------
void OperadorPacientes::listarActivos() const {
    if (cantidadActual_ == 0) {
        cout << "La lista de pacientes está vacía." << endl;
        return;
    }

    cout << "\n--- LISTA DE PACIENTES ACTIVOS (" << cantidadActual_ << " en el sistema) ---" << endl;
    for (int i = 0; i < cantidadActual_; ++i) {
        const auto& p = listaPacientes_[i];
        if (p.activo && !p.eliminado) {
            cout << "ID: " << p.id 
                 << ", Nombre: " << p.nombre << " " << p.apellido 
                 << ", Cédula: " << p.cedula 
                 << endl;
        }
    }
    cout << "---------------------------------------------------------\n" << endl;
}