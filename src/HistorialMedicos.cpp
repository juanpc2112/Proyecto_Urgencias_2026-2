#include "HistorialMedicos.h"
#include <iostream>

void HistorialMedicos::guardar(const Jornada& jornada) {
    const Medico& medico = jornada.obtenerMedico();
    const MetricasJornada& metricas = jornada.metricas();
    RegistroJornada registro;
    registro.numero = jornada.obtenerNumero();
    registro.turnos = jornada.obtenerTurnoActual();
    registro.recibidos = metricas.obtenerRecibidos();
    registro.altas = metricas.obtenerAltas();
    registro.perdidos = metricas.obtenerPerdidos();
    registro.esperaPromedio = metricas.obtenerEsperaPromedio();
    jornadasPorMedico[medico.obtenerIdentificacion()].push_back(registro);
    nombresPorMedico[medico.obtenerIdentificacion()] = medico.obtenerNombre();
}

int HistorialMedicos::cantidadMedicos() const { return static_cast<int>(jornadasPorMedico.size()); }

void HistorialMedicos::mostrarHistorial(const std::string& identificacion) const {
    auto it = jornadasPorMedico.find(identificacion);
    if (it == jornadasPorMedico.end()) {
        std::cout << "No hay jornadas registradas para el medico " << identificacion << ".\n";
        return;
    }
    std::cout << "Historial de " << nombresPorMedico.at(identificacion) << " (" << identificacion << ")\n";
    std::cout << "Jornadas trabajadas: " << it->second.size() << '\n';
    for (const RegistroJornada& jornada : it->second)
        std::cout << "Jornada " << jornada.numero << ": " << jornada.turnos << " turnos, "
                  << jornada.recibidos << " recibidos, " << jornada.altas << " altas, "
                  << jornada.perdidos << " perdidos.\n";
}

void HistorialMedicos::mostrarTodos() const {
    int perdidos = 0;
    std::cout << "Auditoria de pacientes perdidos:\n";
    for (const auto& medico : jornadasPorMedico) {
        for (const RegistroJornada& jornada : medico.second) {
            perdidos += jornada.perdidos;
            if (jornada.perdidos > 0)
                std::cout << nombresPorMedico.at(medico.first) << " (" << medico.first << "), jornada "
                          << jornada.numero << ": " << jornada.perdidos << " paciente(s).\n";
        }
    }
    std::cout << "Total perdidos: " << perdidos << '\n';
}
