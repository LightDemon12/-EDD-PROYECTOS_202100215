#ifndef ARBOLB_H
#define ARBOLB_H

#include "nodob.h"

class ArbolB {
public:
    ArbolB();

    // Métodos para manejar el árbol B
    void insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void mostrar();

private:
    NodoB* raiz;

    // Métodos auxiliares
    void mostrar(NodoB* nodo, int nivel);
};

#endif // ARBOLB_H
