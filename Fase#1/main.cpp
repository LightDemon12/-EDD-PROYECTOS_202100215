#include <iostream>
#include <windows.h>
#include <locale>
#include "Headers/Usuarios.h"
#include "Headers/ListaEnlazada.h"
#include "Headers/Perfil.h"
#include "Headers/MenuUsuario.h"
#include "Headers/InicioSeccion.h"
#include "Headers/Registro.h"

using namespace std;

ListaEnlazada lista;

void configurarConsolaUTF8() {
    // Establecer la página de códigos de salida en UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Establecer la página de códigos de entrada en UTF-8
    SetConsoleCP(CP_UTF8);
    // Establecer la localización en UTF-8
    setlocale(LC_ALL, ".UTF-8");
}

void mostrarMenuPrincipal() {
    int opcion;
    do {
        cout << "Menú Principal" << endl;
        cout << "1. Iniciar sesión" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Información" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                string correo, contrasena;
                cout << "Ingrese su correo electrónico: ";
                cin >> correo;
                cout << "Ingrese su contraseña: ";
                cin >> contrasena;
                iniciarSesion(lista, correo, contrasena);
                break;
            }
            case 2:
                registrarUsuario(lista);
                break;
            case 3:
                cout << "Funcionalidad de información no implementada." << endl;
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }
    } while(opcion != 4);
}

int main() {
    // Configurar la consola para usar UTF-8
    configurarConsolaUTF8();

    // Supongamos que ya tienes una lista de usuarios cargada
    // Aquí solo se muestra un ejemplo de cómo podrías llamar a las funciones

    // Agregar usuarios de ejemplo
    lista.agregarNodo(new Usuario(1, "Admin", "Admin", "01/01/2000", "admin@example.com", "admin"));
    lista.agregarNodo(new Usuario(2, "Usuario", "Ejemplo", "02/02/2000", "usuario@example.com", "password"));
    lista.agregarNodo(new Usuario(3, "Usuario", "Ejemplo", "02/02/2000", "1", "1"));

    // Crear relación entre usuario@example.com y 1
    lista.crearRelacion("usuario@example.com", "1");

    // Imprimir usuarios y matriz dispersa
    lista.imprimirUsuarios();

    // Mostrar menú principal
    mostrarMenuPrincipal();

    return 0;
}