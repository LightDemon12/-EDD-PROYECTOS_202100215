#include "listarelaciones.h"
#include <iostream>

// Constructor de la lista enlazada
ListaRelaciones::ListaRelaciones() : cabeza(nullptr) {}

// Destructor de la lista enlazada
ListaRelaciones::~ListaRelaciones() {
    liberarMemoria();
}

// Método para agregar un nodo a la lista
void ListaRelaciones::agregar(const std::string& usuario) {
    Relaciones* nuevoNodo = new Relaciones(usuario);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

// Método para eliminar un nodo de la lista
void ListaRelaciones::eliminar(const std::string& usuario) {
    Relaciones* actual = cabeza;
    Relaciones* anterior = nullptr;

    while (actual && actual->usuario != usuario) {
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
void ListaRelaciones::mostrar() const {
    Relaciones* actual = cabeza;
    while (actual) {
        std::cout << "Usuario: " << actual->usuario << std::endl;
        actual->amistades.mostrar();
        actual = actual->siguiente;
    }
}

// Método para buscar un nodo en la lista
Relaciones* ListaRelaciones::buscar(const std::string& usuario) const {
    Relaciones* actual = cabeza;
    while (actual && actual->usuario != usuario) {
        actual = actual->siguiente;
    }
    return actual;
}

// Método para buscar un nodo en la lista o crearlo si no existe
Relaciones* ListaRelaciones::buscarOCrear(const std::string& usuario) {
    Relaciones* nodo = buscar(usuario);
    if (!nodo) {
        agregar(usuario);
        nodo = buscar(usuario);
    }
    return nodo;
}

// Método privado para liberar la memoria de los nodos
void ListaRelaciones::liberarMemoria() {
    while (cabeza) {
        Relaciones* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
