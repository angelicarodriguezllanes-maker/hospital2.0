#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdlib>

using namespace std;

Hospital* inicializarHospital(const char* nombre, const char* direccion, const char* telefono); {
    Hospital* h = new Hospital;
    
    // Inicialización de arrays dinámicos principales
    h->capacidadPacientes = 10; 
    h->pacientes = new Paciente[h->capacidadPacientes]; 
    h->capacidadDoctores = 10;
    h->doctores = new Doctor[h->capacidadDoctores]; 
    h->capacidadCitas = 20; 
    h->citas = new Cita[h->capacidadCitas]; 

    // Inicialización de datos
    strncpy(h->nombre, nombre, 99);
    strncpy(h->direccion, direccion, 149);
    strncpy(h->telefono, telefono, 14);
    h->cantidadPacientes = 0; h->cantidadDoctores = 0; h->cantidadCitas = 0;
    h->siguienteIdPaciente = 1; h->siguienteIdDoctor = 1; 
    h->siguienteIdCita = 1; h->siguienteIdConsulta = 1;

    return h;
}
bool removerIdDeArray(int* &array, int &cantidad, int id) {
    int indiceEncontrado = -1;
    for (int i = 0; i < cantidad; i++) {
        if (array[i] == id) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado != -1) {
        for (int i = indiceEncontrado; i < cantidad - 1; i++) {
            array[i] = array[i + 1];
        }
        cantidad--;
        return true;
    }
    return false;
}
//validacion
bool validarFecha(const char* fecha) {
    if (strlen(fecha) != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;
    
    int anio = atoi(fecha);
    int mes = atoi(fecha + 5);
    int dia = atoi(fecha + 8);
    
    if (anio < 2020 || mes < 1 || mes > 12 || dia < 1 || dia > 31) return false;
    
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
    if (mes == 2) {
        bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (bisiesto && dia > 29) return false;
        if (!bisiesto && dia > 28) return false;
bool validarHora(const char* hora) {
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;
    
    int h = atoi(hora);
    int m = atoi(hora + 3);
    
    if (h < 0 || h > 23 || m < 0 || m > 59) return false;
    return true;
}

    
    
void redimensionarArrayPacientes(Hospital* hospital) {


void redimensionarArrayPacientes(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadPacientes * 2;
    Paciente* nuevoArray = new Paciente[nuevaCapacidad]; 
    
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        nuevoArray[i] = hospital->pacientes[i]; 
    }
    
    delete[] hospital->pacientes;
    hospital->pacientes = nuevoArray;
    hospital->capacidadPacientes = nuevaCapacidad;
    
    cout << "\n[INFO] Array de pacientes redimensionado a " << nuevaCapacidad << " cupos." << endl;
}
Paciente* buscarPacientePorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}

Paciente* nuevoPaciente = &(hospital->pacientes[hospital->cantidadPacientes]);
    
    // Asignación de datos
    nuevoPaciente->id = hospital->siguienteIdPaciente;
    strncpy(nuevoPaciente->nombre, nombre, 49); strncpy(nuevoPaciente->apellido, apellido, 49);
    strncpy(nuevoPaciente->cedula, cedula, 19);
    nuevoPaciente->edad = edad; nuevoPaciente->sexo = sexo;
    strncpy(nuevoPaciente->telefono, tel, 14); strncpy(nuevoPaciente->email, email, 49);
    
    // Inicialización de arrays dinámicos internos (new)
    nuevoPaciente->capacidadHistorial = 5; 
    nuevoPaciente->historial = new HistorialMedico[nuevoPaciente->capacidadHistorial];
    nuevoPaciente->cantidadConsultas = 0;

    nuevoPaciente->capacidadCitas = 5;
    nuevoPaciente->citasAgendadas = new int[nuevoPaciente->capacidadCitas]; 
    nuevoPaciente->cantidadCitas = 0;

    strncpy(nuevoPaciente->tipoSangre, "N/A", 4); nuevoPaciente->activo = true;
    hospital->cantidadPacientes++;
    hospital->siguienteIdPaciente++;
    
    cout << "Paciente " << nuevoPaciente->nombre << " (ID: " << nuevoPaciente->id << ") registrado con éxito." << endl;
    return nuevoPaciente;
    }
 bool eliminarPaciente(Hospital* hospital, int id) {
    int indiceAEliminar = -1;
    for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        if (hospital->pacientes[i].id == id) { indiceAEliminar = i; break; }
    }
    if (indiceAEliminar == -1) { cout << "ERROR: Paciente con ID " << id << " no encontrado." << endl; return false; }
    
    Paciente* paciente = &(hospital->pacientes[indiceAEliminar]);

    // 1. Cancelar citas activas antes de eliminar
    int numCitas = paciente->cantidadCitas;
    for (int i = 0; i < numCitas; ++i) {
        cancelarCita(hospital, paciente->citasAgendadas[0]); 
    }
    
    // 2. Liberar memoria asociada al paciente
    delete[] paciente->historial;
    delete[] paciente->citasAgendadas;

    // 3. Compactar el array principal
    for (int i = indiceAEliminar; i < hospital->cantidadPacientes - 1; ++i) {
        hospital->pacientes[i] = hospital->pacientes[i + 1];
    }

    hospital->cantidadPacientes--;
    cout << "Paciente ID " << id << " eliminado correctamente." << endl;
    return true;
}
void listarPacientes(Hospital* hospital) { 
    cout << "\n=== LISTADO DE PACIENTES (" << hospital->cantidadPacientes << " registrados) ===" << endl;
    if (hospital->cantidadPacientes == 0) { cout << "No hay pacientes para mostrar." << endl; return; } 

    cout << setfill('-') << setw(60) << "" << endl;
    cout << "|" << setw(5) << "ID" << "|" << setw(20) << left << "NOMBRE" 
         << "|" << setw(15) << left << "CÉDULA" << "|" << setw(5) << "EDAD" << "|" << endl;
    cout << setfill('-') << setw(60) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < hospital->cantidadPacientes; ++i) {
        Paciente p = hospital->pacientes[i];
        
        // Uso de string temporal para concatenar nombre y apellido, y substr para limitar la longitud
        char fullName[100];
        strncpy(fullName, p.nombre, 49);
        strncat(fullName, " ", 1);
        strncat(fullName, p.apellido, 49);
        fullName[99] = '\0'; // Asegurar terminación
        
        cout << "|" << setw(5) << p.id 
             << "|" << setw(20) << left << fullName
             << "|" << setw(15) << left << p.cedula
             << "|" << setw(5) << p.edad << "|" << endl;
    }
    cout << setfill('-') << setw(60) << "" << endl;
}

