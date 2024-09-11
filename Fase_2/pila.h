#ifndef PILA_H
#define PILA_H

#include "NodoSolicitud.h"
#include <qtablewidget.h>
#include <string>

class Pila {
public:
    Pila();
    ~Pila();

    void agregar(const std::string& emisor, const std::string& receptor, const std::string& estado);
    void eliminar();
    void ordenar();
    void mostrar() const;
    NodoSolicitud* buscar(const std::string& emisor, const std::string& receptor, const std::string& estado) const; // Declarar el nuevo método
    void mostrarEnTabla(QTableWidget* table) const; // Declarar el nuevo método
    void eliminarPorIndice(int indice); // Declarar el nuevo método
    std::string obtenerEmisorPorIndice(int indice) const; // Declarar el nuevo método

private:
    NodoSolicitud* cima;
    int longitud;
};

#endif // PILA_H
