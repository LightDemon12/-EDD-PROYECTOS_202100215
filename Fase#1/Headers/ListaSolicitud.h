//
// Created by LightDemon12 on 10/08/2024.
//
#ifndef LISTASOLICITUD_H
#define LISTASOLICITUD_H

#include "Solicitud.h"
#include <iostream>

class ListaSolicitud {
private:
    Solicitud* cabeza; // Puntero al primer nodo de la lista

public:
    // Constructor para inicializar la lista vacía
    ListaSolicitud();

    // Método para agregar una nueva solicitud de amistad a la lista
    void agregarSolicitud(std::string destinatario, std::string emisor, std::string estado);

    // Método para eliminar una solicitud de amistad de la lista
    bool eliminarSolicitud(std::string destinatario, std::string emisor);

    // Método para buscar una solicitud de amistad en la lista
    Solicitud* buscarSolicitud(std::string destinatario, std::string emisor);

    // Método para conseguir la cabeza de la lista
    Solicitud* conseguirCabeza();

    // Método para mostrar todas las solicitudes de amistad en la lista
    void mostrarSolicitudes() const; // Declarar como constante

    // Método para verificar si ya existe una solicitud de amistad
    bool existeSolicitud(std::string destinatario, std::string emisor); // Declaración del nuevo método

    // Destructor para liberar la memoria de todos los nodos al destruir la lista
    ~ListaSolicitud();
};

#endif // LISTASOLICITUD_H