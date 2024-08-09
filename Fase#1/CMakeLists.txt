cmake_minimum_required(VERSION 3.28)
project(Fase_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Fase_1 main.cpp
        Logica/Usuarios.cpp
        Logica/ListaEnlazada.cpp
        Logica/InicioSeccion.cpp
        Headers/Usuarios.h
        Headers/ListaEnlazada.h
        Headers/InicioSeccion.h
        Logica/Registro.cpp
        Headers/Registro.h)
