ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

namespace Constantes {

    // Rutas para las entidades principales
    const char* const RUTA_PACIENTES = "datos/pacientes.dat";
    const char* const RUTA_DOCTORES = "datos/doctores.dat";
    const char* const RUTA_CITAS = "datos/citas.dat";
    const char* const RUTA_HISTORIALES = "datos/historiales.dat";
    
    // Ruta para el objeto Hospital (configuración y contadores)
    const char* const RUTA_HOSPITAL = "datos/hospital.cfg"; 

    //Estructura que define el encabezado de un archivo binario.
     //gestionar el control de IDs y el conteo de registros válidos.
     
    struct ArchivoHeader {
        int proximoID;    // ID que se debe asignar al siguiente registro nuevo (Ej: 1, 2, 3...)
        int numRegistros; // Número total de registros (pacientes, doctores, etc.) que están activos en el archivo.
    };
    
    // Opcional: Definir el tamaño del ArchivoHeader para facilitar cálculos
    const int TAMANO_HEADER = sizeof(ArchivoHeader);
}

#endif // CONSTANTES_HPP
