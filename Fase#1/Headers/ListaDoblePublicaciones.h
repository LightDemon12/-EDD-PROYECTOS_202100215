//
// Created by LightDemon12 on 12/08/2024.
//

#ifndef LISTADOBLEPUBLICACIONES_H
#define LISTADOBLEPUBLICACIONES_H

#include "Publicacion.h"
#include <string>
#include <vector>

class ListaDoblePublicaciones {
public:
    ListaDoblePublicaciones();
    ~ListaDoblePublicaciones();
    void agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void imprimirPublicaciones() const;
    void eliminarPublicacion(const std::string& correo, const std::string& fecha, const std::string& hora);
    void clasificarPorCorreo();
    void mostrarPorCorreo(const std::string& correo) const;
    void mostrarPublicacionesFiltradas(const std::vector<std::string>& correosPermitidos) const;
    void navegarPublicaciones() const; // Asegúrate de declarar la función aquí

private:
    Publicacion* cabeza;
    Publicacion* cola;
};

#endif // LISTADOBLEPUBLICACIONES_H