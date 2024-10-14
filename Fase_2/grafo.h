#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <iostream>

struct NodoAdyacencia {
    std::string correo;
    NodoAdyacencia* siguiente;

    NodoAdyacencia(const std::string& correo) : correo(correo), siguiente(nullptr) {}
};

struct ListaAdyacencia {
    std::string correo;
    NodoAdyacencia* head;

    ListaAdyacencia(const std::string& correo) : correo(correo), head(nullptr) {}
};

class Grafo {
private:
    ListaAdyacencia** listaAdyacencia;
    int numVertices;
    int capacidad;

    int buscarIndice(const std::string& correo) const;
    bool existeArista(const std::string& correo1, const std::string& correo2) const;

public:
    Grafo(int capacidad);
    ~Grafo();
    void agregarVertice(const std::string& correo);
    void agregarArista(const std::string& correo1, const std::string& correo2);
    void mostrarGrafo() const;
    void graficarListaAdyacencia(const std::string& nombreArchivo) const; // Nuevo método
};

#endif // GRAFO_H
