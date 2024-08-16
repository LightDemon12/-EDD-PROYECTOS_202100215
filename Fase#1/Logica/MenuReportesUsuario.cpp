//
// Created by LightDemon12 on 15/08/2024.
//
// MenuReportesUsuario.cpp
#include <iostream>
#include "../Headers/MenuReportesUsuario.h"
#include "../Headers/ListaEnlazada.h"
#include "../Headers/ListaDoblePublicaciones.h"

extern ListaEnlazada lista;
extern ListaDoblePublicaciones listaPublicaciones;

using namespace std;

void mostrarMenuReportesUsuario(const std::string& correoElectronico) {
    int opcion;
    do {
        std::cout << "*******************************" << std::endl;
        cout << "Menu de Reportes del Usuario" << endl;
        cout << "1. Mis Amigos" << endl;
        cout << "2. Mis Publicaciones" << endl;
        cout << "3. Solicitudes Enviadas y Recibidas" << endl;
        cout << "4. Relaciones de Amistad" << endl;
        cout << "5. Salir" << endl;
        std::cout << "*******************************" << std::endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Generando reporte de mis amigos..." << endl;
                lista.generarReporteAmigosUsuario(correoElectronico, "mis_amigos.dot");
                cout << "Reporte de amigos generado como 'mis_amigos.dot'" << endl;
                break;
            case 2:
                cout << "Generando reporte de mis publicaciones..." << endl;
            listaPublicaciones.imprimirPublicaciones(); // Verificar el contenido antes de generar el reporte
                listaPublicaciones.generarReportePublicacionesUsuario( "mis_publicaciones.dot");
                cout << "Reporte de publicaciones generado como 'mis_publicaciones.dot'" << endl;
                break;
            case 3:
                cout << "Funcionalidad de reporte de solicitudes enviadas y recibidas no implementada." << endl;
            lista.generarReportePilaUsuario(correoElectronico, "reporte_pila.dot");
                lista.generarReporteListaSolicitudes(correoElectronico, "solicitudes_enviadas_recibidas.dot");
                break;
            case 4:
                cout << "Generando reporte de relaciones de amistad..." << endl;
                lista.generarReporteRelacionesAmistad("relaciones_amistad.dot");
                cout << "Reporte de relaciones de amistad generado como 'relaciones_amistad.dot'" << endl;
                break;
            case 5:
                cout << "Saliendo del menú de reportes del usuario..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 5);
}