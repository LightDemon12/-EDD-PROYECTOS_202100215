//
// Created by LightDemon12 on 11/08/2024.
//
#include <iostream>
#include "../Headers/Perfil.h"
#include "../Headers/ListaEnlazada.h"
using namespace std;

// Declaración de la variable global lista
extern ListaEnlazada lista; // Declarar lista como extern

void mostrarPerfil(const string& correoElectronico) {
    Usuario* actual = lista.getCabeza();
    while (actual != nullptr) {
        if (actual->correoElectronico == correoElectronico) {
            std::cout << "*******************************" << std::endl;
            cout << "ID: " << actual->id << endl;
            cout << "Nombre: " << actual->nombres << endl;
            cout << "Apellido: " << actual->apellidos << endl;
            cout << "Fecha de Nacimiento: " << actual->fechaNacimiento << endl;
            cout << "Correo: " << actual->correoElectronico << endl;
            std::cout << "*******************************" << std::endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Usuario no encontrado." << endl;
}

