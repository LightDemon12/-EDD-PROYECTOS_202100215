#include "Grafo.h"
#include <fstream>
#include <cstdlib> // Para system()
#include <unordered_set>
#include <unordered_map>
#include <utility> // Para std::pair

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



std::unordered_map<std::string, std::vector<std::string>> Grafo::sugerirAmigos(const std::string& correo) const {
    std::unordered_map<std::string, std::vector<std::string>> sugerencias;
    int indice = buscarIndice(correo);
    if (indice == -1) {
        std::cerr << "Usuario no encontrado: " << correo << std::endl;
        return sugerencias; // Usuario no encontrado
    }

    std::cerr << "Usuario encontrado: " << correo << std::endl;

    NodoAdyacencia* actual = listaAdyacencia[indice]->head;
    while (actual != nullptr) {
        std::cerr << "Amigo directo: " << actual->correo << std::endl;
        int indiceAmigo = buscarIndice(actual->correo);
        if (indiceAmigo != -1) {
            NodoAdyacencia* amigoDeAmigo = listaAdyacencia[indiceAmigo]->head;
            while (amigoDeAmigo != nullptr) {
                std::cerr << "Amigo de amigo: " << amigoDeAmigo->correo << std::endl;
                if (amigoDeAmigo->correo != correo && !existeArista(correo, amigoDeAmigo->correo)) {
                    std::cerr << "Posible sugerencia: " << amigoDeAmigo->correo << std::endl;
                    sugerencias[amigoDeAmigo->correo].push_back(actual->correo);
                }
                amigoDeAmigo = amigoDeAmigo->siguiente;
            }
        }
        actual = actual->siguiente;
    }

    // Depuración: Mostrar el contenido de sugerencias
    for (const auto& par : sugerencias) {
        std::cerr << "Sugerencia: " << par.first << std::endl;
        for (const auto& amigoEnComun : par.second) {
            std::cerr << "  Amigo en común: " << amigoEnComun << std::endl;
        }
    }

    return sugerencias;
}

void Grafo::mostrarSugerencias(const std::unordered_map<std::string, std::vector<std::string>>& sugerencias) const {
    for (const auto& par : sugerencias) {
        std::cout << "Sugerencias" << std::endl;
        std::cout << par.first << std::endl;
        std::cout << "-----------------" << std::endl;
        for (const auto& amigoEnComun : par.second) {
            std::cout << amigoEnComun << std::endl;
        }
    }
}

void Grafo::mostrarGrafoConColores(const std::string& correo) const {
    std::ofstream archivo("grafo_colores.dot");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir el grafo." << std::endl;
        return;
    }

    int indice = buscarIndice(correo);
    if (indice == -1) {
        std::cerr << "Usuario no encontrado: " << correo << std::endl;
        return;
    }

    archivo << "graph G {\n";

    // Pintar el nodo especificado de verde
    archivo << "    \"" << listaAdyacencia[indice]->correo << "\" [style=filled, fillcolor=green];\n";

    // Conjuntos para almacenar los nodos a una y dos aristas de distancia
    std::unordered_set<int> nodosAmarillos;
    std::unordered_set<int> nodosRojos;

    // Pintar los nodos con una arista directa de amarillo
    NodoAdyacencia* actual = listaAdyacencia[indice]->head;
    while (actual != nullptr) {
        int indiceAmigo = buscarIndice(actual->correo);
        if (indiceAmigo != -1) {
            nodosAmarillos.insert(indiceAmigo);
            archivo << "    \"" << actual->correo << "\" [style=filled, fillcolor=yellow];\n";
        }
        actual = actual->siguiente;
    }

    // Pintar los nodos a dos aristas de distancia de rojo
    for (int nodoAmarillo : nodosAmarillos) {
        NodoAdyacencia* amigoDeAmigo = listaAdyacencia[nodoAmarillo]->head;
        while (amigoDeAmigo != nullptr) {
            int indiceAmigoDeAmigo = buscarIndice(amigoDeAmigo->correo);
            if (indiceAmigoDeAmigo != -1 && nodosAmarillos.find(indiceAmigoDeAmigo) == nodosAmarillos.end() && indiceAmigoDeAmigo != indice) {
                nodosRojos.insert(indiceAmigoDeAmigo);
                archivo << "    \"" << amigoDeAmigo->correo << "\" [style=filled, fillcolor=red];\n";
            }
            amigoDeAmigo = amigoDeAmigo->siguiente;
        }
    }

    // Agregar todos los nodos y aristas del grafo
    for (int i = 0; i < numVertices; ++i) {
        if (nodosAmarillos.find(i) == nodosAmarillos.end() && nodosRojos.find(i) == nodosRojos.end() && i != indice) {
            archivo << "    \"" << listaAdyacencia[i]->correo << "\";\n";
        }
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
    system("dot -Tpng grafo_colores.dot -o grafo_colores.png");
}
