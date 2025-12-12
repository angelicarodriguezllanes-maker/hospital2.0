#include "operacionesPacientes.hpp"
#include "../persistencia/GestorArchivos.hpp" // Necesario para guardar en archivo
#include "../persistencia/Constantes.hpp"     // Rutas de archivos binarios
#include <iostream>

using namespace std;

void registrarpaciente(Hospital& hospital) {
    // 1. Obtener nuevo ID desde el Hospital (responsabilidad del Hospital)
    int nuevoID = hospital.generarNuevoIDPaciente(); // Método de Hospital.hpp [cite: 213]
    
    // 2. Crear instancia de la Entidad (responsabilidad de Paciente)
    Paciente nuevopaciente(nuevoID, "","","", 0, "M", ""); // Constructor con parámetros
    
    // 3. Obtener datos por consola (estandar)
    // TODO: Usar cin para llenar los datos de nuevoPaciente

    // 4. Validar datos (responsabilidad de Paciente)
    if (!nuevoPaciente.validarDatos()) { // Método de Paciente.hpp 
        cout << "Error: Los datos del paciente no son válidos." << endl;
        hospital.decrementarIDPaciente(); // Revertir el contador de ID
        return;
    }

    // 5. Guardar en archivo (responsabilidad de GestorArchivos)
    if (GestorArchivos::guardarRegistro(&nuevoPaciente, sizeof(Paciente), Constantes::RUTA_PACIENTES)) { 
        cout << "Paciente registrado con éxito. ID: " << nuevoID << endl;
        hospital.incrementarPacientesRegistrados(); // Actualizar estadística del Hospital [cite: 214]
        GestorArchivos::guardarHospital(hospital); // Guardar cambios en el Hospital
    } else {
        cout << "Error al guardar el paciente en el archivo." << endl;
        hospital.decrementarIDPaciente();
    }
}