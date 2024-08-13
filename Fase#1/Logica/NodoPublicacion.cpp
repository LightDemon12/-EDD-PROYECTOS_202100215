//
// Created by LightDemon12 on 12/08/2024.
//

#include "../Headers/Publicacion.h"

Publicacion::Publicacion(const std::string& correo, const std::string& cont, const std::string& fechaPub, const std::string& horaPub)
    : correoUsuario(correo), contenido(cont), fecha(fechaPub), hora(horaPub), siguiente(nullptr), anterior(nullptr) {}