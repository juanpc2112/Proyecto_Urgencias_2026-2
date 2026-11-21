cmake_minimum_required(VERSION 3.20)
project(Urgencias LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Urgencias
        main.cpp
        Paciente.cpp
        Medico.cpp
        NodoCama.cpp
        SalaUrgencias.cpp
        MetricasJornada.cpp
        Jornada.cpp
        ColaPrioridadPacientes.cpp
        RegistroPacientes.cpp
        PilaUltimosAtendidos.cpp
        HistorialMedicos.cpp
        InterfazTexto.cpp
        SimuladorUrgencias.cpp
)
