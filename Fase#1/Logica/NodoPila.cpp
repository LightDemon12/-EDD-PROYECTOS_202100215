//
// Created by LightDemon12 on 11/08/2024.
//
#include "../Headers/NodoPila.h"

std::ostream& operator<<(std::ostream& os, const NodoPila& nodo) {
    os << "Destinatario: " << nodo.destinatario << ", Emisor: " << nodo.emisor << ", Estado: " << nodo.estado;
    return os;
}