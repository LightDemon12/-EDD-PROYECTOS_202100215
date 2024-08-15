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
        Headers/Registro.h
        Headers/Pila.h
        Logica/Pila.cpp
        Headers/MenuUsuario.h
        Logica/MenuUsuario.cpp
        Headers/Solicitud.h
        Logica/Solicitud.cpp
        Logica/ListaSolicitud.cpp
        Headers/ListaSolicitud.h
        Headers/Perfil.h
        Logica/Perfil.cpp
        Headers/MenuSolicitud.h
        Logica/MenuSolicitud.cpp
        Headers/NodoPila.h
        Logica/NodoPila.cpp
        Headers/NodoMatriz.h
        Headers/MatrizDispersa.h
        Logica/MatrizDispersa.cpp
        Headers/ListaEnlazadaRechazo.h
        Logica/ListaEnlazadaRechazo.cpp
        Logica/NodoPublicacion.cpp
        Headers/ListaDoblePublicaciones.h
        Logica/ListaDoblePublicaciones.cpp
        Headers/Publicacion.h
        Headers/MenuPublicaciones.h
        Logica/MenuPublicaciones.cpp
        Headers/MenuAdmin.h
        Logica/MenuAdmin.cpp
        Logica/CargaUsuarios.cpp
        Headers/CargaUsuarios.h
        Headers/CargaSolicitudes.h
        Logica/CargaSolicitudes.cpp
        Headers/CargarPublicaciones.h
        Logica/CargarPublicaciones.cpp
        Headers/MenuReportes.h
        Logica/MenuReportes.cpp
)
