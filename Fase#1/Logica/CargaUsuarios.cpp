#include "../Headers/CargaUsuarios.h"
#include "../Headers/nlohmann/json.hpp" // Incluir la biblioteca JSON primero
#include <string> // Incluir la biblioteca estándar de C++
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void cargarUsuariosDesdeJSON(ListaEnlazada& lista) {
    std::string rutaCarpeta = "../Archivos Carga/"; // Ruta fija a la carpeta

    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo JSON (incluyendo la extensión) que desea cargar: ";
    std::cin >> nombreArchivo;

    std::string rutaArchivo = rutaCarpeta + nombreArchivo; // Construir la ruta completa al archivo

    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    json j;
    archivo >> j;

    if (!j.contains("usuarios") || !j["usuarios"].is_array()) {
        std::cerr << "El archivo JSON no contiene una lista de usuarios válida." << std::endl;
        return;
    }

    int idCounter = lista.obtenerTamano() + 1; // Iniciar el contador de IDs basado en el tamaño actual de la lista

    for (const auto& usuario : j["usuarios"]) {
        if (!usuario.contains("nombres") || !usuario.contains("apellidos") ||
            !usuario.contains("fecha_de_nacimiento") || !usuario.contains("correo") || !usuario.contains("contraseña")) {
            std::cerr << "El usuario no tiene todos los campos necesarios." << std::endl;
            continue;
        }

        int nuevoId = idCounter++;
        std::string nombres = usuario["nombres"];
        std::string apellidos = usuario["apellidos"];
        std::string fechaNacimiento = usuario["fecha_de_nacimiento"];
        std::string correo = usuario["correo"];
        std::string contrasena = usuario["contraseña"];

        // Crear un nuevo usuario y agregarlo a la lista
        Usuario* nuevoUsuario = new Usuario(nuevoId, nombres, apellidos, fechaNacimiento, correo, contrasena);
        lista.agregarNodo(nuevoUsuario);
    }

    std::cout << "Usuarios cargados exitosamente desde " << rutaArchivo << std::endl;
}