#ifndef URGENCIAS_COLA_PRIORIDAD_PACIENTES_H
#define URGENCIAS_COLA_PRIORIDAD_PACIENTES_H

#include "Paciente.h"
#include <list>
#include <set>
#include <string>

// Ordena por gravedad ascendente y, en empate, por orden de llegada.
struct ComparadorPrioridadPaciente {
    bool operator()(const Paciente* a, const Paciente* b) const;
};

// TAD de espera implementado con un conjunto STL ordenado.
class ColaPrioridadPacientes {
public:
    // Inserta un paciente que se encuentra en estado EnCola.
    bool insertar(Paciente* paciente);
    // Extrae el paciente de mayor prioridad.
    Paciente* siguiente();
    // Consultas de cantidad y contenido.
    bool vacia() const;
    int cantidad() const;
    int cantidadPorGravedad(int gravedad) const;
    // Avanza la espera y retira a quienes alcanzaron su límite.
    void avanzarEspera();
    std::list<Paciente*> retirarVencidos();
    void limpiar();
    // Produce un resumen agrupado por gravedad.
    std::string resumen() const;
    const std::set<Paciente*, ComparadorPrioridadPaciente>& pacientes() const;

private:
    std::set<Paciente*, ComparadorPrioridadPaciente> pendientes; // Pacientes en espera ordenados por prioridad.
};

#endif
