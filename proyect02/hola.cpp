#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip> // Para std::put_time

using namespace std;

// archivos binarios
const char* HOSPITAL_FILE = "hospital.bin";
const char* PACIENTES_FILE = "pacientes.bin";
const char* CITAS_FILE = "citas.bin";
const char* DOCTORES_FILE = "doctores.bin";
const char* HISTORIAL_FILE = "historial.bin";

//ndice de un libro
struct ArchivoHeader {
    int cantidadRegistros = 0;      // Conteo total de registros activos y eliminados
    int proximoID = 1;              
    int registrosActivos = 0;
    int version = 2;              //version de formato 
};

//hospital.bin
struct Hospital {
    char nombre[100] = "Hospital San Jose St. Bonaventure"; 
    char direccion[150] = "San Jose, California"; 
    char telefono[15] = "0414-7348227"; 

    // Contadores de IDs (inician en 1)
    int siguienteIDPaciente = 1;
    int siguienteIDDoctor = 1;
    int siguienteIDCita = 1;
    int siguienteIDConsulta = 1;

    
    int totalPacientesRegistrados = 0;
    int totalDoctoresRegistrados = 0;
    int totalCitasAgendadas = 0;
    int totalConsultasRealizadas = 0;
};

//pacientes.bin
struct Paciente {
    int id = -1;
    char nombre[50] = "";
    char apellido[50] = "";
    char cedula[20] = "";
    int edad = 0;
    char sexo = ' ';
    char tipoSangre[5] = "";
    char telefono[15] = "";
    char direccion[100] = "";
    char email[50] = "";
    char alergias[500] = "";
    char observaciones[500] = "";

    // Índice para Historial Médico (El -1 indica que no hay historial)
    int cantidadConsultas = 0;
    int primerConsultaID = -1;

    // Índice Citas (Array fijo)
    int citasIDs[20] = {0};
    int cantidadCitas = 0;

    // datos de registro
    bool activo = true;
    bool eliminado = false;
    time_t fechaCreacion = 0;
    time_t fechaModificacion = 0;
};

//doctores.bin

struct Doctor {
    int id = -1;
    char nombre[50] = "";
    char apellido[50] = "";
    char cedulaProfesional[20] = "";
    char especialidad[50] = "";
    int aniosExperiencia = 0;
    float costoConsulta = 0.0f;
    char horarioAtencion[50] = "";
    char telefono[15] = "";
    char email[50] = "";
    bool disponible = true;

    [cite_start]  //crea una lista de doctores hasta 50 pacientes
    int pacientesIDs[50] = {0};
    int cantidadPacientes = 0;

    // Array FIJO de IDs de citas agendadas
    int citasIDs[30] = {0};
    int cantidadCitas = 0;

    // datos de registro
    bool eliminado = false;
    time_t fechaCreacion = 0;
    time_t fechaModificacion = 0;
};

//citas.bin
struct Cita {
    int id = -1;
    int pacienteID = -1;
    int doctorID = -1;
    char fecha[11] = "";
    char hora[6] = "";
    char motivo[150] = "";
    char estado[20] = "Agendada";
    char observaciones[200] = "";
    bool atendida = false;

    int consultaID = -1;
    bool eliminado = false;

    time_t fechaCreacion = 0; //guarda fecha y hora exacta
    time_t fechaModificacion = 0;  //garda la modificacion de la fecha y la creaciom

};

//historial.bin
struct HistorialMedico {
    int id = -1;
    int pacienteID = -1;
    char fecha[11] = "";
    char hora[6] = "";
    char diagnostico[200] = "";
    char tratamiento[200] = "";
    char medicamentos[150] = "";
    int doctorID = -1;
    float costo = 0.0f;


    int siguienteConsultaID = -1;

  //datos del registro
    bool eliminado = false;
    time_t fechaRegistro = 0;
};

long calcularPosicion(int indice, size_t structSize) { //busca donde comienza el registro buscando en el indice y con pasos de distancia
    return sizeof(ArchivoHeader) + (indice * structSize);
}

