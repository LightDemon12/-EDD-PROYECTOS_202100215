#ifndef AMISTADES_H
#define AMISTADES_H

#include "amistad.h"

// Clase de la lista enlazada Amistades
class Amistades {
public:
    Amistades();
    ~Amistades();
    void agregar(const std::string& correo);
    void eliminar(const std::string& correo);
    void mostrar() const;

private:
    Amistad* cabeza;
    void liberarMemoria();
};

#endif // AMISTADES_H
