#ifndef URGENCIAS_PILA_ULTIMOS_ATENDIDOS_H
#define URGENCIAS_PILA_ULTIMOS_ATENDIDOS_H

#include "Paciente.h"
#include <stack>

// Guarda las altas de la jornada actual en orden LIFO.
class PilaUltimosAtendidos {
public:
    // Agrega el paciente más recientemente dado de alta.
    void apilar(Paciente* paciente);
    // Muestra desde el alta más reciente hasta la más antigua.
    void mostrar() const;

private:
    std::stack<Paciente*> altas; // Referencias a pacientes propiedad del registro hash.
};

#endif
