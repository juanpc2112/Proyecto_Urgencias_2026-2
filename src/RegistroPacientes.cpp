#include "RegistroPacientes.h"

Paciente* RegistroPacientes::registrar(const Paciente& paciente) {
    if (!cedulaDisponible(paciente.obtenerCedula())) return nullptr;
    pacientes.push_back(paciente);
    Paciente* almacenado = &pacientes.back();
    porCedula.insert({almacenado->obtenerCedula(), almacenado});
    return almacenado;
}

Paciente* RegistroPacientes::buscar(const std::string& cedula) const {
    auto it = porCedula.find(cedula);
    return it == porCedula.end() ? nullptr : it->second;
}

bool RegistroPacientes::cedulaDisponible(const std::string& cedula) const {
    return porCedula.find(cedula) == porCedula.end();
}

int RegistroPacientes::cantidad() const {
    return static_cast<int>(porCedula.size());
}

const std::unordered_map<std::string, Paciente*>& RegistroPacientes::todos() const {
    return porCedula;
}
