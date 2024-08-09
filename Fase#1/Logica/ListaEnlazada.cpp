//
// Created by LightDemon12 on 08/08/2024.
//
#include "../Headers/ListaEnlazada.h"
#include <iostream>
using namespace std;

ListaEnlazada::ListaEnlazada() : cabeza(nullptr) {}

ListaEnlazada::~ListaEnlazada() {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        Usuario* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaEnlazada::agregarNodo(Usuario* nuevoUsuario) {
    if (cabeza == nullptr) {
        cabeza = nuevoUsuario;
    } else {
        Usuario* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoUsuario;
    }
}

void ListaEnlazada::eliminarNodo(const string& correoElectronico) {
    if (cabeza == nullptr) return;

    if (cabeza->correoElectronico == correoElectronico) {
        Usuario* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return;
    }

    Usuario* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->correoElectronico != correoElectronico) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != nullptr) {
        Usuario* temp = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        delete temp;
    }
}

void ListaEnlazada::imprimirLista() const {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        imprimirUsuario(*actual);
        actual = actual->siguiente;
    }
}

Usuario* ListaEnlazada::buscarUsuario(const string& correoElectronico, const string& contrasena) const {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoElectronico == correoElectronico && actual->contrasena == contrasena) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}