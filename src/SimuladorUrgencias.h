#ifndef URGENCIAS_SIMULADOR_URGENCIAS_H
#define URGENCIAS_SIMULADOR_URGENCIAS_H

#include "ColaPrioridadPacientes.h"
#include "HistorialMedicos.h"
#include "InterfazTexto.h"
#include "RegistroPacientes.h"
#include "SalaUrgencias.h"
#include <random>
#include <string>

// Coordina las acciones, las jornadas, la sala y los registros del simulador.
class SimuladorUrgencias {
public:
    SimuladorUrgencias();
    // Ejecuta el ciclo principal hasta que termine la jornada o la entrada.
    void ejecutar();

private:
    SalaUrgencias sala;                 // Diez camas enlazadas.
    ColaPrioridadPacientes cola;        // Pacientes que esperan en triage.
    RegistroPacientes registro;         // Historial hash de pacientes.
    HistorialMedicos historial;         // Historial de jornadas por médico.
    InterfazTexto interfaz;             // Entrada y salida de consola.
    Jornada jornada;                    // Jornada activa del médico actual.
    std::mt19937 generador;             // Generador para casos y cédulas aleatorias.
    int siguienteJornada = 1;           // Número de la próxima jornada.
    int ordenLlegada = 0;               // Orden global para desempatar la cola.
    bool finalizar = false;             // Controla el ciclo principal.
    bool hayJornada = false;            // Indica que ya se registró un médico.

    // Inicia jornadas, avanza turnos y conserva la sala al cambiar de médico.
    bool iniciarJornada(bool reemplazo);
    bool procesarAccion(const std::string& linea);
    // Actualiza espera, pérdidas y llegadas programadas para el turno completado.
    void completarTurno();
    // Crea un paciente aleatorio y lo agrega al registro y a la cola.
    void generarPacienteAutomatico();
    void cerrarJornada();
    std::string generarCedula();
    std::string normalizarCedula(const std::string& entrada) const;
    void auditarPerdidos() const;
};

#endif
