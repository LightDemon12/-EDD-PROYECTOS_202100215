#include <iostream>
#include <fstream>
#include <string>
#include "../Headers/nlohmann/json.hpp"
#include "../Headers/ListaDoblePublicaciones.h"
#include "../Headers/CargarPublicaciones.h"

using json = nlohmann::json;

extern ListaDoblePublicaciones listaPublicaciones; // Declarar la lista de publicaciones como externa

void cargarPublicacionesDesdeJSON() {
    // Ruta fija del archivo JSON de publicaciones
    const std::string rutaArchivo = "../Archivos Carga/Publicaciones.json";

    // Leer el archivo JSON de publicaciones
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo de publicaciones: " << rutaArchivo << std::endl;
        return;
    }

    json jPublicaciones;
    archivo >> jPublicaciones;
    archivo.close();

    // Verificar si el JSON contiene el campo "publicaciones"
    if (!jPublicaciones.contains("publicaciones") || !jPublicaciones["publicaciones"].is_array()) {
        std::cerr << "El archivo JSON no contiene una lista de publicaciones válida." << std::endl;
        return;
    }

    // Iterar sobre cada publicación en el JSON y agregarla a la lista
    for (const auto& publicacion : jPublicaciones["publicaciones"]) {
        if (!publicacion.contains("correo") || !publicacion.contains("contenido") ||
            !publicacion.contains("fecha") || !publicacion.contains("hora")) {
            std::cerr << "La publicación no tiene todos los campos necesarios." << std::endl;
            continue;
        }

        std::string correo = publicacion["correo"];
        std::string contenido = publicacion["contenido"];
        std::string fecha = publicacion["fecha"];
        std::string hora = publicacion["hora"];

        listaPublicaciones.agregarPublicacion(correo, contenido, fecha, hora);
        std::cout << "Publicación agregada: Correo=" << correo << ", Contenido=" << contenido
                  << ", Fecha=" << fecha << ", Hora=" << hora << std::endl; // Mensaje de depuración
    }

    std::cout << "Publicaciones cargadas exitosamente desde " << rutaArchivo << std::endl;
}