void agregarConsultaAlHistorial(Paciente* paciente, HistorialMedico consulta) {
    if (paciente->cantidadConsultas >= paciente->capacidadHistorial) {
        int nuevaCapacidad = paciente->capacidadHistorial * 2;
        HistorialMedico* nuevoHistorial = new HistorialMedico[nuevaCapacidad];
        
        for (int i = 0; i < paciente->cantidadConsultas; ++i) {
            nuevoHistorial[i] = paciente->historial[i];
        }
        
        delete[] paciente->historial; 
        paciente->historial = nuevoHistorial;
        paciente->capacidadHistorial = nuevaCapacidad;
        cout << "\n[INFO] Historial médico de Paciente ID " << paciente->id << " redimensionado." << endl;
    }

    paciente->historial[paciente->cantidadConsultas] = consulta;
    paciente->cantidadConsultas++;
} 
void redimensionarArrayDoctores(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadDoctores * 2;
    Doctor* nuevoArray = new Doctor[nuevaCapacidad]; 

    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        nuevoArray[i] = hospital->doctores[i]; 
    }

    delete[] hospital->doctores;
    hospital->doctores = nuevoArray;
    hospital->capacidadDoctores = nuevaCapacidad;
    cout << "\n[INFO] Array de Doctores redimensionado a " << nuevaCapacidad << " cupos." << endl;
}
Doctor* buscarDoctorPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        if (hospital->doctores[i].id == id) return &(hospital->doctores[i]);
    }
    return nullptr;
}
Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido, 
                    const char* cedula, const char* especialidad, float costoConsulta, int experiencia) {
    
    // Validación de cédula (unicidad)
    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        if (strcmp(hospital->doctores[i].cedula, cedula) == 0) {
            cout << "ERROR: La cédula '" << cedula << "' ya está registrada. Registro cancelado." << endl;
            return nullptr;
        }
    }

    if (hospital->cantidadDoctores >= hospital->capacidadDoctores) redimensionarArrayDoctores(hospital);
    
    Doctor* nuevoDoctor = &(hospital->doctores[hospital->cantidadDoctores]);
    
    // Asignación de datos
    nuevoDoctor->id = hospital->siguienteIdDoctor;
    strncpy(nuevoDoctor->nombre, nombre, 49); strncpy(nuevoDoctor->apellido, apellido, 49);
    strncpy(nuevoDoctor->cedula, cedula, 19);
    strncpy(nuevoDoctor->especialidad, especialidad, 49);
    nuevoDoctor->costoConsulta = costoConsulta;
    nuevoDoctor->aniosExperiencia = experiencia;
    
    // Inicialización de arrays dinámicos internos (new)
    nuevoDoctor->capacidadPacientes = 5;
    nuevoDoctor->pacientesAsignados = new int[nuevoDoctor->capacidadPacientes];
    nuevoDoctor->cantidadPacientes = 0;

    nuevoDoctor->capacidadCitas = 10;
    nuevoDoctor->citasAgendadas = new int[nuevoDoctor->capacidadCitas];
    nuevoDoctor->cantidadCitas = 0;

    strncpy(nuevoDoctor->horarioAtencion, "08:00-16:00", 49);
    nuevoDoctor->disponible = true;

    hospital->cantidadDoctores++;
    hospital->siguienteIdDoctor++;
    
    cout << "Doctor " << nuevoDoctor->nombre << " (ID: " << nuevoDoctor->id << ") registrado con éxito." << endl;
    return nuevoDoctor;
}
void listarDoctores(Hospital* hospital) {
    cout << "\n=== LISTADO DE DOCTORES (" << hospital->cantidadDoctores << " registrados) ===" << endl;
    if (hospital->cantidadDoctores == 0) { cout << "No hay doctores para mostrar." << endl; return; } 

    cout << setfill('-') << setw(70) << "" << endl;
    cout << "|" << setw(5) << "ID" << "|" << setw(20) << left << "NOMBRE" 
         << "|" << setw(20) << left << "ESPECIALIDAD" << "|" << setw(15) << left << "CONSULTA" << "|" << endl;
    cout << setfill('-') << setw(70) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < hospital->cantidadDoctores; ++i) {
        Doctor d = hospital->doctores[i];
        
        char fullName[100];
        strncpy(fullName, d.nombre, 49);
        strncat(fullName, " ", 1);
        strncat(fullName, d.apellido, 49);
        fullName[99] = '\0';
        
        cout << "|" << setw(5) << d.id 
             << "|" << setw(20) << left << fullName
             << "|" << setw(20) << left << d.especialidad 
             << "|" << setw(15) << left << fixed << setprecision(2) << d.costoConsulta << "|" << endl;
    }
    cout << setfill('-') << setw(70) << "" << endl;
}
void redimensionarArrayCitas(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadCitas * 2;
    Cita* nuevoArray = new Cita[nuevaCapacidad]; 
    
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        nuevoArray[i] = hospital->citas[i]; 
    }
    
    delete[] hospital->citas; 
    hospital->citas = nuevoArray;
    hospital->capacidadCitas = nuevaCapacidad;
}
bool verificarDisponibilidad(Hospital* hospital, int idDoctor, const char* fecha, const char* hora) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita c = hospital->citas[i];
        if (c.idDoctor == idDoctor &&
            strcmp(c.estado, "Cancelada") != 0 &&
            strcmp(c.estado, "Atendida") != 0 &&
            strcmp(c.fecha, fecha) == 0 &&
            strcmp(c.hora, hora) == 0) {
            return false; // No disponible
        }
    }
    return true; // Disponible
}
Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor,
                  const char* fecha, const char* hora, const char* motivo) {
    
    Paciente* paciente = buscarPacientePorId(hospital, idPaciente);
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor); 

    if (paciente == nullptr || doctor == nullptr || !validarFecha(fecha) || !validarHora(hora) || !verificarDisponibilidad(hospital, idDoctor, fecha, hora)) {
        cout << "ERROR: Validación fallida (Paciente/Doctor no encontrado, formato inválido o no disponible)." << endl;
        return nullptr;
    }

    if (hospital->cantidadCitas >= hospital->capacidadCitas) redimensionarArrayCitas(hospital);

    Cita* nuevaCita = &(hospital->citas[hospital->cantidadCitas]);

    // Asignación de datos de la cita
    nuevaCita->id = hospital->siguienteIdCita;
    nuevaCita->idPaciente = idPaciente;
    nuevaCita->idDoctor = idDoctor;
    strncpy(nuevaCita->fecha, fecha, 10);
    strncpy(nuevaCita->hora, hora, 5);
    strncpy(nuevaCita->motivo, motivo, 149);
    strncpy(nuevaCita->estado, "Agendada", 19);
    nuevaCita->atendida = false;
    
    // Vinculación crítica: Añadir ID de cita a los arrays dinámicos de Paciente y Doctor
    if (paciente->cantidadCitas >= paciente->capacidadCitas) redimensionarArrayInt(paciente->citasAgendadas, paciente->cantidadCitas, paciente->capacidadCitas);
    paciente->citasAgendadas[paciente->cantidadCitas++] = nuevaCita->id;

    if (doctor->cantidadCitas >= doctor->capacidadCitas) redimensionarArrayInt(doctor->citasAgendadas, doctor->cantidadCitas, doctor->capacidadCitas);
    doctor->citasAgendadas[doctor->cantidadCitas++] = nuevaCita->id;

    hospital->cantidadCitas++;
    hospital->siguienteIdCita++;
    
    cout << "Cita ID " << nuevaCita->id << " agendada con éxito." << endl;
    return nuevaCita;
}
bool cancelarCita(Hospital* hospital, int idCita) {
    Cita* cita = nullptr;
    for (int i = 0; i < hospital->cantidadCitas; ++i) {
        if (hospital->citas[i].id == idCita && strcmp(hospital->citas[i].estado, "Agendada") == 0) {
            cita = &(hospital->citas[i]);
            break;
        }
    }

    if (cita == nullptr) {
        cout << "ERROR: Cita no encontrada o ya ha sido cancelada/atendida." << endl;
        return false;
    }

    strncpy(cita->estado, "Cancelada", 19);

    // Desvinculación crítica: Remover ID de los arrays dinámicos
    Paciente* paciente = buscarPacientePorId(hospital, cita->idPaciente);
    Doctor* doctor = buscarDoctorPorId(hospital, cita->idDoctor);

    if (paciente) removerIdDeArray(paciente->citasAgendadas, paciente->cantidadCitas, idCita);
    if (doctor) removerIdDeArray(doctor->citasAgendadas, doctor->cantidadCitas, idCita);

    cout << "Cita ID " << idCita << " cancelada correctamente." << endl;
    return true;
}
void mensajeBienvenida() {
    cout << "========================================================================\n";
    cout << "             Hospital San Jose St. Bonaventure " << endl; 
    cout << "========================================================================\n";
    cout << "Bienvenido. Este sistema permite la administracion completa de: Doctotres, Pacientes y sus historiales clinicos" << endl;
    cout << "En caso de emergencia: " << endl;
    cout << " Llamar a: 0414-7348227" << endl;
    cout << " Encuentranos en: San José, California " << endl;
}

