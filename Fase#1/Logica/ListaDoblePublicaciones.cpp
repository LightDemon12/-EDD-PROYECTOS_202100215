//
// Created by LightDemon12 on 12/08/2024.
//
#include "../Headers/ListaDoblePublicaciones.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <algorithm>


ListaDoblePublicaciones::ListaDoblePublicaciones() : cabeza(nullptr), cola(nullptr) {}

ListaDoblePublicaciones::~ListaDoblePublicaciones() {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        Publicacion* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}
void ListaDoblePublicaciones::agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    Publicacion* nuevaPublicacion = new Publicacion(correo, contenido, fecha, hora);
    if (cabeza == nullptr) {
        cabeza = cola = nuevaPublicacion;
    } else {
        cola->siguiente = nuevaPublicacion;
        nuevaPublicacion->anterior = cola;
        cola = nuevaPublicacion;
    }
}

void ListaDoblePublicaciones::imprimirPublicaciones() const {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "*******************************" << std::endl;
        std::cout << "Correo: " << actual->correoUsuario << std::endl;
        std::cout << "Contenido: " << actual->contenido << std::endl;
        std::cout << "Fecha: " << actual->fecha << std::endl;
        std::cout << "Hora: " << actual->hora << std::endl;
        std::cout << "*******************************" << std::endl;
        actual = actual->siguiente;
    }
}

