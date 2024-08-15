//
// Created by LightDemon12 on 13/08/2024.
//
#include "../Headers/CargaSolicitudes.h"
#include "../Headers/nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void cargarSolicitudesDesdeJSON(ListaEnlazada& lista) {
    std::string rutaArchivo = "../Archivos Carga/Solicitudes.json";

    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    json j;
    archivo >> j;

    std::cout << "Archivo JSON leído correctamente." << std::endl; // Mensaje de depuración

    if (!j.contains("solicitudes") || !j["solicitudes"].is_array()) {
        std::cerr << "El archivo JSON no contiene una lista de solicitudes válida." << std::endl;
        return;
    }

    for (const auto& solicitud : j["solicitudes"]) {
        if (!solicitud.contains("emisor") || !solicitud.contains("receptor") || !solicitud.contains("estado")) {
            std::cerr << "La solicitud no tiene todos los campos necesarios." << std::endl;
            continue;
        }

        std::string emisor = solicitud["emisor"];
        std::string receptor = solicitud["receptor"];
        std::string estado = solicitud["estado"];

        std::cout << "Procesando solicitud: Emisor=" << emisor << ", Receptor=" << receptor << ", Estado=" << estado << std::endl; // Mensaje de depuración

        Usuario* usuarioReceptor = lista.buscarUsuario(receptor);
        if (usuarioReceptor != nullptr) {
            if (estado == "Aceptada") {
                lista.crearRelacion(emisor, receptor);
                std::cout << "Acciones realizadas para el estado Aceptada entre " << emisor << " y " << receptor << std::endl; // Mensaje de depuración
            }
            if (estado == "Pendiente") {
                usuarioReceptor->agregarSolicitud(receptor, emisor, estado);
                NodoPila nuevaSolicitudPila(receptor, emisor, estado);
                usuarioReceptor->pilaPersonal.push(nuevaSolicitudPila);

                // Agregar solicitud a la lista de solicitudes del emisor
                Usuario* usuarioEmisor = lista.buscarUsuario(emisor);
                if (usuarioEmisor != nullptr) {
                    usuarioEmisor->agregarSolicitud(receptor, emisor, estado);
                } else {
                    std::cout << "Usuario emisor no encontrado con el correo: " << emisor << std::endl;
                }

                // Agregar solicitud a la lista de solicitudes del destinatario
                usuarioReceptor->agregarSolicitud(receptor, emisor, estado);

                std::cout << "Acciones realizadas para el estado Pendiente entre " << emisor << " y " << receptor << std::endl; // Mensaje de depuración
            }
        } else {
            std::cout << "Usuario destinatario no encontrado con el correo: " << receptor << std::endl;
        }
    }

    std::cout << "Solicitudes cargadas exitosamente desde " << rutaArchivo << std::endl;
}