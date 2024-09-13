#include "nodob.h"

NodoB::NodoB(bool esHoja) : esHoja(esHoja), numClaves(0) {
    // Inicializar los punteros a los hijos a nullptr
    for (int i = 0; i < 2 * T; i++) {
        hijos[i] = nullptr;
    }
}

bool NodoB::esMenor(const std::string& fecha1, const std::string& hora1, const std::string& fecha2, const std::string& hora2) {
    if (fecha1 < fecha2) {
        return true;
    } else if (fecha1 == fecha2) {
        return hora1 < hora2;
    }
    return false;
}

void NodoB::insertarNoLleno(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    int i = numClaves - 1;

    if (esHoja) {
        // Encuentra la ubicación de la nueva clave y mueve todas las claves mayores una posición hacia adelante
        while (i >= 0 && esMenor(fecha, hora, fechas[i], horas[i])) {
            correos[i + 1] = correos[i];
            contenidos[i + 1] = contenidos[i];
            fechas[i + 1] = fechas[i];
            horas[i + 1] = horas[i];
            i--;
        }

        // Insertar la nueva clave en la ubicación encontrada
        correos[i + 1] = correo;
        contenidos[i + 1] = contenido;
        fechas[i + 1] = fecha;
        horas[i + 1] = hora;
        numClaves++;
    } else {
        // Encuentra el hijo que debe tener la nueva clave
        while (i >= 0 && esMenor(fecha, hora, fechas[i], horas[i])) {
            i--;
        }
        i++;

        // Si el hijo encontrado está lleno, divídelo
        if (hijos[i]->numClaves == 2 * T - 1) {
            dividirHijo(i, hijos[i]);

            // Después de dividir, la clave del medio de hijos[i] sube y hijos[i] se divide en dos
            if (esMenor(fechas[i], horas[i], fecha, hora)) {
                i++;
            }
        }
        hijos[i]->insertarNoLleno(correo, contenido, fecha, hora);
    }
}

void NodoB::dividirHijo(int i, NodoB* y) {
    NodoB* z = new NodoB(y->esHoja);
    z->numClaves = T - 1;

    // Copiar las últimas T-1 claves de y a z
    for (int j = 0; j < T - 1; j++) {
        z->correos[j] = y->correos[j + T];
        z->contenidos[j] = y->contenidos[j + T];
        z->fechas[j] = y->fechas[j + T];
        z->horas[j] = y->horas[j + T];
    }

    // Copiar los últimos T hijos de y a z
    if (!y->esHoja) {
        for (int j = 0; j < T; j++) {
            z->hijos[j] = y->hijos[j + T];
        }
    }

    y->numClaves = T - 1;

    // Mover los hijos de y para hacer espacio para z
    for (int j = numClaves; j >= i + 1; j--) {
        hijos[j + 1] = hijos[j];
    }

    // Vincular z con este nodo
    hijos[i + 1] = z;

    // Mover las claves de este nodo para hacer espacio para la clave de y
    for (int j = numClaves - 1; j >= i; j--) {
        correos[j + 1] = correos[j];
        contenidos[j + 1] = contenidos[j];
        fechas[j + 1] = fechas[j];
        horas[j + 1] = horas[j];
    }

    // Copiar la clave del medio de y a este nodo
    correos[i] = y->correos[T - 1];
    contenidos[i] = y->contenidos[T - 1];
    fechas[i] = y->fechas[T - 1];
    horas[i] = y->horas[T - 1];

    numClaves++;
}
