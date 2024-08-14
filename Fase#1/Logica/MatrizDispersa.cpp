//
// Created by LightDemon12 on 11/08/2024.
//
#include "../Headers/MatrizDispersa.h"
#include "../Headers/ListaEnlazada.h" // Incluir la cabecera de ListaEnlazada
#include "../Headers/Usuarios.h" // Incluir la cabecera de Usuario
#include <fstream>
#include <cstdlib> // Para usar system()
#include <algorithm> // Para std::find_if
#include <iostream> // Para std::cout

MatrizDispersa::MatrizDispersa(int f, int c) : filas(f), columnas(c) {}

MatrizDispersa::~MatrizDispersa() {
    for (NodoMatriz* nodo : nodos) {
        delete nodo;
    }
}

void MatrizDispersa::insertar(const std::string& correo, const std::string& nombreCompleto) {
    NodoMatriz* nuevoNodo = new NodoMatriz(correo, nombreCompleto);
    nodos.push_back(nuevoNodo);
}
bool MatrizDispersa::existeRelacion(const std::string& correo1, const std::string& correo2) const {
    auto it = std::find_if(relaciones.begin(), relaciones.end(), [&](const std::pair<std::string, std::string>& relacion) {
        return (relacion.first == correo1 && relacion.second == correo2) ||
            (relacion.first == correo2 && relacion.second == correo1);
    });
    return it != relaciones.end();
}
void MatrizDispersa::crearRelacion(const std::string& correo1, const std::string& correo2) {
    relaciones.push_back({correo1, correo2});
}

void MatrizDispersa::imprimir() const {
    std::cout << "Matriz Dispersa de Usuarios:" << std::endl;

    // Imprimir encabezados de columnas
    std::cout << "Filas/Columnas\t";
    for (const NodoMatriz* nodo : nodos) {
        std::cout << nodo->correo << "\t";
    }
    std::cout << std::endl;

    // Imprimir filas
    for (const NodoMatriz* nodoFila : nodos) {
        std::cout << nodoFila->correo << "\t"; // Imprimir encabezado de fila
        for (const NodoMatriz* nodoColumna : nodos) {
            auto it = std::find_if(relaciones.begin(), relaciones.end(), [&](const std::pair<std::string, std::string>& relacion) {
                return (relacion.first == nodoFila->correo && relacion.second == nodoColumna->correo) ||
                    (relacion.first == nodoColumna->correo && relacion.second == nodoFila->correo);
            });
            if (it != relaciones.end()) {
                std::cout << "1\t";
            } else {
                std::cout << "\t";
            }
        }
        std::cout << std::endl; // Nueva línea al final de cada fila
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
    for (const NodoMatriz* nodo : nodos) {
        archivo << "<td>" << nodo->correo << "</td>";
    }
    archivo << "</tr>" << std::endl;

    // Filas
    for (const NodoMatriz* nodoFila : nodos) {
        archivo << "<tr><td>" << nodoFila->correo << "</td>";
        for (const NodoMatriz* nodoColumna : nodos) {
            auto it = std::find_if(relaciones.begin(), relaciones.end(), [&](const std::pair<std::string, std::string>& relacion) {
                return (relacion.first == nodoFila->correo && relacion.second == nodoColumna->correo) ||
                    (relacion.first == nodoColumna->correo && relacion.second == nodoFila->correo);
            });
            if (it != relaciones.end()) {
                archivo << "<td bgcolor='black'></td>"; // Celda con fondo negro
            } else {
                archivo << "<td></td>";
            }
        }
        archivo << "</tr>" << std::endl;
    }

    archivo << "</table>>];" << std::endl;
    archivo << "}" << std::endl;
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o matriz_usuarios.png";
    system(comando.c_str());
}
void MatrizDispersa::agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    publicaciones.emplace_back(correo, contenido, fecha, hora);
}

