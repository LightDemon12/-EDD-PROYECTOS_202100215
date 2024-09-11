#ifndef MATRIZ_H
#define MATRIZ_H

#include <string>

class MatrizDispersa {
public:
    struct Nodo {
        int fila;
        int columna;
        std::string valor;
        Nodo* siguienteFila;
        Nodo* siguienteColumna;
        bool esCabecera;  // Nuevo atributo para identificar si el nodo es una cabecera

        Nodo(int f, int c, const std::string& v, bool esCabecera = false)
            : fila(f), columna(c), valor(v), siguienteFila(nullptr), siguienteColumna(nullptr), esCabecera(esCabecera) {}
    };

    MatrizDispersa(int filas, int columnas);
    ~MatrizDispersa();
    void setValor(int fila, int columna, const std::string& valor);
    std::string getValor(int fila, int columna) const;
    void eliminarNodos();
    void generarReporte(const std::string& nombreArchivo) const;
    void marcarInterseccion(const std::string& usuario1, const std::string& usuario2);
    void mostrarAmigos(const std::string& usuario) const; // Declarar el nuevo método
    void inicializarCabeceras();  // Nuevo método para inicializar cabeceras

private:
    int filas;
    int columnas;
    Nodo** filasCabecera;
    Nodo** columnasCabecera;
};

#endif // MATRIZ_H
