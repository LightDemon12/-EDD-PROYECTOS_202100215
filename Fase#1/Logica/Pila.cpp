#include "../Headers/Pila.h"
#include <iostream>

void Pila::push(const NodoPila& nodo) {
    elementos.push_back(nodo);
}

void Pila::pop() {
    if (!elementos.empty()) {
        elementos.pop_back();
    }
}

NodoPila Pila::top() const {
    if (!elementos.empty()) {
        return elementos.back();
    }
    return NodoPila("", "", ""); // Devuelve un nodo vacío si la pila está vacía
}

bool Pila::empty() const {
    return elementos.empty();
}

size_t Pila::size() const {
    return elementos.size();
}

void Pila::mostrarTop() const {
    if (!elementos.empty()) {
        const NodoPila& nodo = elementos.back();
        std::cout << "Elemento en el tope:" << std::endl;
        std::cout << "Destinatario: " << nodo.destinatario << std::endl;
        std::cout << "Emisor: " << nodo.emisor << std::endl;
        std::cout << "Estado: " << nodo.estado << std::endl;
    } else {
        std::cout << "La pila está vacía." << std::endl;
    }
}