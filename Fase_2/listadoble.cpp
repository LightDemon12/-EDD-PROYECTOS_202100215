#include "listadoble.h"
#include <iostream>
#include <QDebug>

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

ListaDoble::~ListaDoble() {
    liberarMemoria();
}

void ListaDoble::insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen) {
    NodoLista* nuevoNodo = new NodoLista(correo, contenido, fecha, hora, pathimagen);

    if (cabeza == nullptr) {
        // La lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        // Insertar al final de la lista
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }

    qDebug() << "Nodo insertado - Correo:" << QString::fromStdString(correo) << ", Contenido:" << QString::fromStdString(contenido) << ", Fecha:" << QString::fromStdString(fecha) << ", Hora:" << QString::fromStdString(hora);
}

NodoLista* ListaDoble::obtenerUltimoNodo() const {
    return cola;
}

void ListaDoble::eliminar(const std::string& correo, const std::string& fecha, const std::string& hora) {
    NodoLista* actual = cabeza;

    while (actual != nullptr) {
        if (actual->correo == correo && actual->fecha == fecha && actual->hora == hora) {
            if (actual->anterior != nullptr) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente;
            }

            if (actual->siguiente != nullptr) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior;
            }

            delete actual;
            return;
        }
        actual = actual->siguiente;
    }
}

void ListaDoble::mostrar() const {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "Correo: " << actual->correo << std::endl;
        std::cout << "Contenido: " << actual->contenido << std::endl;
        std::cout << "Fecha: " << actual->fecha << std::endl;
        std::cout << "Hora: " << actual->hora << std::endl;
        std::cout << "Path Imagen: " << actual->pathimagen << std::endl;
        std::cout << "Comentarios: " << std::endl;
        actual->comentarios.mostrar();
        std::cout << "-------------------------" << std::endl;
        actual = actual->siguiente;
    }
}

void ListaDoble::liberarMemoria() {
    while (cabeza != nullptr) {
        NodoLista* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    cola = nullptr;
}

void ListaDoble::pasarAlArbolBinarioPorFecha(ArbolBinarioCompleto& arbol, const std::string& fecha) {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->fecha == fecha) {
            arbol.insertar(actual->correo, actual->contenido, actual->fecha, actual->hora, actual->pathimagen);
        }
        actual = actual->siguiente;
    }
}
NodoLista* ListaDoble::buscar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correo == correo && actual->contenido == contenido && actual->fecha == fecha && actual->hora == hora) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}
