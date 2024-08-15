//
// Created by LightDemon12 on 14/08/2024.
//
#include <iostream>
#include "../Headers/MenuReportes.h"
#include "../Headers/MatrizDispersa.h"
#include "../Headers/ListaEnlazada.h"
#include "../Headers/ListaDoblePublicaciones.h"
extern ListaEnlazada lista;
extern ListaDoblePublicaciones listaPublicaciones;
using namespace std;

void mostrarMenuReportes(const string& correoElectronico) {
    int opcion;
    do {
        cout << "Menu de Reportes" << endl;
        cout << "1. Usuarios" << endl;
        cout << "2. Relaciones de Amistad" << endl;
        cout << "3. Publicaciones" << endl;
        cout << "4. Top" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Reportes de Usuarios" << endl;
            // Implementar funcionalidad de reportes de usuario
            lista.generarReporteListaEnlazada("lista_enlazada.dot");
            break;
            case 2:
                cout << "Reportes de Relaciones de Amistad" << endl;
            // Implementar funcionalidad de reportes de relaciones de amistad
            lista.generarReporteRelacionesAmistad("relaciones.dot");
            cout << "Reporte de relaciones de amistad generado como 'relaciones.dot' y 'matriz_usuarios.png'" << endl;
            break;
            case 3:
                std::cerr << "Generando reporte de publicaciones...\n";
            listaPublicaciones.imprimirPublicaciones(); // Verificar el contenido antes de generar el reporte
            listaPublicaciones.generarReporteListaDoble("lista_doble_publicaciones.dot");
            break;
            case 4:
                cout << "Reportes de Top" << endl;
            // Implementar funcionalidad de reportes de top
            break;
            case 5:
                cout << "Saliendo del menú de reportes..." << endl;
            break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 5);
}