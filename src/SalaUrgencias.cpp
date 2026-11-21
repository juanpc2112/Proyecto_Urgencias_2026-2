#include "SalaUrgencias.h"
#include <iostream>

SalaUrgencias::SalaUrgencias() {
    NodoCama* anterior = nullptr;
    for (int numero = 1; numero <= CANTIDAD_CAMAS; ++numero) {
        camas.emplace_back(numero);
        NodoCama* nodo = &camas.back();
        nodo->establecerAnterior(anterior);
        if (anterior) anterior->establecerSiguiente(nodo);
        if (!actual) actual = nodo;
        anterior = nodo;
    }
}

bool SalaUrgencias::moverIzquierda() {
    if (!actual || !actual->obtenerAnterior()) {
        return false;
    }
    actual = actual->obtenerAnterior();
    return true;
}

bool SalaUrgencias::moverDerecha() {
    if (!actual || !actual->obtenerSiguiente()) {
        return false;
    }
    actual = actual->obtenerSiguiente();
    return true;
}

NodoCama& SalaUrgencias::camaActual() {
    return *actual;
}

const NodoCama& SalaUrgencias::camaActual() const {
    return *actual;
}

NodoCama* SalaUrgencias::buscarCama(int numero) {
    for (NodoCama& cama : camas) {
        if (cama.obtenerNumero() == numero) {
            return &cama;
        }
    }
    return nullptr;
}

int SalaUrgencias::contarCamasVacias() const {
    int vacias = 0;
    for (const NodoCama& cama : camas) {
        if (cama.obtenerEstado() == EstadoCama::Vacia) {
            ++vacias;
        }
    }
    return vacias;
}

void SalaUrgencias::ubicarMedicoEnEntrada() {
    actual = buscarCama(1);
}

void SalaUrgencias::mostrar() const {
    for (const NodoCama& nodo : camas) {
        std::cout << "[";
        if (nodo.obtenerNumero() < 10) std::cout << ' ';
        std::cout << '#' << nodo.obtenerNumero() << ':';
        if (nodo.obtenerEstado() == EstadoCama::Mantenimiento) std::cout << "MANT";
        else if (nodo.obtenerPaciente()) std::cout << 'P' << nodo.obtenerPaciente()->obtenerGravedad();
        else std::cout << 'V';
        if (&nodo == actual) std::cout << " M";
        std::cout << "] ";
    }
    std::cout << '\n';
}
