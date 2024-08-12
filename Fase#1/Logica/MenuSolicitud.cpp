#include <iostream>
#include "../Headers/MenuSolicitud.h"
#include "../Headers/Usuarios.h"
#include "../Headers/ListaSolicitud.h"
#include "../Headers/ListaEnlazada.h"
#include "../Headers/Pila.h"
#include "../Headers/MatrizDispersa.h"
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
                do {
                    cout << "Ver Solicitudes" << endl;
                    // Mostrar el objeto en el tope de la pila
                    usuario->pilaPersonal.mostrarTop();
                    cout << "1. Aceptar o Rechazar solicitud" << endl;
                    cout << "2. Regresar al módulo de solicitudes" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> subopcion;

                    switch(subopcion) {
                        case 1: {
                            // Verificar si la pila no está vacía
                            if (!usuario->pilaPersonal.empty()) {
                                char opcion;
                                cout << "¿Desea aceptar (A) o rechazar (R) la solicitud? ";
                                cin >> opcion;

                                // Obtener el objeto en el tope de la pila
                                NodoPila solicitud = usuario->pilaPersonal.top();

                                if (opcion == 'A' || opcion == 'a') {
                                    // Aceptar la solicitud
                                    solicitud.estado = "Aceptada";
                                    cout << "Solicitud aceptada." << endl;

                                    // Crear la relación entre los usuarios
                                    lista.crearRelacion(solicitud.emisor, solicitud.destinatario);
                                    lista.imprimirUsuarios();
                                } else if (opcion == 'R' || opcion == 'r') {
                                    // Rechazar la solicitud
                                    solicitud.estado = "Rechazada";
                                    cout << "Solicitud rechazada." << endl;
                                } else {
                                    cout << "Opción no válida." << endl;
                                    break;
                                }

                                // Eliminar la solicitud de la lista de solicitudes del destinatario
                                usuario->listaSolicitudes.eliminarSolicitud(solicitud.destinatario, solicitud.emisor);

                                // Eliminar la solicitud de la pila
                                usuario->pilaPersonal.pop();
                            } else {
                                cout << "No hay solicitudes en la pila." << endl;
                            }
                            break;
                        }
                        case 2:
                            // Regresar al módulo de solicitudes
                                break;
                        default:
                            cout << "Opción no válida, por favor intente de nuevo." << endl;
                    }
                } while(subopcion != 2);
                break;
            }
            case 2: {
                int subopcion;
                do {
                    lista.imprimirCorreosYNombres(correoElectronico); // Mostrar correos y nombres antes de solicitar el destinatario
                    string destinatario;
                    cout << "Ingrese el correo del destinatario de la solicitud: ";
                    cin >> destinatario;
                    Usuario* destinatarioUsuario = lista.buscarUsuario(destinatario, "");
                    if (destinatarioUsuario != nullptr) {
                        // Verificar si ya existe una relación
                        if (!lista.existeRelacion(correoElectronico, destinatario)) {
                            // Verificar si ya existe una solicitud pendiente
                            if (!destinatarioUsuario->listaSolicitudes.existeSolicitud(destinatario, correoElectronico)) {
                                // Agregar solicitud a la lista de solicitudes del destinatario
                                destinatarioUsuario->listaSolicitudes.agregarSolicitud(destinatario, correoElectronico, "Pendiente");
                                cout << "Solicitud enviada." << endl;

                                // Crear el objeto NodoPila para la solicitud
                                NodoPila nuevaSolicitud(destinatario, correoElectronico, "Pendiente");

                                // Usar el método agregarObjetoAPila para agregar la solicitud a la pila del destinatario
                                lista.agregarObjetoAPila(destinatario, nuevaSolicitud);
                            } else {
                                cout << "Ya existe una solicitud pendiente para este destinatario." << endl;
                            }
                        } else {
                            cout << "Ya existe una relación entre el emisor y el destinatario." << endl;
                        }
                    } else {
                        cout << "Usuario destinatario no encontrado." << endl;
                    }
                    cout << "1. Enviar otra solicitud" << endl;
                    cout << "2. Regresar al módulo de solicitudes" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> subopcion;
                } while(subopcion != 2);
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