#ifndef URGENCIAS_PACIENTE_H
#define URGENCIAS_PACIENTE_H

#include <string>

// Estados posibles durante el recorrido del paciente en el simulador.
enum class EstadoPaciente { EnCola, EnCama, DadoDeAlta, Perdido };

// Datos del paciente y estado que se conserva en el registro histórico.
class Paciente {
public:
    // Crea un paciente con su orden de llegada para resolver empates FIFO.
    Paciente(const std::string& cedula, const std::string& nombre, int gravedad,
             const std::string& condicion, int turnoLlegada, int ordenLlegada);

    // Consultas de los datos del paciente.
    const std::string& obtenerCedula() const;
    const std::string& obtenerNombre() const;
    const std::string& obtenerCondicion() const;
    const std::string& obtenerMedicoResponsable() const;
    int obtenerGravedad() const;
    int obtenerTurnoLlegada() const;
    int obtenerOrdenLlegada() const;
    int obtenerEsperaMinutos() const;
    int obtenerTurnosEspera() const;
    int obtenerRiesgoCritico() const;
    int obtenerJornadaResponsable() const;
    // Calcula el límite de espera según la gravedad.
    int turnosMaximosEspera() const;
    EstadoPaciente obtenerEstado() const;

    // Suma un turno de espera y cinco minutos.
    void incrementarEspera();
    // Guarda el médico y la jornada responsables de su resultado.
    void fijarResponsable(const std::string& medico, int jornada);
    // Actualiza su estado dentro del flujo de atención.
    void establecerEstado(EstadoPaciente nuevoEstado);
    // Indica si el paciente tiene gravedad crítica.
    bool esCritico() const;

private:
    std::string cedula;                 // Identificador de cuatro dígitos.
    std::string nombre;                 // Nombre mostrado en la sala.
    int gravedad;                       // Nivel de gravedad entre 1 y 5.
    std::string condicion;              // Descripción del caso.
    int turnoLlegada;                   // Turno en que ingresó a la cola.
    int ordenLlegada;                   // Orden global para mantener FIFO en empates.
    int esperaMinutos = 0;              // Tiempo acumulado mientras espera.
    int turnosEspera = 0;               // Turnos completos que lleva en la cola.
    int riesgoCritico = 0;              // Turnos de espera de un paciente crítico.
    int jornadaResponsable = 0;         // Jornada asociada a su resultado final.
    std::string medicoResponsable;      // Médico asociado a su resultado final.
    EstadoPaciente estado = EstadoPaciente::EnCola; // Ubicación o resultado actual.
};

#endif
