#ifndef URGENCIAS_INTERFAZ_TEXTO_H
#define URGENCIAS_INTERFAZ_TEXTO_H

#include "ColaPrioridadPacientes.h"
#include "Jornada.h"
#include "Medico.h"
#include "RegistroPacientes.h"
#include "SalaUrgencias.h"
#include <string>

// Presenta información y recibe entradas en modo texto.
class InterfazTexto {
public:
    // Pide los datos del médico. Devuelve false si se termina la entrada.
    bool solicitarMedico(Medico& medico, bool reemplazo) const;
    bool leerAccion(std::string& accion) const;
    // Pide la cédula después de que el usuario selecciona la acción C.
    bool leerCedula(std::string& cedula) const;
    // Muestra la sala, la cola y la cama actual.
    void mostrarEstado(const SalaUrgencias& sala, const ColaPrioridadPacientes& cola,
                       const Jornada& jornada) const;
    // Muestra la ficha de un paciente o el reporte de jornada.
    void mostrarPaciente(const Paciente* paciente) const;
    void mostrarReporte(const Jornada& jornada) const;
    // Consulta por cédula y presenta las acciones disponibles.
    void consultarPaciente(const RegistroPacientes& registro, const std::string& cedula) const;
    void mostrarAyuda() const;
    // Imprime un mensaje de información en consola.
    void informar(const std::string& mensaje) const;
};

#endif
