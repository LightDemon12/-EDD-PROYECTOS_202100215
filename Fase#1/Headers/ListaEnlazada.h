//
// Created by LightDemon12 on 08/08/2024.
//
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Usuarios.h"

class ListaEnlazada {
private:
    Usuario* cabeza;

public:
    ListaEnlazada();
    ~ListaEnlazada();
    void agregarNodo(Usuario* nuevoUsuario);
    void eliminarNodo(const std::string& correoElectronico);
    void imprimirLista() const;
    Usuario* buscarUsuario(const std::string& correoElectronico, const std::string& contrasena = "") const;
    int obtenerTamano() const;
    Usuario* getCabeza() const;
    void imprimirCorreosYNombres(const std::string& correoLogueado) const;
    void agregarObjetoAPila(const std::string& correo, const NodoPila& nodo); // Nuevo método
};

#endif // LISTAENLAZADA_H