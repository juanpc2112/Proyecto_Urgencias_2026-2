#include "MetricasJornada.h"
void MetricasJornada::registrarRecepcion(int esperaMinutos) {
    ++recibidos;
    sumaEsperaMinutos += esperaMinutos;
}

void MetricasJornada::registrarAlta() {
    ++altas;
}

void MetricasJornada::registrarPerdida() {
    ++perdidos;
}

void MetricasJornada::fijarCamasVacias(int cantidad) {
    camasVacias = cantidad;
}

int MetricasJornada::obtenerRecibidos() const {
    return recibidos;
}

int MetricasJornada::obtenerAltas() const {
    return altas;
}

int MetricasJornada::obtenerPerdidos() const {
    return perdidos;
}

int MetricasJornada::obtenerCamasVacias() const {
    return camasVacias;
}

int MetricasJornada::obtenerEsperaPromedio() const {
    if (recibidos == 0) {
        return 0;
    }
    return sumaEsperaMinutos / recibidos;
}
