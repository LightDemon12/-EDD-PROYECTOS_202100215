#include "matriz.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <qdebug.h>
#include <qlogging.h>

MatrizDispersa::MatrizDispersa(int filas, int columnas)
    : filas(filas), columnas(columnas) {
    filasCabecera = new Nodo*[filas];
    columnasCabecera = new Nodo*[columnas];

    for (int i = 0; i < filas; ++i) {
        filasCabecera[i] = nullptr;
    }

    for (int j = 0; j < columnas; ++j) {
        columnasCabecera[j] = nullptr;
    }
}


MatrizDispersa::~MatrizDispersa() {
    eliminarNodos();
    delete[] filasCabecera;
    delete[] columnasCabecera;
}

void MatrizDispersa::setValor(int fila, int columna, const std::string& valor) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        std::cerr << "Índice fuera de rango" << std::endl;
        return;
    }

    // No modificar la cabecera
    if (fila == 0 || columna == 0) {
        std::cerr << "Error: No se puede modificar la fila 0 o columna 0." << std::endl;
        return;
    }

    Nodo* actual = filasCabecera[fila];
    while (actual && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }

    if (actual && actual->columna == columna) {
        if (actual->esCabecera) {
            std::cerr << "Error: No se puede modificar un nodo de cabecera." << std::endl;
            return;
        }
        actual->valor = valor;
        return;
    }

    Nodo* nuevoNodo = new Nodo(fila, columna, valor);

    if (!filasCabecera[fila]) {
        filasCabecera[fila] = nuevoNodo;
    } else {
        actual = filasCabecera[fila];
        Nodo* anterior = nullptr;
        while (actual && actual->columna < columna) {
            anterior = actual;
            actual = actual->siguienteColumna;
        }
        nuevoNodo->siguienteColumna = actual;
        if (anterior) {
            anterior->siguienteColumna = nuevoNodo;
        } else {
            filasCabecera[fila] = nuevoNodo;
        }
    }

    if (!columnasCabecera[columna]) {
        columnasCabecera[columna] = nuevoNodo;
    } else {
        actual = columnasCabecera[columna];
        Nodo* anterior = nullptr;
        while (actual && actual->fila < fila) {
            anterior = actual;
            actual = actual->siguienteFila;
        }
        nuevoNodo->siguienteFila = actual;
        if (anterior) {
            anterior->siguienteFila = nuevoNodo;
        } else {
            columnasCabecera[columna] = nuevoNodo;
        }
    }
}


void MatrizDispersa::inicializarCabeceras() {
    for (int i = 0; i < filas; ++i) {
        // Inicializar la cabecera de fila
        if (!filasCabecera[i]) {
            filasCabecera[i] = new Nodo(i, -1, "Header");
            filasCabecera[i]->esCabecera = true;
        }
    }

    for (int j = 0; j < columnas; ++j) {
        // Inicializar la cabecera de columna
        if (!columnasCabecera[j]) {
            columnasCabecera[j] = new Nodo(-1, j, "Header");
            columnasCabecera[j]->esCabecera = true;
        }
    }
}


std::string MatrizDispersa::getValor(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        std::cerr << "Índice fuera de rango" << std::endl;
        return "";
    }

    Nodo* actual = filasCabecera[fila];
    while (actual && actual->columna < columna) {
        actual = actual->siguienteColumna;
    }
    if (actual && actual->columna == columna) {
        return actual->valor;
    }
    return "";
}

