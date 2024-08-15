//
// Created by LightDemon12 on 08/08/2024.
//
#include "../Headers/InicioSeccion.h"
#include "../Headers/MenuUsuario.h"
#include "../Headers/MenuPublicaciones.h"
#include "../Headers/ListaDoblePublicaciones.h"
#include "../Headers/ListaEnlazada.h"
#include "../Headers/MenuAdmin.h"
#include "../Headers/CargarPublicaciones.h"
#include <iostream>
using namespace std;

// Función para verificar el inicio de sesión
void iniciarSesion(const ListaEnlazada& lista, const string& correo, const string& contrasena) {
    Usuario* usuario = lista.buscarUsuario(correo);
    if (usuario != nullptr && usuario->contrasena == contrasena) {
        if (usuario->correoElectronico == "admin" && usuario->contrasena == "admin") {
            cout << "Bienvenido admin" << endl;
            mostrarMenuAdmin(usuario->correoElectronico); // Redirigir al menú del administrador
        } else {
            cout << "Iniciando sesión" << endl;
            mostrarMenuUsuario(usuario->correoElectronico); // Pasar el correo electrónico
        }
    } else {
        cout << "Correo o contraseña incorrectos" << endl;
    }
}