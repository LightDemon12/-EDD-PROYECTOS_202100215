#include "feed.h"
#include "mainview.h"
#include "ui_feed.h"
#include <QDebug>
#include <QMessageBox> // Incluir QMessageBox
#include "matriz.h"

Feed::Feed(QWidget *parent, ArbolAVL* arbol, const QString& email, MatrizDispersa* matriz) :
    QDialog(parent), // Cambiar a QDialog
    ui(new Ui::Feed),
    arbol(arbol), // Inicializar el puntero al árbol AVL
    currentUserEmail(email), // Inicializar el correo electrónico del usuario actual
    matriz(matriz) // Inicializar el puntero a MatrizDispersa

{
    ui->setupUi(this);
    qDebug() << "Feed window setup completed";

    // Configurar las columnas de la tabla
    ui->tableUsuarios->setColumnCount(4);
    QStringList headers = {"Nombre", "Apellido", "Fecha de Nacimiento", "Correo Electrónico"};
    ui->tableUsuarios->setHorizontalHeaderLabels(headers);

    // Configurar las columnas de la tabla de enviados
    ui->tableenviados->setColumnCount(3);
    QStringList headersEnviados = {"Emisor", "Receptor", "Estado"};
    ui->tableenviados->setHorizontalHeaderLabels(headersEnviados);

    // Configurar las columnas de la tabla de enviados
    ui->tablepila->setColumnCount(3);
    QStringList headerspila = {"Emisor", "Receptor", "Estado"};
    ui->tablepila->setHorizontalHeaderLabels(headersEnviados);
}

Feed::~Feed()
{
    delete ui;
}

void Feed::setCurrentUserEmail(const QString& email)
{
    currentUserEmail = email;
}

void Feed::on_ButtonBuscar_clicked()
{
    qDebug() << "ButtonBuscar clicked";

    // Obtener el texto del QLineEdit
    QString correo = ui->lineCorreo->text();

    // Verificar si el campo está vacío
    if (correo.isEmpty()) {
        QMessageBox::warning(this, "Error", "El campo de correo electrónico debe estar lleno.");
        return;
    }

    // Realizar la búsqueda y mostrar la información del usuario
    std::string info = arbol->mostrarUsuario(correo.toStdString());
    if (info.empty()) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado.");
    } else {
        ui->TxtBusqueda->setPlainText(QString::fromStdString(info));
    }
}

void Feed::on_ButtonMostrar_clicked()
{
    qDebug() << "ButtonMostrar clicked";

    // Usar el correo electrónico del usuario actual
    QString correo = currentUserEmail;

    // Realizar la búsqueda y mostrar la información del usuario
    std::string info = arbol->mostrarUsuario(correo.toStdString());
    if (info.empty()) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado.");
    } else {
        ui->TxtBusqueda->setPlainText(QString::fromStdString(info));
    }
}


void Feed::on_ButtonEliminar_clicked()
{
    qDebug() << "ButtonEliminar clicked";

    // Usar el correo electrónico del usuario actual
    QString correo = currentUserEmail;

    // Eliminar el usuario del árbol AVL
    arbol->eliminar(correo.toStdString());
    qDebug() << "Usuario eliminado:" << correo;

    // Mostrar mensaje de confirmación
    QMessageBox::information(this, "Usuario Eliminado", "El usuario ha sido eliminado exitosamente.");

    // Cerrar la ventana Feed y abrir la ventana MainView
    this->close();
    qobject_cast<MainView*>(parent())->show();
}


void Feed::on_ButtonCerrar_clicked()
{
    // Cerrar la ventana Feed y abrir la ventana MainView
    this->close();
    qobject_cast<MainView*>(parent())->show();
}


void Feed::on_Buttonmostrar_clicked()
{

}


