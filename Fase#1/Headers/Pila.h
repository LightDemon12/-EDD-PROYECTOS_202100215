//
// Created by LightDemon12 on 10/08/2024.
//

#ifndef PILA_H
#define PILA_H

#include <vector>
#include <string>
#include "NodoPila.h"

class Pila {
private:
    std::vector<NodoPila> elementos;

public:
    void push(const NodoPila& nodo);
    void pop();
    NodoPila top() const;
    bool empty() const;
    size_t size() const;
    void mostrarTop() const; // Método para mostrar el elemento en el tope
};

#endif // PILA_H
