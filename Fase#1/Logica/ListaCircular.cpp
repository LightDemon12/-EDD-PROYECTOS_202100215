//
// Created by LightDemon12 on 18/08/2024.
//
#include "../Headers/ListaCircular.h"

// Método para insertar un nodo al final de la lista
void ListaCircular::insertar(const std::string& dato) {
    Nodo* nuevoNodo = new Nodo(dato);
    if (!cabeza) {
        cabeza = nuevoNodo;
        cabeza->siguiente = cabeza; // Apunta a sí mismo para formar el ciclo
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente != cabeza) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
        nuevoNodo->siguiente = cabeza;
    }
}

// Método para eliminar un nodo por su dato
void ListaCircular::eliminar(const std::string& dato) {
    if (!cabeza) return;

    Nodo* temp = cabeza;
    Nodo* anterior = nullptr;

    do {
        if (temp->dato == dato) {
            if (anterior) {
                anterior->siguiente = temp->siguiente;
            } else {
                Nodo* ultimo = cabeza;
                while (ultimo->siguiente != cabeza) {
                    ultimo = ultimo->siguiente;
                }
                cabeza = cabeza->siguiente;
                ultimo->siguiente = cabeza;
            }
            delete temp;
            return;
        }
        anterior = temp;
        temp = temp->siguiente;
    } while (temp != cabeza);
}

// Método para mostrar la lista
void ListaCircular::mostrar() const {
    if (!cabeza) return;

    Nodo* temp = cabeza;
    do {
        std::cout << temp->dato << " ";
        temp = temp->siguiente;
    } while (temp != cabeza);
    std::cout << std::endl;
}

// Destructor para liberar memoria
ListaCircular::~ListaCircular() {
    if (!cabeza) return;

    Nodo* temp = cabeza;
    do {
        Nodo* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
    } while (temp != cabeza);
}