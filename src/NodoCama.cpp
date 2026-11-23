#include "NodoCama.h"

NodoCama::NodoCama(int numero) : numero(numero) {}

int NodoCama::obtenerNumero() const {
    return numero;
}

EstadoCama NodoCama::obtenerEstado() const {
    return estado;
}

Paciente* NodoCama::obtenerPaciente() const {
    return paciente;
}

int NodoCama::obtenerTurnosTratamientoRestantes() const {
    return turnosTratamientoRestantes;
}

NodoCama* NodoCama::obtenerAnterior() const {
    return anterior;
}

NodoCama* NodoCama::obtenerSiguiente() const {
    return siguiente;
}

bool NodoCama::estaDisponible() const {
    return estado == EstadoCama::Vacia && paciente == nullptr;
}

bool NodoCama::asignarPaciente(Paciente* paciente) {
    if (!estaDisponible() || paciente == nullptr) {
        return false;
    }
    this->paciente = paciente;
    paciente->establecerEstado(EstadoPaciente::EnCama);
    turnosTratamientoRestantes = 6 - paciente->obtenerGravedad();
    estado = EstadoCama::Ocupada;
    return true;
}

bool NodoCama::tratarPaciente() {
    if (estado != EstadoCama::Ocupada || !paciente || turnosTratamientoRestantes <= 0) {
        return false;
    }
    --turnosTratamientoRestantes;
    return true;
}

Paciente* NodoCama::liberar() {
    if (estado != EstadoCama::Ocupada || paciente == nullptr || turnosTratamientoRestantes != 0) {
        return nullptr;
    }
    Paciente* paciente = this->paciente;
    this->paciente->establecerEstado(EstadoPaciente::DadoDeAlta);
    this->paciente = nullptr;
    estado = EstadoCama::Vacia;
    return paciente;
}

void NodoCama::establecerAnterior(NodoCama* anterior) {
    this->anterior = anterior;
}

void NodoCama::establecerSiguiente(NodoCama* siguiente) {
    this->siguiente = siguiente;
}