ArchivoHeader leerHeader(const char* nombreArchivo) { //lee la informacion inicial del indice 
    ArchivoHeader header; 
    ifstream archivo(nombreArchivo, ios::binary); //abarae el archivo en  binario
    if (archivo.is_open()) { //validacion
        archivo.read((char*)&header, sizeof(ArchivoHeader)); //lee cantidad de byttes adentro del header
        archivo.close();
    }
    return header;
}

bool actualizarHeader(const char* nombreArchivo, ArchivoHeader header) { //guarda los nuevos datos en al cabezera
    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out); //abre en modo leer y escribir en binario
    if (!archivo.is_open()) return false; //validacion

    archivo.seekp(0); // busca posicion por escritura mueve al byte 0
    archivo.write((char*)&header, sizeof(ArchivoHeader)); //escribe la informacion en la cabezera
    archivo.close();
    return true;
}

void inicializarArchivo(const char* nombreArchivo) { //crea el archivo por primera vez si no existe
    ifstream checkFile(nombreArchivo, ios::binary);  //aabre el aarchivo para leer
    if (!checkFile.good()) { //si ls comprobacion falla
        cout << "Inicializando archivo " << nombreArchivo << "..." << endl; //mensaje para creaar archivo
        ofstream archivo(nombreArchivo, ios::binary);  //crea un nuevo archivo
        if (archivo.is_open()) { //validacion
            ArchivoHeader header;
            archivo.write((char*)&header, sizeof(ArchivoHeader));
            archivo.close();
        }
    }
}

//asegura que se tenga datos del hospital en el programa
Hospital cargarDatosHospital() {
    Hospital hospital; //crea la variable hospital en el hospital
    ifstream archivo(HOSPITAL_FILE, ios::binary); //abre el archivo y guarda los datoss del hospital
    if (archivo.is_open()) { //validacion
        archivo.read((char*)&hospital, sizeof(Hospital)); //lee los datos del byte y verifica la variable
        archivo.close();
    } else {
        // Si no existe, lo crea y guarda el struct en el disco (con valores por defecto)
        ofstream newFile(HOSPITAL_FILE, ios::binary); //crea un archivo con ese nombre
        if (newFile.is_open()) { //validacion
            newFile.write((char*)&hospital, sizeof(Hospital)); //escribe lo recien agregado que contiene los valores iniciales
            newFile.close();
        }
    }
    return hospital;
}

void guardarDatosHospital(const Hospital& hospital) { //guarda los datos del hospital en el hospital
    ofstream archivo(HOSPITAL_FILE, ios::binary | ios::trunc); //lo abre para que se lea y se escriba en binario
    if (archivo.is_open()) { //validacion
        archivo.write((char*)&hospital, sizeof(Hospital)); //sobre escribe en el nurvo archi
        archivo.close();
    }
}

//busca el indice fisico del doctor por su id
int buscarIndiceDeIDDoctor(int id) {
    ifstream archivo(DOCTORES_FILE, ios::binary); //lee el archivo de doctores
    if (!archivo.is_open()) return -1; // sino existe

    ArchivoHeader header = leerHeader(DOCTORES_FILE); // lee para revisar registros revisa
    archivo.seekg(sizeof(ArchivoHeader)); //se posciona al primer registro 

    Doctor temp; //variable temporal
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&temp, sizeof(Doctor)); //lee el registro del doctor completo a la variable temp

        if (temp.id == id && !temp.eliminado) { //validacion de exito y eliminado
            archivo.close();
            return i;
        }
        if (archivo.eof()) break;
    }
    archivo.close();
    return -1; // No encontrado
}

//lee el doctor por su id 
Doctor leerDoctorPorID(int id) {
    Doctor d;
    int indice = buscarIndiceDeIDDoctor(id);
    if (indice == -1) return d;

    long posicion = calcularPosicion(indice, sizeof(Doctor)); //calcula la posicion 

    ifstream archivo(DOCTORES_FILE, ios::binary); //abre el acrchivo modo lectura 
    if (!archivo.is_open()) return d;

    archivo.seekg(posicion); //se mueve 
    archivo.read((char*)&d, sizeof(Doctor)); //posicion 
    archivo.close();

    return d;
}

