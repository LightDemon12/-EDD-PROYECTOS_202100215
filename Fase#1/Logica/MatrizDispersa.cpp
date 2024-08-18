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
#include <unordered_map>
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
    std::cout << "Relación agregada a la matriz dispersa: " << correo1 << " - " << correo2 << std::endl; // Mensaje de depuración
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
    int resultado = system(comando.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente: matriz_usuarios.png" << std::endl;

        // Abrir la imagen automáticamente
        std::string comandoAbrir = "start matriz_usuarios.png";
        resultado = system(comandoAbrir.c_str());
        if (resultado != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
}

void MatrizDispersa::agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    publicaciones.emplace_back(correo, contenido, fecha, hora);
}

void MatrizDispersa::generarTopMenosAmigos(int topN) const {
    std::unordered_map<std::string, int> conteoAmigos;

    // Inicializar el conteo de amigos para cada usuario
    for (const NodoMatriz* nodo : nodos) {
        conteoAmigos[nodo->correo] = 0;
    }

    // Contar las relaciones de amistad
    for (const auto& relacion : relaciones) {
        conteoAmigos[relacion.first]++;
        conteoAmigos[relacion.second]++;
    }

    // Convertir el unordered_map en un vector de pares
    std::vector<std::pair<std::string, int>> vectorAmigos(conteoAmigos.begin(), conteoAmigos.end());

    // Ordenar el vector por el número de amigos (de menor a mayor)
    std::sort(vectorAmigos.begin(), vectorAmigos.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Imprimir el top de usuarios con menos amigos
    std::cout << "Top " << topN << " usuarios con menos amigos:" << std::endl;
    for (int i = 0; i < topN && i < vectorAmigos.size(); ++i) {
        std::cout << i + 1 << ". " << vectorAmigos[i].first << " - " << vectorAmigos[i].second << " amigos" << std::endl;
    }
}
void MatrizDispersa::generarReporteAmigosUsuario(const std::string& correo, const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {" << std::endl;
    archivo << "    node [shape=ellipse];" << std::endl;

    // Encontrar el nodo del usuario
    NodoMatriz* usuario = nullptr;
    for (const auto& nodo : nodos) {
        if (nodo->correo == correo) {
            usuario = nodo;
            break;
        }
    }

    if (usuario == nullptr) {
        std::cerr << "Error: Usuario no encontrado." << std::endl;
        archivo << "}" << std::endl;
        archivo.close();
        return;
    }

    // Agregar el nodo del usuario
    archivo << "    \"" << usuario->correo << "\" [label=\"" << usuario->nombreCompleto << "\"];" << std::endl;

    // Agregar los nodos de los amigos y las relaciones
    for (const auto& relacion : relaciones) {
        if (relacion.first == correo) {
            archivo << "    \"" << relacion.first << "\" -> \"" << relacion.second << "\";" << std::endl;
        } else if (relacion.second == correo) {
            archivo << "    \"" << relacion.second << "\" -> \"" << relacion.first << "\";" << std::endl;
        }
    }

    archivo << "}" << std::endl;
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o " + nombreArchivo + ".png";
    int resultado = system(comando.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente: " << nombreArchivo << ".png" << std::endl;

        // Abrir la imagen automáticamente
        std::string comandoAbrir = "start " + nombreArchivo + ".png";
        resultado = system(comandoAbrir.c_str());
        if (resultado != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
}

void MatrizDispersa::eliminarNodoPorCorreo(const std::string& correo) {
    // Eliminar el nodo de la lista de nodos
    auto itNodo = std::remove_if(nodos.begin(), nodos.end(), [&](NodoMatriz* nodo) {
        if (nodo->correo == correo) {
            delete nodo;
            return true;
        }
        return false;
    });
    nodos.erase(itNodo, nodos.end());

    // Eliminar las relaciones asociadas al nodo
    auto itRelacion = std::remove_if(relaciones.begin(), relaciones.end(), [&](const std::pair<std::string, std::string>& relacion) {
        return relacion.first == correo || relacion.second == correo;
    });
    relaciones.erase(itRelacion, relaciones.end());

    std::cout << "Nodo y relaciones eliminadas para el correo: " << correo << std::endl;
}


