//
// Created by LightDemon12 on 11/08/2024.
//
//
// Created by LightDemon12 on 10/08/2024.
//
#include <iostream>
#include "../Headers/MenuSolicitud.h"
#include "../Headers/Usuarios.h"
#include "../Headers/ListaSolicitud.h"
#include "../Headers/ListaEnlazada.h"
using namespace std;

extern ListaEnlazada lista;  // Asegúrate de que la lista de usuarios sea accesible

void mostrarMenuSolicitud(const std::string& correoElectronico) {
    int opcion;
    do {
        cout << "Modulo Solicitudes" << endl;
        cout << "1. Ver solicitudes" << endl;
        cout << "2. Enviar solicitud" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        Usuario* usuario = lista.buscarUsuario(correoElectronico, "");
        if (usuario == nullptr) {
            cout << "Usuario no encontrado." << endl;
            break;
        }

        switch(opcion) {
            case 1: {
                int subopcion;
                cout << "Ver Solicitudes" << endl;
                cout << "1. Aceptar solicitud" << endl;
                cout << "2. Rechazar solicitud" << endl;
                cout << "Seleccione una opción: ";
                cin >> subopcion;

                switch(subopcion) {
                    case 1: {
                        string emisor;
                        cout << "Ingrese el correo del emisor de la solicitud a aceptar: ";
                        cin >> emisor;
                        Solicitud* solicitud = usuario->listaSolicitudes.buscarSolicitud(correoElectronico, emisor);
                        if (solicitud != nullptr) {
                            solicitud->estado = "Aceptada";
                            cout << "Solicitud aceptada." << endl;
                        } else {
                            cout << "Solicitud no encontrada." << endl;
                        }
                        break;
                    }
                    case 2: {
                        string emisor;
                        cout << "Ingrese el correo del emisor de la solicitud a rechazar: ";
                        cin >> emisor;
                        if (usuario->listaSolicitudes.eliminarSolicitud(correoElectronico, emisor)) {
                            cout << "Solicitud rechazada." << endl;
                        } else {
                            cout << "Solicitud no encontrada." << endl;
                        }
                        break;
                    }
                    default:
                        cout << "Opción no válida, por favor intente de nuevo." << endl;
                }
                break;
            }
            case 2: {
                lista.imprimirCorreosYNombres(correoElectronico); // Mostrar correos y nombres antes de solicitar el destinatario
                string destinatario;
                cout << "Ingrese el correo del destinatario de la solicitud: ";
                cin >> destinatario;
                Usuario* destinatarioUsuario = lista.buscarUsuario(destinatario, "");
                if (destinatarioUsuario != nullptr) {
                    destinatarioUsuario->listaSolicitudes.agregarSolicitud(destinatario, correoElectronico, "Pendiente");
                    cout << "Solicitud enviada." << endl;
                } else {
                    cout << "Usuario destinatario no encontrado." << endl;
                }
                break;
            }
            case 3:
                cout << "Saliendo del módulo solicitudes..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 3);
}