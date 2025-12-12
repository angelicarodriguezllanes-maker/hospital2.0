#ifndef PACIENTE_HPP // pregunta si aun no se ahan creado los pacientes 
#define PACIENTE_HPP // si no se han creado va al contenido 
#include <cstddef>
#include <iostream>
class Paciente { //medicamento y funciona como un agucate 
private: //locker, PEPITA DEL AGUCATE                   
     int id; 
    char nombre[50];
    char apellido[50];
    char cedula[20]; 
    int edad;
    char sexo;       
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    // se pueden seguir anadiendo atributos 

public: // pulpa del agucate 
    // CONSTRUCTORES
    Paciente();  
    
    // GETTERS (Solo leen, no modifican, por eso llevan 'const')
   const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedula() const;
    int getEdad() const;
    char getSexo() const;
    const char* getTipoSangre() const;
    const char* getTelefono() const;
    const char* getDireccion() const;
    const char* getEmail() const;

    // SETTERS, protegen el contenido durante la escritura 
    void setNombre(const char* nuevoNombre);
    void setApellido(const char* nuevoApellido);
    void setCedula(const char* nuevaCedula);
    void setEdad(int nuevaEdad);
    void setSexo(char nuevoSexo);
    void setTipoSangre(const char* nuevoTipoSangre);
    void setTelefono(const char* nuevoTelefono);
    void setDireccion(const char* nuevaDireccion);
    void setEmail(const char* nuevoEmail);

    // Método de presentación
   void mostrarInformacionBasica() const {
    cout << "---------------------------------------" << std::endl;
    cout << "         DATOS BÁSICOS DEL PACIENTE    " << std::endl;
    cout << "---------------------------------------" << std::endl;
    cout << "NOMBRE COMPLETO: " << nombre << " " << apellido << std::endl;
    cout << "CÉDULA: " << cedula << std::endl;
    cout << "EDAD: " << edad << " años" << std::endl;
    cout << "SEXO: " << sexo << std::endl;
    cout << "TIPO DE SANGRE: " << tipoSangre << std::endl;
    cout << "TELÉFONO: " << telefono << std::endl;
    cout << "DIRECCIÓN: " << direccion << std::endl;
    cout << "EMAIL: " << email << std::endl;
    cout << "---------------------------------------" << std::endl;
}
    int getID() const;


void setID(int nuevoID);
Paciente(int id, const char* n, const char* a, const char* c, int e, char s, const char* ts, const char* tel, const char* dir, const char* email);
    // Método auxiliar para el GestorArchivos o planificador de tareas 
    static size_t obtenerTamano(); //devuelve tamano o cantidad 
};

#endif // PACIENTE_HPP