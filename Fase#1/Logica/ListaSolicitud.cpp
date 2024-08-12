//
// Created by LightDemon12 on 10/08/2024.
//
#include "../Headers/ListaSolicitud.h"

// Constructor para inicializar la lista vacía
ListaSolicitud::ListaSolicitud() : cabeza(nullptr) {}

// Método para agregar una nueva solicitud de amistad a la lista
void ListaSolicitud::agregarSolicitud(std::string destinatario, std::string emisor, std::string estado) {
    Solicitud* nuevaSolicitud = new Solicitud(destinatario, emisor, estado);
    if (cabeza == nullptr) {
        cabeza = nuevaSolicitud;
    } else {
        Solicitud* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevaSolicitud;
    }
}

// Método para eliminar una solicitud de amistad de la lista
bool ListaSolicitud::eliminarSolicitud(std::string destinatario, std::string emisor) {
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

// Método para buscar una solicitud de amistad en la lista
Solicitud* ListaSolicitud::buscarSolicitud(std::string destinatario, std::string emisor) {
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
Solicitud* ListaSolicitud::conseguirCabeza() {
    return cabeza;
}

// Método para mostrar todas las solicitudes de amistad en la lista
void ListaSolicitud::mostrarSolicitudes() const {
    Solicitud* temp = cabeza;
    while (temp != nullptr) {
        std::cout << "Destinatario: " << temp->destinatario << ", Emisor: " << temp->emisor << ", Estado: " << temp->estado << std::endl;
        temp = temp->siguiente;
    }
}
// Método para verificar si ya existe una solicitud de amistad
bool ListaSolicitud::existeSolicitud(std::string destinatario, std::string emisor) {
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
ListaSolicitud::~ListaSolicitud() {
    Solicitud* temp;
    while (cabeza != nullptr) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}