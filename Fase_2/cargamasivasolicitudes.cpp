#include "cargamasivasolicitudes.h"
#include <nlohmann/json.hpp>
#include <QFile>
#include <QDebug>
#include <QTextStream>

using json = nlohmann::json;

CargaMasivaSolicitudes::CargaMasivaSolicitudes(ArbolAVL* arbol, ListaRelaciones* listaDeRelaciones, Grafo* grafo)
    : arbol(arbol), listaDeRelaciones(listaDeRelaciones), grafo(grafo) {}

void CargaMasivaSolicitudes::cargarDesdeJson(const QString& rutaArchivo) {
    qDebug() << "Iniciando carga masiva de solicitudes desde archivo:" << rutaArchivo;

    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo:" << rutaArchivo;
        return;
    }

    QTextStream in(&archivo);
    QString contenido = in.readAll();
    archivo.close();

    qDebug() << "Contenido del archivo JSON:" << contenido;

    // Parsear el contenido JSON
    json j;
    try {
        j = json::parse(contenido.toStdString());
    } catch (const std::exception& e) {
        qDebug() << "Error al parsear el JSON:" << e.what();
        return;
    }

    // Iterar sobre las solicitudes y realizar las acciones correspondientes
    for (const auto& solicitudJson : j) {
        QString emisor = QString::fromStdString(solicitudJson["emisor"]);
        QString receptor = QString::fromStdString(solicitudJson["receptor"]);
        QString estado = QString::fromStdString(solicitudJson["estado"]);

        qDebug() << "Procesando solicitud - Emisor:" << emisor << ", Receptor:" << receptor << ", Estado:" << estado;

        NodoAVL* nodoEmisor = arbol->buscarNodo(arbol->getRaiz(), emisor.toStdString());
        NodoAVL* nodoReceptor = arbol->buscarNodo(arbol->getRaiz(), receptor.toStdString());

        if (nodoEmisor == nullptr) {
            qDebug() << "Error: nodoEmisor no encontrado";
            continue;
        }

        if (nodoReceptor == nullptr) {
            qDebug() << "Error: nodoReceptor no encontrado";
            continue;
        }

        Usuario* usuarioEmisor = nodoEmisor->usuario;
        Usuario* usuarioReceptor = nodoReceptor->usuario;

        if (estado == "PENDIENTE") {
            // Verificar si ya existe una solicitud pendiente recibida en la pila del receptor
            if (usuarioReceptor->getPila().buscar(emisor.toStdString(), receptor.toStdString(), "PENDIENTE") != nullptr) {
                qDebug() << "Error: Ya existe una solicitud pendiente recibida por el receptor.";
                continue;
            }

            // Verificar si ya existe una solicitud pendiente enviada en la lista del emisor
            if (usuarioEmisor->getListaEnviados().buscar(emisor.toStdString(), receptor.toStdString()) != nullptr) {
                qDebug() << "Error: Ya existe una solicitud pendiente enviada al receptor.";
                continue;
            }

            // Verificar si ya existe una solicitud pendiente recibida en la pila del emisor
            if (usuarioEmisor->getPila().buscar(receptor.toStdString(), emisor.toStdString(), "PENDIENTE") != nullptr) {
                qDebug() << "Error: Ya existe una solicitud pendiente recibida del receptor.";
                continue;
            }

            // Verificar si ya existe una solicitud pendiente enviada en la lista del receptor
            if (usuarioReceptor->getListaEnviados().buscar(receptor.toStdString(), emisor.toStdString()) != nullptr) {
                qDebug() << "Error: Ya existe una solicitud pendiente enviada por el receptor.";
                continue;
            }

            // Agregar el nodo a la pila del destinatario
            qDebug() << "Agregando a la pila del receptor";
            usuarioReceptor->getPila().agregar(emisor.toStdString(), receptor.toStdString(), "PENDIENTE");

            // Agregar el nodo a la lista enlazada del emisor
            qDebug() << "Agregando a la lista de enviados del emisor";
            usuarioEmisor->getListaEnviados().agregar(emisor.toStdString(), receptor.toStdString(), "PENDIENTE");
        } else if (estado == "ACEPTADA") {
            // Realizar las acciones necesarias para solicitudes aceptadas
            qDebug() << "Procesando solicitud aceptada";

            // Agregar el usuario receptor a la lista de relaciones del emisor
            Relaciones* relacionEmisor = listaDeRelaciones->buscarOCrear(emisor.toStdString());
            relacionEmisor->amistades.agregar(receptor.toStdString());

            // Agregar el usuario emisor a la lista de relaciones del receptor
            Relaciones* relacionReceptor = listaDeRelaciones->buscarOCrear(receptor.toStdString());
            relacionReceptor->amistades.agregar(emisor.toStdString());

            // Agregar la arista en el grafo
            grafo->agregarArista(emisor.toStdString(), receptor.toStdString());

            qDebug() << "Relación de amistad agregada entre" << emisor << "y" << receptor;
        }
    }

    // Mostrar la lista de relaciones al final del proceso
    qDebug() << "Lista de relaciones después de la carga masiva:";
    listaDeRelaciones->mostrar();

    qDebug() << "Carga de solicitudes completada.";
}
