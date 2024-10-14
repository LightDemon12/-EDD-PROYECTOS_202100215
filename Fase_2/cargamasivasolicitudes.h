#ifndef CARGAMASIVASOLICITUDES_H
#define CARGAMASIVASOLICITUDES_H

#include <QString>
#include "arbolavl.h"
#include "listarelaciones.h"
#include "Grafo.h" // Incluir la clase Grafo

class CargaMasivaSolicitudes {
public:
    CargaMasivaSolicitudes(ArbolAVL* arbol, ListaRelaciones* listaDeRelaciones, Grafo* grafo); // Modificar el constructor
    void cargarDesdeJson(const QString& rutaArchivo);

private:
    ArbolAVL* arbol;
    ListaRelaciones* listaDeRelaciones;
    Grafo* grafo; // Agregar el grafo

};

#endif // CARGAMASIVASOLICITUDES_H