void ListaDoblePublicaciones::navegarPublicaciones() const {
    if (cabeza == nullptr) {
        std::cout << "No hay publicaciones disponibles." << std::endl;
        return;
    }

    Publicacion* actual = cabeza;
    char opcion;

    while (true) {
        std::cout << "*******************************" << std::endl;
        std::cout << "Correo: " << actual->correoUsuario << std::endl;
        std::cout << "Contenido: " << actual->contenido << std::endl;
        std::cout << "Fecha: " << actual->fecha << std::endl;
        std::cout << "Hora: " << actual->hora << std::endl;
        std::cout << "*******************************" << std::endl;
        std::cout << "Presione 'A' para anterior, 'S' para siguiente, 'Q' para salir: ";
        std::cin >> opcion;

        if (opcion == 'A' || opcion == 'a') {
            if (actual->anterior != nullptr) {
                actual = actual->anterior;
            } else {
                actual = cola; // Mover a la última publicación
            }
        } else if (opcion == 'S' || opcion == 's') {
            if (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            } else {
                actual = cabeza; // Mover a la primera publicación
            }
        } else if (opcion == 'Q' || opcion == 'q') {
            break;
        } else {
            std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    }
}

// Método para mostrar publicaciones del usuario actual con índice
void ListaDoblePublicaciones::mostrarPublicacionesUsuario(const std::string& correoUsuario) const {
    Publicacion* actual = cabeza;
    int indice = 0;
    while (actual != nullptr) {
        if (actual->correoUsuario == correoUsuario) {
            std::cout << indice << ": " << actual->correoUsuario << " - " << actual->contenido << " (" << actual->fecha << " " << actual->hora << ")" << std::endl;
        }
        actual = actual->siguiente;
        indice++;
    }
}
void ListaDoblePublicaciones::eliminarPublicacionPorIndice(int indice) {
    Publicacion* actual = cabeza;
    int contador = 0;
    while (actual != nullptr) {
        if (contador == indice) {
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
        contador++;
    }
}

// Método para generar el reporte en formato DOT
void ListaDoblePublicaciones::generarReporteListaDoble(const std::string& nombreArchivo) const {
    if (cabeza == nullptr) {
        std::cerr << "Error: La lista está vacía." << std::endl;
        return;
    }

    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "node [shape=record];\n";

    // Crear nodos para cada publicación con índice
    Publicacion* actual = cabeza;
    int indice = 0;
    while (actual != nullptr) {
        archivo << "node" << indice << " [label=\"{"
                << "Correo: " << actual->correoUsuario << " | "
                << "Contenido: " << actual->contenido << " | "
                << "Fecha: " << actual->fecha << " | "
                << "Hora: " << actual->hora << "}\"];\n";
        std::cerr << "Nodo " << indice << " creado: "
                  << "Correo: " << actual->correoUsuario << ", "
                  << "Contenido: " << actual->contenido << ", "
                  << "Fecha: " << actual->fecha << ", "
                  << "Hora: " << actual->hora << std::endl;
        actual = actual->siguiente;
        indice++;
    }

    // Crear enlaces entre los nodos
    actual = cabeza;
    indice = 0;
    while (actual != nullptr) {
        if (actual->siguiente != nullptr) {
            archivo << "node" << indice << " -> node" << (indice + 1) << ";\n";
            archivo << "node" << (indice + 1) << " -> node" << indice << ";\n";
            std::cerr << "Enlace creado entre node" << indice << " y node" << (indice + 1) << std::endl;
        }
        actual = actual->siguiente;
        indice++;
    }

    archivo << "}\n";
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o lista_doble_publicaciones.png";
    int result = system(comando.c_str());
    if (result != 0) {
        std::cerr << "Error: No se pudo generar la imagen usando Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente: lista_doble_publicaciones.png" << std::endl;

        // Abrir la imagen automáticamente
        std::string comandoAbrir = "start lista_doble_publicaciones.png";
        result = system(comandoAbrir.c_str());
        if (result != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
}
// Añadir esta función a la clase ListaDoblePublicaciones
void ListaDoblePublicaciones::generarTopCorreos(int topN) const {
    std::unordered_map<std::string, int> conteoCorreos;
    Publicacion* actual = cabeza;

    // Contar las ocurrencias de cada correo
    while (actual != nullptr) {
        std::string correo = actual->correoUsuario;
        conteoCorreos[correo]++;
        actual = actual->siguiente;
    }

    // Convertir el unordered_map en un vector de pares
    std::vector<std::pair<std::string, int>> vectorCorreos(conteoCorreos.begin(), conteoCorreos.end());

    // Ordenar el vector por el número de publicaciones (de mayor a menor)
    std::sort(vectorCorreos.begin(), vectorCorreos.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    // Imprimir el top de correos
    std::cout << "Top " << topN << " correos con más publicaciones:" << std::endl;
    for (int i = 0; i < topN && i < vectorCorreos.size(); ++i) {
        std::cout << i + 1 << ". " << vectorCorreos[i].first << " - " << vectorCorreos[i].second << " publicaciones" << std::endl;
    }
}



void ListaDoblePublicaciones::generarReportePublicacionesUsuario(const std::string& nombreArchivo) const {
    if (cabeza == nullptr) {
        std::cerr << "Error: La lista está vacía." << std::endl;
        return;
    }

    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "node [shape=record];\n";

    // Crear nodos para cada publicación con índice
    Publicacion* actual = cabeza;
    int indice = 0;
    while (actual != nullptr) {
        archivo << "node" << indice << " [label=\"{"
                << "Correo: " << actual->correoUsuario << " | "
                << "Contenido: " << actual->contenido << " | "
                << "Fecha: " << actual->fecha << " | "
                << "Hora: " << actual->hora << "}\"];\n";
        std::cerr << "Nodo " << indice << " creado: "
                  << "Correo: " << actual->correoUsuario << ", "
                  << "Contenido: " << actual->contenido << ", "
                  << "Fecha: " << actual->fecha << ", "
                  << "Hora: " << actual->hora << std::endl;
        actual = actual->siguiente;
        indice++;
    }

    // Crear enlaces entre los nodos
    actual = cabeza;
    indice = 0;
    Publicacion* ultimo = nullptr;
    while (actual != nullptr) {
        if (actual->siguiente != nullptr) {
            archivo << "node" << indice << " -> node" << (indice + 1) << ";\n";
            archivo << "node" << (indice + 1) << " -> node" << indice << ";\n";
            std::cerr << "Enlace creado entre node" << indice << " y node" << (indice + 1) << std::endl;
        } else {
            ultimo = actual;
        }
        actual = actual->siguiente;
        indice++;
    }

    // Crear enlace entre el primer y el último nodo
    if (ultimo != nullptr) {
        archivo << "node0 -> node" << (indice - 1) << ";\n";
        archivo << "node" << (indice - 1) << " -> node0;\n";
        std::cerr << "Enlace creado entre node0 y node" << (indice - 1) << std::endl;
    }

    archivo << "}\n";
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o mis_publicaciones.png";
    int result = system(comando.c_str());
    if (result != 0) {
        std::cerr << "Error: No se pudo generar la imagen usando Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente: mis_publicaciones.png" << std::endl;

        // Abrir la imagen automáticamente
        std::string comandoAbrir = "start mis_publicaciones.png";
        result = system(comandoAbrir.c_str());
        if (result != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
}

void ListaDoblePublicaciones::eliminarPublicacionPorCorreo(const std::string& correo) {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoUsuario == correo) {
            Publicacion* aEliminar = actual;
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
            actual = actual->siguiente;
            delete aEliminar;
        } else {
            actual = actual->siguiente;
        }
    }
}