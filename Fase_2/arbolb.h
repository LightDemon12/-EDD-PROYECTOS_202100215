#ifndef ARBOLB_H
#define ARBOLB_H

#include "nodob.h"
#include <QTableWidget>

class ArbolB {
public:
    ArbolB();

    // Métodos para manejar el árbol B
    void insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void mostrar();
    void imprimirArbol();
    void imprimirComentarios(NodoB* nodo);
    void mostrarEnTabla(QTableWidget* tableWidget); // Nueva función para mostrar en QTableWidget

private:
    NodoB* raiz;

    // Métodos auxiliares
    void mostrar(NodoB* nodo, int nivel);
    void imprimirNodo(NodoB* nodo, int nivel);
    void mostrarEnTabla(NodoB* nodo, QTableWidget* tableWidget, int& row); // Función auxiliar para mostrar en QTableWidget

};

#endif // ARBOLB_H
