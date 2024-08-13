//
// Created by LightDemon12 on 12/08/2024.
//
// Created by LightDemon12 on 10/08/2024.
//
#include "../Headers/ListaEnlazadaRechazo.h"

// Constructor para inicializar la lista vacía
ListaEnlazadaRechazo::ListaEnlazadaRechazo() : cabeza(nullptr) {}

// Método para agregar un nuevo rechazo a la lista
void ListaEnlazadaRechazo::agregarRechazo(std::string destinatario, std::string emisor) {
    Solicitud* nuevoRechazo = new Solicitud(destinatario, emisor, "Rechazado");
    if (cabeza == nullptr) {
        cabeza = nuevoRechazo;
    } else {
        Solicitud* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoRechazo;
    }
}

// Método para eliminar un rechazo de la lista
bool ListaEnlazadaRechazo::eliminarRechazo(std::string destinatario, std::string emisor) {
    if (cabeza == nullptr) return false;

    if (cabeza->destinatario == destinatario && cabeza->emisor == emisor) {
        Solicitud* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return true;
    }

    Solicitud* temp = cabeza;
    while (temp->siguiente != nullptr && (temp->siguiente->destinatario != destinatario || temp->siguiente->emisor != emisor)) {
        temp = temp->siguiente;
    }

    if (temp->siguiente == nullptr) return false;

    Solicitud* nodoAEliminar = temp->siguiente;
    temp->siguiente = temp->siguiente->siguiente;
    delete nodoAEliminar;
    return true;
}

// Método para buscar un rechazo en la lista
Solicitud* ListaEnlazadaRechazo::buscarRechazo(std::string destinatario, std::string emisor) {
    Solicitud* temp = cabeza;
    while (temp != nullptr) {
        if (temp->destinatario == destinatario && temp->emisor == emisor) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return nullptr;
}

// Método para conseguir la cabeza de la lista
Solicitud* ListaEnlazadaRechazo::conseguirCabeza() {
    return cabeza;
}

// Método para mostrar todos los rechazos en la lista
void ListaEnlazadaRechazo::mostrarRechazos() const {
    Solicitud* temp = cabeza;
    while (temp != nullptr) {
        std::cout << "Destinatario: " << temp->destinatario << ", Emisor: " << temp->emisor << ", Estado: " << temp->estado << std::endl;
        temp = temp->siguiente;
    }
}

// Método para verificar si ya existe un rechazo
bool ListaEnlazadaRechazo::existeRechazo(std::string destinatario, std::string emisor) {
    Solicitud* temp = cabeza;
    while (temp != nullptr) {
        if (temp->destinatario == destinatario && temp->emisor == emisor) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

// Destructor para liberar la memoria de todos los nodos al destruir la lista
ListaEnlazadaRechazo::~ListaEnlazadaRechazo() {
    Solicitud* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
