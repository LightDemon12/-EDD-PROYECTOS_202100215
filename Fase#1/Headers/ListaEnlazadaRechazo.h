//
// Created by LightDemon12 on 12/08/2024.
//

// Created by LightDemon12 on 10/08/2024.

#ifndef LISTA_ENLAZADA_RECHAZO_H
#define LISTA_ENLAZADA_RECHAZO_H

#include <iostream>
#include <string>
#include "Solicitud.h"

// Clase ListaEnlazadaRechazo para manejar la lista de rechazos
class ListaEnlazadaRechazo {
private:
    Solicitud* cabeza;

public:
    // Constructor para inicializar la lista vacía
    ListaEnlazadaRechazo();

    // Método para agregar un nuevo rechazo a la lista
    void agregarRechazo(std::string destinatario, std::string emisor);

    // Método para eliminar un rechazo de la lista
    bool eliminarRechazo(std::string destinatario, std::string emisor);

    // Método para buscar un rechazo en la lista
    Solicitud* buscarRechazo(std::string destinatario, std::string emisor);

    // Método para conseguir la cabeza de la lista
    Solicitud* conseguirCabeza();

    // Método para mostrar todos los rechazos en la lista
    void mostrarRechazos() const;

    // Método para verificar si ya existe un rechazo
    bool existeRechazo(std::string destinatario, std::string emisor);

    // Destructor para liberar la memoria de todos los nodos al destruir la lista
    ~ListaEnlazadaRechazo();
};

#endif // LISTA_ENLAZADA_RECHAZO_H