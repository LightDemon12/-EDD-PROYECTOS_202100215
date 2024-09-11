#include "NodoSolicitud.h"

NodoSolicitud::NodoSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado)
    : emisor(emisor), receptor(receptor), estado(estado), siguiente(nullptr) {}
