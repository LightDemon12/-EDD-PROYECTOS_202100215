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
    void enOrden(NodoAVL* nodo); // Declaración del nuevo método
    bool buscarUsuario(const std::string& correoElectronico, const std::string& contrasena); // Declaración del nuevo método
    std::string mostrarUsuario(const std::string& correoElectronico); // Declaración del método modificado
    NodoAVL* getRaiz();
};

#endif // ARBOLAVL_H
