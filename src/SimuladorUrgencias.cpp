#include "SimuladorUrgencias.h"
#include <iostream>
#include <list>
#include <vector>

namespace {
struct CasoPaciente {
    std::string nombre;
    int gravedad;
    std::string condicion;
};

std::string formatearCedula(int numero) {
    std::string cedula("0000");
    cedula[3] = static_cast<char>('0' + numero % 10);
    cedula[2] = static_cast<char>('0' + (numero / 10) % 10);
    cedula[1] = static_cast<char>('0' + (numero / 100) % 10);
    cedula[0] = static_cast<char>('0' + (numero / 1000) % 10);
    return cedula;
}

char mayuscula(char caracter) {
    if (caracter >= 'a' && caracter <= 'z') return static_cast<char>(caracter - 'a' + 'A');
    return caracter;
}
}

SimuladorUrgencias::SimuladorUrgencias()
    : generador(std::random_device{}()) {}

bool SimuladorUrgencias::iniciarJornada(bool reemplazo) {
    Medico medico;
    if (!interfaz.solicitarMedico(medico, reemplazo)) return false;
    jornada = Jornada(medico, siguienteJornada++);
    hayJornada = true;
    sala.ubicarMedicoEnEntrada();
    generarPacienteAutomatico();
    return true;
}

void SimuladorUrgencias::ejecutar() {
    std::cout << "SIMULADOR DE URGENCIAS\n";
    if (!iniciarJornada(false)) return;

    while (!finalizar) {
        if (!hayJornada || !jornada.puedeRealizarTurno()) {
            cerrarJornada();
            finalizar = true;
            break;
        }
        interfaz.mostrarEstado(sala, cola, jornada);
        std::string accion;
        if (!interfaz.leerAccion(accion) || !procesarAccion(accion)) {
            cerrarJornada();
            finalizar = true;
        }
    }
    auditarPerdidos();
    std::cout << "Medicos con jornadas cerradas: " << historial.cantidadMedicos() << '\n';
}

void SimuladorUrgencias::completarTurno() {
    if (!hayJornada) return;
    jornada.registrarTurnoValido();
    cola.avanzarEspera();
    std::list<Paciente*> vencidos = cola.retirarVencidos();
    for (Paciente* paciente : vencidos) {
        paciente->fijarResponsable(jornada.obtenerMedico().obtenerNombre(), jornada.obtenerNumero());
        jornada.metricas().registrarPerdida();
        std::cout << "ALERTA: paciente " << paciente->obtenerNombre() << " (CC "
                  << paciente->obtenerCedula() << ") se perdio por exceder su espera.\n";
    }
    int turnoActual = jornada.obtenerTurnoActual();
    int cantidadNuevos = 0;
    if (turnoActual == 10) cantidadNuevos = 1;
    else if (turnoActual == 20) cantidadNuevos = 2;
    else if (turnoActual == 30) cantidadNuevos = 3;
    else if (turnoActual == 40) cantidadNuevos = 4;

    for (int i = 0; i < cantidadNuevos; ++i) {
        generarPacienteAutomatico();
    }
}

std::string SimuladorUrgencias::generarCedula() {
    std::uniform_int_distribution<int> distribucion(0, 9999);
    int inicio = distribucion(generador);
    for (int desplazamiento = 0; desplazamiento < 10000; ++desplazamiento) {
        std::string cedula = formatearCedula((inicio + desplazamiento) % 10000);
        if (registro.cedulaDisponible(cedula)) return cedula;
    }
    return "";
}

void SimuladorUrgencias::generarPacienteAutomatico() {
    const std::vector<CasoPaciente> casos = {
        {"Ana Ruiz", 1, "Dolor toracico intenso"},
        {"Luis Mejia", 2, "Dificultad respiratoria"},
        {"Marta Velez", 3, "Fiebre alta y malestar"},
        {"Carlos Perez", 4, "Herida superficial"},
        {"Sofia Torres", 5, "Consulta general"},
        {"Diego Rojas", 1, "Trauma con sangrado"},
        {"Elena Castro", 3, "Dolor abdominal"},
        {"Juan Salazar", 2, "Reaccion alergica"},
        {"Laura Gomez", 5, "Dolor de garganta"},
        {"Andres Mora", 4, "Esguince leve"}
    };
    std::uniform_int_distribution<int> casoAleatorio(0, static_cast<int>(casos.size()) - 1);
    std::string cedula = generarCedula();
    if (cedula.empty()) {
        std::cout << "No quedan cedulas disponibles en el rango 0000-9999.\n";
        return;
    }
    const CasoPaciente& caso = casos[static_cast<std::size_t>(casoAleatorio(generador))];
    Paciente nuevo(cedula, caso.nombre, caso.gravedad, caso.condicion,
                   jornada.obtenerTurnoActual(), ordenLlegada++);
    Paciente* almacenado = registro.registrar(nuevo);
    cola.insertar(almacenado);
    std::cout << "Nuevo paciente en triage: " << almacenado->obtenerNombre() << " (CC "
              << almacenado->obtenerCedula() << "), gravedad " << almacenado->obtenerGravedad() << ".\n";
}

std::string SimuladorUrgencias::normalizarCedula(const std::string& entrada) const {
    if (entrada.empty() || entrada.size() > 4) return "";
    std::string resultado("0000");
    int destino = 3;
    for (int origen = static_cast<int>(entrada.size()) - 1; origen >= 0; --origen) {
        if (entrada[static_cast<std::size_t>(origen)] < '0' || entrada[static_cast<std::size_t>(origen)] > '9') return "";
        resultado[static_cast<std::size_t>(destino--)] = entrada[static_cast<std::size_t>(origen)];
    }
    return resultado;
}

