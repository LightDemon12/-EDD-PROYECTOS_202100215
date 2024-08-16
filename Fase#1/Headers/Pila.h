//
// Created by LightDemon12 on 10/08/2024.
//

#ifndef PILA_H
#define PILA_H

#include <vector>
#include <string>
#include "NodoPila.h"

class Pila {
private:
    std::vector<NodoPila> elementos;

public:
    void push(const NodoPila& nodo);
    void pop();
    NodoPila top() const;
    bool empty() const;
    size_t size() const;
    void mostrarTop() const; // Método para mostrar el elemento en el tope
    bool existeEmisor(const std::string& emisor) const; // Nuevo método para verificar si existe un emisor en la pila
    void generarReportePila(const std::string& nombreArchivo) const; // Nuevo método
    void generarReportePilaUsuario(const std::string& correo, const std::string& nombreArchivo) const;
    void eliminarPorCorreoEmisor(const std::string& correoEmisor);

};

#endif // PILA_H