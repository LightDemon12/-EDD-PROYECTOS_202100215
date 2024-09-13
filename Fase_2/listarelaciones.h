#ifndef LISTARELACIONES_H
#define LISTARELACIONES_H

#include <string>
#include "amistades.h"

class Relaciones {
public:
    Relaciones(const std::string& usuario) : usuario(usuario), siguiente(nullptr) {}
    std::string usuario;
    Relaciones* siguiente;
    Amistades amistades;
};

class ListaRelaciones {
public:
    ListaRelaciones();
    ~ListaRelaciones();
    void agregar(const std::string& usuario);
    void eliminar(const std::string& usuario);
    void mostrar() const;
    Relaciones* buscar(const std::string& usuario) const;
    Relaciones* buscarOCrear(const std::string& usuario);

private:
    Relaciones* cabeza;
    void liberarMemoria();
};

#endif // LISTARELACIONES_H
