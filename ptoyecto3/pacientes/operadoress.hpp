#ifndef OPERACIONES_PACIENTES_HPP
#define OPERACIONES_PACIENTES_HPP

#include "../hospital/Hospital.hpp" // Asegúrate de que esta ruta sea correcta

// Declaraciones de las funciones:
void registrarPaciente(Hospital& hospital); // Si requiere el objeto Hospital (como el case 1)
void modificarPaciente();
void buscarPaciente();
void listarPacientes();
void eliminarPaciente();

#endif // OPERACIONES_PACIENTES_HPP