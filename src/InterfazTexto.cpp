#include "InterfazTexto.h"
#include <iostream>

bool InterfazTexto::solicitarMedico(Medico& medico, bool reemplazo) const {
    while (true) {
        std::string identificacion;
        std::string nombre;
        std::cout << (reemplazo ? "\nNuevo medico\n" : "Registro del medico de turno\n");
        std::cout << "Identificacion: ";
        if (!std::getline(std::cin, identificacion)) return false;
        std::cout << "Nombre: ";
        if (!std::getline(std::cin, nombre)) return false;
        if (!identificacion.empty() && !nombre.empty()) {
            medico = Medico(identificacion, nombre);
            return true;
        }
        std::cout << "Identificacion y nombre son obligatorios.\n";
    }
}

bool InterfazTexto::leerAccion(std::string& accion) const {
    std::cout << "Accion > ";
    return static_cast<bool>(std::getline(std::cin, accion));
}

bool InterfazTexto::leerCedula(std::string& cedula) const {
    std::cout << "Ingresa el numero de cedula: ";
    return static_cast<bool>(std::getline(std::cin, cedula));
}

void InterfazTexto::mostrarEstado(const SalaUrgencias& sala, const ColaPrioridadPacientes& cola,
                                  const Jornada& jornada) const {
    std::cout << "\n============================================================\n";
    std::cout << "Dr./Dra. " << jornada.obtenerMedico().obtenerNombre() << " | Jornada "
              << jornada.obtenerNumero() << " | Turno " << jornada.obtenerTurnoActual() + 1 << "/50\n";
    sala.mostrar();
    const NodoCama& cama = sala.camaActual();
    std::cout << "Cama actual: #" << cama.obtenerNumero();
    if (cama.obtenerPaciente()) {
        const Paciente* paciente = cama.obtenerPaciente();
        std::cout << " - " << paciente->obtenerNombre() << " (cedula " << paciente->obtenerCedula()
                  << ", gravedad " << paciente->obtenerGravedad()
                  << "), tratamiento pendiente: " << cama.obtenerTurnosTratamientoRestantes();
    } else {
        std::cout << (cama.obtenerEstado() == EstadoCama::Mantenimiento ? " (mantenimiento)" : " (vacia)");
    }
    std::cout << "\nCola (" << cola.cantidad() << "): " << cola.resumen() << '\n';
    for (Paciente* paciente : cola.obtenerPacientes()) {
        int restantes = paciente->turnosMaximosEspera() - paciente->obtenerTurnosEspera();
        if (restantes <= 2)
            std::cout << "  ALERTA: " << paciente->obtenerNombre() << " (CC " << paciente->obtenerCedula()
                      << "), gravedad " << paciente->obtenerGravedad() << ", riesgo en " << restantes << " turno(s).\n";
    }
    mostrarAyuda();
}

void InterfazTexto::mostrarPaciente(const Paciente* paciente) const {
    if (paciente == nullptr) {
        std::cout << "No se encontro un paciente con esa cedula.\n";
    } else {
        std::cout << "Cedula: " << paciente->obtenerCedula() << "\nNombre: " << paciente->obtenerNombre()
                  << "\nGravedad: " << paciente->obtenerGravedad() << "\nCondicion: "
                  << paciente->obtenerCondicion() << "\nEspera acumulada: " << paciente->obtenerEsperaMinutos()
                  << " minutos\nEstado: ";
        EstadoPaciente estado = paciente->obtenerEstado();
        switch (estado) {
            case EstadoPaciente::EnCola: std::cout << "En cola"; break;
            case EstadoPaciente::EnCama: std::cout << "En cama"; break;
            case EstadoPaciente::DadoDeAlta: std::cout << "Dado de alta"; break;
            case EstadoPaciente::Perdido: std::cout << "Perdido"; break;
        }
        if (!paciente->obtenerMedicoResponsable().empty())
            std::cout << "\nMedico/jornada responsable: " << paciente->obtenerMedicoResponsable()
                      << " / " << paciente->obtenerJornadaResponsable();
        std::cout << '\n';
    }
}

void InterfazTexto::mostrarReporte(const Jornada& jornada) const {
    const MetricasJornada& m = jornada.metricas();
    std::cout << "\n--- Reporte de jornada " << jornada.obtenerNumero() << " ---\n"
              << "Medico: " << jornada.obtenerMedico().obtenerNombre() << " ("
              << jornada.obtenerMedico().obtenerIdentificacion() << ")\n"
              << "Turnos usados: " << jornada.obtenerTurnoActual() << "/50\n"
              << "Pacientes recibidos: " << m.obtenerRecibidos() << '\n'
              << "Pacientes dados de alta: " << m.obtenerAltas() << '\n'
              << "Pacientes perdidos: " << m.obtenerPerdidos() << '\n'
              << "Espera promedio de recibidos: " << m.obtenerEsperaPromedio() << " minutos\n"
              << "Camas vacias al cierre: " << m.obtenerCamasVacias() << "/10\n";
}

void InterfazTexto::consultarPaciente(const RegistroPacientes& registro, const std::string& cedula) const {
    mostrarPaciente(registro.buscar(cedula));
}

void InterfazTexto::mostrarAyuda() const {
    std::cout << "A/D mover | R recibir | T tratar | X alta | U ultimos | C consultar por cedula"
                 " | H historial medico | V auditoria | O cambiar medico | E cerrar jornada | S salir\n";
}

void InterfazTexto::informar(const std::string& mensaje) const { std::cout << mensaje << '\n'; }
