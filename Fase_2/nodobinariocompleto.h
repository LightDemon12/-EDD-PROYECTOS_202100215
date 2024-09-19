#ifndef NODOBINARIOCOMPLETO_H
#define NODOBINARIOCOMPLETO_H

#include <string>
#include "NodoLista.h" // Asegúrate de incluir NodoLista

class NodoBinarioCompleto {
public:
    NodoBinarioCompleto(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen)
        : correo(correo), contenido(contenido), fecha(fecha), hora(hora), pathimagen(pathimagen), izquierdo(nullptr), derecho(nullptr), publicaciones(nullptr) {}

    std::string correo;
    std::string contenido;
    std::string fecha;
    std::string hora;
    std::string pathimagen;
    NodoBinarioCompleto* izquierdo;
    NodoBinarioCompleto* derecho;
    NodoLista* publicaciones; // Miembro para las publicaciones
};

#endif // NODOBINARIOCOMPLETO_H
