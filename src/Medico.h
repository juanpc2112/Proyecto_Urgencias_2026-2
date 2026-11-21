#ifndef URGENCIAS_MEDICO_H
#define URGENCIAS_MEDICO_H

#include <string>

// Identidad del médico responsable de una o varias jornadas.
class Medico {
public:
    // Crea un médico inicial o uno con identificación y nombre definidos.
    Medico();
    Medico(std::string identificacion, std::string nombre);

    // Devuelve los datos de identificación del médico.
    const std::string& obtenerIdentificacion() const noexcept;
    const std::string& obtenerNombre() const noexcept;

private:
    std::string identificacion; // Código único usado en el historial.
    std::string nombre;         // Nombre que aparece en pantalla.
};

#endif // URGENCIAS_MEDICO_H
