#include "PilaUltimosAtendidos.h"
#include <iostream>

void PilaUltimosAtendidos::apilar(Paciente* paciente) {
    if (paciente != nullptr) altas.push(paciente);
}

void PilaUltimosAtendidos::mostrar() const {
    if (altas.empty()) {
        std::cout << "No hay pacientes dados de alta en esta jornada.\n";
    } else {
        std::stack<Paciente*> copia = altas;
        int posicion = 1;
        while (!copia.empty()) {
            const Paciente* paciente = copia.top();
            std::cout << posicion++ << ". " << paciente->obtenerNombre() << " (CC "
                      << paciente->obtenerCedula() << ", gravedad " << paciente->obtenerGravedad() << ")\n";
            copia.pop();
        }
    }
}

