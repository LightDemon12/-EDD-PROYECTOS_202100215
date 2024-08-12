//
// Created by LightDemon12 on 08/08/2024.
//
#include "../Headers/InicioSeccion.h"
#include "../Headers/MenuUsuario.h"
#include <iostream>
using namespace std;

// Función para verificar el inicio de sesión
void iniciarSesion(const ListaEnlazada& lista, const string& correo, const string& contrasena) {
    Usuario* usuario = lista.buscarUsuario(correo, contrasena);
    if (usuario != nullptr) {
        if (usuario->correoElectronico == "admin@example.com" && usuario->contrasena == "admin") {
            cout << "Bienvenido admin" << endl;
        } else {
            cout << "Iniciando sesión" << endl;
            mostrarMenuUsuario(usuario->correoElectronico); // Pasar el correo electrónico
        }
    } else {
        cout << "Correo o contraseña incorrectos" << endl;
    }
}