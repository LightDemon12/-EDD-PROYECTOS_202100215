//
// Created by LightDemon12 on 11/08/2024.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include "NodoMatriz.h"
#include <vector>
#include <string>

class MatrizDispersa {
public:
    MatrizDispersa(int f, int c);
    ~MatrizDispersa();
    void insertar(const std::string& correo, const std::string& nombreCompleto);
    void imprimir() const;
    void generarArchivoDOT(const std::string& nombreArchivo) const;
    void crearRelacion(const std::string& correo1, const std::string& correo2);

private:
    int filas;
    int columnas;
    std::vector<NodoMatriz*> nodos;
    std::vector<std::pair<std::string, std::string>> relaciones; // Almacena las relaciones
};

#endif // MATRIZDISPERSA_H