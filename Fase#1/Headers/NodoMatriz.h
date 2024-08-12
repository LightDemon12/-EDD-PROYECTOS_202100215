//
// Created by LightDemon12 on 11/08/2024.
//

#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H

#include <string>

class NodoMatriz {
public:
    std::string correo;
    std::string nombreCompleto;
    NodoMatriz* siguienteFila;
    NodoMatriz* siguienteColumna;

    NodoMatriz(const std::string& correo, const std::string& nombreCompleto)
        : correo(correo), nombreCompleto(nombreCompleto), siguienteFila(nullptr), siguienteColumna(nullptr) {}
};

#endif // NODOMATRIZ_H