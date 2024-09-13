#ifndef CARGAMASIVASOLICITUDES_H
#define CARGAMASIVASOLICITUDES_H

#include <QString>
#include "arbolavl.h"
#include "listarelaciones.h"

class CargaMasivaSolicitudes {
public:
    CargaMasivaSolicitudes(ArbolAVL* arbol, ListaRelaciones* listaDeRelaciones);
    void cargarDesdeJson(const QString& rutaArchivo);

private:
    ArbolAVL* arbol;
    ListaRelaciones* listaDeRelaciones;
};

#endif // CARGAMASIVASOLICITUDES_H
