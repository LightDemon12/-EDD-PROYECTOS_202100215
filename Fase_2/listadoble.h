#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "nodolista.h"
#include "arbolbinariocompleto.h"

class ListaDoble {
public:
    ListaDoble();
    ~ListaDoble();

    // Métodos para manejar la lista doblemente enlazada
    void insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen);
    void eliminar(const std::string& correo, const std::string& fecha, const std::string& hora);
    void mostrar() const;
    void pasarAlArbolBinarioPorFecha(ArbolBinarioCompleto& arbol, const std::string& fecha); // Nuevo método para pasar al árbol binario por fecha

    // Método para obtener el último nodo insertado
    NodoLista* obtenerUltimoNodo() const;
    NodoLista* buscar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);

private:
    NodoLista* cabeza;
    NodoLista* cola;

    // Método auxiliar para liberar la memoria de los nodos
    void liberarMemoria();
};

#endif // LISTADOBLE_H
