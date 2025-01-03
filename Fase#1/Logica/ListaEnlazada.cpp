//
// Created by LightDemon12 on 08/08/2024.
//
#include "../Headers/ListaEnlazada.h"
#include <iostream>
#include <fstream>
using namespace std;

// Constructor para inicializar la lista vacía
ListaEnlazada::ListaEnlazada() {
    cabeza = nullptr;
    matrizUsuarios = new MatrizDispersa(100, 100); // Tamaño arbitrario

}


// Destructor para liberar la memoria de todos los nodos al destruir la lista
ListaEnlazada::~ListaEnlazada() {
    // Liberar memoria de los usuarios
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        Usuario* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    delete matrizUsuarios;
}

// Método para agregar un nuevo usuario a la lista
void ListaEnlazada::agregarNodo(Usuario* nuevoUsuario) {
    nuevoUsuario->siguiente = cabeza;
    cabeza = nuevoUsuario;
    // Insertar en la matriz dispersa
    matrizUsuarios->insertar(nuevoUsuario->correoElectronico, nuevoUsuario->nombres + " " + nuevoUsuario->apellidos);
}

void ListaEnlazada::eliminarNodo(const std::string& correoElectronico) {
    Usuario* actual = cabeza;
    Usuario* anterior = nullptr;
    while (actual != nullptr && actual->correoElectronico != correoElectronico) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual != nullptr) {
        // Eliminar objetos de la pila asociados al usuario
        eliminarObjetosDePilaPorCorreoEmisor(correoElectronico, correoElectronico);
        // Eliminar el nodo de la lista
        if (anterior == nullptr) {
            cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        // Eliminar el nodo de la matriz dispersa
        if (matrizUsuarios != nullptr) {
            matrizUsuarios->eliminarNodoPorCorreo(correoElectronico);
        } else {
            std::cerr << "Error: matrizUsuarios es nullptr." << std::endl;
        }
        delete actual;
        std::cout << "Usuario con correo " << correoElectronico << " eliminado." << std::endl;
    } else {
        std::cout << "Usuario con correo " << correoElectronico << " no encontrado." << std::endl;
    }
}

void ListaEnlazada::imprimirLista() const {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoElectronico != "admin") {
            cout << "ID: " << actual->id << ", Nombre: " << actual->nombres << " " << actual->apellidos << ", Correo: " << actual->correoElectronico << endl;
        }
        actual = actual->siguiente;
    }
}

// Método para buscar un usuario en la lista por correo electrónico y contraseña
Usuario* ListaEnlazada::buscarUsuario(const string& correoElectronico, const string& contrasena) const {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoElectronico == correoElectronico && (contrasena.empty() || actual->contrasena == contrasena)) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Método para obtener el tamaño de la lista
int ListaEnlazada::obtenerTamano() const {
    int tamano = 0;
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        tamano++;
        actual = actual->siguiente;
    }
    return tamano;
}

// Definición del método getCabeza
Usuario* ListaEnlazada::getCabeza() const {
    return cabeza;
}

// Nuevo método para imprimir el correo y nombre completo de cada usuario, omitiendo el usuario logueado
void ListaEnlazada::imprimirCorreosYNombres(const string& correoLogueado) const {
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correoElectronico != correoLogueado && actual->correoElectronico != "admin@example.com") {
            cout << "Correo: " << actual->correoElectronico << ", Nombre: " << actual->nombres << " " << actual->apellidos << endl;
        }
        actual = actual->siguiente;
    }
}
void ListaEnlazada::eliminarObjetosDePilaPorCorreoEmisor(const std::string& correoUsuario, const std::string& correoEmisor) {
    Usuario* usuario = buscarUsuario(correoUsuario);
    if (usuario != nullptr) {
        usuario->pilaPersonal.eliminarPorCorreoEmisor(correoEmisor);
        std::cout << "Objetos eliminados de la pila del usuario con correo: " << correoUsuario << std::endl;
    } else {
        std::cout << "Usuario no encontrado con el correo: " << correoUsuario << std::endl;
    }
}

void ListaEnlazada::agregarObjetoAPila(const std::string& correo, const NodoPila& nodo) {
    Usuario* usuario = buscarUsuario(correo);
    if (usuario != nullptr) {
        usuario->pilaPersonal.push(nodo);
        std::cout << "Objeto agregado a la pila del usuario con correo: " << correo << std::endl;
    } else {
        std::cout << "Usuario no encontrado con el correo: " << correo << std::endl;
    }
}



void ListaEnlazada::crearRelacion(const std::string& correo1, const std::string& correo2) {
    if (matrizUsuarios != nullptr) {
        matrizUsuarios->crearRelacion(correo1, correo2);
        std::cout << "Relación creada en la matriz dispersa entre " << correo1 << " y " << correo2 << std::endl; // Mensaje de depuración
    } else {
        std::cerr << "Error: matrizUsuarios es nullptr." << std::endl;
    }
}
bool ListaEnlazada::existeRelacion(const std::string& correo1, const std::string& correo2) {
    return matrizUsuarios->existeRelacion(correo1, correo2); // Usar el operador ->
}
void ListaEnlazada::imprimirUsuarios() const {
    std::cout << "Lista Enlazada de Usuarios:" << std::endl;
    Usuario* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "ID: " << actual->id << ", Correo: " << actual->correoElectronico << ", Nombre: " << actual->nombres << " " << actual->apellidos << std::endl;
        actual = actual->siguiente;
    }

    // Imprimir la matriz dispersa
    std::cout << "\nMatriz Dispersa de Usuarios:" << std::endl;
    matrizUsuarios->imprimir();
    matrizUsuarios->generarArchivoDOT("matriz_usuarios.dot");
}

