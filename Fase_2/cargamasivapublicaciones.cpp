#include "cargamasivapublicaciones.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

using json = nlohmann::json;

CargaMasivaPublicaciones::CargaMasivaPublicaciones(ListaDoble* listaDoble)
    : listaDoble(listaDoble) {}

void CargaMasivaPublicaciones::cargarDesdeJson(const QString& rutaArchivo) {
    qDebug() << "Iniciando carga masiva de publicaciones desde archivo:" << rutaArchivo;

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

    // Iterar sobre las publicaciones y realizar las acciones correspondientes
    for (const auto& publicacionJson : j) {
        QString correo = QString::fromStdString(publicacionJson["correo"]);
        QString contenido = QString::fromStdString(publicacionJson["contenido"]);
        QString fecha = QString::fromStdString(publicacionJson["fecha"]);
        QString hora = QString::fromStdString(publicacionJson["hora"]);
        QString pathimagen = ""; // Asumimos que no hay pathimagen en el JSON

        qDebug() << "Insertando publicación - Correo:" << correo << ", Contenido:" << contenido << ", Fecha:" << fecha << ", Hora:" << hora;

        // Insertar la publicación en la lista doblemente enlazada
        listaDoble->insertar(correo.toStdString(), contenido.toStdString(), fecha.toStdString(), hora.toStdString(), pathimagen.toStdString());

        // Obtener el nodo recién insertado
        NodoLista* nodoPublicacion = listaDoble->obtenerUltimoNodo();

        // Verificar si el nodoPublicacion es válido
        if (nodoPublicacion == nullptr) {
            qDebug() << "Error: nodoPublicacion es nullptr después de la inserción.";
            continue;
        }

        qDebug() << "Nodo de publicación insertado correctamente.";

        // Iterar sobre los comentarios y agregarlos al árbol B de comentarios
        for (const auto& comentarioJson : publicacionJson["comentarios"]) {
            QString correoComentario = QString::fromStdString(comentarioJson["correo"]);
            QString comentario = QString::fromStdString(comentarioJson["comentario"]);
            QString fechaComentario = QString::fromStdString(comentarioJson["fecha"]);
            QString horaComentario = QString::fromStdString(comentarioJson["hora"]);

            qDebug() << "Insertando comentario - Correo:" << correoComentario << ", Comentario:" << comentario << ", Fecha:" << fechaComentario << ", Hora:" << horaComentario;

            // Insertar el comentario en el árbol B de comentarios
            nodoPublicacion->comentarios.insertar(correoComentario.toStdString(), comentario.toStdString(), fechaComentario.toStdString(), horaComentario.toStdString());
        }
    }

    qDebug() << "Carga de publicaciones completada.";
}
