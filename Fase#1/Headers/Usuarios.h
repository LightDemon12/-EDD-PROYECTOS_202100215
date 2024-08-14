//
// Created by LightDemon12 on 08/08/2024.
//

// Usuarios.h
#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include "Pila.h"
#include "ListaSolicitud.h"
#include "ListaEnlazadaRechazo.h" // Incluir la cabecera de ListaEnlazadaRechazo
#include "ListaDoblePublicaciones.h"

class Usuario {
public:
    int id;
    std::string nombres;
    std::string apellidos;
    std::string fechaNacimiento;
    std::string correoElectronico;
    std::string contrasena;
    Usuario* siguiente;
    Pila pilaPersonal; // Pila personal para cada usuario
    ListaSolicitud listaSolicitudes; // Lista de solicitudes de amistad personal para cada usuario
    ListaEnlazadaRechazo listaRechazos; // Lista de rechazos personal para cada usuario
    ListaDoblePublicaciones listaPublicaciones; // Lista doble de publicaciones para cada usuario

    Usuario(int id, std::string nom, std::string ape, std::string fechaNac, std::string correo, std::string contra);
};

void imprimirUsuario(const Usuario& usuario);

#endif // USUARIOS_H