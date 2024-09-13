#ifndef RELACIONES_H
#define RELACIONES_H

#include <string>
#include "amistades.h" // Incluir la cabecera de Amistades

// Estructura del nodo Relaciones
struct Relaciones {
    std::string usuario;
    Amistades amistades; // Lista de amistades
    Relaciones* siguiente; // Puntero al siguiente nodo en la lista

    Relaciones(const std::string& u)
        : usuario(u), siguiente(nullptr) {}
};

#endif // RELACIONES_H
