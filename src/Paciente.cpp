#include "Paciente.h"

Paciente::Paciente(const std::string& cedula, const std::string& nombre, int gravedad,
                   const std::string& condicion, int turnoLlegada, int ordenLlegada)
    : cedula(cedula), nombre(nombre), gravedad(gravedad), condicion(condicion),
      turnoLlegada(turnoLlegada), ordenLlegada(ordenLlegada) {}

const std::string& Paciente::obtenerCedula() const {
    return cedula;
}
const std::string& Paciente::obtenerNombre() const {
    return nombre;
}
const std::string& Paciente::obtenerCondicion() const {
    return condicion;
}
const std::string& Paciente::obtenerMedicoResponsable() const {
    return medicoResponsable;
}
int Paciente::obtenerGravedad() const {
    return gravedad;
}
int Paciente::obtenerTurnoLlegada() const {
    return turnoLlegada;
}
int Paciente::obtenerOrdenLlegada() const {
    return ordenLlegada;
}
int Paciente::obtenerEsperaMinutos() const {
    return esperaMinutos;
}
int Paciente::obtenerTurnosEspera() const {
    return turnosEspera;
}
int Paciente::obtenerRiesgoCritico() const {
    return riesgoCritico;
}
int Paciente::obtenerJornadaResponsable() const {
    return jornadaResponsable;
}
EstadoPaciente Paciente::obtenerEstado() const {
    return estado;
}
bool Paciente::esCritico() const {
    return gravedad == 1;
}

int Paciente::turnosMaximosEspera() const {
    if (gravedad == 1) {
        return 6;
    }
    return 6 + 2 * gravedad;
}

void Paciente::incrementarEspera() {
    ++turnosEspera;
    esperaMinutos += 5;
    if (esCritico()) {
        ++riesgoCritico;
    }
}

void Paciente::fijarResponsable(const std::string& medico, int jornada) {
    medicoResponsable = medico;
    jornadaResponsable = jornada;
}

void Paciente::establecerEstado(EstadoPaciente nuevoEstado) { estado = nuevoEstado; }
