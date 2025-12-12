
#include <iostream>
#include <limits>    
#include <cstdlib>  

#include "hospital/Hospital.hpp"
#include "persistencia/constante.hpp"
#include "persistencia/gestorarchivos.hpp" 
#include "utilidades/Validaciones.hpp" // Para limpiar el buffer


#include "pacientes/operacionesPacientes.hpp"
#include "doctores/doctores.hpp"
#include "citas/citas.hpp"
#include "historial/historial.hpp"

using namespace std;


void menuPrincipal(Hospital& hospital); // Corregido para recibir la instancia
void menuPacientes(Hospital& hospital);
void menuDoctores(Hospital& hospital);
void menuCitas(Hospital& hospital);
void menuHistorial(Hospital& hospital);

int main() {
    // 1. Inicialización del Sistema
    cout << "Inicializando Sistema de Gestión Hospitalaria..." << endl;
    
    // Verifica y crea la carpeta 'datos' y los archivos .dat si no existen
    GestorArchivos::inicializarSistemaArchivos(); 
    
    // 2. Carga del Hospital (Metadata y Contadores)
    Hospital hospital;

    // Intenta cargar los datos del Hospital (ID, contadores) desde hospital
    if (!GestorArchivos::cargarHospital(hospital)) { 
         // Si la carga falla (archivo no existe), inicializa el sistema
         hospital = Hospital("Hospital ", "Maracaibo", "555-1234");
         GestorArchivos::guardarHospital(hospital); // Guarda la versión inicial
         cout << "Datos iniciales del Hospital creados." << endl;
    } else {
         cout << "Datos del Hospital cargados desde archivo." << endl;
    }

    menuPrincipal(hospital); 

    // 4. Guardar antes de salir
    GestorArchivos::guardarHospital(hospital);
    cout << "\nDatos finales del Hospital guardados. Saliendo..." << endl;

    return 0;
}

void menuPrincipal(Hospital& hospital) {
    int opcion = 0;
                       
    do {
        system("cls"); 
        cout << "========================================" << endl;
        cout << "    SISTEMA DE GESTIÓN HOSPITALARIA     " << endl;
        cout << "========================================" << endl;
        cout << "1. Gestión de Pacientes" << endl;
        cout << "2. Gestión de Doctores" << endl;
        cout << "3. Gestión de Citas Médicas" << endl;
        cout << "4. Gestión de Historiales Clínicos" << endl;
        cout << "5. Reportes y Estadísticas" << endl;
        cout << "0. Salir del Sistema" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            Validaciones::limpiarBufferEntrada();
            opcion = -1; // Opción inválida
        } else {
            Validaciones::limpiarBufferEntrada();
        }

        switch (opcion) {
            case 1: menuPacientes(hospital); break;
            case 2: menuDoctores(hospital); break;
            case 3: menuCitas(hospital); break;
            case 4: menuHistorial(hospital); break;
            case 5: hospital.mostrarEstadisticas(); break; // Asumiendo un método en Hospital
            case 0: break;
            default: cout << "\nOpción no válida. Intente de nuevo.\n"; break;
        }

        if (opcion != 0) {
             cout << "\nPresione ENTER para continuar...";
             cin.get(); // Espera a que el usuario presione Enter
        }

    } while (opcion != 0);
}

void menuPacientes(Hospital& hospital) {
    int opcion = 0;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "       MENÚ: GESTIÓN DE PACIENTES       " << endl;
        cout << "========================================" << endl;
        cout << "1. Registrar Nuevo Paciente" << endl;
        cout << "2. Modificar Datos de Paciente" << endl;
        cout << "3. Buscar Paciente (ID/Cédula)" << endl;
        cout << "4. Listar Todos los Pacientes" << endl;
        cout << "5. Eliminar Paciente (Borrado Lógico)" << endl; // Agregamos Eliminar
        cout << "0. Volver al Menú Principal" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            Validaciones::limpiarBufferEntrada();
            opcion = -1; 
        } else {
            Validaciones::limpiarBufferEntrada();
        }

        switch (opcion) {
            case 1: registrarPaciente(hospital); break;  // Llama a operacionesPacientes
            case 2: modificarPaciente(); break;      
            case 3: buscarPaciente(); break;            
            case 4: listarPacientes(); break;            
            case 5: eliminarPaciente(); break;           
            case 0: break;
            default: cout << "\nOpción no válida. Intente de nuevo.\n"; break;
        }

        if (opcion != 0) {
             cout << "\nPresione ENTER para continuar...";
             cin.get();
        }

    } while (opcion != 0);
}

