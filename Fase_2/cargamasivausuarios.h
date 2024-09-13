#ifndef CARGAMASIVAUSUARIOS_H
#define CARGAMASIVAUSUARIOS_H

#include <QString>
#include "arbolavl.h"

class CargaMasivaUsuarios {
public:
    CargaMasivaUsuarios(ArbolAVL* arbol);
    void cargarDesdeJson(const QString& rutaArchivo);

private:
    ArbolAVL* arbol;
};

#endif // CARGAMASIVAUSUARIOS_H
