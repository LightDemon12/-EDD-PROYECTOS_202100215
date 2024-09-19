#include "listadoble.h"
#include <iostream>
#include <QDebug>
#include <fstream>

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

ListaDoble::~ListaDoble() {
    liberarMemoria();
}

void ListaDoble::insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen) {
    NodoLista* nuevoNodo = new NodoLista(correo, contenido, fecha, hora, pathimagen);

    if (cabeza == nullptr) {
        // La lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        // Insertar al final de la lista
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }

    qDebug() << "Nodo insertado - Correo:" << QString::fromStdString(correo) << ", Contenido:" << QString::fromStdString(contenido) << ", Fecha:" << QString::fromStdString(fecha) << ", Hora:" << QString::fromStdString(hora);
}

NodoLista* ListaDoble::obtenerUltimoNodo() const {
    return cola;
}

void ListaDoble::eliminar(const std::string& correo, const std::string& fecha, const std::string& hora) {
    NodoLista* actual = cabeza;

    while (actual != nullptr) {
        if (actual->correo == correo && actual->fecha == fecha && actual->hora == hora) {
            if (actual->anterior != nullptr) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente;
            }

            if (actual->siguiente != nullptr) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior;
            }

            delete actual;
            return;
        }
        actual = actual->siguiente;
    }
}

void ListaDoble::mostrar() const {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "Correo: " << actual->correo << std::endl;
        std::cout << "Contenido: " << actual->contenido << std::endl;
        std::cout << "Fecha: " << actual->fecha << std::endl;
        std::cout << "Hora: " << actual->hora << std::endl;
        std::cout << "Path Imagen: " << actual->pathimagen << std::endl;
        std::cout << "Comentarios: " << std::endl;
        actual->comentarios.mostrar();
        std::cout << "-------------------------" << std::endl;
        actual = actual->siguiente;
    }
}

void ListaDoble::liberarMemoria() {
    while (cabeza != nullptr) {
        NodoLista* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    cola = nullptr;
}

void ListaDoble::pasarAlArbolBinarioPorFecha(ArbolBinarioCompleto& arbol, const std::string& fecha) {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->fecha == fecha) {
            arbol.insertar(actual->correo, actual->contenido, actual->fecha, actual->hora, actual->pathimagen);
        }
        actual = actual->siguiente;
    }
}

NodoLista* ListaDoble::buscar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correo == correo && actual->contenido == contenido && actual->fecha == fecha && actual->hora == hora) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

std::vector<std::pair<std::string, int>> ListaDoble::obtenerTopFechasConMasPublicaciones(int topN) {
    std::vector<std::pair<std::string, int>> conteo;
    NodoLista* actual = cabeza;

    while (actual != nullptr) {
        auto it = std::find_if(conteo.begin(), conteo.end(), [&actual](const std::pair<std::string, int>& element) {
            return element.first == actual->fecha;
        });

        if (it != conteo.end()) {
            it->second += 1;
        } else {
            conteo.push_back(std::make_pair(actual->fecha, 1));
        }

        actual = actual->siguiente;
    }

    std::sort(conteo.begin(), conteo.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second < b.second; // Ordenar en orden ascendente
    });

    if (conteo.size() > topN) {
        conteo.resize(topN);
    }

    return conteo;
}

std::vector<NodoLista*> ListaDoble::obtenerTopPublicacionesConMasComentarios(int topN) {
    std::vector<NodoLista*> publicaciones;
    NodoLista* actual = cabeza;

    while (actual != nullptr) {
        publicaciones.push_back(actual);
        actual = actual->siguiente;
    }

    std::sort(publicaciones.begin(), publicaciones.end(), [](NodoLista* a, NodoLista* b) {
        return a->comentarios.contarComentarios() > b->comentarios.contarComentarios(); // Ordenar en orden descendente
    });

    if (publicaciones.size() > topN) {
        publicaciones.resize(topN);
    }

    return publicaciones;
}

void ListaDoble::graficarListaDoble(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph G {" << std::endl;
    archivo << "node [shape=record];" << std::endl;
    graficarListaDobleRecursivo(cabeza, archivo);
    archivo << "}" << std::endl;
    archivo.close();

    // Generar la imagen utilizando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
    system(comando.c_str());
}

void ListaDoble::graficarListaDobleRecursivo(NodoLista* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        archivo << "nodo" << nodo << " [label=\"{<f0> |<f1> Correo: " << nodo->correo
                << " | Contenido: " << nodo->contenido
                << " | Fecha: " << nodo->fecha
                << " | Hora: " << nodo->hora
                << " | Path Imagen: " << nodo->pathimagen
                << " |<f2> }\"];" << std::endl;
        if (nodo->siguiente != nullptr) {
            archivo << "nodo" << nodo << ":f2 -> nodo" << nodo->siguiente << ";" << std::endl;
            archivo << "nodo" << nodo->siguiente << ":f0 -> nodo" << nodo << ";" << std::endl;
            graficarListaDobleRecursivo(nodo->siguiente, archivo);
        }
    }
}
