#include "../Headers/MenuPublicaciones.h"
#include "../Headers/ListaEnlazada.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

MenuPublicaciones::MenuPublicaciones(ListaDoblePublicaciones& lista, const std::string& correoUsuario)
    : listaPublicaciones(lista), correoUsuario(correoUsuario) {}

void MenuPublicaciones::mostrarMenu() {
    int opcion;
    do {
        std::cout << "*******************************" << std::endl;
        std::cout << "Menu Publicaciones" << std::endl;
        std::cout << "1. Ver todas" << std::endl;
        std::cout << "2. Crear" << std::endl;
        std::cout << "3. Eliminar" << std::endl;
        std::cout << "4. Ver publicaciones relacionadas" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "*******************************" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                verTodas();
                break;
            case 2:
                crear();
                break;
            case 3:
                eliminar(correoUsuario); // Pasar el correo del usuario actual
            break;
            case 4:

                break;
            case 5:
                std::cout << "Saliendo del menú de publicaciones." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 5);
}

void MenuPublicaciones::verTodas() {
    listaPublicaciones.navegarPublicaciones();
}

void MenuPublicaciones::crear() {
    std::string contenido;
    std::cout << "Ingrese el contenido de la publicación: ";
    std::cin.ignore();
    std::getline(std::cin, contenido);

    // Obtener la fecha y hora actuales
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    std::ostringstream fechaStream;
    fechaStream << std::put_time(&now_tm, "%Y-%m-%d");
    std::string fecha = fechaStream.str();

    std::ostringstream horaStream;
    horaStream << std::put_time(&now_tm, "%H:%M");
    std::string hora = horaStream.str();

    listaPublicaciones.agregarPublicacion(correoUsuario, contenido, fecha, hora);
    std::cout << "Publicación creada exitosamente." << std::endl;
}

void MenuPublicaciones::eliminar(const std::string& correoUsuario) {
    listaPublicaciones.mostrarPublicacionesUsuario(correoUsuario); // Mostrar solo las publicaciones del usuario actual
    int indice;
    std::cout << "Ingrese el índice de la publicación a eliminar: ";
    std::cin >> indice;
    listaPublicaciones.eliminarPublicacionPorIndice(indice);
    std::cout << "Publicación eliminada exitosamente." << std::endl;
}

