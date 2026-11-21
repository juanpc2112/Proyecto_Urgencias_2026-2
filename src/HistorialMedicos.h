#ifndef URGENCIAS_HISTORIAL_MEDICOS_H
#define URGENCIAS_HISTORIAL_MEDICOS_H

#include "Jornada.h"
#include <map>
#include <string>
#include <vector>

// Resumen permanente de una jornada ya cerrada.
struct RegistroJornada {
    int numero = 0;          // Número de jornada.
    int turnos = 0;           // Turnos usados por el médico.
    int recibidos = 0;        // Pacientes recibidos.
    int altas = 0;            // Pacientes dados de alta.
    int perdidos = 0;         // Pacientes perdidos.
    int esperaPromedio = 0;   // Espera promedio de los recibidos, en minutos.
};

// Guarda jornadas cerradas y permite consultarlas por identificación del médico.
class HistorialMedicos {
public:
    // Agrega el resumen de una jornada al historial del médico responsable.
    void guardar(const Jornada& jornada);
    int cantidadMedicos() const;
    // Muestra las jornadas de un médico.
    void mostrarHistorial(const std::string& identificacion) const;
    // Muestra el resumen de todos los médicos y sus jornadas.
    void mostrarTodos() const;

private:
    std::map<std::string, std::vector<RegistroJornada>> jornadasPorMedico; // Historial agrupado por ID.
    std::map<std::string, std::string> nombresPorMedico; // Nombre asociado a cada ID.
};

#endif