//actualiza al doctor modificado 
bool actualizarDoctor(const Doctor& doctorModificado) {
    int indice = buscarIndiceDeIDDoctor(doctorModificado.id); //buscar por posicion
    if (indice == -1) {
        cerr << "Error: Doctor con ID " << doctorModificado.id << " no encontrado para actualizar." << endl;
        return false;
    }

    long posicion = calcularPosicion(indice, sizeof(Doctor)); // calcula la posicion den bytes

    fstream archivo(DOCTORES_FILE, ios::binary | ios::in | ios::out); //abrir para leer y escribir 
    if (!archivo.is_open()) return false; //validacion

    archivo.seekp(posicion); //posicionna hasta donde esta el registri
    archivo.write(const_cast<char*>((char*)&doctorModificado), sizeof(Doctor)); // escrible el doctor modificado en ek registro y sobreescribe el nuevo

    archivo.close();
    cout << "Doctor ID " << doctorModificado.id << " actualizado correctamente (Escritura in situ)." << endl;
    return true;
}

//agrega un doctor al final del archivo
bool agregarDoctor(Hospital& hospital, Doctor& nuevoDoctor) { //prepara un nuevo doctor 
    ArchivoHeader header = leerHeader(DOCTORES_FILE); //lee la cabecera

    // 1. Asignar ID y metadatos
    nuevoDoctor.id = hospital.siguienteIDDoctor;// asigna un nuevo id 
    nuevoDoctor.fechaCreacion = time(nullptr); //asign afecha acatual 
    nuevoDoctor.fechaModificacion = nuevoDoctor.fechaCreacion; //modifica

    // 2. Abrir archivo para escritura al final (append)
    ofstream archivo(DOCTORES_FILE, ios::binary | ios::app); //escribe 
    if (!archivo.is_open()) { //validacion 
        cerr << "ERROR: No se pudo abrir el archivo de doctores para escritura." << endl;
        return false;
    }

    // 3. Escribir el nuevo doctor
    archivo.write((char*)&nuevoDoctor, sizeof(Doctor));
    archivo.close();

    // 4. Actualizar el Hospital y el Header
    hospital.siguienteIDDoctor++;
    hospital.totalDoctoresRegistrados++;

    header.cantidadRegistros++;
    header.registrosActivos++;
    header.proximoID = hospital.siguienteIDDoctor; // Usamos el ID del Hospital como fuente de verdad
    actualizarHeader(DOCTORES_FILE, header);

    return true;
}

//busca el indice fisico con su id 
int buscarIndiceDeID(int id) {
    ifstream archivo(PACIENTES_FILE, ios::binary); //abre ke archivo en binaario 
    if (!archivo.is_open()) return -1; //validacion 

    ArchivoHeader header = leerHeader(PACIENTES_FILE); //lee la cabecera para saber cuantos pacientes tiene
    archivo.seekg(sizeof(ArchivoHeader)); //posiciona en el priemr registr0

    Paciente temp; //paciente temp 
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&temp, sizeof(Paciente)); //lee el registro y lo guarda en el temp

        if (temp.id == id && !temp.eliminado) { //valida si la encontro y si existe 
            archivo.close();
            return i;
        }
        if (archivo.eof()) break;
    }
    archivo.close();
    return -1;
}

//lee paciente por id 
Paciente leerPacientePorID(int id) {
    Paciente p;
    int indice = buscarIndiceDeID(id); 
    if (indice == -1) return p;

    long posicion = calcularPosicion(indice, sizeof(Paciente)); // calcula posicion 

    ifstream archivo(PACIENTES_FILE, ios::binary); // abre en modo binarion 
    if (!archivo.is_open()) return p; //validacuin 

    archivo.seekg(posicion); //le dice donde saltar
    archivo.read((char*)&p, sizeof(Paciente)); // lee cantidad de bytes
    archivo.close();

    return p;
}

