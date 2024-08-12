//
// Created by LightDemon12 on 11/08/2024.
//
#include "../Headers/MatrizDispersa.h"
#include <fstream>
#include <cstdlib> // Para usar system()

MatrizDispersa::MatrizDispersa(int f, int c) : filas(f), columnas(c) {
    cabeza = new NodoMatriz("", ""); // Nodo cabeza
}

MatrizDispersa::~MatrizDispersa() {
    // Liberar memoria de los nodos
    NodoMatriz* actualFila = cabeza;
    while (actualFila != nullptr) {
        NodoMatriz* actualColumna = actualFila->siguienteFila;
        while (actualColumna != nullptr) {
            NodoMatriz* temp = actualColumna;
            actualColumna = actualColumna->siguienteColumna;
            delete temp;
        }
        NodoMatriz* temp = actualFila;
        actualFila = actualFila->siguienteFila;
        delete temp;
    }
}

void MatrizDispersa::insertar(const std::string& correo, const std::string& nombreCompleto) {
    NodoMatriz* nuevoNodo = new NodoMatriz(correo, nombreCompleto);

    // Insertar en la fila
    NodoMatriz* actualFila = cabeza;
    while (actualFila->siguienteFila != nullptr) {
        actualFila = actualFila->siguienteFila;
    }
    actualFila->siguienteFila = nuevoNodo;

    // Insertar en la columna
    NodoMatriz* actualColumna = cabeza;
    while (actualColumna->siguienteColumna != nullptr) {
        actualColumna = actualColumna->siguienteColumna;
    }
    actualColumna->siguienteColumna = nuevoNodo;
}

void MatrizDispersa::imprimir() const {
    NodoMatriz* actualFila = cabeza->siguienteFila;
    std::cout << "Matriz Dispersa de Usuarios:" << std::endl;

    // Imprimir encabezados de columnas
    std::cout << "Filas/Columnas\t";
    NodoMatriz* tempCol = cabeza->siguienteColumna;
    while (tempCol != nullptr) {
        std::cout << tempCol->correo << "\t";
        tempCol = tempCol->siguienteColumna;
    }
    std::cout << std::endl;

    // Imprimir filas
    while (actualFila != nullptr) {
        std::cout << actualFila->correo << "\t"; // Imprimir encabezado de fila
        NodoMatriz* actualColumna = cabeza->siguienteColumna;
        while (actualColumna != nullptr) {
            NodoMatriz* temp = actualFila->siguienteColumna;
            bool found = false;
            while (temp != nullptr) {
                if (temp->correo == actualColumna->correo) {
                    std::cout << "1\t";
                    found = true;
                    break;
                }
                temp = temp->siguienteColumna;
            }
            if (!found) {
                std::cout << "\t";
            }
            actualColumna = actualColumna->siguienteColumna;
        }
        std::cout << std::endl; // Nueva línea al final de cada fila
        actualFila = actualFila->siguienteFila;
    }
}
void MatrizDispersa::generarArchivoDOT(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph G {" << std::endl;
    archivo << "node [shape=plaintext]" << std::endl;
    archivo << "a [label=<" << std::endl;
    archivo << "<table border='1' cellborder='1' cellspacing='0'>" << std::endl;

    // Encabezados de columnas
    archivo << "<tr><td></td>";
    NodoMatriz* tempCol = cabeza->siguienteColumna;
    while (tempCol != nullptr) {
        archivo << "<td>" << tempCol->correo << "</td>";
        tempCol = tempCol->siguienteColumna;
    }
    archivo << "</tr>" << std::endl;

    // Filas
    NodoMatriz* actualFila = cabeza->siguienteFila;
    while (actualFila != nullptr) {
        archivo << "<tr><td>" << actualFila->correo << "</td>";
        NodoMatriz* actualColumna = cabeza->siguienteColumna;
        while (actualColumna != nullptr) {
            NodoMatriz* temp = actualFila->siguienteColumna;
            bool found = false;
            while (temp != nullptr) {
                if (temp->correo == actualColumna->correo) {
                    archivo << "<td>1</td>";
                    found = true;
                    break;
                }
                temp = temp->siguienteColumna;
            }
            if (!found) {
                archivo << "<td></td>";
            }
            actualColumna = actualColumna->siguienteColumna;
        }
        archivo << "</tr>" << std::endl;
        actualFila = actualFila->siguienteFila;
    }

    archivo << "</table>>];" << std::endl;
    archivo << "}" << std::endl;
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o matriz_usuarios.png";
    system(comando.c_str());
}