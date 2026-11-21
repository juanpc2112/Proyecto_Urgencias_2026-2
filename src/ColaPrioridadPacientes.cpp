#include "ColaPrioridadPacientes.h"
#include <iostream>

bool ComparadorPrioridadPaciente::operator()(const Paciente* a, const Paciente* b) const {
    if (a->obtenerGravedad() != b->obtenerGravedad())
        return a->obtenerGravedad() < b->obtenerGravedad();
    if (a->obtenerOrdenLlegada() != b->obtenerOrdenLlegada())
        return a->obtenerOrdenLlegada() < b->obtenerOrdenLlegada();
    return a->obtenerCedula() < b->obtenerCedula();
}

bool ColaPrioridadPacientes::insertar(Paciente* paciente) {
    if (paciente == nullptr || paciente->obtenerEstado() != EstadoPaciente::EnCola) return false;
    return pendientes.insert(paciente).second;
}

Paciente* ColaPrioridadPacientes::siguiente() {
    if (pendientes.empty()) return nullptr;
    auto it = pendientes.begin();
    Paciente* paciente = *it;
    pendientes.erase(it);
    return paciente;
}

bool ColaPrioridadPacientes::vacia() const { return pendientes.empty(); }
int ColaPrioridadPacientes::cantidad() const { return static_cast<int>(pendientes.size()); }

int ColaPrioridadPacientes::cantidadPorGravedad(int gravedad) const {
    int cantidad = 0;
    for (const auto& paciente : pendientes)
        if (paciente->obtenerGravedad() == gravedad) ++cantidad;
    return cantidad;
}

void ColaPrioridadPacientes::avanzarEspera() {
    for (const auto& paciente : pendientes) paciente->incrementarEspera();
}

std::list<Paciente*> ColaPrioridadPacientes::retirarVencidos() {
    std::list<Paciente*> vencidos;
    auto it = pendientes.begin();
    while (it != pendientes.end()) {
        if ((*it)->obtenerTurnosEspera() >= (*it)->turnosMaximosEspera()) {
            Paciente* paciente = *it;
            paciente->establecerEstado(EstadoPaciente::Perdido);
            vencidos.push_back(paciente);
            it = pendientes.erase(it);
        } else {
            ++it;
        }
    }
    return vencidos;
}

void ColaPrioridadPacientes::limpiar() { pendientes.clear(); }

std::string ColaPrioridadPacientes::resumen() const {
    std::string salida;
    for (int gravedad = 1; gravedad <= 5; ++gravedad) {
        int cuantos = 0;
        int suma = 0;
        for (const auto& paciente : pendientes) {
            if (paciente->obtenerGravedad() == gravedad) {
                ++cuantos;
                suma += paciente->obtenerTurnosEspera();
            }
        }
        if (cuantos > 0) {
            if (!salida.empty()) salida += " | ";
            salida += std::to_string(cuantos) + " paciente(s) G" + std::to_string(gravedad);
            salida += ", espera promedio " + std::to_string(suma / cuantos) + " turnos";
        }
    }
    return salida.empty() ? "vacia" : salida;
}

const std::set<Paciente*, ComparadorPrioridadPaciente>& ColaPrioridadPacientes::pacientes() const {
    return pendientes;
}
