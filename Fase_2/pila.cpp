#include "Pila.h"
#include <iostream>

Pila::Pila() : cima(nullptr), longitud(0) {}

Pila::~Pila() {
    while (cima != nullptr) {
        eliminar();
    }
}

void Pila::agregar(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    NodoSolicitud* nuevoNodo = new NodoSolicitud(emisor, receptor, estado);
    nuevoNodo->siguiente = cima;
    cima = nuevoNodo;
    longitud++;
}

void Pila::eliminar() {
    if (cima == nullptr) {
        std::cerr << "La pila está vacía" << std::endl;
        return;
    }

    NodoSolicitud* nodoAEliminar = cima;
    cima = cima->siguiente;
    delete nodoAEliminar;
    longitud--;
}

void Pila::ordenar() {
    if (cima == nullptr || cima->siguiente == nullptr) {
        return;
    }

    bool intercambiado;
    do {
        intercambiado = false;
        NodoSolicitud* actual = cima;
        NodoSolicitud* anterior = nullptr;
        NodoSolicitud* siguiente = cima->siguiente;

        while (siguiente != nullptr) {
            if (actual->emisor > siguiente->emisor) {
                intercambiado = true;
                if (anterior == nullptr) {
                    cima = siguiente;
                } else {
                    anterior->siguiente = siguiente;
                }
                actual->siguiente = siguiente->siguiente;
                siguiente->siguiente = actual;

                anterior = siguiente;
                siguiente = actual->siguiente;
            } else {
                anterior = actual;
                actual = siguiente;
                siguiente = siguiente->siguiente;
            }
        }
    } while (intercambiado);
}

void Pila::mostrar() const {
    NodoSolicitud* actual = cima;
    int indice = 0;
    while (actual != nullptr) {
        std::cout << "Índice: " << indice << ", Emisor: " << actual->emisor << ", Receptor: " << actual->receptor << ", Estado: " << actual->estado << std::endl;
        actual = actual->siguiente;
        indice++;
    }
}

void Pila::mostrarEnTabla(QTableWidget* table) const {
    table->setRowCount(0); // Limpiar la tabla antes de llenarla

    NodoSolicitud* actual = cima;
    int row = 0;
    while (actual != nullptr) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(actual->emisor)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(actual->receptor)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(actual->estado)));
        actual = actual->siguiente;
        row++;
    }

    table->resizeColumnsToContents(); // Ajustar el tamaño de las columnas al contenido
}

NodoSolicitud* Pila::buscar(const std::string& emisor, const std::string& receptor, const std::string& estado) const {
    NodoSolicitud* actual = cima;
    while (actual != nullptr) {
        if (actual->emisor == emisor && actual->receptor == receptor && actual->estado == estado) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void Pila::eliminarPorIndice(int indice) {
    if (indice < 0 || indice >= longitud) {
        std::cerr << "Índice fuera de rango" << std::endl;
        return;
    }

    if (indice == 0) {
        eliminar();
        return;
    }

    NodoSolicitud* actual = cima;
    NodoSolicitud* anterior = nullptr;
    for (int i = 0; i < indice; ++i) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior != nullptr && actual != nullptr) {
        anterior->siguiente = actual->siguiente;
        delete actual;
        longitud--;
    }
}
std::string Pila::obtenerEmisorPorIndice(int indice) const {
    if (indice < 0 || indice >= longitud) {
        std::cerr << "Índice fuera de rango" << std::endl;
        return "";
    }

    NodoSolicitud* actual = cima;
    for (int i = 0; i < indice; ++i) {
        actual = actual->siguiente;
    }

    return actual->emisor;
}