//actualiza el paciente modifica el paciente 
bool actualizarPaciente(const Paciente& pacienteModificado) {
    int indice = buscarIndiceDeID(pacienteModificado.id);
    if (indice == -1) {
        cerr << "Error: Paciente con ID " << pacienteModificado.id << " no encontrado para actualizar." << endl;
        return false;
    }

    long posicion = calcularPosicion(indice, sizeof(Paciente)); //calcula la posicion 

    fstream archivo(PACIENTES_FILE, ios::binary | ios::in | ios::out); //abare en binario 
    if (!archivo.is_open()) return false;

    archivo.seekp(posicion); //se posiciona 
    archivo.write(const_cast<char*>((char*)&pacienteModificado), sizeof(Paciente)); //escribe el registro completo 

    archivo.close();
    cout << "Paciente ID " << pacienteModificado.id << " actualizado correctamente (Escritura in situ)." << endl;
    return true;
}

//agrege un nuevo paciente al final del archivo 
bool agregarPaciente(Hospital& hospital, Paciente& nuevoPaciente) {
    // 1. Asignar ID y metadatos
    nuevoPaciente.id = hospital.siguienteIDPaciente; //asigna un nuevo paciente 
    nuevoPaciente.fechaCreacion = time(nullptr); //asigna fecha actual 
    nuevoPaciente.fechaModificacion = nuevoPaciente.fechaCreacion; //fecha de modificacion 

    // 2. Abrir archivo para escritura al final (append)
    ofstream archivo(PACIENTES_FILE, ios::binary | ios::app);
    if (!archivo.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo de pacientes para escritura." << endl;
        return false;
    }

    // 3. Escribir el nuevo paciente
    archivo.write((char*)&nuevoPaciente, sizeof(Paciente));
    archivo.close();

    // 4. Actualizar el Hospital y el Header
    hospital.siguienteIDPaciente++;
    hospital.totalPacientesRegistrados++;

    ArchivoHeader header = leerHeader(PACIENTES_FILE); //actualiza el header 
    header.cantidadRegistros++;
    header.registrosActivos++;
    header.proximoID = hospital.siguienteIDPaciente;
    actualizarHeader(PACIENTES_FILE, header);

    return true;
}

/**
 * Realiza un borrado lógico de un paciente. (Copias del PDF)
 */
bool eliminarPaciente(int id) { //borrado logico 
    Paciente p = leerPacientePorID(id); //lee y verifica la exisstenica 
    if (p.id == -1 || p.eliminado) return false;

    p.eliminado = true; //marca como leido 
    p.fechaModificacion = time(nullptr);

    if (!actualizarPaciente(p)) return false; //guarda el cambio 

    ArchivoHeader header = leerHeader(PACIENTES_FILE); //actualiza la cabezera 
    header.registrosActivos--;
    actualizarHeader(PACIENTES_FILE, header);

    cout << "Paciente ID " << id << " eliminado logicamente." << endl;
    return true;
}

void mensajeBienvenida () { // [cite: 225, 226, 227, 228, 229, 230]
    cout << "\n=======================================================\n";
    cout << "              Hospital San Jose St. Bonaventure " << endl;
    cout << "=======================================================\n";
    cout << "Bienvenido. Este sistema permite la administracion completa de: Doctotres, Pacientes y sus historiales clinicos" << endl; [cite_start]// [cite: 231, 232]
    cout << "En caso de emergencia: Llamar a: 0414-7348227" << endl; [cite_start]// [cite: 233, 236]
    cout << "Encuentranos en: San José, California " << endl; [cite_start]// [cite: 237]
}

void mostrarMenu() {
    cout << "\n--- HOSPITAL SAN JOSE ST. BONAVENTURE  ---" << endl;
    cout << "1. Agregar Nuevo Paciente " << endl;
    cout << "2. Mostrar Paciente por ID " << endl;
    cout << "3. Agregar Nuevo Doctor " << endl;
    cout << "4. Mostrar Doctor por ID " << endl;
    cout << "5. Mostrar Header del Archivo Pacientes" << endl;
    cout << "6. Salir (Guardar Hospital)" << endl;
    cout << "Opcion: ";
}


