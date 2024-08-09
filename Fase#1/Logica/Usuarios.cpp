//
// Created by LightDemon12 on 08/08/2024.
//
#include "../Headers/Usuarios.h"
#include <iostream>
using namespace std;

// Constructor para inicializar un nodo de usuario
Usuario::Usuario(int id, string nom, string ape, string fechaNac, string correo, string contra)
    : id(id), nombres(nom), apellidos(ape), fechaNacimiento(fechaNac), correoElectronico(correo), contrasena(contra), siguiente(nullptr) {}

// Función para imprimir la información de un usuario
void imprimirUsuario(const Usuario& usuario) {
    cout << "ID: " << usuario.id << endl;
    cout << "Nombres: " << usuario.nombres << endl;
    cout << "Apellidos: " << usuario.apellidos << endl;
    cout << "Fecha de Nacimiento: " << usuario.fechaNacimiento << endl;
    cout << "Correo Electrónico: " << usuario.correoElectronico << endl;
    cout << "Contraseña: " << usuario.contrasena << endl;
}