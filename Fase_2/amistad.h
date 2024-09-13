#ifndef AMISTAD_H
#define AMISTAD_H

#include <string>

// Estructura del nodo Amistad
struct Amistad {
    std::string correo;
    Amistad* siguiente; // Puntero al siguiente nodo en la lista

    Amistad(const std::string& c)
        : correo(c), siguiente(nullptr) {}
};

#endif // AMISTAD_H
