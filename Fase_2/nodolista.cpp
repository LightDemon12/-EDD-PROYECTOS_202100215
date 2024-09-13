#include "nodolista.h"

NodoLista::NodoLista(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen)
    : correo(correo), contenido(contenido), fecha(fecha), hora(hora), pathimagen(pathimagen), siguiente(nullptr), anterior(nullptr) {}