void cargarDatosIniciales(Hospital* hospital) {
    cout << "\n[INFO] Cargando datos iniciales de prueba..." << endl;
    crearDoctor(hospital, "Ana", "Mendez", "123456", "Cardiologia", 85.50, 15);
    crearDoctor(hospital, "Carlos", "Perez", "654321", "Pediatria", 60.00, 8);
    crearPaciente(hospital, "Luisa", "Gomez", "112233", 45, 'F', "555-1234", "luisa@mail.com");
    crearPaciente(hospital, "Jorge", "Rojas", "445566", 30, 'M', "555-5678", "jorge@mail.com");
    agendarCita(hospital, 1, 1, "2025-11-20", "10:00", "Revision cardiologica");
    agendarCita(hospital, 2, 2, "2025-11-20", "11:00", "Control pediatrico");
    cout << "[INFO] Datos de prueba cargados." << endl;
}

void menuDoctores(Hospital* hospital) {
    int opcion;
    do {
        cout << "\n=== MENU DOCTORES ===" << endl;
        cout << "1. Registrar Doctor" << endl;
        cout << "2. Listar Doctores" << endl;
        cout << "4. Salir" << endl; // Simplificado
        cout << "Seleccione una opción: ";
        
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(10000, '\n'); opcion = 0; }
        cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20], especialidad[50];
                float costoConsulta; int experiencia;
                cout << "Ingrese nombre: "; cin.getline(nombre, 50);
                cout << "Ingrese apellido: "; cin.getline(apellido, 50);
                cout << "Ingrese cédula: "; cin.getline(cedula, 20);
                cout << "Ingrese especialidad: "; cin.getline(especialidad, 50);
                
                cout << "Ingrese costo de consulta: "; 
                if (!(cin >> costoConsulta)) { costoConsulta = 0.0f; cin.clear(); cin.ignore(10000, '\n'); }
                
                cout << "Ingrese años de experiencia: "; 
                if (!(cin >> experiencia)) { experiencia = 0; cin.clear(); cin.ignore(10000, '\n'); }
                
                cin.ignore(10000, '\n'); 
                crearDoctor(hospital, nombre, apellido, cedula, especialidad, costoConsulta, experiencia);
                break;
            }
            case 2: listarDoctores(hospital); break;
            case 4: cout << "Saliendo del menú de doctores." << endl; break;
            default: cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);
}
void menuPacientes(Hospital* hospital) {
    int opcion;
    do {
        cout << "\n=== MENU PACIENTES ===" << endl;
        cout << "1. Registrar Paciente" << endl;
        cout << "2. Listar Pacientes" << endl;
        cout << "3. Eliminar Paciente (ID)" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(10000, '\n'); opcion = 0; }
        cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20], tel[15], email[50];
                int edad; char sexo[2];
                
                cout << "Ingrese nombre: "; cin.getline(nombre, 50);
                cout << "Ingrese apellido: "; cin.getline(apellido, 50);
                cout << "Ingrese cédula: "; cin.getline(cedula, 20);
                
                cout << "Ingrese edad: "; 
                if (!(cin >> edad)) { edad = 0; cin.clear(); cin.ignore(10000, '\n'); }
                
                cout << "Ingrese sexo (M/F): "; cin >> sexo;
                cin.ignore(10000, '\n');

                cout << "Ingrese teléfono: "; cin.getline(tel, 15);
                cout << "Ingrese email: "; cin.getline(email, 50);
                
                crearPaciente(hospital, nombre, apellido, cedula, edad, toupper(sexo[0]), tel, email);
                break;
            }
            case 2: listarPacientes(hospital); break;
            case 3: {
                int id;
                cout << "Ingrese ID del paciente a eliminar: "; 
                if (!(cin >> id)) { id = -1; cin.clear(); cin.ignore(10000, '\n'); }
                cin.ignore(10000, '\n');
                eliminarPaciente(hospital, id);
                break;
            }
            case 4: cout << "Saliendo del menú de pacientes." << endl; break;
            default: cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);
}

