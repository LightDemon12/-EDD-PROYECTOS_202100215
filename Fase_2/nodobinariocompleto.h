#ifndef NODOBINARIOCOMPLETO_H
#define NODOBINARIOCOMPLETO_H

#include <string>
#include "ArbolB.h"

class NodoBinarioCompleto {
public:
    NodoBinarioCompleto(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen);

    // Atributos del nodo
    std::string correo;
    std::string contenido;
    std::string fecha;
    std::string hora;
    std::string pathimagen;

    // Árbol B para los comentarios
    ArbolB comentarios;

    // Punteros a los hijos
    NodoBinarioCompleto* izquierdo;
    NodoBinarioCompleto* derecho;
};

#endif // NODOBINARIOCOMPLETO_H