void Feed::on_Buttonlista_clicked()
{
    qDebug() << "ButtonMostrar clicked";

    // Limpiar la tabla antes de llenarla
    ui->tableUsuarios->setRowCount(0);

    // Llenar la tabla con los usuarios del árbol AVL
    arbol->enTable(arbol->getRaiz(), ui->tableUsuarios);

    // Ajustar el tamaño de las columnas al contenido
    ui->tableUsuarios->resizeColumnsToContents();
}



void Feed::on_ButtonEnviar_clicked()
{
    qDebug() << "ButtonEnviar clicked";

    // Obtener el correo del receptor del QLineEdit
    QString receptorCorreo = ui->lineEnviar->text();

    // Verificar si el campo está vacío
    if (receptorCorreo.isEmpty()) {
        QMessageBox::warning(this, "Error", "El campo de correo electrónico del receptor debe estar lleno.");
        return;
    }

    // Buscar el nodo del usuario actual en el árbol AVL
    NodoAVL* nodoActual = arbol->buscarNodo(arbol->getRaiz(), currentUserEmail.toStdString());
    if (nodoActual == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario actual no encontrado.");
        return;
    }

    Usuario* usuarioActual = nodoActual->usuario;

    // Buscar el nodo del destinatario en el árbol AVL
    NodoAVL* nodoDestinatario = arbol->buscarNodo(arbol->getRaiz(), receptorCorreo.toStdString());
    if (nodoDestinatario == nullptr) {
        QMessageBox::warning(this, "Error", "Destinatario no encontrado.");
        return;
    }

    Usuario* usuarioDestinatario = nodoDestinatario->usuario;

    // Verificar si ya existe una solicitud recibida en la pila del destinatario
    if (usuarioDestinatario->getPila().buscar(currentUserEmail.toStdString(), receptorCorreo.toStdString(), "PENDIENTE") != nullptr) {
        QMessageBox::warning(this, "Error", "Ya existe una solicitud pendiente recibida por el destinatario.");
        return;
    }

    // Verificar si ya existe una solicitud enviada en la lista del usuario actual
    if (usuarioActual->getListaEnviados().buscar(currentUserEmail.toStdString(), receptorCorreo.toStdString()) != nullptr) {
        QMessageBox::warning(this, "Error", "Ya existe una solicitud pendiente enviada al destinatario.");
        return;
    }

    // Verificar si ya existe una solicitud recibida en la pila del usuario actual
    if (usuarioActual->getPila().buscar(receptorCorreo.toStdString(), currentUserEmail.toStdString(), "PENDIENTE") != nullptr) {
        QMessageBox::warning(this, "Error", "Ya existe una solicitud pendiente recibida del destinatario.");
        return;
    }

    // Verificar si ya existe una solicitud enviada en la lista del destinatario
    if (usuarioDestinatario->getListaEnviados().buscar(receptorCorreo.toStdString(), currentUserEmail.toStdString()) != nullptr) {
        QMessageBox::warning(this, "Error", "Ya existe una solicitud pendiente enviada por el destinatario.");
        return;
    }

    // Agregar el nodo a la pila del destinatario
    usuarioDestinatario->getPila().agregar(currentUserEmail.toStdString(), receptorCorreo.toStdString(), "PENDIENTE");

    // Agregar el nodo a la lista enlazada del usuario actual
    usuarioActual->getListaEnviados().agregar(currentUserEmail.toStdString(), receptorCorreo.toStdString(), "PENDIENTE");

    // Mostrar los datos de la lista enlazada del usuario actual en la tabla
    usuarioActual->getListaEnviados().mostrarEnTabla(ui->tableenviados);

    // Mostrar los datos de la pila del usuario actual en la tabla
    usuarioActual->getPila().mostrarEnTabla(ui->tablepila);

    // Mostrar mensaje de confirmación
    QMessageBox::information(this, "Solicitud Enviada", "La solicitud ha sido enviada exitosamente.");
}