bool SimuladorUrgencias::procesarAccion(const std::string& linea) {
    std::size_t inicio = linea.find_first_not_of(" \t");
    if (inicio == std::string::npos) {
        interfaz.informar("Accion vacia; no consume turno.");
        return true;
    }
    std::size_t espacio = linea.find_first_of(" \t", inicio);
    std::string comando = linea.substr(inicio, espacio == std::string::npos ? std::string::npos : espacio - inicio);
    if (comando.size() == 1) comando[0] = mayuscula(comando[0]);
    bool valida = false;
    bool cambioMedico = false;
    if (comando == "A") {
        valida = sala.moverIzquierda();
        if (!valida) interfaz.informar("No hay cama anterior.");
    } else if (comando == "D") {
        valida = sala.moverDerecha();
        if (!valida) interfaz.informar("No hay cama siguiente.");
    } else if (comando == "R") {
        if (!sala.camaActual().estaDisponible()) interfaz.informar("La cama actual no esta vacia.");
        else if (cola.vacia()) interfaz.informar("No hay pacientes en la cola.");
        else {
            Paciente* paciente = cola.siguiente();
            paciente->fijarResponsable(jornada.obtenerMedico().obtenerNombre(), jornada.obtenerNumero());
            if (sala.camaActual().asignarPaciente(paciente)) {
                jornada.metricas().registrarRecepcion(paciente->obtenerEsperaMinutos());
                std::cout << paciente->obtenerNombre() << " asignado a cama #"
                          << sala.camaActual().obtenerNumero() << ".\n";
                valida = true;
            } else {
                cola.insertar(paciente);
                interfaz.informar("No se pudo asignar al paciente.");
            }
        }
    } else if (comando == "T") {
        valida = sala.camaActual().tratarPaciente();
        if (valida) {
            Paciente* paciente = sala.camaActual().obtenerPaciente();
            paciente->fijarResponsable(jornada.obtenerMedico().obtenerNombre(), jornada.obtenerNumero());
            std::cout << "Tratamiento aplicado. Turnos pendientes: "
                      << sala.camaActual().obtenerTurnosTratamientoRestantes() << '\n';
        } else interfaz.informar("La cama esta vacia o el tratamiento ya termino.");
    } else if (comando == "X") {
        Paciente* paciente = sala.camaActual().liberar();
        if (paciente != nullptr) {
            paciente->fijarResponsable(jornada.obtenerMedico().obtenerNombre(), jornada.obtenerNumero());
            jornada.ultimosAtendidos().apilar(paciente);
            jornada.metricas().registrarAlta();
            std::cout << paciente->obtenerNombre() << " fue dado de alta.\n";
            valida = true;
        } else interfaz.informar("Solo se puede dar de alta con tratamiento completo.");
    } else if (comando == "U") {
        jornada.ultimosAtendidos().mostrar();
        valida = true;
    } else if (comando == "C") {
        std::string entradaCedula;
        if (!interfaz.leerCedula(entradaCedula)) return false;
        std::string cedula = normalizarCedula(entradaCedula);
        if (cedula.empty()) interfaz.informar("Ingresa solo numeros, con una cedula entre 0000 y 9999.");
        else {
            interfaz.consultarPaciente(registro, cedula);
            valida = true;
        }
    } else if (comando == "H") {
        interfaz.informar("Identificacion del medico para consultar historial:");
        std::string identificacion;
        if (!std::getline(std::cin, identificacion)) return false;
        historial.mostrarHistorial(identificacion);
        if (jornada.obtenerMedico().obtenerIdentificacion() == identificacion && jornada.estaActiva())
            std::cout << "Jornada actual " << jornada.obtenerNumero() << ": "
                      << jornada.obtenerTurnoActual() << " turnos completados.\n";
        valida = true;
    } else if (comando == "V") {
        auditarPerdidos();
        valida = true;
    } else if (comando == "O") {
        valida = true;
        cambioMedico = true;
    } else if (comando == "E") {
        cerrarJornada();
        if (!iniciarJornada(true)) {
            finalizar = true;
        }
        return true;
    } else if (comando == "S") {
        cerrarJornada();
        finalizar = true;
        return true;
    } else {
        interfaz.informar("Comando desconocido. Las acciones invalidas no consumen turno.");
    }

    if (!valida) return true;
    completarTurno();
    if (cambioMedico || jornada.obtenerTurnoActual() >= 50) {
        cerrarJornada();
        if (!iniciarJornada(true)) {
            finalizar = true;
        }
    }
    return true;
}

void SimuladorUrgencias::cerrarJornada() {
    if (!hayJornada || !jornada.estaActiva()) return;
    jornada.cerrar(sala.contarCamasVacias());
    interfaz.mostrarReporte(jornada);
    historial.guardar(jornada);
}

void SimuladorUrgencias::auditarPerdidos() const {
    int total = 0;
    std::cout << "\nAuditoria de pacientes perdidos:\n";
    for (const auto& entrada : registro.todos()) {
        const Paciente* paciente = entrada.second;
        if (paciente->obtenerEstado() == EstadoPaciente::Perdido) {
            ++total;
            std::cout << "CC " << paciente->obtenerCedula() << " - " << paciente->obtenerNombre()
                      << " - Dr./Dra. " << paciente->obtenerMedicoResponsable()
                      << " - jornada " << paciente->obtenerJornadaResponsable() << '\n';
        }
    }
    std::cout << "Total de pacientes perdidos: " << total << '\n';
}
