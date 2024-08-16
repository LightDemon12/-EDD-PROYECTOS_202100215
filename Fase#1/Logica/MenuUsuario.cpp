//
// Created by LightDemon12 on 10/08/2024.
//
// Perfil.cpp
#include <iostream>
#include "../Headers/Perfil.h"
#include "../Headers/MenuSolicitud.h"
#include "../Headers/MenuPublicaciones.h"
#include "../Headers/ListaDoblePublicaciones.h"
#include "../Headers/CargarPublicaciones.h"
#include "../Headers/MenuReportesUsuario.h"
#include "../Headers/ListaEnlazada.h"
#include "../Headers/MatrizDispersa.h"

using namespace std;

extern ListaDoblePublicaciones listaPublicaciones; // Declarar la lista de publicaciones como externa
extern ListaEnlazada lista; // Declarar la lista enlazada como externa
extern MatrizDispersa matrizDispersa; // Declarar la matriz dispersa como externa

void mostrarMenuUsuario(const string& correoElectronico) {
    int opcion;
    do {
        std::cout << "*******************************" << std::endl;
        cout << "Modulo Usuario" << endl;
        cout << "1. Perfil" << endl;
        cout << "2. Solicitudes" << endl;
        cout << "3. Publicaciones" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;
        std::cout << "*******************************" << std::endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                int subopcion;
                std::cout << "*******************************" << std::endl;
                cout << "Perfil" << endl;
                cout << "1. Mostrar perfil" << endl;
                cout << "2. Eliminar cuenta" << endl;
                std::cout << "*******************************" << std::endl;
                cout << "Seleccione una opción: ";
                cin >> subopcion;

                switch(subopcion) {
                    case 1:
                        cout << "Mostrando perfil..." << endl;

                        mostrarPerfil(correoElectronico); // Pasar el correo electrónico
                        break;
                    case 2:
                        cout << "Eliminando cuenta..." << endl;
                    lista.eliminarNodo(correoElectronico); // Eliminar el nodo de la lista enlazada
                    listaPublicaciones.eliminarPublicacionPorCorreo(correoElectronico); // Eliminar publicaciones del usuario
                    cout << "Cuenta eliminada exitosamente." << endl;
                    opcion = 5; // Salir del menú después de eliminar la cuenta
                    break;
                    default:
                        cout << "Opción no válida, por favor intente de nuevo." << endl;
                }
                break;
            }
            case 2:
                cout << "Solicitudes" << endl;
                mostrarMenuSolicitud(correoElectronico); // Llamar al menú de solicitudes
                break;
            case 3: {
                cout << "Publicaciones" << endl;
                MenuPublicaciones menu(listaPublicaciones, correoElectronico);
                menu.mostrarMenu();
                break;
            }
            case 4:

            mostrarMenuReportesUsuario(correoElectronico);
                break;
            case 5:
                cout << "Saliendo del módulo usuario..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 5);
}








