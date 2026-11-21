#ifndef URGENCIAS_METRICAS_JORNADA_H
#define URGENCIAS_METRICAS_JORNADA_H

// Acumula los resultados que se muestran en el reporte de jornada.
class MetricasJornada {
public:
    // Registra una recepción y su espera acumulada.
    void registrarRecepcion(int esperaMinutos);
    // Registra altas, pérdidas y camas vacías al cierre.
    void registrarAlta();
    void registrarPerdida();
    void fijarCamasVacias(int cantidad);
    int obtenerRecibidos() const;
    int obtenerAltas() const;
    int obtenerPerdidos() const;
    int obtenerCamasVacias() const;
    int obtenerEsperaPromedio() const;

private:
    int recibidos = 0;             // Pacientes asignados a una cama.
    int altas = 0;                 // Pacientes que completaron tratamiento.
    int perdidos = 0;              // Pacientes retirados por exceder su espera.
    int sumaEsperaMinutos = 0;     // Total usado para calcular el promedio.
    int camasVacias = 0;           // Camas disponibles al cerrar la jornada.
};

#endif
