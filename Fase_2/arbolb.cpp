#include "arbolb.h"
#include <iostream>

ArbolB::ArbolB() : raiz(nullptr) {}

void ArbolB::insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    if (raiz == nullptr) {
        // Si el árbol está vacío, crea la raíz
        raiz = new NodoB(true);
        raiz->correos[0] = correo;
        raiz->contenidos[0] = contenido;
        raiz->fechas[0] = fecha;
        raiz->horas[0] = hora;
        raiz->numClaves = 1;
    } else {
        // Si la raíz está llena, divídela y crea una nueva raíz
        if (raiz->numClaves == 2 * NodoB::T - 1) {
            NodoB* nuevaRaiz = new NodoB(false);
            nuevaRaiz->hijos[0] = raiz;
            nuevaRaiz->dividirHijo(0, raiz);

            int i = 0;
            if (nuevaRaiz->esMenor(nuevaRaiz->fechas[0], nuevaRaiz->horas[0], fecha, hora)) {
                i++;
            }
            nuevaRaiz->hijos[i]->insertarNoLleno(correo, contenido, fecha, hora);

            raiz = nuevaRaiz;
        } else {
            raiz->insertarNoLleno(correo, contenido, fecha, hora);
        }
    }
}

void ArbolB::mostrar() {
    if (raiz != nullptr) {
        mostrar(raiz, 0);
    }
}

void ArbolB::mostrar(NodoB* nodo, int nivel) {
    if (nodo != nullptr) {
        std::cout << "Nivel " << nivel << ": ";
        for (int i = 0; i < nodo->numClaves; i++) {
            std::cout << "(" << nodo->correos[i] << ", " << nodo->contenidos[i] << ", " << nodo->fechas[i] << ", " << nodo->horas[i] << ") ";
        }
        std::cout << std::endl;

        if (!nodo->esHoja) {
            for (int i = 0; i <= nodo->numClaves; i++) {
                mostrar(nodo->hijos[i], nivel + 1);
            }
        }
    }
}

void ArbolB::imprimirArbol() {
    if (raiz != nullptr) {
        imprimirNodo(raiz, 0);
    }
}

void ArbolB::imprimirNodo(NodoB* nodo, int nivel) {
    if (nodo == nullptr) return;

    std::cout << "Nivel " << nivel << ": ";
    for (int i = 0; i < nodo->numClaves; ++i) {
        std::cout << "(" << nodo->correos[i] << ", " << nodo->contenidos[i] << ", " << nodo->fechas[i] << ", " << nodo->horas[i] << ") ";
    }
    std::cout << std::endl;

    for (int i = 0; i <= nodo->numClaves; ++i) {
        imprimirNodo(nodo->hijos[i], nivel + 1);
    }
}

void ArbolB::imprimirComentarios(NodoB* nodo) {
    if (nodo == nullptr) {
        std::cout << "Nodo de publicación es nullptr." << std::endl;
        return;
    }

    std::cout << "Comentarios:" << std::endl;
    imprimirNodo(nodo, 0);
}

void ArbolB::mostrarEnTabla(QTableWidget* tableWidget) {
    tableWidget->setRowCount(0); // Limpia la tabla
    int row = 0;
    mostrarEnTabla(raiz, tableWidget, row);
}

void ArbolB::mostrarEnTabla(NodoB* nodo, QTableWidget* tableWidget, int& row) {
    if (nodo != nullptr) {
        for (int i = 0; i < nodo->numClaves; i++) {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(nodo->contenidos[i])));
            row++;
        }
        for (int i = 0; i <= nodo->numClaves; i++) {
            mostrarEnTabla(nodo->hijos[i], tableWidget, row);
        }
    }
}
