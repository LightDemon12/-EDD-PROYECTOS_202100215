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

#include "../Headers/ListaSolicitud.h"
#include <fstream>
#include <iostream>

void ListaSolicitud::generarReporteListaSolicitud(const std::string& correoUsuario, const std::string& nombreArchivo) const {
    if (cabeza == nullptr) {
        std::cerr << "Error: La lista de solicitudes está vacía." << std::endl;
        return;
    }

    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "rankdir=TB;\n"; // Cambiar la dirección a Top-Bottom
    archivo << "node [shape=record];\n";

    // Crear nodos para cada solicitud en la lista del usuario especificado
    Solicitud* temp = cabeza;
    int i = 0;
    while (temp != nullptr) {
        if (temp->emisor == correoUsuario) {
            archivo << "node" << i << " [label=\"{"
                    << "Destinatario: " << temp->destinatario << " | "
                    << "Emisor: " << temp->emisor << " | "
                    << "Estado: " << temp->estado << "}\"];\n";
            ++i;
        }
        temp = temp->siguiente;
    }

    // Crear enlaces invisibles entre los nodos para forzar la disposición vertical
    for (int j = 0; j < i - 1; ++j) {
        archivo << "node" << j << " -> node" << (j + 1) << " [style=invis];\n";
    }

    archivo << "}\n";
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o lista_solicitudes.png";
    int result = system(comando.c_str());
    if (result != 0) {
        std::cerr << "Error: No se pudo generar la imagen usando Graphviz." << std::endl;
    }
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