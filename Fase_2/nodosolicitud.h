#ifndef NODOSOLICITUD_H
#define NODOSOLICITUD_H

#include <string>

class NodoSolicitud {
public:
    std::string emisor;
    std::string receptor;
    std::string estado;
    NodoSolicitud* siguiente;

    NodoSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
};

#endif // NODOSOLICITUD_H
