#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "usuario.h"
#include <QDebug>

class NodoAVL {
public:
    Usuario* usuario;
    NodoAVL* izquierda;
    NodoAVL* derecha;
    int altura;

    NodoAVL(Usuario* usuario)
        : usuario(usuario), izquierda(nullptr), derecha(nullptr), altura(1) {}
};

class ArbolAVL {
private:
    NodoAVL* raiz;

    // Métodos auxiliares
    int obtenerAltura(NodoAVL* nodo);
    int obtenerFactorBalanceo(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    NodoAVL* insertarNodo(NodoAVL* nodo, Usuario* usuario);
    NodoAVL* nodoConValorMinimo(NodoAVL* nodo);
    NodoAVL* eliminarNodo(NodoAVL* raiz, const std::string& correoElectronico);
    NodoAVL* buscarNodo(NodoAVL* nodo, const std::string& correoElectronico);

public:
    ArbolAVL() : raiz(nullptr) {}

    void insertar(Usuario* usuario);
    void eliminar(const std::string& correoElectronico);
    bool buscar(const std::string& correoElectronico);
    void preOrden(NodoAVL* nodo);
    NodoAVL* getRaiz();
};

#endif // ARBOLAVL_H
