#include "Grafo.h"
#include <fstream>
#include <cstdlib> // Para system()

Grafo::Grafo(int capacidad) : capacidad(capacidad), numVertices(0) {
    listaAdyacencia = new ListaAdyacencia*[capacidad];
    for (int i = 0; i < capacidad; ++i) {
        listaAdyacencia[i] = nullptr;
    }
}

Grafo::~Grafo() {
    for (int i = 0; i < numVertices; ++i) {
        NodoAdyacencia* actual = listaAdyacencia[i]->head;
        while (actual != nullptr) {
            NodoAdyacencia* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        delete listaAdyacencia[i];
    }
    delete[] listaAdyacencia;
}

int Grafo::buscarIndice(const std::string& correo) const {
    for (int i = 0; i < numVertices; ++i) {
        if (listaAdyacencia[i]->correo == correo) {
            return i;
        }
    }
    return -1;
}

void Grafo::agregarVertice(const std::string& correo) {
    if (buscarIndice(correo) == -1 && numVertices < capacidad) {
        listaAdyacencia[numVertices++] = new ListaAdyacencia(correo);
    }
}

bool Grafo::existeArista(const std::string& correo1, const std::string& correo2) const {
    int indice1 = buscarIndice(correo1);
    if (indice1 != -1) {
        NodoAdyacencia* actual = listaAdyacencia[indice1]->head;
        while (actual != nullptr) {
            if (actual->correo == correo2) {
                return true;
            }
            actual = actual->siguiente;
        }
    }
    return false;
}

void Grafo::agregarArista(const std::string& correo1, const std::string& correo2) {
    if (!existeArista(correo1, correo2)) {
        int indice1 = buscarIndice(correo1);
        int indice2 = buscarIndice(correo2);

        if (indice1 != -1 && indice2 != -1) {
            NodoAdyacencia* nuevoNodo1 = new NodoAdyacencia(correo2);
            nuevoNodo1->siguiente = listaAdyacencia[indice1]->head;
            listaAdyacencia[indice1]->head = nuevoNodo1;

            NodoAdyacencia* nuevoNodo2 = new NodoAdyacencia(correo1);
            nuevoNodo2->siguiente = listaAdyacencia[indice2]->head;
            listaAdyacencia[indice2]->head = nuevoNodo2;
        }
    }
}

void Grafo::mostrarGrafo() const {
    std::ofstream archivo("grafo.dot");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir el grafo." << std::endl;
        return;
    }

    archivo << "graph G {\n";
    for (int i = 0; i < numVertices; ++i) {
        archivo << "    \"" << listaAdyacencia[i]->correo << "\";\n";
        NodoAdyacencia* actual = listaAdyacencia[i]->head;
        while (actual != nullptr) {
            if (i < buscarIndice(actual->correo)) { // Evitar duplicados
                archivo << "    \"" << listaAdyacencia[i]->correo << "\" -- \"" << actual->correo << "\";\n";
            }
            actual = actual->siguiente;
        }
    }
    archivo << "}\n";

    archivo.close();

    // Generar la imagen del grafo utilizando Graphviz
    system("dot -Tpng grafo.dot -o grafo.png");
}

void Grafo::graficarListaAdyacencia(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo + ".dot");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir la lista de adyacencia." << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "    node [shape=record];\n";

    for (int i = 0; i < numVertices; ++i) {
        archivo << "    \"" << listaAdyacencia[i]->correo << "\" [label=\"{" << listaAdyacencia[i]->correo << "}\"];\n";
        NodoAdyacencia* actual = listaAdyacencia[i]->head;
        int nodoId = 0;
        while (actual != nullptr) {
            archivo << "    \"" << listaAdyacencia[i]->correo << nodoId << "\" [label=\"{" << actual->correo << "}\"];\n";
            if (nodoId == 0) {
                archivo << "    \"" << listaAdyacencia[i]->correo << "\" -> \"" << listaAdyacencia[i]->correo << nodoId << "\";\n";
            } else {
                archivo << "    \"" << listaAdyacencia[i]->correo << (nodoId - 1) << "\" -> \"" << listaAdyacencia[i]->correo << nodoId << "\";\n";
            }
            actual = actual->siguiente;
            nodoId++;
        }
    }

    archivo << "}\n";
    archivo.close();

    // Generar la imagen de la lista de adyacencia utilizando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
    system(comando.c_str());
}
