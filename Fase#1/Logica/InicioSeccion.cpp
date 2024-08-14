//
// Created by LightDemon12 on 08/08/2024.
//
#include "../Headers/InicioSeccion.h"
#include "../Headers/MenuUsuario.h"
#include "../Headers/MenuPublicaciones.h"
#include "../Headers/ListaDoblePublicaciones.h"
#include "../Headers/ListaEnlazada.h"
#include "../Headers/MenuAdmin.h" // Incluir MenuAdmin.h
#include <iostream>
using namespace std;

// Función para verificar el inicio de sesión
void iniciarSesion(const ListaEnlazada& lista, const string& correo, const string& contrasena) {
    Usuario* usuario = lista.buscarUsuario(correo, contrasena);
    if (usuario != nullptr) {
        if (usuario->correoElectronico == "admin" && usuario->contrasena == "admin") {
            cout << "Bienvenido admin" << endl;
            mostrarMenuAdmin(usuario->correoElectronico); // Redirigir al menú del administrador
        } else {
            cout << "Iniciando sesión" << endl;
            ListaDoblePublicaciones listaPublicaciones;
            MenuPublicaciones menu(listaPublicaciones, usuario->correoElectronico);
            mostrarMenuUsuario(usuario->correoElectronico); // Pasar el correo electrónico
        }
    } else {
        cout << "Correo o contraseña incorrectos" << endl;
    }
}