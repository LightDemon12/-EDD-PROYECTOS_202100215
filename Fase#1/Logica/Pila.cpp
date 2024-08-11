//
// Created by LightDemon12 on 10/08/2024.
//
// Pila.cpp
#include "../Headers/Pila.h"

void Pila::push(const std::string& elemento) {
    elementos.push_back(elemento);
}

void Pila::pop() {
    if (!elementos.empty()) {
        elementos.pop_back();
    }
}

std::string Pila::top() const {
    if (!elementos.empty()) {
        return elementos.back();
    }
    return "";
}

bool Pila::empty() const {
    return elementos.empty();
}

size_t Pila::size() const {
    return elementos.size();
}