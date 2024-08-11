//
// Created by LightDemon12 on 10/08/2024.
//

// Pila.h
#ifndef PILA_H
#define PILA_H

#include <vector>
#include <string>

class Pila {
private:
    std::vector<std::string> elementos;

public:
    void push(const std::string& elemento);
    void pop();
    std::string top() const;
    bool empty() const;
    size_t size() const;
};

#endif // PILA_H
