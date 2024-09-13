#ifndef NODOLISTA_H
#define NODOLISTA_H

#include <string>
#include "arbolb.h"

class NodoLista {
public:
    // Constructor
    NodoLista(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen);

    // Atributos del nodo
    std::string correo;
    std::string contenido;
    std::string fecha;
    std::string hora;
    std::string pathimagen;

    // Árbol B para los comentarios
    ArbolB comentarios;

    // Punteros al siguiente y anterior nodo
    NodoLista* siguiente;
    NodoLista* anterior;
};

#endif // NODOLISTA_H
