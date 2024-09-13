#ifndef CARGAMASIVAPUBLICACIONES_H
#define CARGAMASIVAPUBLICACIONES_H

#include <QString>
#include "listadoble.h"
#include <nlohmann/json.hpp>

class CargaMasivaPublicaciones {
public:
    CargaMasivaPublicaciones(ListaDoble* listaDoble);
    void cargarDesdeJson(const QString& rutaArchivo);

private:
    ListaDoble* listaDoble;
};

#endif // CARGAMASIVAPUBLICACIONES_H
