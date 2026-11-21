#ifndef URGENCIAS_SALA_URGENCIAS_H
#define URGENCIAS_SALA_URGENCIAS_H

#include "NodoCama.h"
#include <list>

// Administra las diez camas y la posición actual del médico.
class SalaUrgencias {
public:
    static const int CANTIDAD_CAMAS = 10; // Cantidad fija de camas del proyecto.
    SalaUrgencias();

    // Mueve al médico si existe una cama en esa dirección.
    bool moverIzquierda();
    bool moverDerecha();
    // Devuelve la cama donde se encuentra el médico.
    NodoCama& camaActual();
    const NodoCama& camaActual() const;
    // Busca una cama por su número.
    NodoCama* buscarCama(int numero);
    // Operaciones para el cierre de jornada y la impresión del estado.
    int contarCamasVacias() const;
    // Ubica al médico entrante en la cama 1 sin modificar el estado de las camas.
    void ubicarMedicoEnEntrada();
    void mostrar() const;

private:
    std::list<NodoCama> camas; // Lista propietaria de los nodos de cama.
    NodoCama* actual = nullptr; // Referencia a la cama actual del médico.
};

#endif
