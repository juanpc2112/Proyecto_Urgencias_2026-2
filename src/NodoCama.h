#ifndef URGENCIAS_NODO_CAMA_H
#define URGENCIAS_NODO_CAMA_H

#include "Paciente.h"

// Estados disponibles para cada cama de la sala.
enum class EstadoCama { Vacia, Ocupada, Mantenimiento };

// Nodo de la lista doblemente enlazada. La sala mantiene la propiedad de los nodos.
class NodoCama {
public:
    // Crea la cama con su número del 1 al 10.
    explicit NodoCama(int numero);

    // Consultas del estado y de los enlaces de la cama.
    int obtenerNumero() const;
    EstadoCama obtenerEstado() const;
    Paciente* obtenerPaciente() const;
    int obtenerTurnosTratamientoRestantes() const;
    NodoCama* obtenerAnterior() const;
    NodoCama* obtenerSiguiente() const;
    bool estaDisponible() const;
    // Asigna y trata al paciente que ocupa esta cama.
    bool asignarPaciente(Paciente* paciente);
    bool tratarPaciente();
    // Libera una cama cuando el tratamiento terminó.
    Paciente* liberar();
    // Cambia una cama vacía entre los estados vacía y mantenimiento.
    bool establecerMantenimiento(bool mantenimiento);
    // Configura los enlaces de la lista doblemente enlazada.
    void establecerAnterior(NodoCama* anterior);
    void establecerSiguiente(NodoCama* siguiente);

private:
    int numero;                              // Número fijo de cama.
    EstadoCama estado = EstadoCama::Vacia;   // Disponibilidad de la cama.
    Paciente* paciente = nullptr;            // Referencia no propietaria al paciente.
    int turnosTratamientoRestantes = 0;      // Usos de T que faltan para completar tratamiento.
    NodoCama* anterior = nullptr;            // Cama anterior en la sala.
    NodoCama* siguiente = nullptr;           // Cama siguiente en la sala.
};

#endif
