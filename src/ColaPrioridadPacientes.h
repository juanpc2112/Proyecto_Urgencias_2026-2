#ifndef URGENCIAS_COLA_PRIORIDAD_PACIENTES_H
#define URGENCIAS_COLA_PRIORIDAD_PACIENTES_H

#include "Paciente.h"
#include <list>
#include <queue>
#include <string>
#include <vector>

// Deja arriba la gravedad más alta (1) y, en empate, la llegada más antigua.
struct ComparadorPrioridadPaciente {
    bool operator()(const Paciente* a, const Paciente* b) const;
};

// TAD de espera implementado con una cola de prioridad de la STL.
class ColaPrioridadPacientes {
public:
    // Inserta un paciente que se encuentra en estado EnCola.
    bool insertar(Paciente* paciente);
    // Extrae el paciente de mayor prioridad.
    Paciente* siguiente();
    // Consultas de cantidad y contenido.
    bool vacia() const;
    int cantidad() const;
    // Avanza la espera y retira a quienes alcanzaron su límite.
    void avanzarEspera();
    std::list<Paciente*> retirarVencidos();
    // Produce un resumen agrupado por gravedad.
    std::string resumen() const;
    // Devuelve una copia ordenada para mostrar pacientes sin alterar la cola.
    std::vector<Paciente*> obtenerPacientes() const;

private:
    std::priority_queue<Paciente*, std::vector<Paciente*>, ComparadorPrioridadPaciente> pendientes;
};

#endif
