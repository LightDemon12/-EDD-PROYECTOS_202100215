#include "ArbolBinarioCompleto.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <fstream>
#include <stdexcept>
#include <unordered_set>
#include <sstream>

ArbolBinarioCompleto::ArbolBinarioCompleto() : raiz(nullptr) {}

ArbolBinarioCompleto::~ArbolBinarioCompleto() {
    destruir(raiz);
}

void ArbolBinarioCompleto::insertar(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen) {
    insertar(raiz, correo, contenido, fecha, hora, pathimagen);
}

void ArbolBinarioCompleto::insertar(NodoBinarioCompleto*& nodo, const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora, const std::string& pathimagen) {
    if (nodo == nullptr) {
        nodo = new NodoBinarioCompleto(correo, contenido, fecha, hora, pathimagen);
    } else if (fecha < nodo->fecha || (fecha == nodo->fecha && hora < nodo->hora)) {
        insertar(nodo->izquierdo, correo, contenido, fecha, hora, pathimagen);
    } else {
        insertar(nodo->derecho, correo, contenido, fecha, hora, pathimagen);
    }
}

void ArbolBinarioCompleto::destruir(NodoBinarioCompleto* nodo) {
    if (nodo != nullptr) {
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }
}

void ArbolBinarioCompleto::mostrarEnTabla(QTableWidget* tableWidget) {
    tableWidget->setRowCount(0); // Limpia la tabla
    int row = 0;
    mostrarEnTabla(raiz, tableWidget, row);
}

void ArbolBinarioCompleto::mostrarEnTabla(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& row) {
    if (nodo != nullptr) {
        mostrarEnTabla(nodo->izquierdo, tableWidget, row);

        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(row))); // Índice de la publicación
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(nodo->correo)));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(nodo->contenido)));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(nodo->fecha)));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(nodo->hora)));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(nodo->pathimagen)));
        row++;

        mostrarEnTabla(nodo->derecho, tableWidget, row);
    }
}

void ArbolBinarioCompleto::eliminarTodosLosNodos() {
    eliminarTodosLosNodos(raiz);
    raiz = nullptr;
}

void ArbolBinarioCompleto::eliminarTodosLosNodos(NodoBinarioCompleto*& nodo) {
    if (nodo != nullptr) {
        eliminarTodosLosNodos(nodo->izquierdo);
        eliminarTodosLosNodos(nodo->derecho);
        delete nodo;
        nodo = nullptr;
    }
}

NodoBinarioCompleto* ArbolBinarioCompleto::buscarPorIndice(int indice) {
    int currentIndex = 0;
    return buscarPorIndice(raiz, currentIndex, indice);
}

NodoBinarioCompleto* ArbolBinarioCompleto::buscarPorIndice(NodoBinarioCompleto* nodo, int& currentIndex, int targetIndex) {
    if (nodo == nullptr) {
        return nullptr;
    }

    NodoBinarioCompleto* result = buscarPorIndice(nodo->izquierdo, currentIndex, targetIndex);
    if (result != nullptr) {
        return result;
    }

    if (currentIndex == targetIndex) {
        return nodo;
    }
    currentIndex++;

    return buscarPorIndice(nodo->derecho, currentIndex, targetIndex);
}

void ArbolBinarioCompleto::mostrarInordenLimitado(QTableWidget* tableWidget, int limite) {
    int contador = 0;
    tableWidget->setRowCount(0); // Limpiar la tabla
    mostrarInordenLimitado(raiz, tableWidget, contador, limite);
}

void ArbolBinarioCompleto::mostrarInordenLimitado(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& contador, int limite) {
    if (nodo != nullptr && contador < limite) {
        mostrarInordenLimitado(nodo->izquierdo, tableWidget, contador, limite);
        if (contador < limite) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(nodo->correo)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(nodo->contenido)));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(nodo->fecha)));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(nodo->hora)));
            tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(nodo->pathimagen)));
            contador++;
        }
        mostrarInordenLimitado(nodo->derecho, tableWidget, contador, limite);
    }
}

void ArbolBinarioCompleto::mostrarPreordenLimitado(QTableWidget* tableWidget, int limite) {
    int contador = 0;
    tableWidget->setRowCount(0); // Limpiar la tabla
    mostrarPreordenLimitado(raiz, tableWidget, contador, limite);
}

void ArbolBinarioCompleto::mostrarPreordenLimitado(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& contador, int limite) {
    if (nodo != nullptr && contador < limite) {
        if (contador < limite) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(nodo->correo)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(nodo->contenido)));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(nodo->fecha)));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(nodo->hora)));
            tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(nodo->pathimagen)));
            contador++;
        }
        mostrarPreordenLimitado(nodo->izquierdo, tableWidget, contador, limite);
        mostrarPreordenLimitado(nodo->derecho, tableWidget, contador, limite);
    }
}

void ArbolBinarioCompleto::mostrarPostordenLimitado(QTableWidget* tableWidget, int limite) {
    int contador = 0;
    tableWidget->setRowCount(0); // Limpiar la tabla
    mostrarPostordenLimitado(raiz, tableWidget, contador, limite);
}

void ArbolBinarioCompleto::mostrarPostordenLimitado(NodoBinarioCompleto* nodo, QTableWidget* tableWidget, int& contador, int limite) {
    if (nodo != nullptr && contador < limite) {
        mostrarPostordenLimitado(nodo->izquierdo, tableWidget, contador, limite);
        mostrarPostordenLimitado(nodo->derecho, tableWidget, contador, limite);
        if (contador < limite) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(nodo->correo)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(nodo->contenido)));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(nodo->fecha)));
            tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(nodo->hora)));
            tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(nodo->pathimagen)));
            contador++;
        }
    }
}

void ArbolBinarioCompleto::graficarArbol(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escribir el gráfico.");
    }

    archivo << "digraph G {\n";
    archivo << "node [shape=record];\n";
    archivo << "root [label=\"Raíz\", shape=none];\n"; // Nodo raíz
    if (raiz != nullptr) {
        archivo << "root -> \"" << raiz << "\";\n";
        graficarNodo(raiz, archivo);
    }
    archivo << "}\n";

    archivo.close();
}

void ArbolBinarioCompleto::graficarNodo(NodoBinarioCompleto* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        // Nodo de la fecha general
        archivo << "\"" << nodo << "_fecha\" [label=\"Fecha: " << nodo->fecha << "\", shape=ellipse];\n";
        archivo << "\"" << nodo << "_fecha\" -> \"" << nodo << "\";\n";

        // Nodo con la información del nodo
        archivo << "\"" << nodo << "\" [label=\"<f0> " << nodo->correo << "\\n" << nodo->contenido << "\\n" << nodo->hora << "\"];\n";

        if (nodo->izquierdo != nullptr) {
            archivo << "\"" << nodo << "\":f0 -> \"" << nodo->izquierdo << "\":f0;\n";
            graficarNodo(nodo->izquierdo, archivo);
        }
        if (nodo->derecho != nullptr) {
            archivo << "\"" << nodo << "\":f0 -> \"" << nodo->derecho << "\":f0;\n";
            graficarNodo(nodo->derecho, archivo);
        }
    }
}
