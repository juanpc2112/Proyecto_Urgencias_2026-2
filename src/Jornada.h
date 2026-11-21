#ifndef URGENCIAS_JORNADA_H
#define URGENCIAS_JORNADA_H

#include "Medico.h"
#include "MetricasJornada.h"
#include "PilaUltimosAtendidos.h"

// Agrupa el trabajo de un médico durante un máximo de 50 turnos.
class Jornada {
public:
    // El constructor vacío permite crear el simulador antes de pedir los datos del médico.
    Jornada();
    // Inicia una jornada para el médico indicado.
    Jornada(const Medico& medico, int numero);

    // Consultas de turno, médico y estado de la jornada.
    const Medico& obtenerMedico() const;
    int obtenerNumero() const;
    int obtenerTurnoActual() const;
    bool estaActiva() const;
    bool puedeRealizarTurno() const;
    // Avanza un turno válido.
    void registrarTurnoValido();
    // Cierra la jornada y guarda cuántas camas quedaron vacías.
    void cerrar(int camasVacias);
    // Acceso a las métricas y a la pila de altas de esta jornada.
    MetricasJornada& metricas();
    const MetricasJornada& metricas() const;
    PilaUltimosAtendidos& ultimosAtendidos();
    const PilaUltimosAtendidos& ultimosAtendidos() const;

private:
    Medico medico;                               // Médico a cargo de la jornada.
    int numero;                                  // Número secuencial de jornada.
    int turnoActual = 0;                        // Turnos válidos que ya se usaron.
    bool activa = true;                         // Indica si todavía acepta acciones.
    MetricasJornada metricasDeJornada;           // Resultados acumulados en esta jornada.
    PilaUltimosAtendidos pilaUltimosAtendidos;   // Altas de la jornada actual.
};

#endif
