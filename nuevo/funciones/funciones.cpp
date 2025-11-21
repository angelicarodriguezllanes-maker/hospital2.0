#include <strucks.h>
#include <fstream>
long calcularPosicion(int indice) {    //goggle maps
    
    return sizeof(ArchivoHeader) + (indice * sizeof(Paciente));//
} 

//lee el archivo header
ArchivoHeader leerHeader(const char* nombreArchivo) { //trailer, solo lee la portada 
    ArchivoHeader header;
    ifstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open()) {
        archivo.read((char*)&header, sizeof(ArchivoHeader));
        archivo.close();
    } // Si el archivo no existe o no se puede leer, retorna un header con valores por defecto.
    return header;
}
//Sobrescribe el ArchivoHeader al inicio de un archivo de datos.

bool actualizarHeader(const char* nombreArchivo, ArchivoHeader header) { // editorial
    // Abrir en modo lectura/escritura (in | out) para sobrescribir.
    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false; // verifica la apertura

    archivo.seekp(0); // mueve el cursor de escritura al o bytes
    archivo.write((char*)&header, sizeof(ArchivoHeader)); // copia de ram a ssd
    archivo.close();
    return true;
}
void inicializarArchivo(const char* nombreArchivo) {

    ifstream checkFile(nombreArchivo, ios::binary);   //revisa si el archivo existe
    if (!checkFile.good()) {
        cout << "Inicializando archivo " << nombreArchivo << "..." << endl;
      
        ofstream archivo(nombreArchivo, ios::binary); // crea el archivo y escribe la portada
        if (archivo.is_open()) {
            ArchivoHeader header; 
            archivo.write((char*)&header, sizeof(ArchivoHeader));
            archivo.close();
        }
    }
}

//lee el struck hospital y lo inicializa
Hospital cargarDatosHospital() { // lo encuentra en la memoria ssd lo lleva a la ram lo lee y lo actuliza
    Hospital hospital;
    ifstream archivo(HOSPITAL_FILE, ios::binary);
    if (archivo.is_open()) { // se encuentra en la ssd
        archivo.read((char*)&hospital, sizeof(Hospital)); // se trae el archivo a la ram
        archivo.close();
    } else {    // plan b Si no existe, lo crea y guarda el struct en el disco 

        ofstream newFile(HOSPITAL_FILE, ios::binary);
        if (newFile.is_open()) {
            newFile.write((char*)&hospital, sizeof(Hospital));
            newFile.close();
        }
    }
    return hospital;
}

// guarda y sobreescribe en ssd pasa de la ram al ssd
void guardarDatosHospital(const Hospital& hospital) {
    ofstream archivo(HOSPITAL_FILE, ios::binary | ios::trunc); // se prepara para sobre escribir 
    if (archivo.is_open()) {
        archivo.write((char*)&hospital, sizeof(Hospital));
        archivo.close();
    }
}

// agrega un nuevo paciente al final del archivo, pero solamente para escribir un nuevo registro
bool agregarPaciente(Hospital& hospital, Paciente& nuevoPaciente) { 
    
    nuevoPaciente.id = hospital.siguienteIDPaciente;   //asigna  el id 
    nuevoPaciente.fechaCreacion = time(nullptr);
}
    long posicion = calcularPosicion(indice); // calcula la posicion en bytws del paciente

    fstream archivo(PACIENTES_FILE, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;

    archivo.seekp(posicion); // ´pocisiona en la posicion para la excritura

    archivo.write(const_cast<char*>((char*)&pacienteModificado), sizeof(Paciente));  //guarda los cambios de forma permanente 

    archivo.close();
    cout << "Paciente ID " << pacienteModificado.id << " actualizado correctamente (Escritura in situ)." << endl;
    return true;

    int buscarIndiceDeID(int id) {
    ifstream archivo(PACIENTES_FILE, ios::binary);  // preparacion de lectura    
    if (!archivo.is_open()) return -1; // si no se puede abrir el archivo 

    ArchivoHeader header = leerHeader(PACIENTES_FILE); // carga la portda 

    archivo.seekg(sizeof(ArchivoHeader)); // mueve el el curso de lectura despuesd de la portada

    Paciente temp; //copia temporalmete el archivo binario 

    // Bucle para leer cada registro uno por uno
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&temp, sizeof(Paciente)); 
        
        // Comprobar si el ID coincide y no esta eliminado
        if (temp.id == id && !temp.eliminado) {
            archivo.close();
            return i; // Indice fisico encontrado.
        }
        // Si el archivo termina, salir
        if (archivo.eof()) break; 
    }
    archivo.close();
    return -1; // No encontrado
}

// lee el paciente por su id 
    Paciente leerPacientePorID(int id) {

    Paciente p; // Retorna un paciente vacio si falla
    int indice = buscarIndiceDeID(id);
    if (indice == -1) return p;

    long posicion = calcularPosicion(indice);   //Calcular posicion en bytes

    
    ifstream archivo(PACIENTES_FILE, ios::binary);  //  Abrir archivo en modo lectura
    if (!archivo.is_open()) return p;

    archivo.seekg(posicion);  // posicionarseee 
    
    archivo.read((char*)&p, sizeof(Paciente));// leer solo ese registro
    archivo.close();

    return p;
}

bool actualizarPaciente(const Paciente& pacienteModificado) {

    int indice = buscarIndiceDeID(pacienteModificado.id); // encuentra el numero del paciente que se quiere actualizar el id
    if (indice == -1) {
        cerr << "Error: Paciente con ID " << pacienteModificado.id << " no encontrado para actualizar." << endl;
        return false;
    }

    long posicion = calcularPosicion(indice); // pocicion en bytes

    fstream archivo(PACIENTES_FILE, ios::binary | ios::in | ios::out); // modo lectura
    if (!archivo.is_open()) return false;

    archivo.seekp(posicion); // posicion escritura 

    // 4. SOBREESCRIBIR la estructura completa sobre el registro existente.
    archivo.write(const_cast<char*>((char*)&pacienteModificado), sizeof(Paciente));  // copia de ram y pega en binario   

    archivo.close();
    cout << "Paciente ID " << pacienteModificado.id << " actualizado correctamente (Escritura in situ)." << endl;
    return true;
}


bool eliminarPaciente(int id) {1
    Paciente p = leerPacientePorID(id); // carga la ficha del paciente 
    if (p.id == -1 || p.eliminado) return false; // proceso de marca como eliminado  

    p.eliminado = true; // marca como eliminado
    p.fechaModificacion = time(nullptr); // registra la accion 

    if (!actualizarPaciente(p)) return false; // sobreesxribe lo modificado 

    ArchivoHeader header = leerHeader(PACIENTES_FILE); // actualiza el indice y disminuye los activos 
    header.registrosActivos--;
    actualizarHeader(PACIENTES_FILE, header);
    
    cout << "Paciente ID " << id << " eliminado logicamente." << endl;
    return true;
}

void mostrarMenu() {
    cout << "\n--- HOSPITAL SAN JOSE ST. BONAVENTURE  ---" << endl;
    cout << "1. Agregar Nuevo Paciente " << endl;
    cout << "2. Mostrar Paciente por ID " << endl;
    cout << "3. Actualizar Telefono Paciente " << endl;
    cout << "4. Eliminar Paciente " << endl;
    cout << "5. Mostrar Header del Archivo" << endl;
    cout << "6. Salir (Guardar Hospital)" << endl;
    cout << "Opcion: ";
}