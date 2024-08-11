#include <iostream>
#include <windows.h>
#include "./Headers/Usuarios.h"
#include "./Headers/ListaEnlazada.h"
#include "./Headers/InicioSeccion.h"
#include "./Headers/Registro.h"
#include "./Headers/MenuUsuario.h" // Incluir el nuevo archivo de cabecera

using namespace std;

int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);

    // Crear la lista enlazada de usuarios
    ListaEnlazada lista;

    // Agregar usuarios quemados a la lista
    Usuario* usuario1 = new Usuario(1, "Angel", "Pérez", "2000/01/01", "1", "a");
    lista.agregarNodo(usuario1);
    Usuario* usuario2 = new Usuario(2, "Angel", "Pérez", "2000/01/01", "2", "b");
    lista.agregarNodo(usuario2);

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
                if (correo != "1" || contrasena != "a") {
                    iniciarSesion(lista, correo, contrasena);
                    mostrarMenuUsuario(); // Mostrar el menú del usuario si el inicio de sesión es exitoso
                } else {
                    cout << "Bienvenido admin" << endl;
                }
                break;
            }
            case 2: {
                cout << "Registro de nuevo usuario" << endl;
                string nombres, apellidos, fechaNacimiento, correo, contrasena;
                cout << "Ingrese los nombres: ";
                cin.ignore();
                getline(cin, nombres);
                cout << "Ingrese los apellidos: ";
                getline(cin, apellidos);
                cout << "Ingrese la fecha de nacimiento (YYYY/MM/DD): ";
                getline(cin, fechaNacimiento);
                cout << "Ingrese el correo electrónico: ";
                getline(cin, correo);
                cout << "Ingrese la contraseña: ";
                getline(cin, contrasena);
                registrarUsuario(lista, nombres, apellidos, fechaNacimiento, correo, contrasena);
                break;
            }
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