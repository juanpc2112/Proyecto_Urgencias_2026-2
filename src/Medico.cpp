#include "Medico.h"

Medico::Medico() : identificacion("MED-0"), nombre("Medico de turno") {}

Medico::Medico(std::string identificacion, std::string nombre)
    : identificacion(identificacion), nombre(nombre) {}

const std::string& Medico::obtenerIdentificacion() const noexcept {
    return identificacion;
}

const std::string& Medico::obtenerNombre() const noexcept {
    return nombre;
}
