//
// Created by LightDemon12 on 11/08/2024.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include "NodoMatriz.h"
#include <iostream>
#include <string>

class MatrizDispersa {
private:
    NodoMatriz* cabeza;
    int filas;
    int columnas;

public:
    MatrizDispersa(int f, int c);
    ~MatrizDispersa();
    void insertar(const std::string& correo, const std::string& nombreCompleto);
    void imprimir() const;
    void generarArchivoDOT(const std::string& nombreArchivo) const; // Nuevo método
};

#endif // MATRIZDISPERSA_H