void Feed::on_ButtonActualizar_clicked()
{
    qDebug() << "ButtonActualizar clicked";

    // Buscar el nodo del usuario actual en el árbol AVL
    NodoAVL* nodoActual = arbol->buscarNodo(arbol->getRaiz(), currentUserEmail.toStdString());
    if (nodoActual == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario actual no encontrado.");
        return;
    }

    Usuario* usuarioActual = nodoActual->usuario;

    // Mostrar los datos de la lista enlazada del usuario actual en la tabla
    usuarioActual->getListaEnviados().mostrarEnTabla(ui->tableenviados);
}

void Feed::on_ButtonPila_clicked()
{
    qDebug() << "ButtonPila clicked";

    // Buscar el nodo del usuario actual en el árbol AVL
    NodoAVL* nodoActual = arbol->buscarNodo(arbol->getRaiz(), currentUserEmail.toStdString());
    if (nodoActual == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario actual no encontrado.");
        return;
    }

    Usuario* usuarioActual = nodoActual->usuario;

    // Mostrar los datos de la pila del usuario actual en la tabla
    usuarioActual->getPila().mostrarEnTabla(ui->tablepila);

    // Mostrar los amigos del usuario actual usando la matriz dispersa
    matriz->mostrarAmigos(currentUserEmail.toStdString());
}

void Feed::on_ButtonCancelar_clicked()
{
    qDebug() << "ButtonCancelar clicked";

    // Obtener el índice del QLineEdit
    QString indiceStr = ui->lineEliminar->text();

    // Verificar si el campo está vacío
    if (indiceStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "El campo de índice debe estar lleno.");
        return;
    }

    // Convertir el índice a un número entero
    bool ok;
    int indice = indiceStr.toInt(&ok);

    // Verificar si la conversión fue exitosa y si el índice es válido
    if (!ok || indice <= 0) {
        QMessageBox::warning(this, "Error", "El índice debe ser un número entero válido mayor que 0.");
        return;
    }

    // Restar 1 al índice para ajustarlo a la base 0
    indice -= 1;

    // Buscar el nodo del usuario actual en el árbol AVL
    NodoAVL* nodoActual = arbol->buscarNodo(arbol->getRaiz(), currentUserEmail.toStdString());
    if (nodoActual == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario actual no encontrado.");
        return;
    }

    Usuario* usuarioActual = nodoActual->usuario;

    // Obtener el correo del destinatario de la lista de enviados
    std::string receptorCorreo = usuarioActual->getListaEnviados().obtenerReceptorPorIndice(indice);

    // Buscar el nodo del destinatario en el árbol AVL
    NodoAVL* nodoDestinatario = arbol->buscarNodo(arbol->getRaiz(), receptorCorreo);
    if (nodoDestinatario == nullptr) {
        QMessageBox::warning(this, "Error", "Destinatario no encontrado.");
        return;
    }

    Usuario* usuarioDestinatario = nodoDestinatario->usuario;



    // Eliminar el nodo de la pila del destinatario
    usuarioDestinatario->getPila().eliminarPorIndice(indice);

    // Eliminar el nodo de la lista de enviados del usuario actual
    usuarioActual->getListaEnviados().eliminar(indice);

    // Actualizar las tablas correspondientes
    usuarioActual->getPila().mostrarEnTabla(ui->tablepila);
    usuarioActual->getListaEnviados().mostrarEnTabla(ui->tableenviados);

    // Mostrar mensaje de confirmación
    QMessageBox::information(this, "Solicitud Cancelada", "La solicitud ha sido cancelada exitosamente.");
}
void Feed::on_ButtonRechazar_clicked()
{
    qDebug() << "ButtonRechazar clicked";

    // Obtener el índice del QLineEdit
    QString indiceStr = ui->linesolicitud->text();

    // Verificar si el campo está vacío
    if (indiceStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "El campo de índice debe estar lleno.");
        return;
    }

    // Convertir el índice a un número entero
    bool ok;
    int indice = indiceStr.toInt(&ok);

    // Verificar si la conversión fue exitosa y si el índice es válido
    if (!ok || indice <= 0) {
        QMessageBox::warning(this, "Error", "El índice debe ser un número entero válido mayor que 0.");
        return;
    }

    // Restar 1 al índice para ajustarlo a la base 0
    indice -= 1;

    // Buscar el nodo del usuario actual en el árbol AVL
    NodoAVL* nodoActual = arbol->buscarNodo(arbol->getRaiz(), currentUserEmail.toStdString());
    if (nodoActual == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario actual no encontrado.");
        return;
    }

    Usuario* usuarioActual = nodoActual->usuario;



    // Obtener el emisor del nodo en la pila
    std::string emisor = usuarioActual->getPila().obtenerEmisorPorIndice(indice);

    // Eliminar el nodo de la pila
    usuarioActual->getPila().eliminarPorIndice(indice);

    // Buscar el nodo del emisor en el árbol AVL
    NodoAVL* nodoEmisor = arbol->buscarNodo(arbol->getRaiz(), emisor);
    if (nodoEmisor == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario emisor no encontrado.");
        return;
    }

    Usuario* usuarioEmisor = nodoEmisor->usuario;



    // Eliminar el nodo de la lista de enviados del emisor
    usuarioEmisor->getListaEnviados().eliminar(indice);

    // Actualizar las tablas correspondientes
    usuarioActual->getPila().mostrarEnTabla(ui->tablepila);
    usuarioEmisor->getListaEnviados().mostrarEnTabla(ui->tableenviados);

    // Mostrar mensaje de confirmación
    QMessageBox::information(this, "Solicitud Rechazada", "La solicitud ha sido rechazada exitosamente.");
}

