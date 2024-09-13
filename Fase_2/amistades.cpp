#include "amistades.h"
#include <iostream>

// Constructor de la lista enlazada
Amistades::Amistades() : cabeza(nullptr) {}

// Destructor de la lista enlazada
Amistades::~Amistades() {
    liberarMemoria();
}

// Método para agregar un nodo a la lista
void Amistades::agregar(const std::string& correo) {
    Amistad* nuevoNodo = new Amistad(correo);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

// Método para eliminar un nodo de la lista
void Amistades::eliminar(const std::string& correo) {
    Amistad* actual = cabeza;
    Amistad* anterior = nullptr;

    while (actual && actual->correo != correo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual) {
        if (anterior) {
            anterior->siguiente = actual->siguiente;
        } else {
            cabeza = actual->siguiente;
        }
        delete actual;
    }
}

// Método para mostrar todos los nodos de la lista
void Amistades::mostrar() const {
    Amistad* actual = cabeza;
    while (actual) {
        std::cout << "Correo: " << actual->correo << std::endl;
        actual = actual->siguiente;
    }
}

// Método privado para liberar la memoria de los nodos
void Amistades::liberarMemoria() {
    while (cabeza) {
        Amistad* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
