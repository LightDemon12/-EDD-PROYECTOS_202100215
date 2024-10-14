#ifndef CARGAMASIVAUSUARIOS_H
#define CARGAMASIVAUSUARIOS_H

#include "ArbolAVL.h"
#include "Grafo.h"
#include <QString>

class CargaMasivaUsuarios {
private:
    ArbolAVL* arbol;
    Grafo* grafo; // Agregar el grafo

public:
    CargaMasivaUsuarios(ArbolAVL* arbol, Grafo* grafo); // Modificar el constructor
    void cargarDesdeJson(const QString& rutaArchivo);
};

#endif // CARGAMASIVAUSUARIOS_H
