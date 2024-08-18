//
// Created by LightDemon12 on 18/08/2024.
//

#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include <iostream>
#include <string>

class Nodo {
public:
    std::string dato;
    Nodo* siguiente;

    Nodo(const std::string& dato) : dato(dato), siguiente(nullptr) {}
};

class ListaCircular {
private:
    Nodo* cabeza;

public:
    ListaCircular() : cabeza(nullptr) {}

    // Método para insertar un nodo al final de la lista
    void insertar(const std::string& dato);

    // Método para eliminar un nodo por su dato
    void eliminar(const std::string& dato);

    // Método para mostrar la lista
    void mostrar() const;

    // Destructor para liberar memoria
    ~ListaCircular();
};

#endif // LISTA_CIRCULAR_H