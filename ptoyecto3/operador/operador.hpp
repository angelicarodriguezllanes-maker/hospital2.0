#ifndef OPERADORPACIENTES_HPP
#define OPERADORPACIENTES_HPP
#include "../pacientes/pacientes.hpp"
#include <string> 
#include <ctime>
#include <cstring> 

// Tamaño inicial y factor de crecimiento para el array dinámico
const int TAMANO_INICIAL = 10; 
const float FACTOR_CRECIMIENTO = 1.5; 


class OperadorPacientes {
public: //legibilidad y usabilidad
    // Constructor (prepara ela array dinamico para que pueda utilizarlo)
    OperadorPacientes();
    // Destructor: escoba de limpieza

    // Métodos Principales
    bool agregarpaciente(const Paciente& nuevoPaciente); //crea un nuevo registro de pacientes en el sistena 
    Paciente* buscarPacientePorID(int id); //consulta unn id especifico 
    bool actualizarPaciente(const Paciente& pacienteModificado); //actualiza los pacientes ya existentes
    bool eliminarPaciente(int id); //eliminar paciente 

    // Métodos Auxiliares, (simplificacioin pequena y privada que organiza la clase)
    void listarActivos() const; //lectura masiva de datos 
    
private: // importa pero puede esperar
    // Puntero al array dinámico de Pacientes
    Paciente* listaPacientes_;

    int capacidadMaxima_; 
   
    int cantidadActual_;// Número actual de pacientes en el array
   
    int ultimoIDAsignado_; // Rastrea el último ID asignado
    
    // Función privada para gestionar la memoria
    void verificarYExpandir();
    int getSiguienteID();
};

#endif 