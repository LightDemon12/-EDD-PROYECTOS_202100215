//
// Created by LightDemon12 on 10/08/2024.
//

#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <string>

using namespace std;

// Clase Solicitud que representa una solicitud de amistad
class Solicitud {
public:
    string destinatario; // Usuario que recibe la solicitud
    string emisor;       // Usuario que envía la solicitud
    string estado;       // Estado de la solicitud (e.g., "Pendiente", "Aceptada", "Rechazada")
    Solicitud* siguiente; // Puntero al siguiente nodo en la lista

    // Constructor para inicializar los atributos del nodo
    Solicitud(string dest, string emi, string est);
};

#endif // SOLICITUD_H