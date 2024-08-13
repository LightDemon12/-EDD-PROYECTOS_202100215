//
// Created by LightDemon12 on 12/08/2024.
//
#include "../Headers/ListaDoblePublicaciones.h"
#include <iostream>
#include <algorithm>

ListaDoblePublicaciones::ListaDoblePublicaciones() : cabeza(nullptr), cola(nullptr) {}

ListaDoblePublicaciones::~ListaDoblePublicaciones() {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        Publicacion* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDoblePublicaciones::agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    Publicacion* nuevaPublicacion = new Publicacion(correo, contenido, fecha, hora);
    if (cabeza == nullptr) {
        cabeza = cola = nuevaPublicacion;
    } else {
        cola->siguiente = nuevaPublicacion;
        nuevaPublicacion->anterior = cola;
        cola = nuevaPublicacion;
    }
}

void ListaDoblePublicaciones::imprimirPublicaciones() const {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "Correo: " << actual->correoUsuario << std::endl;
        std::cout << "Contenido: " << actual->contenido << std::endl;
        std::cout << "Fecha: " << actual->fecha << std::endl;
        std::cout << "Hora: " << actual->hora << std::endl;
        std::cout << "-------------------------" << std::endl;
        actual = actual->siguiente;
    }
}

void ListaDoblePublicaciones::eliminarPublicacion(const std::string& correo, const std::string& fecha, const std::string& hora) {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoUsuario == correo && actual->fecha == fecha && actual->hora == hora) {
            if (actual->anterior != nullptr) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente;
            }
            if (actual->siguiente != nullptr) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior;
            }
            delete actual;
            std::cout << "Publicación eliminada." << std::endl;
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "Publicación no encontrada." << std::endl;
}

void ListaDoblePublicaciones::clasificarPorCorreo() {
    if (cabeza == nullptr) return;

    std::vector<Publicacion*> publicaciones;
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        publicaciones.push_back(actual);
        actual = actual->siguiente;
    }

    std::sort(publicaciones.begin(), publicaciones.end(), [](Publicacion* a, Publicacion* b) {
        return a->correoUsuario < b->correoUsuario;
    });

    cabeza = publicaciones[0];
    cabeza->anterior = nullptr;
    actual = cabeza;
    for (size_t i = 1; i < publicaciones.size(); ++i) {
        actual->siguiente = publicaciones[i];
        publicaciones[i]->anterior = actual;
        actual = actual->siguiente;
    }
    cola = actual;
    cola->siguiente = nullptr;
}

void ListaDoblePublicaciones::mostrarPorCorreo(const std::string& correo) const {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoUsuario == correo) {
            std::cout << "Correo: " << actual->correoUsuario << std::endl;
            std::cout << "Contenido: " << actual->contenido << std::endl;
            std::cout << "Fecha: " << actual->fecha << std::endl;
            std::cout << "Hora: " << actual->hora << std::endl;
            std::cout << "-------------------------" << std::endl;
        }
        actual = actual->siguiente;
    }
}

void ListaDoblePublicaciones::mostrarPublicacionesFiltradas(const std::vector<std::string>& correosPermitidos) const {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        if (std::find(correosPermitidos.begin(), correosPermitidos.end(), actual->correoUsuario) != correosPermitidos.end()) {
            std::cout << "Correo: " << actual->correoUsuario << std::endl;
            std::cout << "Contenido: " << actual->contenido << std::endl;
            std::cout << "Fecha: " << actual->fecha << std::endl;
            std::cout << "Hora: " << actual->hora << std::endl;
            std::cout << "-------------------------" << std::endl;
        }
        actual = actual->siguiente;
    }
}