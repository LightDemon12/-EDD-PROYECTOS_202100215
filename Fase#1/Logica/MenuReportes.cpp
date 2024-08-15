//
// Created by LightDemon12 on 14/08/2024.
//
#include <iostream>
#include "../Headers/MenuReportes.h"
#include "../Headers/ListaEnlazada.h"
#include "../Headers/ListaDoblePublicaciones.h"
#include "../Headers/MatrizDispersa.h"

extern ListaEnlazada lista;
extern ListaDoblePublicaciones listaPublicaciones;
extern MatrizDispersa matrizDispersa;
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
                int subopcion;
            cout << "Reportes de Top" << endl;
            cout << "1. Top de Publicaciones" << endl;
            cout << "2. Top de Amigos" << endl;
            cout << "3. Top de Menos Amigos" << endl; // Nueva opción para el top de menos amigos
            cout << "Seleccione una opción: ";
            cin >> subopcion;

            switch(subopcion) {
                case 1:
                    int topN;
                cout << "Ingrese el número de top publicaciones a mostrar: ";
                cin >> topN;
                listaPublicaciones.generarTopCorreos(topN);
                break;
                case 2:
                    cout << "Funcionalidad de Top de Amigos aún no implementada." << endl;
                // Implementar funcionalidad de top de amigos
                break;
                case 3:
                    int topM;
                cout << "Ingrese el número de top de menos amigos a mostrar: ";
                cin >> topM;
                lista.generarTopMenosAmigos(topM);
                break;
                default:
                    cout << "Opción no válida, por favor intente de nuevo." << endl;
            }
            break;
            case 5:
                cout << "Saliendo del menú de reportes..." << endl;
            break;
            default:
                cout << "Opción no válida, por favor intente de nuevo." << endl;
        }

    } while(opcion != 5);
}