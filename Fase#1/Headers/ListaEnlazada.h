//
// Created by LightDemon12 on 08/08/2024.
//
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <string>
#include "Usuarios.h"

using namespace std;

class ListaEnlazada {
private:
    Usuario* cabeza;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    void agregarNodo(Usuario* nuevoUsuario);
    void eliminarNodo(const string& correoElectronico);
    void imprimirLista() const;
    Usuario* buscarUsuario(const string& correoElectronico, const string& contrasena) const;
    int obtenerTamano() const; // Método para obtener el tamaño de la lista
};

#endif // LISTAENLAZADA_H