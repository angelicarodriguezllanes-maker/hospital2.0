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
    ifstream checkFile(nombreArchivo, ios::binary);
    if (!checkFile.good()) {
        cout << "Inicializando archivo " << nombreArchivo << "..." << endl;
        // Crear archivo y escribir header inicial
        ofstream archivo(nombreArchivo, ios::binary);
        if (archivo.is_open()) {
            ArchivoHeader header; // Valores por defecto (cantidadRegistros=0, proximoID=1)
            archivo.write((char*)&header, sizeof(ArchivoHeader));
            archivo.close();
        }
    }
}