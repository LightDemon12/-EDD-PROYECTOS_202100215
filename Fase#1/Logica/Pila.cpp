#include "../Headers/Pila.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

void Pila::push(const NodoPila& nodo) {
    elementos.push_back(nodo);
}

void Pila::pop() {
    if (!elementos.empty()) {
        elementos.pop_back();
    }
}

NodoPila Pila::top() const {
    if (!elementos.empty()) {
        return elementos.back();
    }
    return NodoPila("", "", ""); // Devuelve un nodo vacío si la pila está vacía
}

bool Pila::empty() const {
    return elementos.empty();
}

size_t Pila::size() const {
    return elementos.size();
}

void Pila::mostrarTop() const {
    if (!elementos.empty()) {
        const NodoPila& nodo = elementos.back();
        std::cout << "*******************************" << std::endl;
        std::cout << "Elemento en el tope:" << std::endl;
        std::cout << "Destinatario: " << nodo.destinatario << std::endl;
        std::cout << "Emisor: " << nodo.emisor << std::endl;
        std::cout << "Estado: " << nodo.estado << std::endl;
        std::cout << "*******************************" << std::endl;
    } else {
        std::cout << "*******************************" << std::endl;
        std::cout << "La pila está vacía." << std::endl;
        std::cout << "*******************************" << std::endl;
    }
}

void Pila::generarReportePila(const std::string& nombreArchivo) const {
    if (elementos.empty()) {
        std::cerr << "Error: La pila está vacía." << std::endl;
        return;
    }
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    archivo << "digraph G {\n";
    archivo << "rankdir=BT;\n"; // Cambiar la dirección a Bottom-Top
    archivo << "node [shape=record];\n";
    // Crear nodos para cada elemento de la pila en orden inverso
    for (size_t i = 0; i < elementos.size(); ++i) {
        archivo << "node" << i << " [label=\"{"
                << "Destinatario: " << elementos[elementos.size() - 1 - i].destinatario << " | "
                << "Emisor: " << elementos[elementos.size() - 1 - i].emisor << " | "
                << "Estado: " << elementos[elementos.size() - 1 - i].estado << "}\"];\n";
    }
    // Crear enlaces invisibles entre los nodos para forzar la disposición vertical
    for (size_t i = 0; i < elementos.size() - 1; ++i) {
        archivo << "node" << i << " -> node" << (i + 1) << " [style=invis];\n";
    }
    archivo << "}\n";
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o pila.png";
    int resultado = system(comando.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente: pila.png" << std::endl;

        // Abrir la imagen automáticamente
        std::string comandoAbrir = "start pila.png";
        resultado = system(comandoAbrir.c_str());
        if (resultado != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
}

void Pila::eliminarPorCorreoEmisor(const std::string& correoEmisor) {
    std::vector<NodoPila> elementosFiltrados;

    // Filtrar los elementos que no coinciden con el correo del emisor
    for (const auto& nodo : elementos) {
        if (nodo.emisor != correoEmisor) {
            elementosFiltrados.push_back(nodo);
        }
    }

    // Reemplazar la pila original con los elementos filtrados
    elementos = elementosFiltrados;
}
