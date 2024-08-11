//
// Created by LightDemon12 on 10/08/2024.
//
#include <iostream>

#include "../Headers/MenuUsuario.h"

using namespace std;

void manejarPerfil();
void manejarSolicitudes();
void manejarPublicaciones();
void manejarReportes();

void mostrarMenuUsuario() {
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

        // Aquí se manejarán las opciones del menú
        switch(opcion) {
            case 1:
                manejarPerfil();
                break;
            case 2:
                manejarSolicitudes();
                break;
            case 3:
                manejarPublicaciones();
                break;
            case 4:
                manejarReportes();
                break;
            case 5:
                cout << "Saliendo del módulo usuario..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 5);
}

// Función para manejar las opciones de Perfil
void manejarPerfil() {
    int opcion;
    do {
        cout << "1. Ver perfil" << endl;
        cout << "2. Eliminar cuenta" << endl;
        cout << "3. Regresar al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Mostrando perfil..." << endl;
                // Lógica para ver perfil
                break;
            case 2:
                cout << "Eliminando cuenta..." << endl;
                // Lógica para eliminar cuenta
                break;
            case 3:
                cout << "Regresando al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }
    } while(opcion != 3);
}

// Función para manejar las opciones de Solicitudes
void manejarSolicitudes() {
    int opcion;
    do {
        cout << "1. Ver solicitudes" << endl;
        cout << "2. Enviar" << endl;
        cout << "3. Regresar al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                int subopcion;
                cout << "1. Aceptar/Rechazar" << endl;
                cout << "2. Regresar al menú de solicitudes" << endl;
                cout << "Seleccione una opción: ";
                cin >> subopcion;

                switch(subopcion) {
                    case 1:
                        cout << "Aceptando/Rechazando solicitud..." << endl;
                        // Lógica para aceptar/rechazar solicitud
                        break;
                    case 2:
                        cout << "Regresando al menú de solicitudes..." << endl;
                        break;
                    default:
                        cout << "Opción no válida, por favor intente de nuevo." << endl;
                }
                break;
            }
            case 2:
                cout << "Enviando solicitud..." << endl;
                // Lógica para enviar solicitud
                break;
            case 3:
                cout << "Regresando al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }
    } while(opcion != 3);
}

// Función para manejar las opciones de Publicaciones
void manejarPublicaciones() {
    int opcion;
    do {
        cout << "1. Ver todas" << endl;
        cout << "2. Crear" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Regresar al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Mostrando todas las publicaciones..." << endl;
                // Lógica para ver todas las publicaciones
                break;
            case 2:
                cout << "Creando publicación..." << endl;
                // Lógica para crear publicación
                break;
            case 3:
                cout << "Eliminando publicación..." << endl;
                // Lógica para eliminar publicación
                break;
            case 4:
                cout << "Regresando al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }
    } while(opcion != 4);
}

// Función para manejar las opciones de Reportes
void manejarReportes() {
    int opcion;
    do {
        cout << "1. Ver reportes" << endl;
        cout << "2. Regresar al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Mostrando reportes..." << endl;
                // Lógica para manejar reportes
                break;
            case 2:
                cout << "Regresando al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }
    } while(opcion != 2);
}


