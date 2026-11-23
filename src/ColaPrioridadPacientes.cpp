#include "ColaPrioridadPacientes.h"

bool ComparadorPrioridadPaciente::operator()(const Paciente* a, const Paciente* b) const {
    if (a->obtenerGravedad() != b->obtenerGravedad()) {
        return a->obtenerGravedad() > b->obtenerGravedad();
    }
    if (a->obtenerOrdenLlegada() != b->obtenerOrdenLlegada()) {
        return a->obtenerOrdenLlegada() > b->obtenerOrdenLlegada();
    }
    return a->obtenerCedula() > b->obtenerCedula();
}

bool ColaPrioridadPacientes::insertar(Paciente* paciente) {
    if (paciente == nullptr || paciente->obtenerEstado() != EstadoPaciente::EnCola) {
        return false;
    }
    pendientes.push(paciente);
    return true;
}

Paciente* ColaPrioridadPacientes::siguiente() {
    if (pendientes.empty()) {
        return nullptr;
    }

    Paciente* paciente = pendientes.top();
    pendientes.pop();
    return paciente;
}

bool ColaPrioridadPacientes::vacia() const {
    return pendientes.empty();
}

int ColaPrioridadPacientes::cantidad() const {
    return static_cast<int>(pendientes.size());
}

int ColaPrioridadPacientes::cantidadPorGravedad(int gravedad) const {
    int cantidad = 0;
    std::vector<Paciente*> pacientes = obtenerPacientes();
    for (Paciente* paciente : pacientes) {
        if (paciente->obtenerGravedad() == gravedad) {
            ++cantidad;
        }
    }
    return cantidad;
}

void ColaPrioridadPacientes::avanzarEspera() {
    std::vector<Paciente*> pacientes = obtenerPacientes();
    for (Paciente* paciente : pacientes) {
        paciente->incrementarEspera();
    }
}

std::list<Paciente*> ColaPrioridadPacientes::retirarVencidos() {
    std::list<Paciente*> vencidos;
    std::priority_queue<Paciente*, std::vector<Paciente*>, ComparadorPrioridadPaciente> restantes;

    while (!pendientes.empty()) {
        Paciente* paciente = pendientes.top();
        pendientes.pop();

        if (paciente->obtenerTurnosEspera() >= paciente->turnosMaximosEspera()) {
            paciente->establecerEstado(EstadoPaciente::Perdido);
            vencidos.push_back(paciente);
        } else {
            restantes.push(paciente);
        }
    }

    pendientes.swap(restantes);
    return vencidos;
}

void ColaPrioridadPacientes::limpiar() {
    pendientes = decltype(pendientes)();
}

std::string ColaPrioridadPacientes::resumen() const {
    std::string salida;
    std::vector<Paciente*> pacientesEnCola = obtenerPacientes();

    for (int gravedad = 1; gravedad <= 5; ++gravedad) {
        int cuantos = 0;
        int suma = 0;
        for (Paciente* paciente : pacientesEnCola) {
            if (paciente->obtenerGravedad() == gravedad) {
                ++cuantos;
                suma += paciente->obtenerTurnosEspera();
            }
        }

        if (cuantos > 0) {
            if (!salida.empty()) {
                salida += " | ";
            }
            salida += std::to_string(cuantos) + " paciente(s) G" + std::to_string(gravedad);
            salida += ", espera promedio " + std::to_string(suma / cuantos) + " turnos";
        }
    }

    return salida.empty() ? "vacia" : salida;
}

std::vector<Paciente*> ColaPrioridadPacientes::obtenerPacientes() const {
    std::vector<Paciente*> pacientes;
    auto copia = pendientes;

    while (!copia.empty()) {
        pacientes.push_back(copia.top());
        copia.pop();
    }

    return pacientes;
}