void ListaEnlazada::generarReporteRelacionesAmistad(const std::string& nombreArchivo) const {
    if (matrizUsuarios != nullptr) {
        matrizUsuarios->generarArchivoDOT(nombreArchivo);
    } else {
        std::cerr << "Error: La matriz de usuarios no está inicializada." << std::endl;
    }
}
void ListaEnlazada::generarTopMenosAmigos(int topN) const {
    if (matrizUsuarios != nullptr) {
        matrizUsuarios->generarTopMenosAmigos(topN);
    } else {
        std::cerr << "Error: La matriz de usuarios no está inicializada." << std::endl;
    }
}
// Nuevos métodos para manejar rechazos

void ListaEnlazada::agregarRechazo(const std::string& correoUsuario, const std::string& destinatario, const std::string& emisor) {
    Usuario* usuario = buscarUsuario(correoUsuario);
    if (usuario != nullptr) {
        usuario->listaRechazos.agregarRechazo(destinatario, emisor);
        std::cout << "Rechazo agregado para el usuario con correo: " << correoUsuario << std::endl;
    } else {
        std::cout << "Usuario no encontrado con el correo: " << correoUsuario << std::endl;
    }
}

bool ListaEnlazada::eliminarRechazo(const std::string& correoUsuario, const std::string& destinatario, const std::string& emisor) {
    Usuario* usuario = buscarUsuario(correoUsuario);
    if (usuario != nullptr) {
        return usuario->listaRechazos.eliminarRechazo(destinatario, emisor);
    } else {
        std::cout << "Usuario no encontrado con el correo: " << correoUsuario << std::endl;
        return false;
    }
}

Solicitud* ListaEnlazada::buscarRechazo(const std::string& correoUsuario, const std::string& destinatario, const std::string& emisor) const {
    Usuario* usuario = buscarUsuario(correoUsuario);
    if (usuario != nullptr) {
        return usuario->listaRechazos.buscarRechazo(destinatario, emisor);
    } else {
        std::cout << "Usuario no encontrado con el correo: " << correoUsuario << std::endl;
        return nullptr;
    }
}

void ListaEnlazada::mostrarRechazos(const std::string& correoUsuario) const {
    Usuario* usuario = buscarUsuario(correoUsuario);
    if (usuario != nullptr) {
        usuario->listaRechazos.mostrarRechazos();
    } else {
        std::cout << "Usuario no encontrado con el correo: " << correoUsuario << std::endl;
    }
}

void ListaEnlazada::generarReporteListaEnlazada(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph G {" << std::endl;
    archivo << "node [shape=record];" << std::endl;

    Usuario* actual = cabeza;
    int contador = 0;

    // Crear nodos para cada usuario
    while (actual != nullptr) {
        archivo << "node" << contador << " [label=\"{" << actual->nombres << " " << actual->apellidos << " | " << actual->correoElectronico << "}\"];" << std::endl;
        actual = actual->siguiente;
        contador++;
    }

    // Crear enlaces entre los nodos
    actual = cabeza;
    contador = 0;
    while (actual != nullptr && actual->siguiente != nullptr) {
        archivo << "node" << contador << " -> node" << (contador + 1) << ";" << std::endl;
        actual = actual->siguiente;
        contador++;
    }

    archivo << "}" << std::endl;
    archivo.close();

    // Generar la imagen usando Graphviz
    std::string comando = "dot -Tpng " + nombreArchivo + " -o lista_enlazada.png";
    int result = system(comando.c_str());
    if (result != 0) {
        std::cerr << "Error: No se pudo generar la imagen usando Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente: lista_enlazada.png" << std::endl;

        // Abrir la imagen automáticamente
        std::string comandoAbrir = "start lista_enlazada.png";
        result = system(comandoAbrir.c_str());
        if (result != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
}

void ListaEnlazada::generarReporteAmigosUsuario(const std::string& correo, const std::string& nombreArchivo) const {
    if (matrizUsuarios != nullptr) {
        matrizUsuarios->generarReporteAmigosUsuario(correo, nombreArchivo);
    } else {
        std::cerr << "Error: La matriz de usuarios no está inicializada." << std::endl;
    }
}
void ListaEnlazada::generarReportePilaUsuario(const std::string& correo, const std::string& nombreArchivo) const {
    Usuario* usuario = buscarUsuario(correo);
    if (usuario != nullptr) {
        usuario->pilaPersonal.generarReportePila(nombreArchivo);
        std::cout << "Reporte de la pila generado para el usuario con correo: " << correo << std::endl;
    } else {
        std::cout << "Usuario no encontrado con el correo: " << correo << std::endl;
    }
}

void ListaEnlazada::generarReporteListaSolicitudes(const std::string& correo, const std::string& nombreArchivo) const {
    listaSolicitudes.generarReporteListaSolicitud(correo, nombreArchivo);
    std::cout << "Reporte de la lista de solicitudes generado como '" << nombreArchivo << "'" << std::endl;
}