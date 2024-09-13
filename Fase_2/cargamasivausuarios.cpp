#include "cargamasivausuarios.h"
#include <nlohmann/json.hpp>
#include <QFile>
#include <QDebug>
#include <QTextStream>

using json = nlohmann::json;

CargaMasivaUsuarios::CargaMasivaUsuarios(ArbolAVL* arbol) : arbol(arbol) {}

void CargaMasivaUsuarios::cargarDesdeJson(const QString& rutaArchivo) {
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo:" << rutaArchivo;
        return;
    }

    QTextStream in(&archivo);
    QString contenido = in.readAll();
    archivo.close();

    // Parsear el contenido JSON
    json j = json::parse(contenido.toStdString());

    // Iterar sobre los usuarios y agregarlos al árbol AVL
    for (const auto& usuarioJson : j) {
        QString nombres = QString::fromStdString(usuarioJson["nombres"]);
        QString apellidos = QString::fromStdString(usuarioJson["apellidos"]);
        QString fechaNacimiento = QString::fromStdString(usuarioJson["fecha_de_nacimiento"]);
        QString correo = QString::fromStdString(usuarioJson["correo"]);
        QString contrasena = QString::fromStdString(usuarioJson["contraseña"]);

        Usuario* usuario = new Usuario(nombres.toStdString(), apellidos.toStdString(), fechaNacimiento.toStdString(), correo.toStdString(), contrasena.toStdString());
        arbol->insertar(usuario);
    }

    // Mostrar los usuarios del árbol AVL
    arbol->enOrden(arbol->getRaiz());
}
