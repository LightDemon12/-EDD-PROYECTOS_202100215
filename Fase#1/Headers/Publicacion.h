//
// Created by LightDemon12 on 12/08/2024.
//

#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <string>

class Publicacion {
public:
    std::string correoUsuario;
    std::string contenido;
    std::string fecha;
    std::string hora;
    Publicacion* siguiente;
    Publicacion* anterior;

    Publicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
};

#endif // PUBLICACION_H