void MatrizDispersa::eliminarNodos() {
    for (int i = 0; i < filas; ++i) {
        Nodo* actual = filasCabecera[i];
        while (actual) {
            Nodo* temp = actual;
            actual = actual->siguienteColumna;
            delete temp;
        }
    }
}
void MatrizDispersa::marcarInterseccion(const std::string& usuario1, const std::string& usuario2) {
    int fila1 = -1, columna1 = -1;
    int fila2 = -1, columna2 = -1;

    // Buscar las posiciones de los usuarios en las cabeceras de filas
    for (int i = 0; i < filas; ++i) {
        if (filasCabecera[i] && filasCabecera[i]->valor == usuario1) {
            fila1 = i;
        }
        if (filasCabecera[i] && filasCabecera[i]->valor == usuario2) {
            fila2 = i;
        }
    }

    // Buscar las posiciones de los usuarios en las cabeceras de columnas
    for (int j = 0; j < columnas; ++j) {
        if (columnasCabecera[j] && columnasCabecera[j]->valor == usuario1) {
            columna1 = j;
        }
        if (columnasCabecera[j] && columnasCabecera[j]->valor == usuario2) {
            columna2 = j;
        }
    }

    // Verificar que los usuarios hayan sido encontrados en la matriz
    if (fila1 == -1 || columna1 == -1 || fila2 == -1 || columna2 == -1) {
        std::cerr << "Uno de los usuarios no fue encontrado en la matriz." << std::endl;
        return;
    }

    // Crear la relación de usuario1 con usuario2 (en (fila1, columna2))
    if (!filasCabecera[fila1]->esCabecera && !columnasCabecera[columna2]->esCabecera) {
        setValor(fila1, columna2, "1");
    }

    // Crear la relación de usuario2 con usuario1 (en (fila2, columna1))
    if (!filasCabecera[fila2]->esCabecera && !columnasCabecera[columna1]->esCabecera) {
        setValor(fila2, columna1, "1");
    }
}


void MatrizDispersa::generarReporte(const std::string& nombreArchivo) const {
    // Crear la carpeta de salida si no existe
    std::filesystem::path outputPath = std::filesystem::current_path().parent_path() / "Fase_2" / "output";
    std::filesystem::create_directories(outputPath);

    // Ruta completa del archivo .dot
    std::filesystem::path rutaArchivo = outputPath / nombreArchivo;

    std::ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    archivo << "digraph G {" << std::endl;
    archivo << "node [shape=plaintext]" << std::endl;
    archivo << "a [label=<" << std::endl;
    archivo << "<table border='1' cellborder='1' cellspacing='0'>" << std::endl;

    // Encabezados de columnas
    archivo << "<tr><td></td>";
    for (int j = 0; j < columnas; ++j) {
        if (columnasCabecera[j]) {
            archivo << "<td>" << columnasCabecera[j]->valor << "</td>";
        }
    }
    archivo << "</tr>" << std::endl;

    // Filas
    for (int i = 0; i < filas; ++i) {
        if (filasCabecera[i]) {
            archivo << "<tr><td>" << filasCabecera[i]->valor << "</td>";
            for (int j = 0; j < columnas; ++j) {
                if (columnasCabecera[j]) {
                    std::string valor = getValor(i, j);
                    if (valor == "1") {
                        archivo << "<td bgcolor=\"black\"></td>";
                    } else {
                        archivo << "<td></td>";
                    }
                }
            }
            archivo << "</tr>" << std::endl;
        }
    }

    archivo << "</table>>];" << std::endl;
    archivo << "}" << std::endl;
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + rutaArchivo.string() + " -o " + (outputPath / "matriz_usuarios.png").string();
    int resultado = system(comando.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente: " << (outputPath / "matriz_usuarios.png").string() << std::endl;

        // Abrir la imagen automáticamente
        std::string comandoAbrir = "start " + (outputPath / "matriz_usuarios.png").string();
        resultado = system(comandoAbrir.c_str());
        if (resultado != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
}

void MatrizDispersa::mostrarAmigos(const std::string& usuario) const {
    int fila = -1;
    int columna = -1;

    // Buscar la posición del usuario en las cabeceras
    for (int i = 0; i < filas; ++i) {
        if (filasCabecera[i] && filasCabecera[i]->valor == usuario) {
            fila = i;
            break;
        }
    }

    for (int j = 0; j < columnas; ++j) {
        if (columnasCabecera[j] && columnasCabecera[j]->valor == usuario) {
            columna = j;
            break;
        }
    }

    if (fila == -1 && columna == -1) {
        qDebug() << "Usuario no encontrado en la matriz.";
        return;
    }

    qDebug() << "Amigos de" << QString::fromStdString(usuario) << ":";

    // Mostrar amigos en la fila
    if (fila != -1) {
        Nodo* actual = filasCabecera[fila];
        while (actual) {
            if (actual->valor == "1") {
                qDebug() << QString::fromStdString(columnasCabecera[actual->columna]->valor);
            }
            actual = actual->siguienteColumna;
        }
    }

    // Mostrar amigos en la columna
    if (columna != -1) {
        Nodo* actual = columnasCabecera[columna];
        while (actual) {
            if (actual->valor == "1") {
                qDebug() << QString::fromStdString(filasCabecera[actual->fila]->valor);
            }
            actual = actual->siguienteFila;
        }
    }
}
