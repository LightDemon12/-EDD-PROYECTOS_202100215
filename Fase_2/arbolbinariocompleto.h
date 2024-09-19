#ifndef ARBOLBINARIOCOMPLETO_H
#define ARBOLBINARIOCOMPLETO_H

#include <string>
#include <QTableWidget>
#include "NodoBinarioCompleto.h"
#include "NodoLista.h" // Asegúrate de incluir NodoLista

class ArbolBinarioCompleto {
public:
    ArbolBinarioCompleto();
    ~ArbolBinarioCompleto();
    void insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen);
    void mostrarEnTabla(QTableWidget* tableWidget); // Nueva función para mostrar en QTableWidget
    void eliminarTodosLosNodos(); // Nueva función para eliminar todos los nodos
    NodoBinarioCompleto* buscarPorIndice(int indice); // Nueva función para buscar por índice

    // Métodos de recorrido limitado
    void mostrarInordenLimitado(QTableWidget* tableWidget, int limite);
    void mostrarPreordenLimitado(QTableWidget* tableWidget, int limite);
    void mostrarPostordenLimitado(QTableWidget* tableWidget, int limite);

    // Nueva función para graficar el árbol binario usando Graphviz
    void graficarArbol(const std::string& nombreArchivo);

private:
    NodoBinarioCompleto* raiz;
    void insertar(NodoBinarioCompleto*& nodo, const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen);
    void destruir(NodoBinarioCompleto* nodo);
    void mostrarEnTabla(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& row); // Función auxiliar para mostrar en QTableWidget
    void eliminarTodosLosNodos(NodoBinarioCompleto*& nodo); // Función auxiliar para eliminar todos los nodos
    NodoBinarioCompleto* buscarPorIndice(NodoBinarioCompleto* nodo, int& currentIndex, int targetIndex); // Función auxiliar para buscar por índice
    void mostrarInordenLimitado(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& contador, int limite);
    void mostrarPreordenLimitado(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& contador, int limite);
    void mostrarPostordenLimitado(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& contador, int limite);

    // Función auxiliar para graficar el árbol binario usando Graphviz
    void graficarNodo(NodoBinarioCompleto* nodo, std::ofstream& archivo);
};

#endif // ARBOLBINARIOCOMPLETO_H
