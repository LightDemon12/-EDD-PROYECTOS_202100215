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

void ListaDoblePublicaciones::navegarPublicaciones() const {
    if (cabeza == nullptr) {
        std::cout << "No hay publicaciones disponibles." << std::endl;
        return;
    }

    Publicacion* actual = cabeza;
    char opcion;

    while (true) {
        std::cout << "Correo: " << actual->correoUsuario << std::endl;
        std::cout << "Contenido: " << actual->contenido << std::endl;
        std::cout << "Fecha: " << actual->fecha << std::endl;
        std::cout << "Hora: " << actual->hora << std::endl;
        std::cout << "-------------------------" << std::endl;

        std::cout << "Presione 'A' para anterior, 'S' para siguiente, 'Q' para salir: ";
        std::cin >> opcion;

        if (opcion == 'A' || opcion == 'a') {
            if (actual->anterior != nullptr) {
                actual = actual->anterior;
            } else {
                actual = cola; // Mover a la última publicación
            }
        } else if (opcion == 'S' || opcion == 's') {
            if (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            } else {
                actual = cabeza; // Mover a la primera publicación
            }
        } else if (opcion == 'Q' || opcion == 'q') {
            break;
        } else {
            std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    }
}

void ListaDoblePublicaciones::mostrarPublicacionesConIndice() const {
    Publicacion* actual = cabeza;
    int indice = 0;
    while (actual != nullptr) {
        std::cout << indice << ": " << actual->correoUsuario << " - " << actual->contenido << " (" << actual->fecha << " " << actual->hora << ")" << std::endl;
        actual = actual->siguiente;
        indice++;
    }
}
void ListaDoblePublicaciones::eliminarPublicacionPorIndice(int indice) {
    Publicacion* actual = cabeza;
    int contador = 0;
    while (actual != nullptr) {
        if (contador == indice) {
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
            return;
        }
        actual = actual->siguiente;
        contador++;
    }
}