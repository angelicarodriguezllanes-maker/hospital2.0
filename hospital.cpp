#include <iostream>
#include <cstring>
#include <iomanip> //salida de datos
#include <ctime>   // validación de fecha 
#include <cctype>  // comparaciones 
using namespace std;

//funciones
Hospital* inicializarHospital(const char* nombre, const char* direccion, const char* telefono);

destruirHospital(Hospital* hospital);//libera la memoria 

redimensionarArrayInt(int* &array, int &cantidad, int &capacidad); 

bool removerIdDeArray(int* &array, int &cantidad, int id);

bool validarFecha(const char* fecha);

bool validarHora(const char* hora)

redimensionarArrayPacientes(Hospital* hospital); 

Paciente* buscarPacientePorId(Hospital* hospital, int id);

bool eliminarPaciente(Hospital* hospital, int id); 

listarPacientes(Hospital* hospital);  

agregarConsultaAlHistorial(Paciente* paciente, HistorialMedico consulta);

redimensionarArrayDoctores(Hospital* hospital);

Doctor* buscarDoctorPorId(Hospital* hospital, int id); 

Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido, 
                    const char* cedula, const char* especialidad, float costoConsulta, int experiencia); 

redimensionarArrayCitas(Hospital* hospital);

bool verificarDisponibilidad(Hospital* hospital, int idDoctor, const char* fecha, const char* hora);

Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor,
                  const char* fecha, const char* hora, const char* motivo); 

bool cancelarCita(Hospital* hospital, int idCita); 

cargarDatosIniciales(Hospital* hospital); 

menuDoctores(Hospital* hospital); 

menuPacientes(Hospital* hospital); 

void menuCitas(Hospital* hospital); 


int main() {
    mensajeBienvenida();

    Hospital* hospital = inicializarHospital("Hospital Universitario", "Av. Universidad", "0261-7550000");

    cargarDatosIniciales(hospital);
    
    int opcion;

    do {
        cout << "\n╔════════════════════════════════════════╗" << endl;
        cout << "║          MENÚ PRINCIPAL                ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        cout << "1. Gestión de Pacientes" << endl;
        cout << "2. Gestión de Doctores" << endl;
        cout << "3. Gestión de Citas" << endl;
        cout << "4. SALIR DEL SISTEMA" << endl;
        cout << "Seleccione una opción: ";
        
        if (!(cin >> opcion)) {
            cout << "ERROR: Entrada inválida. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n'); 

        switch (opcion) {
            case 1: menuPacientes(hospital); break;
            case 2: menuDoctores(hospital); break;
            case 3: menuCitas(hospital); break;
            case 4: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);
    
    // Limpieza de memoria crítica al finalizar
    destruirHospital(hospital);
    
    return 0;
}
    
