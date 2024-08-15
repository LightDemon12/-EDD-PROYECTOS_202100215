//
// Created by LightDemon12 on 10/08/2024.
//
#include <iostream>
#include "../Headers/Perfil.h"
#include "../Headers/CargaUsuarios.h"
#include "../Headers/CargaSolicitudes.h"
#include "../Headers/CargarPublicaciones.h"
#include <locale>

#include "../Headers/ListaEnlazada.h"

using namespace std;

extern ListaEnlazada lista;

void mostrarMenuAdmin(const string& correoElectronico) {
    int opcion;
    do {
        cout << "Modulo Administrador" << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de relaciones" << endl;
        cout << "3. Carga de publicaciones" << endl;
        cout << "4. Gestionar usuarios" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Carga de usuarios" << endl;
                cargarUsuariosDesdeJSON(lista);
                break;
            case 2:
                cout << "Carga de relaciones" << endl;
                cargarSolicitudesDesdeJSON(lista);
                break;
            case 3: {
                cout << "Carga de publicaciones" << endl;
                ListaDoblePublicaciones listaDoblePublicaciones;
                cargarPublicacionesDesdeJSON(listaDoblePublicaciones);
                break;
            }
            case 4: {
                int subopcion;
                cout << "Gestionar usuarios" << endl;
                cout << "1. Eliminar usuarios" << endl;
                cout << "Seleccione una opción: ";
                cin >> subopcion;

                switch(subopcion) {
                    case 1:
                        cout << "Eliminar usuarios" << endl;
                        // Implementar funcionalidad de eliminar usuarios
                        break;
                    default:
                        cout << "Opción no válida, por favor intente de nuevo." << endl;
                }
                break;
            }
            case 5:
                cout << "Reportes" << endl;
                // Implementar funcionalidad de reportes
                break;
            case 6:
                cout << "Saliendo del módulo administrador..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 6);
}