int main() {
    // Inicializar todos los archivos de datos binarios
    inicializarArchivo(PACIENTES_FILE);
    inicializarArchivo(DOCTORES_FILE);
    // inicializarArchivo(CITAS_FILE);
    // inicializarArchivo(HISTORIAL_FILE);

    // Cargar la configuración principal del hospital (contadores)
    Hospital hospital = cargarDatosHospital();

    mensajeBienvenida();

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        // En un entorno de consola real se usaría system("cls") o system("clear")
        // system("cls");

        if (opcion == 1) {
            cout << "--- Agregar Paciente ---" << endl;
            Paciente nuevo;

            cout << "Nombre: "; cin.getline(nuevo.nombre, 50);
            cout << "Apellido: "; cin.getline(nuevo.apellido, 50);
            cout << "Cedula: "; cin.getline(nuevo.cedula, 20);
            cout << "Telefono: "; cin.getline(nuevo.telefono, 15);

            if (agregarPaciente(hospital, nuevo)) {
                cout << "\n[OK] Paciente ID " << nuevo.id << " agregado con exito." << endl;
            } else {
                cerr << "[ERROR] No se pudo agregar el paciente." << endl;
            }

        } else if (opcion == 2) {
            int id;
            cout << "--- Leer Paciente por ID ---" << endl;
            cout << "Ingrese ID: "; cin >> id;

            Paciente p = leerPacientePorID(id);
            if (p.id != -1 && !p.eliminado) {
                cout << "\n[OK] Lectura Aleatoria Exitosa (ID: " << p.id << ")" << endl;
                cout << "Nombre: " << p.nombre << " " << p.apellido << endl;
                cout << "Cedula: " << p.cedula << endl;
                cout << "Telefono: " << p.telefono << endl;
                cout << "Fecha Mod: " << put_time(localtime(&p.fechaModificacion), "%Y-%m-%d %H:%M:%S") << endl;
            } else {
                cout << "\n[ERROR] Paciente ID " << id << " no encontrado o eliminado." << endl;
            }

        } else if (opcion == 3) {
            cout << "--- Agregar Doctor ---" << endl;
            Doctor nuevo;

            cout << "Nombre: "; cin.getline(nuevo.nombre, 50);
            cout << "Apellido: "; cin.getline(nuevo.apellido, 50);
            cout << "Cedula Profesional: "; cin.getline(nuevo.cedulaProfesional, 20);
            cout << "Especialidad: "; cin.getline(nuevo.especialidad, 50);
            cout << "Costo Consulta: "; cin >> nuevo.costoConsulta;
            cin.ignore();

            if (agregarDoctor(hospital, nuevo)) {
                cout << "\n[OK] Doctor ID " << nuevo.id << " agregado con exito." << endl;
            } else {
                cerr << "[ERROR] No se pudo agregar el doctor." << endl;
            }

        } else if (opcion == 4) {
            int id;
            cout << "--- Leer Doctor por ID ---" << endl;
            cout << "Ingrese ID: "; cin >> id;

            Doctor d = leerDoctorPorID(id);
            if (d.id != -1 && !d.eliminado) {
                cout << "\n[OK] Lectura Aleatoria Exitosa (ID: " << d.id << ")" << endl;
                cout << "Nombre: " << d.nombre << " " << d.apellido << endl;
                cout << "Cedula: " << d.cedulaProfesional << endl;
                cout << "Especialidad: " << d.especialidad << endl;
                cout << "Costo: " << d.costoConsulta << endl;
            } else {
                cout << "\n[ERROR] Doctor ID " << id << " no encontrado o eliminado." << endl;
            }
        } else if (opcion == 5) {
            cout << "--- Header de " << PACIENTES_FILE << " ---" << endl;
            ArchivoHeader header = leerHeader(PACIENTES_FILE);
            cout << "Registros Totales (R+E): " << header.cantidadRegistros << endl;
            cout << "Proximo ID a asignar: " << header.proximoID << endl;
            cout << "Registros Activos: " << header.registrosActivos << endl;
            cout << "Tamano de Paciente: " << sizeof(Paciente) << " bytes" << endl;
            cout << "Tamano de Header: " << sizeof(ArchivoHeader) << " bytes" << endl;

        } else if (opcion == 6) {
            guardarDatosHospital(hospital);
            cout << "\nGuardando datos de Hospital y saliendo..." << endl;
        } else {
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 6);

    return 0;
}