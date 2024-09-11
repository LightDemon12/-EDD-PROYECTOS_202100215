#ifndef LISTAENVIADOS_H
#define LISTAENVIADOS_H

#include "NodoSolicitud.h"
#include <qtablewidget.h>
#include <string>

class ListaEnviados {
public:
    ListaEnviados();
    ~ListaEnviados();

    void agregar(const std::string& emisor, const std::string& receptor, const std::string& estado);
    void eliminar(int indice);
    NodoSolicitud* mostrarPorIndice(int indice);
    void ordenar();
    NodoSolicitud* buscar(const std::string& emisor, const std::string& receptor);
    void mostrarEnTabla(QTableWidget* table); // Declarar el nuevo método
    std::string obtenerReceptorPorIndice(int indice) const; // Declarar el nuevo método

private:
    NodoSolicitud* cabeza;
    int longitud;
};

#endif // LISTAENVIADOS_H
