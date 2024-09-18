#ifndef ARBOLBINARIOCOMPLETO_H
#define ARBOLBINARIOCOMPLETO_H

#include <string>
#include <QTableWidget>
#include "NodoBinarioCompleto.h"

class ArbolBinarioCompleto {
public:
    ArbolBinarioCompleto();
    ~ArbolBinarioCompleto();
    void insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen);
    void mostrarEnTabla(QTableWidget* tableWidget); // Nueva función para mostrar en QTableWidget
    void eliminarTodosLosNodos(); // Nueva función para eliminar todos los nodos
    NodoBinarioCompleto* buscarPorIndice(int indice); // Nueva función para buscar por índice

private:
    NodoBinarioCompleto* raiz;
    void insertar(NodoBinarioCompleto*& nodo, const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen);
    void destruir(NodoBinarioCompleto* nodo);
    void mostrarEnTabla(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& row); // Función auxiliar para mostrar en QTableWidget
    void eliminarTodosLosNodos(NodoBinarioCompleto*& nodo); // Función auxiliar para eliminar todos los nodos
    NodoBinarioCompleto* buscarPorIndice(NodoBinarioCompleto* nodo, int& currentIndex, int targetIndex); // Función auxiliar para buscar por índice
};

#endif // ARBOLBINARIOCOMPLETO_H
