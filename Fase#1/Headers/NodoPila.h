//
// Created by LightDemon12 on 11/08/2024.
//

#ifndef NODOPILA_H
#define NODOPILA_H

#include <string>
#include <iostream>

class NodoPila {
public:
    std::string destinatario; // Usuario que recibe la solicitud
    std::string emisor;       // Usuario que envía la solicitud
    std::string estado;       // Estado de la solicitud (e.g., "Pendiente", "Aceptada", "Rechazada")

    NodoPila(const std::string& dest, const std::string& emi, const std::string& est)
        : destinatario(dest), emisor(emi), estado(est) {}

    // Sobrecarga del operador << para NodoPila
    friend std::ostream& operator<<(std::ostream& os, const NodoPila& nodo);
};

#endif // NODOPILA_H