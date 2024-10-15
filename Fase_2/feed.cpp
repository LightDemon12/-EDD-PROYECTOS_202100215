#include "feed.h"
#include "mainview.h"
#include "ui_feed.h"
#include <QDebug>
#include <QMessageBox> // Incluir QMessageBox
#include "matriz.h"
#include "ventana.h" // Incluir la cabecera de la nueva ventana
#include <QGraphicsPixmapItem>
#include <QPixmap>

Feed::Feed(QWidget *parent, ArbolAVL* arbol, const QString& currentUserEmail, MatrizDispersa* matriz, ListaRelaciones* listaRelaciones, ListaDoble* listaDoble, ArbolBinarioCompleto* arbolBinarioCompleto, Grafo* grafo):
    QDialog(parent),
    ui(new Ui::Feed),
    arbol(arbol),
    currentUserEmail(currentUserEmail),
    matriz(matriz),
    listaRelaciones(listaRelaciones), // Inicializar el puntero a la lista de relaciones
    listaDoble(listaDoble), // Inicializar el puntero a ListaDoble
    ventana(nullptr), // Inicializar la nueva ventana
    arbolBinarioCompleto(arbolBinarioCompleto), // Inicializa el árbol binario completo
    grafo(grafo)


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
    scene = new QGraphicsScene(this);
    ui->graphicsViewfeed->setScene(scene);

}

Feed::~Feed()
{
    delete ui;
}

void Feed::wheelEvent(QWheelEvent* event)
{
    const double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        ui->graphicsViewfeed->scale(scaleFactor, scaleFactor);
    } else {
        ui->graphicsViewfeed->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
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

    // Agregar el usuario actual a la lista de relaciones del emisor
    Relaciones* relacionEmisor = listaRelaciones->buscar(emisor);
    if (relacionEmisor == nullptr) {
        listaRelaciones->agregar(emisor);
        relacionEmisor = listaRelaciones->buscar(emisor);
    }
    relacionEmisor->amistades.agregar(currentUserEmail.toStdString());

    // Agregar el emisor a la lista de relaciones del usuario actual
    Relaciones* relacionActual = listaRelaciones->buscar(currentUserEmail.toStdString());
    if (relacionActual == nullptr) {
        listaRelaciones->agregar(currentUserEmail.toStdString());
        relacionActual = listaRelaciones->buscar(currentUserEmail.toStdString());
    }
    relacionActual->amistades.agregar(emisor);

    // Crear una arista en el grafo entre el emisor y el receptor
    grafo->agregarArista(emisor, currentUserEmail.toStdString());

    // Actualizar las tablas correspondientes
    usuarioActual->getPila().mostrarEnTabla(ui->tablepila);
    usuarioEmisor->getListaEnviados().mostrarEnTabla(ui->tableenviados);

    // Mostrar las listas de relaciones
    qDebug() << "Lista de relaciones del usuario actual:";
    relacionActual->amistades.mostrar();
    //qDebug() << "Lista de relaciones del emisor:";
    //relacionEmisor->amistades.mostrar();

    // Mostrar mensaje de confirmación
    QMessageBox::information(this, "Solicitud Aceptada", "La solicitud ha sido aceptada exitosamente.");
}


void Feed::on_ButtonPublicaciones_clicked()
{
    if (!ventana) {
        ventana = new class ventana(this, arbol, currentUserEmail, matriz, listaRelaciones, listaDoble, arbolBinarioCompleto); // Pasa el puntero de arbolBinarioCompleto
    }

    ventana->show();
    ventana->raise();
    ventana->activateWindow();
}

