//
// Created by LightDemon12 on 12/08/2024.
//

#ifndef LISTADOBLEPUBLICACIONES_H
#define LISTADOBLEPUBLICACIONES_H

#include "Publicacion.h"
#include <string>
#include <vector>

class ListaDoblePublicaciones {
public:
    ListaDoblePublicaciones();
    ~ListaDoblePublicaciones();
    void agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void imprimirPublicaciones() const;
    void navegarPublicaciones() const; // Asegúrate de declarar la función aquí
    void mostrarPublicacionesUsuario(const std::string& correoUsuario) const; // Nuevo método
    void eliminarPublicacionPorIndice(int indice); // Nuevo método
    void generarReporteListaDoble(const std::string& nombreArchivo) const;
    void generarTopCorreos(int topN) const;
    void generarReportePublicacionesUsuario(const std::string& nombreArchivo) const;
    void eliminarPublicacionPorCorreo(const std::string& correo);
private:
    Publicacion* cabeza = nullptr;
    Publicacion* cola = nullptr;
};

#endif // LISTADOBLEPUBLICACIONES_H..