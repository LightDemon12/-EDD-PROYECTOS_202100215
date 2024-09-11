#include "ListaEnviados.h"
#include <iostream>

ListaEnviados::ListaEnviados() : cabeza(nullptr), longitud(0) {}

ListaEnviados::~ListaEnviados() {
    NodoSolicitud* actual = cabeza;
    while (actual != nullptr) {
        NodoSolicitud* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaEnviados::agregar(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    NodoSolicitud* nuevoNodo = new NodoSolicitud(emisor, receptor, estado);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        NodoSolicitud* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    longitud++;
}

void ListaEnviados::eliminar(int indice) {
    if (indice < 0 || indice >= longitud) {
        std::cerr << "Índice fuera de rango" << std::endl;
        return;
    }

    NodoSolicitud* actual = cabeza;
    NodoSolicitud* anterior = nullptr;

    for (int i = 0; i < indice; ++i) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == nullptr) {
        cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    longitud--;
}

NodoSolicitud* ListaEnviados::mostrarPorIndice(int indice) {
    if (indice < 0 || indice >= longitud) {
        std::cerr << "Índice fuera de rango" << std::endl;
        return nullptr;
    }

    NodoSolicitud* actual = cabeza;
    for (int i = 0; i < indice; ++i) {
        actual = actual->siguiente;
    }

    return actual;
}

void ListaEnviados::ordenar() {
    if (cabeza == nullptr || cabeza->siguiente == nullptr) {
        return;
    }

    bool intercambiado;
    do {
        intercambiado = false;
        NodoSolicitud* actual = cabeza;
        NodoSolicitud* anterior = nullptr;
        NodoSolicitud* siguiente = cabeza->siguiente;

        while (siguiente != nullptr) {
            if (actual->emisor > siguiente->emisor) {
                intercambiado = true;
                if (anterior == nullptr) {
                    cabeza = siguiente;
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

NodoSolicitud* ListaEnviados::buscar(const std::string& emisor, const std::string& receptor) {
    NodoSolicitud* actual = cabeza;
    while (actual != nullptr) {
        if (actual->emisor == emisor && actual->receptor == receptor) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void ListaEnviados::mostrarEnTabla(QTableWidget* table) {
    table->setRowCount(0); // Limpiar la tabla antes de llenarla

    NodoSolicitud* actual = cabeza;
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
std::string ListaEnviados::obtenerReceptorPorIndice(int indice) const {
    if (indice < 0 || indice >= longitud) {
        std::cerr << "Índice fuera de rango" << std::endl;
        return "";
    }

    NodoSolicitud* actual = cabeza;
    for (int i = 0; i < indice; ++i) {
        actual = actual->siguiente;
    }

    return actual->receptor;
}