void Feed::on_ButtonAceptar_clicked()
{
    qDebug() << "ButtonAceptar clicked";

    // Obtener el índice del QLineEdit
    QString indiceStr = ui->linesolicitud->text();

    // Verificar si el campo está vacío
    if (indiceStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "El campo de índice debe estar lleno.");
        return;
    }

    // Convertir el índice a un número entero
    bool ok;
    int indice = indiceStr.toInt(&ok);

    // Verificar si la conversión fue exitosa y si el índice es válido
    if (!ok || indice <= 0) {
        QMessageBox::warning(this, "Error", "El índice debe ser un número entero válido mayor que 0.");
        return;
    }

    // Restar 1 al índice para ajustarlo a la base 0
    indice -= 1;

    // Buscar el nodo del usuario actual en el árbol AVL
    NodoAVL* nodoActual = arbol->buscarNodo(arbol->getRaiz(), currentUserEmail.toStdString());
    if (nodoActual == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario actual no encontrado.");
        return;
    }

    Usuario* usuarioActual = nodoActual->usuario;


    // Obtener el emisor del nodo en la pila
    std::string emisor = usuarioActual->getPila().obtenerEmisorPorIndice(indice);

    // Eliminar el nodo de la pila
    usuarioActual->getPila().eliminarPorIndice(indice);

    // Buscar el nodo del emisor en el árbol AVL
    NodoAVL* nodoEmisor = arbol->buscarNodo(arbol->getRaiz(), emisor);
    if (nodoEmisor == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario emisor no encontrado.");
        return;
    }

    Usuario* usuarioEmisor = nodoEmisor->usuario;


    // Eliminar el nodo de la lista de enviados del emisor
    usuarioEmisor->getListaEnviados().eliminar(indice);

    // Marcar la intersección en la matriz dispersa
    //matriz->marcarInterseccion(currentUserEmail.toStdString(), emisor);

    // Generar el reporte de la matriz dispersa
    //matriz->generarReporte("matriz_usuarios.dot");

    // Actualizar las tablas correspondientes
    usuarioActual->getPila().mostrarEnTabla(ui->tablepila);
    usuarioEmisor->getListaEnviados().mostrarEnTabla(ui->tableenviados);

    // Mostrar mensaje de confirmación
    QMessageBox::information(this, "Solicitud Aceptada", "La solicitud ha sido aceptada exitosamente.");
}