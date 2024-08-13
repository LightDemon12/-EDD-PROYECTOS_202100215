//
// Created by LightDemon12 on 12/08/2024.
//
#include "../Headers/MenuPublicaciones.h"
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
        std::cout << "Menu Publicaciones" << std::endl;
        std::cout << "1. Ver todas" << std::endl;
        std::cout << "2. Crear" << std::endl;
        std::cout << "3. Eliminar" << std::endl;
        std::cout << "4. Salir" << std::endl;
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
                eliminar();
                break;
            case 4:
                std::cout << "Saliendo del menú de publicaciones." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 4);
}

void MenuPublicaciones::verTodas() {
    listaPublicaciones.imprimirPublicaciones();
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

void MenuPublicaciones::eliminar() {
    std::string correo, fecha, hora;
    std::cout << "Ingrese el correo del usuario: ";
    std::cin >> correo;
    std::cout << "Ingrese la fecha de la publicación (YYYY-MM-DD): ";
    std::cin >> fecha;
    std::cout << "Ingrese la hora de la publicación (HH:MM): ";
    std::cin >> hora;

    listaPublicaciones.eliminarPublicacion(correo, fecha, hora);
}