void menuDoctores(Hospital& hospital) {
    int opcion = 0;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "       MENÚ: GESTIÓN DE DOCTORES        " << endl;
        cout << "========================================" << endl;
        cout << "1. Registrar Nuevo Doctor" << endl;
        cout << "2. Modificar Datos de Doctor" << endl;
        cout << "3. Buscar Doctor (ID/Cédula)" << endl;
        cout << "4. Listar Todos los Doctores" << endl;
        cout << "5. Eliminar Doctor (Borrado Lógico)" << endl;
        cout << "0. Volver al Menú Principal" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            Validaciones::limpiarBufferEntrada();
            opcion = -1; 
        } else {
            Validaciones::limpiarBufferEntrada();
        }

        switch (opcion) {
            case 1: registrarDoctor(hospital); break;  // Llama a operacionesDoctores
            case 2: modificarDoctor(); break;        
            case 3: buscarDoctor(); break;            
            case 4: listarDoctores(); break;          
            case 5: eliminarDoctor(); break;          
            case 0: break;
            default: cout << "\nOpción no válida. Intente de nuevo.\n"; break;
        }

        if (opcion != 0) {
             cout << "\nPresione ENTER para continuar...";
             cin.get();
        }

    } while (opcion != 0);
}


void menuCitas(Hospital& hospital) {
    int opcion = 0;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "     MENÚ: GESTIÓN DE CITAS MÉDICAS     " << endl;
        cout << "========================================" << endl;
        cout << "1. Agendar Nueva Cita" << endl;
        cout << "2. Cancelar Cita Existente" << endl;
        cout << "3. Modificar Cita (Fecha/Doctor)" << endl;
        cout << "4. Listar Citas Pendientes" << endl;
        cout << "0. Volver al Menú Principal" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            Validaciones::limpiarBufferEntrada();
            opcion = -1; 
        } else {
            Validaciones::limpiarBufferEntrada();
        }

        switch (opcion) {
            case 1: agendarCita(hospital); break; // Llama a operacionesCitas
            case 2: cancelarCita(); break;       
            case 3: modificarCita(); break;     
            case 4: listarCitas(); break;     
            case 0: break;
            default: cout << "\nOpción no válida. Intente de nuevo.\n"; break;
        }

        if (opcion != 0) {
             cout << "\nPresione ENTER para continuar...";
             cin.get();
        }

    } while (opcion != 0);
}

void menuHistorial(Hospital& hospital) {
    int opcion = 0;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << " MENÚ: GESTIÓN DE HISTORIALES CLÍNICOS  " << endl;
        cout << "========================================" << endl;
        cout << "1. Crear Historial (Asociar Primera Cita)" << endl;
        cout << "2. Agregar Consulta a Historial Existente" << endl;
        cout << "3. Buscar Historial por ID de Paciente" << endl;
        cout << "4. Listar Todos los Historiales" << endl;
        cout << "0. Volver al Menú Principal" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            Validaciones::limpiarBufferEntrada();
            opcion = -1; 
        } else {
            Validaciones::limpiarBufferEntrada();
        }

        switch (opcion) {
            case 1: crearHistorial(hospital); break;     // Llama a operacionesHistorial
            case 2: agregarConsulta(); break;           
            case 3: buscarHistorial(); break;           
            case 4: listarHistoriales(); break;       
            case 0: break;
            default: cout << "\nOpción no válida. Intente de nuevo.\n"; break;
        }

        if (opcion != 0) {
             cout << "\nPresione ENTER para continuar...";
             cin.get();
        }

    } while (opcion != 0);
}