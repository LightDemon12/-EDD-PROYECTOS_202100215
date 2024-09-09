#include "arbolavl.h"
#include <algorithm>

// Obtener la altura de un nodo
int ArbolAVL::obtenerAltura(NodoAVL* nodo) {
    if (nodo == nullptr)
        return 0;
    return nodo->altura;
}

// Obtener el factor de balanceo de un nodo
int ArbolAVL::obtenerFactorBalanceo(NodoAVL* nodo) {
    if (nodo == nullptr)
        return 0;
    return obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha);
}

// Rotación a la derecha
NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierda;
    NodoAVL* T2 = x->derecha;

    // Realizar rotación
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar alturas
    y->altura = std::max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = std::max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

    // Retornar nueva raíz
    return x;
}

// Rotación a la izquierda
NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izquierda;

    // Realizar rotación
    y->izquierda = x;
    x->derecha = T2;

    // Actualizar alturas
    x->altura = std::max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = std::max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

    // Retornar nueva raíz
    return y;
}

// Insertar un nodo en el árbol AVL
NodoAVL* ArbolAVL::insertarNodo(NodoAVL* nodo, Usuario* usuario) {
    // Realizar la inserción normal en un árbol binario de búsqueda
    if (nodo == nullptr)
        return new NodoAVL(usuario);

    // Comparar por correo electrónico
    if (usuario->getCorreoElectronico() < nodo->usuario->getCorreoElectronico())
        nodo->izquierda = insertarNodo(nodo->izquierda, usuario);
    else if (usuario->getCorreoElectronico() > nodo->usuario->getCorreoElectronico())
        nodo->derecha = insertarNodo(nodo->derecha, usuario);
    else
        return nodo;

    // Actualizar la altura del nodo ancestro
    nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

    // Obtener el factor de balanceo del nodo ancestro
    int balance = obtenerFactorBalanceo(nodo);

    // Si el nodo está desbalanceado, hay 4 casos

    // Caso Izquierda Izquierda
    if (balance > 1 && usuario->getCorreoElectronico() < nodo->izquierda->usuario->getCorreoElectronico())
        return rotacionDerecha(nodo);

    // Caso Derecha Derecha
    if (balance < -1 && usuario->getCorreoElectronico() > nodo->derecha->usuario->getCorreoElectronico())
        return rotacionIzquierda(nodo);

    // Caso Izquierda Derecha
    if (balance > 1 && usuario->getCorreoElectronico() > nodo->izquierda->usuario->getCorreoElectronico()) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    // Caso Derecha Izquierda
    if (balance < -1 && usuario->getCorreoElectronico() < nodo->derecha->usuario->getCorreoElectronico()) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

// Insertar un usuario en el árbol AVL
void ArbolAVL::insertar(Usuario* usuario) {
    raiz = insertarNodo(raiz, usuario);
}

// Obtener el nodo con el valor mínimo
NodoAVL* ArbolAVL::nodoConValorMinimo(NodoAVL* nodo) {
    NodoAVL* actual = nodo;
    while (actual->izquierda != nullptr)
        actual = actual->izquierda;
    return actual;
}

// Eliminar un nodo del árbol AVL
NodoAVL* ArbolAVL::eliminarNodo(NodoAVL* raiz, const std::string& correoElectronico) {
    // Realizar la eliminación normal en un árbol binario de búsqueda
    if (raiz == nullptr)
        return raiz;

    if (correoElectronico < raiz->usuario->getCorreoElectronico())
        raiz->izquierda = eliminarNodo(raiz->izquierda, correoElectronico);
    else if (correoElectronico > raiz->usuario->getCorreoElectronico())
        raiz->derecha = eliminarNodo(raiz->derecha, correoElectronico);
    else {
        if ((raiz->izquierda == nullptr) || (raiz->derecha == nullptr)) {
            NodoAVL* temp = raiz->izquierda ? raiz->izquierda : raiz->derecha;

            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            } else
                *raiz = *temp;

            delete temp;
        } else {
            NodoAVL* temp = nodoConValorMinimo(raiz->derecha);
            raiz->usuario = temp->usuario;
            raiz->derecha = eliminarNodo(raiz->derecha, temp->usuario->getCorreoElectronico());
        }
    }

    if (raiz == nullptr)
        return raiz;

    // Actualizar la altura del nodo ancestro
    raiz->altura = 1 + std::max(obtenerAltura(raiz->izquierda), obtenerAltura(raiz->derecha));

    // Obtener el factor de balanceo del nodo ancestro
    int balance = obtenerFactorBalanceo(raiz);

    // Si el nodo está desbalanceado, hay 4 casos

    // Caso Izquierda Izquierda
    if (balance > 1 && obtenerFactorBalanceo(raiz->izquierda) >= 0)
        return rotacionDerecha(raiz);

    // Caso Izquierda Derecha
    if (balance > 1 && obtenerFactorBalanceo(raiz->izquierda) < 0) {
        raiz->izquierda = rotacionIzquierda(raiz->izquierda);
        return rotacionDerecha(raiz);
    }

    // Caso Derecha Derecha
    if (balance < -1 && obtenerFactorBalanceo(raiz->derecha) <= 0)
        return rotacionIzquierda(raiz);

    // Caso Derecha Izquierda
    if (balance < -1 && obtenerFactorBalanceo(raiz->derecha) > 0) {
        raiz->derecha = rotacionDerecha(raiz->derecha);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

// Eliminar un usuario del árbol AVL por correo electrónico
void ArbolAVL::eliminar(const std::string& correoElectronico) {
    raiz = eliminarNodo(raiz, correoElectronico);
}

// Buscar un nodo en el árbol AVL por correo electrónico
NodoAVL* ArbolAVL::buscarNodo(NodoAVL* nodo, const std::string& correoElectronico) {
    if (nodo == nullptr || nodo->usuario->getCorreoElectronico() == correoElectronico)
        return nodo;

    if (correoElectronico < nodo->usuario->getCorreoElectronico())
        return buscarNodo(nodo->izquierda, correoElectronico);

    return buscarNodo(nodo->derecha, correoElectronico);
}

// Buscar un usuario en el árbol AVL por correo electrónico
bool ArbolAVL::buscar(const std::string& correoElectronico) {
    return buscarNodo(raiz, correoElectronico) != nullptr;
}

// Buscar un usuario en el árbol AVL por correo electrónico y contraseña
bool ArbolAVL::buscarUsuario(const std::string& correoElectronico, const std::string& contrasena) {
    NodoAVL* nodo = buscarNodo(raiz, correoElectronico);
    if (nodo != nullptr && nodo->usuario->getContrasena() == contrasena) {
        return true;
    }
    return false;
}

// Recorrido en preorden
void ArbolAVL::preOrden(NodoAVL* nodo) {
    if (nodo != nullptr) {
        Usuario* usuario = nodo->usuario;
        qDebug() << "Nombre:" << QString::fromStdString(usuario->getNombres());
        qDebug() << "Apellido:" << QString::fromStdString(usuario->getApellidos());
        qDebug() << "Fecha de Nacimiento:" << QString::fromStdString(usuario->getFechaNacimiento());
        qDebug() << "Correo Electrónico:" << QString::fromStdString(usuario->getCorreoElectronico());
        qDebug() << "Contraseña:" << QString::fromStdString(usuario->getContrasena());
        qDebug() << "-----------------------------";
        preOrden(nodo->izquierda);
        preOrden(nodo->derecha);
    }
}

// Recorrido en orden
void ArbolAVL::enOrden(NodoAVL* nodo) {
    if (nodo != nullptr) {
        enOrden(nodo->izquierda); // Visitar subárbol izquierdo
        Usuario* usuario = nodo->usuario;
        qDebug() << "Nombre:" << QString::fromStdString(usuario->getNombres());
        qDebug() << "Apellido:" << QString::fromStdString(usuario->getApellidos());
        qDebug() << "Fecha de Nacimiento:" << QString::fromStdString(usuario->getFechaNacimiento());
        qDebug() << "Correo Electrónico:" << QString::fromStdString(usuario->getCorreoElectronico());
        qDebug() << "Contraseña:" << QString::fromStdString(usuario->getContrasena());
        qDebug() << "-----------------------------";
        enOrden(nodo->derecha); // Visitar subárbol derecho
    }
}
std::string ArbolAVL::mostrarUsuario(const std::string& correoElectronico) {
    NodoAVL* nodo = buscarNodo(raiz, correoElectronico);
    if (nodo != nullptr) {
        Usuario* usuario = nodo->usuario;
        std::string info = "Nombre: " + usuario->getNombres() + "\n" +
                           "Apellido: " + usuario->getApellidos() + "\n" +
                           "Fecha de Nacimiento: " + usuario->getFechaNacimiento() + "\n" +
                           "Correo Electrónico: " + usuario->getCorreoElectronico() + "\n" +
                           "Contraseña: " + usuario->getContrasena();
        return info; // Usuario encontrado
    } else {
        return ""; // Usuario no encontrado
    }
}
// Obtener la raíz del árbol
NodoAVL* ArbolAVL::getRaiz() {
    return raiz;
}