void Feed::on_ButtonSugerenias_clicked()
{
    if (grafo == nullptr) {
        QMessageBox::warning(this, "Error", "El grafo no está disponible.");
        return;
    }

    // Obtener sugerencias de amigos para el usuario actual
    auto sugerencias = grafo->sugerirAmigos(currentUserEmail.toStdString());

    // Construir el mensaje con las sugerencias
    QString info = "Sugerencias de amigos para " + currentUserEmail + ":\n";
    qDebug() << "Generando sugerencias para:" << currentUserEmail;
    for (const auto& par : sugerencias) {
        info += "\nSugerencia: " + QString::fromStdString(par.first) + "\nAmigos en común:\n";
        qDebug() << "Sugerencia:" << QString::fromStdString(par.first);
        for (const auto& amigoEnComun : par.second) {
            info += " - " + QString::fromStdString(amigoEnComun) + "\n";
            qDebug() << "Amigo en común:" << QString::fromStdString(amigoEnComun);
        }
    }

    // Mostrar las sugerencias en un QMessageBox
    qDebug() << "Mostrando sugerencias en QMessageBox";
    qDebug() << info;
    QMessageBox::information(this, "Sugerencias de Amigos", info);

    // Llamar a la función mostrarGrafoConColores con el currentUserEmail
    grafo->mostrarGrafoConColores(currentUserEmail.toStdString());

    // Limpiar el graphicsViewfeed
    ui->graphicsViewfeed->scene()->clear();

    // Cargar la imagen generada en el graphicsViewfeed
    QPixmap pixmap("grafo_colores.png");
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar la imagen del grafo.");
        return;
    }

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->graphicsViewfeed->setScene(scene);
    ui->graphicsViewfeed->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Feed::on_Mostrar_clicked()
{
    qDebug() << "Mostrar button clicked";

    // Buscar el nodo del usuario actual en el árbol AVL
    NodoAVL* nodoActual = arbol->buscarNodo(arbol->getRaiz(), currentUserEmail.toStdString());
    if (nodoActual == nullptr) {
        QMessageBox::warning(this, "Error", "Usuario actual no encontrado.");
        return;
    }

    Usuario* usuarioActual = nodoActual->usuario;

    // Cargar los datos del usuario en los QLineEdit y QDateEdit correspondientes
    ui->Mnombre->setText(QString::fromStdString(usuarioActual->getNombres()));
    ui->Mapellido->setText(QString::fromStdString(usuarioActual->getApellidos()));
    ui->Mcontra->setText(QString::fromStdString(usuarioActual->getContrasena()));

    // Convertir la fecha de nacimiento a QDate y establecerla en QDateEdit
    QString fechaNacimiento = QString::fromStdString(usuarioActual->getFechaNacimiento());
    QDate date = QDate::fromString(fechaNacimiento, "dd/MM/yyyy");
    if (date.isValid()) {
        ui->Mfecha->setDate(date);
    } else {
        QMessageBox::warning(this, "Error", "Fecha de nacimiento inválida.");
    }
}

void Feed::on_Actualizar_clicked()
{
    qDebug() << "Actualizar button clicked";

    // Obtener los datos actualizados de los QLineEdit y QDateEdit
    QString nuevosNombres = ui->Mnombre->text();
    QString nuevosApellidos = ui->Mapellido->text();
    QString nuevaContrasena = ui->Mcontra->text();
    QString nuevaFechaNacimiento = ui->Mfecha->date().toString("dd/MM/yyyy");

    // Verificar si los campos están vacíos
    if (nuevosNombres.isEmpty() || nuevosApellidos.isEmpty() || nuevaContrasena.isEmpty() || nuevaFechaNacimiento.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
        return;
    }

    // Modificar los datos del usuario en el árbol AVL
    bool exito = arbol->modificarUsuario(currentUserEmail.toStdString(), nuevosNombres.toStdString(), nuevosApellidos.toStdString(), nuevaFechaNacimiento.toStdString(), nuevaContrasena.toStdString());

    if (exito) {
        QMessageBox::information(this, "Actualización Exitosa", "Los datos del usuario han sido actualizados exitosamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se pudo actualizar los datos del usuario.");
    }
}
