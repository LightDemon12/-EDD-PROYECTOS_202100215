#include <iostream>
#include <windows.h> // Necesario para SetConsoleOutputCP
#include "./Headers/Usuarios.h"
#include "./Headers/ListaEnlazada.h"
#include "./Headers/InicioSeccion.h"

using namespace std;

int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);

    // Crear la lista enlazada de usuarios
    ListaEnlazada lista;

    // Agregar un usuario quemado a la lista
    Usuario* usuario1 = new Usuario(1, "Angel", "Pérez", "01/01/2000", "1", "a");
    lista.agregarNodo(usuario1);

    int opcion;
    do {
        cout << "\nMenú Principal" << endl;
        cout << "1. Iniciar sesión" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Información" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                cout << "Ingrese el correo electrónico: ";
                string correo;
                cin >> correo;
                cout << "Ingrese la contraseña: ";
                string contrasena;
                cin >> contrasena;
                iniciarSesion(lista, correo, contrasena);
                break;
            }
            case 2:
                cout << "Registro" << endl;
            break;
            case 3:
                cout << "Información" << endl;
            lista.imprimirLista();
            break;
            case 4:
                cout << "Finalizando" << endl;
            break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }
    } while(opcion != 4);

    return 0;
}