//
// Created by LightDemon12 on 08/08/2024.
//
// ListaEnlazada.cpp

#include "../Headers/ListaEnlazada.h"
#include <iostream>
using namespace std;

// Constructor para inicializar la lista vacía
ListaEnlazada::ListaEnlazada() : cabeza(nullptr) {}

// Destructor para liberar la memoria de todos los nodos al destruir la lista
ListaEnlazada::~ListaEnlazada() {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        Usuario* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

// Método para agregar un nuevo usuario a la lista
void ListaEnlazada::agregarNodo(Usuario* nuevoUsuario) {
    nuevoUsuario->siguiente = cabeza;
    cabeza = nuevoUsuario;
}

// Método para eliminar un usuario de la lista por correo electrónico
void ListaEnlazada::eliminarNodo(const string& correoElectronico) {
    Usuario* actual = cabeza;
    Usuario* anterior = nullptr;
    while (actual != nullptr && actual->correoElectronico != correoElectronico) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual != nullptr) {
        if (anterior == nullptr) {
            cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        delete actual;
    }
}

// Método para imprimir la lista de usuarios
void ListaEnlazada::imprimirLista() const {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombres << " " << actual->apellidos << ", Correo: " << actual->correoElectronico << endl;
        actual = actual->siguiente;
    }
}

// Método para buscar un usuario en la lista por correo electrónico y contraseña
Usuario* ListaEnlazada::buscarUsuario(const string& correoElectronico, const string& contrasena) const {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoElectronico == correoElectronico && (contrasena.empty() || actual->contrasena == contrasena)) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Método para obtener el tamaño de la lista
int ListaEnlazada::obtenerTamano() const {
    int tamano = 0;
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        tamano++;
        actual = actual->siguiente;
    }
    return tamano;
}