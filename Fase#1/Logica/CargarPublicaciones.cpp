#include <iostream>
#include <fstream>
#include <string>
#include "../Headers/nlohmann/json.hpp"
#include "../Headers/ListaDoblePublicaciones.h"
#include "../Headers/CargarPublicaciones.h"

using json = nlohmann::json;

void cargarPublicacionesDesdeJSON(ListaDoblePublicaciones& listaDoblePublicaciones) {
    // Ruta fija del archivo JSON de publicaciones
    const std::string rutaArchivo = "../Archivos Carga/publicaciones.json";

    // Leer el archivo JSON de publicaciones
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo de publicaciones." << std::endl;
        return;
    }

    json jPublicaciones;
    archivo >> jPublicaciones;
    archivo.close();

    // Verificar si el JSON contiene el campo "publicaciones"
    if (jPublicaciones.contains("publicaciones")) {
        // Iterar sobre cada publicación en el JSON y agregarla a la lista
        for (const auto& publicacion : jPublicaciones["publicaciones"]) {
            std::string correo = publicacion.value("correo", "");
            std::string contenido = publicacion.value("contenido", "");
            std::string fecha = publicacion.value("fecha", "");
            std::string hora = publicacion.value("hora", "");

            listaDoblePublicaciones.agregarPublicacion(correo, contenido, fecha, hora);
        }

        std::cout << "Publicaciones cargadas exitosamente desde " << rutaArchivo << std::endl;
    } else {
        std::cerr << "El archivo JSON no contiene el campo 'publicaciones'." << std::endl;
    }
}