#include <iostream>
#include <windows.h>
#include <locale>
#include "Headers/Usuarios.h"
#include "Headers/ListaEnlazada.h"
#include "Headers/InicioSeccion.h"
#include "Headers/Registro.h"
#include "Headers/ListaDoblePublicaciones.h"
#include "Headers/ListaSolicitud.h"
#include <cstdlib> // Para limpiar la consola
#include <cstdlib>
using namespace std;

ListaEnlazada lista;
ListaDoblePublicaciones listaPublicaciones;

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
        std::cout << "*******************************" << std::endl;
        cout << "Menú Principal" << endl;
        cout << "1. Iniciar sesión" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Información" << endl;
        cout << "4. Salir" << endl;
        std::cout << "*******************************" << std::endl;
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
                // Imprimir datos decorados
                std::cout << "*******************************" << std::endl;
            std::cout << "* Angel Guillermo de Jesús    *" << std::endl;
            std::cout << "*       Pérez Jiménez         *" << std::endl;
            std::cout << "*******************************" << std::endl;
            std::cout << "*         202100215           *" << std::endl;
            std::cout << "*******************************" << std::endl;
            std::cout << "*     Estructura de datos     *" << std::endl;
            std::cout << "*          Sección: B         *" << std::endl;
            std::cout << "*           Fase #1          *" << std::endl;
            std::cout << "*******************************" << std::endl;
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
    configurarConsolaUTF8();

    // Cargar datos desde archivos JSON


    // Generar el reporte de amigos para un usuario específico
    //td::string correo = "usuario@example.com";
    //std::string nombreArchivo = "reporte_amigos.dot";
    //lista.generarReporteAmigosUsuario(correo, nombreArchivo);

    //std::cout << "Reporte de amigos generado como '" << nombreArchivo << "'" << std::endl;
    // Agregar un usuario administrador
    lista.agregarNodo(new Usuario(1, "Admin", "Admin", "01/01/2000", "admin", "admin"));
    // Insertar algunos usuarios y relaciones para el ejemplo


    // Generar el reporte de publicaciones del usuario

    // Imprimir las publicaciones para verificar
    //listaPublicaciones.imprimirPublicaciones();

    // Mostrar menú principal
    mostrarMenuPrincipal();

    return 0;
}