#include <iostream>
#include <windows.h> // Necesario para SetConsoleOutputCP y system("cls")
#include "./Headers/Usuarios.h"
#include "./Headers/ListaEnlazada.h"
#include "./Headers/InicioSeccion.h"
#include "./Headers/Registro.h"

using namespace std;

void limpiarConsola() {
    system("cls");
}

int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);

    // Crear la lista enlazada de usuarios
    ListaEnlazada lista;

    // Agregar un usuario quemado a la lista
    Usuario* usuario1 = new Usuario(1, "Angel", "Pérez", "2000/01/01", "1", "a");
    lista.agregarNodo(usuario1);

    int opcion;
    do {
        // Limpiar la consola
        limpiarConsola();

        cout << "\nMenú Principal" << endl;
        cout << "1. Iniciar sesión" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Información" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Limpiar la consola después de seleccionar una opción
        limpiarConsola();

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
            case 2: {
                cout << "Registro de nuevo usuario" << endl;
                string nombres, apellidos, fechaNacimiento, correo, contrasena;
                int anio, mes, dia;
                cout << "Ingrese los nombres: ";
                cin.ignore();
                getline(cin, nombres);
                cout << "Ingrese los apellidos: ";
                getline(cin, apellidos);
                cout << "Ingrese el año de nacimiento: ";
                cin >> anio;
                cout << "Ingrese el mes de nacimiento: ";
                cin >> mes;
                cout << "Ingrese el día de nacimiento: ";
                cin >> dia;
                fechaNacimiento = to_string(anio) + "/" + (mes < 10 ? "0" : "") + to_string(mes) + "/" + (dia < 10 ? "0" : "") + to_string(dia);
                cout << "Ingrese el correo electrónico: ";
                cin.ignore();
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

        // Pausar para que el usuario pueda ver el resultado antes de limpiar la consola
        if (opcion != 4) {
            cout << "Presione cualquier tecla para continuar...";
            cin.ignore();
            cin.get();
        }
    } while(opcion != 4);

    return 0;
}