#ifndef URGENCIAS_REGISTRO_PACIENTES_H
#define URGENCIAS_REGISTRO_PACIENTES_H

#include "Paciente.h"
#include <list>
#include <string>
#include <unordered_map>

// Conserva a todos los pacientes durante la ejecución y permite buscarlos por cédula.
class RegistroPacientes {
public:
    // Guarda una copia y devuelve un puntero estable al paciente registrado.
    Paciente* registrar(const Paciente& paciente);
    // Busca un paciente por su identificador de cuatro dígitos.
    Paciente* buscar(const std::string& cedula) const;
    bool cedulaDisponible(const std::string& cedula) const;
    const std::unordered_map<std::string, Paciente*>& todos() const;

private:
    std::list<Paciente> pacientes; // Es dueña de los objetos para mantener estables sus direcciones.
    std::unordered_map<std::string, Paciente*> porCedula; // Índice hash por cédula.
};

#endif
