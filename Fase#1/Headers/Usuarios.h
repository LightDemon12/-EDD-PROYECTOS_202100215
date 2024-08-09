//
// Created by LightDemon12 on 08/08/2024.
//

#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
using namespace std;

// Declaración de la estructura Usuario
struct Usuario {
    int id; // Nuevo campo ID
    string nombres;
    string apellidos;
    string fechaNacimiento;
    string correoElectronico;
    string contrasena;
    Usuario* siguiente;

    // Constructor para inicializar un nodo de usuario
    Usuario(int id, string nom, string ape, string fechaNac, string correo, string contra);
};

// Declaración de la función para imprimir la información de un usuario
void imprimirUsuario(const Usuario& usuario);

#endif // USUARIOS_H