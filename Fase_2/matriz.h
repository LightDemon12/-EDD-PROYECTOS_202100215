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
        Nodo(int f, int c, const std::string& v)
            : fila(f), columna(c), valor(v), siguienteFila(nullptr), siguienteColumna(nullptr) {}
    };

    MatrizDispersa(int filas, int columnas);
    ~MatrizDispersa();
    void setValor(int fila, int columna, const std::string& valor);
    std::string getValor(int fila, int columna) const;
    void eliminarNodos();
    void generarReporte(const std::string& nombreArchivo) const;
    void marcarInterseccion(const std::string& usuario1, const std::string& usuario2);

private:
    int filas;
    int columnas;
    Nodo** filasCabecera;
    Nodo** columnasCabecera;
};

#endif // MATRIZ_H
