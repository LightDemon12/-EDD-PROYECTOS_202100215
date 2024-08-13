//
// Created by LightDemon12 on 12/08/2024.
//

#ifndef MENUPUBLICACIONES_H
#define MENUPUBLICACIONES_H

#include "ListaDoblePublicaciones.h"
#include <string>

class MenuPublicaciones {
public:
    MenuPublicaciones(ListaDoblePublicaciones& lista, const std::string& correoUsuario);
    void mostrarMenu();

private:
    void verTodas();
    void crear();
    void eliminar();

    ListaDoblePublicaciones& listaPublicaciones;
    std::string correoUsuario;
};

#endif // MENUPUBLICACIONES_H