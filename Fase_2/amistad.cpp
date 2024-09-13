#include "amistad.h"
#include <iostream>

// Función para mostrar la información del nodo
void mostrarAmistad(const Amistad* nodo) {
    if (nodo) {
        std::cout << "Correo: " << nodo->correo << std::endl;
    } else {
        std::cout << "Nodo es nulo." << std::endl;
    }
}

// Función para liberar la memoria de los nodos
void liberarAmistad(Amistad* nodo) {
    delete nodo;
}
