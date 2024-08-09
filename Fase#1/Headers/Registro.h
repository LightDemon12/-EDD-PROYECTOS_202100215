//
// Created by LightDemon12 on 09/08/2024.
//
#ifndef REGISTRO_H
#define REGISTRO_H

#include "ListaEnlazada.h"

// Declaración de la función para registrar un nuevo usuario
void registrarUsuario(ListaEnlazada& lista, const string& nombres, const string& apellidos, const string& fechaNacimiento, const string& correo, const string& contrasena);

#endif // REGISTRO_H