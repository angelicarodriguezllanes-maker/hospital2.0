int main() {
 
    inicializarArchivo(PACIENTES_FILE); // inicializa archivo

    Hospital hospital = cargarDatosHospital(); // cara dato de la memoria 
    
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        system("cls"); // Se cambia system("cls || clear") por system("cls")

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
        cout << "Consultas: " << (p.primerConsultaID != -1 ? "Si" : "No") << endl;
        cout << "Fecha Mod: " << put_time(localtime(&p.fechaModificacion), "%Y-%m-%d %H:%M:%S") << endl; // convierte a un formto entendible 
    } else {
        cout << "\n[ERROR] Paciente ID " << id << " no encontrado o eliminado." << endl;
    }
    
} else if (opcion == 3) {
    int id;
    cout << "--- Actualizar Telefono (Random Write) ---" << endl;
    cout << "Ingrese ID del paciente a actualizar: "; cin >> id;
    cin.ignore(); 
    
    Paciente p = leerPacientePorID(id);
    if (p.id != -1 && !p.eliminado) {
        cout << "Telefono actual: " << p.telefono << endl;
        cout << "Ingrese nuevo Telefono: "; cin.getline(p.telefono, 15);
        p.fechaModificacion = time(nullptr); // Actualizar timestamp
        
        actualizarPaciente(p);
    } else {
        cout << "\n[ERROR] Paciente ID " << id << " no encontrado o eliminado." << endl;
    }

} else if (opcion == 4) {
    int id;
    cout << "--- Eliminar Paciente (Borrado Logico) ---" << endl;
    cout << "Ingrese ID del paciente a eliminar: "; cin >> id;
    
    if (eliminarPaciente(id)) {
        cout << "\n[OK] Eliminacion logica para ID " << id << " completada." << endl;
    } else {
        cout << "\n[ERROR] No se pudo eliminar el paciente ID " << id << "." << endl;
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