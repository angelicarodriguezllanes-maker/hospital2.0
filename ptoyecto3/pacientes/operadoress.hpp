#ifndef OPERACIONES_PACIENTES_HPP
#define OPERACIONES_PACIENTES_HPP

// Incluimos la clase Hospital para actualizar sus contadores de IDs
#include "../hospital/Hospital.hpp" 
// Incluimos la clase Paciente para poder crear y modificar pacientes
#include "Paciente.hpp" 

// Declaraciones de funciones de lógica de negocio
void registrarPaciente(Hospital& hospital);
Paciente buscarPacientePorID();
// Declarar el resto de operaciones CRque UD y flujos (modificar, eliminar, listar...)

#endif