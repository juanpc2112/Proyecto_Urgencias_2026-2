#include "Jornada.h"
Jornada::Jornada() : medico(), numero(0), activa(false) {}
Jornada::Jornada(const Medico& medico, int numero) : medico(medico), numero(numero) {}
const Medico& Jornada::obtenerMedico() const {
    return medico;
}

int Jornada::obtenerNumero() const {
    return numero;
}

int Jornada::obtenerTurnoActual() const {
    return turnoActual;
}

bool Jornada::estaActiva() const {
    return activa;
}

bool Jornada::puedeRealizarTurno() const {
    return activa && turnoActual < 50;
}

void Jornada::registrarTurnoValido() {
    if (puedeRealizarTurno()) {
        ++turnoActual;
    }
}

void Jornada::cerrar(int camasVacias) {
    metricasDeJornada.fijarCamasVacias(camasVacias);
    activa = false;
}

MetricasJornada& Jornada::metricas() {
    return metricasDeJornada;
}

const MetricasJornada& Jornada::metricas() const {
    return metricasDeJornada;
}

PilaUltimosAtendidos& Jornada::ultimosAtendidos() {
    return pilaUltimosAtendidos;
}

const PilaUltimosAtendidos& Jornada::ultimosAtendidos() const {
    return pilaUltimosAtendidos;
}