void menuCitas(Hospital* hospital) {
    int opcion;
    do {
        cout << "\n=== MENU CITAS ===" << endl;
        cout << "1. Agendar Cita" << endl;
        cout << "2. Atender Cita (ID)" << endl;
        cout << "3. Cancelar Cita (ID)" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(10000, '\n'); opcion = 0; }
        cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: {
                int idp, idd;
                char fecha[11], hora[6], motivo[150];
                
                cout << "ID Paciente: "; 
                if (!(cin >> idp)) { idp = -1; cin.clear(); cin.ignore(10000, '\n'); }
                
                cout << "ID Doctor: "; 
                if (!(cin >> idd)) { idd = -1; cin.clear(); cin.ignore(10000, '\n'); }
                
                cin.ignore(10000, '\n');
                cout << "Fecha (YYYY-MM-DD): "; cin.getline(fecha, 11);
                cout << "Hora (HH:MM 24h): "; cin.getline(hora, 6);
                cout << "Motivo: "; cin.getline(motivo, 150);
                
                agendarCita(hospital, idp, idd, fecha, hora, motivo);
                break;
            }
            case 2: {
                int idc;
                char diag[200], trat[200], med[150];
                
                cout << "Ingrese ID de la Cita a ATENDER: "; 
                if (!(cin >> idc)) { idc = -1; cin.clear(); cin.ignore(10000, '\n'); }
                
                cin.ignore(10000, '\n');
                cout << "Diagnóstico: "; cin.getline(diag, 200);
                cout << "Tratamiento: "; cin.getline(trat, 200);
                cout << "Medicamentos: "; cin.getline(med, 150);
                
                atenderCita(hospital, idc, diag, trat, med);
                break;
            }
            case 3: {
                int idc;
                cout << "Ingrese ID de la Cita a CANCELAR: "; 
                if (!(cin >> idc)) { idc = -1; cin.clear(); cin.ignore(10000, '\n'); }
                cin.ignore(10000, '\n');
                cancelarCita(hospital, idc);
                break;
            }
            case 4: cout << "Saliendo del menú de citas." << endl; break;
            default: cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);
}

void menuPrincipal(){
    cout << "\n==================== Menu Principal ====================\n";
    cout << "1. Ingresar como Doctor\n";
    cout << "2. Ingresar como Paciente\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opcion: ";
