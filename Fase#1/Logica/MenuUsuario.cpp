//
// Created by LightDemon12 on 10/08/2024.
//
#include <iostream>
#include "../Headers/Perfil.h"
#include "../Headers/MenuSolicitud.h" // Asegúrate de incluir MenuSolicitud.h
#include "../Headers/MenuPublicaciones.h" // Incluir MenuPublicaciones.h
#include "../Headers/ListaDoblePublicaciones.h" // Incluir ListaDoblePublicaciones.h
#include "../Headers/CargarPublicaciones.h" // Incluir CargarPublicaciones.h

using namespace std;

void mostrarMenuUsuario(const string& correoElectronico) {
    int opcion;
    do {
        cout << "Modulo Usuario" << endl;
        cout << "1. Perfil" << endl;
        cout << "2. Solicitudes" << endl;
        cout << "3. Publicaciones" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                int subopcion;
                cout << "Perfil" << endl;
                cout << "1. Mostrar perfil" << endl;
                cout << "2. Eliminar cuenta" << endl;
                cout << "Seleccione una opción: ";
                cin >> subopcion;

                switch(subopcion) {
                    case 1:
                        cout << "Mostrando perfil..." << endl;
                        mostrarPerfil(correoElectronico); // Pasar el correo electrónico
                        break;
                    case 2:
                        cout << "Funcionalidad de eliminar cuenta no implementada." << endl;
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
                ListaDoblePublicaciones listaPublicaciones;
                cargarPublicacionesDesdeJSON(listaPublicaciones); // Cargar publicaciones desde JSON
                MenuPublicaciones menu(listaPublicaciones, correoElectronico);
                menu.mostrarMenu();
                break;
            }
            case 4:
                cout << "Funcionalidad de reportes no implementada." << endl;
                break;
            case 5:
                cout << "Saliendo del módulo usuario..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 5);
}









