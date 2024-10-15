#include "admin.h"
#include "ui_admin.h"
#include <QFileDialog>
#include <QDebug>
#include "mainview.h" // Incluir la declaración completa de MainView
#include <QPixmap>
#include <fstream>
#include "Grafo.h" // Incluir la clase Grafo
#include <QWheelEvent>


Admin::Admin(QWidget *parent, ArbolAVL* arbol, MatrizDispersa* matriz, ListaRelaciones* listaRelaciones, ListaDoble* listaDoble, ArbolBinarioCompleto* arbolBinarioCompleto, Grafo* grafo) :
    QDialog(parent),
    ui(new Ui::Admin),
    arbol(arbol),
    matriz(matriz),
    listaRelaciones(listaRelaciones),
    listaDoble(listaDoble),
    arbolBinarioCompleto(arbolBinarioCompleto), // Inicializa el árbol binario completo
    grafo(grafo), // Inicializa el grafo
    scene(new QGraphicsScene(this)), // Inicializa la escena gráfica
    pixmapItem(new QGraphicsPixmapItem()) // Inicializa el item del pixmap
{
    ui->setupUi(this);
    cargaMasivaUsuarios = new CargaMasivaUsuarios(arbol, grafo); // Inicializar cargaMasivaUsuarios
    cargaMasivaSolicitudes = new CargaMasivaSolicitudes(arbol, listaRelaciones, grafo); // Inicializar cargaMasivaSolicitudes
    cargaMasivaPublicaciones = new CargaMasivaPublicaciones(listaDoble); // Inicializar cargaMasivaPublicaciones

    // Configurar la vista gráfica
    ui->graphicsView->setScene(scene);
    scene->addItem(pixmapItem);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}
Admin::~Admin()
{
    delete ui;
    delete cargaMasivaUsuarios;
    delete cargaMasivaSolicitudes;
    delete cargaMasivaPublicaciones; // Liberar memoria
}

void Admin::wheelEvent(QWheelEvent* event)
{
    const double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        ui->graphicsView->scale(scaleFactor, scaleFactor);
    } else {
        ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void Admin::on_ButtonCU_clicked()
{
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Abrir archivo JSON", "", "Archivos JSON (*.json)");
    if (rutaArchivo.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }

    qDebug() << "Archivo seleccionado para carga masiva de usuarios:" << rutaArchivo;

    cargaMasivaUsuarios->cargarDesdeJson(rutaArchivo);
}

void Admin::on_ButtonCS_clicked()
{
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Abrir archivo JSON", "", "Archivos JSON (*.json)");
    if (rutaArchivo.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }

    qDebug() << "Archivo seleccionado para carga masiva de solicitudes:" << rutaArchivo;

    cargaMasivaSolicitudes->cargarDesdeJson(rutaArchivo);

    // Obtener sugerencias de amigos para el usuario con el correo "carlos.gomez@example.com"
    auto sugerencias = grafo->sugerirAmigos("carlos.gomez@example.com");

    // Mostrar las sugerencias en la consola
    qDebug() << "Sugerencias de amigos para carlos.gomez@example.com:";
    grafo->mostrarSugerencias(sugerencias);
}

void Admin::on_pushButton_clicked()
{
    // Cerrar la ventana de Admin y abrir la ventana MainView
    this->close();
    qobject_cast<MainView*>(parent())->show();
}


void Admin::on_ButtonCPlu_clicked()
{
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Abrir archivo JSON", "", "Archivos JSON (*.json)");
    if (rutaArchivo.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }

    qDebug() << "Archivo seleccionado para carga masiva de publicaciones:" << rutaArchivo;

    cargaMasivaPublicaciones->cargarDesdeJson(rutaArchivo);

    listaDoble->mostrar();
}

void Admin::on_ButtonCerrar_clicked()
{
    // Cerrar la ventana Feed y abrir la ventana MainView
    this->close();
    qobject_cast<MainView*>(parent())->show();
}


void Admin::on_ButtonAVL_clicked()
{
    if (arbol == nullptr || arbol->getRaiz() == nullptr) {
        qDebug() << "El árbol AVL está vacío o no está inicializado.";
        return;
    }

    // Llamar al método para graficar el árbol AVL
    std::string nombreArchivo = "arbolAVL.dot";
    arbol->graficarArbolAVL(nombreArchivo);

    // Verificar si el archivo PNG se generó correctamente
    std::ifstream archivo(nombreArchivo + ".png");
    if (!archivo.good()) {
        qDebug() << "No se pudo generar la imagen del árbol AVL.";
        return;
    }
    archivo.close();

    // Cargar la imagen generada en el QLabel
    QPixmap pixmap(QString::fromStdString(nombreArchivo + ".png"));
    if (pixmap.isNull()) {
        qDebug() << "No se pudo cargar la imagen del árbol AVL.";
        return;
    }
    ui->labelAVL->setPixmap(pixmap);
    ui->labelAVL->setScaledContents(true); // Ajustar la imagen al tamaño del QLabel
}

void Admin::on_ButtonAVL_2_clicked()
{
    if (listaDoble == nullptr || listaDoble->obtenerUltimoNodo() == nullptr) {
        qDebug() << "La lista doblemente enlazada está vacía o no está inicializada.";
        return;
    }

    // Llamar al método para graficar la lista doblemente enlazada
    std::string nombreArchivo = "listaDoble.dot";
    listaDoble->graficarListaDoble(nombreArchivo);

    // Verificar si el archivo PNG se generó correctamente
    std::ifstream archivo(nombreArchivo + ".png");
    if (!archivo.good()) {
        qDebug() << "No se pudo generar la imagen de la lista doblemente enlazada.";
        return;
    }
    archivo.close();

    // Cargar la imagen generada en el QGraphicsView
    QPixmap pixmap(QString::fromStdString(nombreArchivo + ".png"));
    if (pixmap.isNull()) {
        qDebug() << "No se pudo cargar la imagen de la lista doblemente enlazada.";
        return;
    }

    // Limpiar cualquier imagen que se esté mostrando en el QGraphicsView
    ui->graphicsView->scene()->clear();

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio); // Ajustar la imagen al tamaño del QGraphicsView
}

void Admin::on_ButtonenOrden_clicked()
{
    if (arbol == nullptr || arbol->getRaiz() == nullptr) {
        qDebug() << "El árbol AVL está vacío o no está inicializado.";
        return;
    }

    // Limpiar la tabla
    ui->tableOrden->setRowCount(0);

    // Definir los encabezados de la tabla
    QStringList headers = {"Nombre", "Apellido", "Fecha de Nacimiento", "Correo Electrónico"};
    ui->tableOrden->setColumnCount(headers.size());
    ui->tableOrden->setHorizontalHeaderLabels(headers);

    // Llamar al método enOrden para llenar la tabla
    arbol->enOrden(arbol->getRaiz(), ui->tableOrden);
}

void Admin::on_ButtonpostOrden_clicked()
{
    if (arbol == nullptr || arbol->getRaiz() == nullptr) {
        qDebug() << "El árbol AVL está vacío o no está inicializado.";
        return;
    }

    // Limpiar la tabla
    ui->tableOrden->setRowCount(0);

    // Definir los encabezados de la tabla
    QStringList headers = {"Nombre", "Apellido", "Fecha de Nacimiento", "Correo Electrónico"};
    ui->tableOrden->setColumnCount(headers.size());
    ui->tableOrden->setHorizontalHeaderLabels(headers);

    // Llamar al método postOrden para llenar la tabla
    arbol->postOrden(arbol->getRaiz(), ui->tableOrden);
}

void Admin::on_ButtonpreOrden_clicked()
{
    if (arbol == nullptr || arbol->getRaiz() == nullptr) {
        qDebug() << "El árbol AVL está vacío o no está inicializado.";
        return;
    }

    // Limpiar la tabla
    ui->tableOrden->setRowCount(0);

    // Definir los encabezados de la tabla
    QStringList headers = {"Nombre", "Apellido", "Fecha de Nacimiento", "Correo Electrónico"};
    ui->tableOrden->setColumnCount(headers.size());
    ui->tableOrden->setHorizontalHeaderLabels(headers);

    // Llamar al método preOrden para llenar la tabla
    arbol->preOrden(arbol->getRaiz(), ui->tableOrden);
}

void Admin::on_Buttonmostrar_clicked()
{
    qDebug() << "ButtonMostrar clicked";

    // Limpiar la tabla antes de llenarla
    ui->tableOrden->setRowCount(0);

    // Definir los encabezados de la tabla
    QStringList headers = {"Nombre", "Apellido", "Fecha de Nacimiento", "Correo Electrónico"};
    ui->tableOrden->setColumnCount(headers.size());
    ui->tableOrden->setHorizontalHeaderLabels(headers);

    // Llenar la tabla con los usuarios del árbol AVL
    arbol->enTable(arbol->getRaiz(), ui->tableOrden);

    // Ajustar el tamaño de las columnas al contenido
    ui->tableOrden->resizeColumnsToContents();
}

void Admin::on_ButonBuscar_clicked()
{
    qDebug() << "ButtonBuscar clicked";

    // Obtener el correo electrónico del QLineEdit
    QString correo = ui->lineCorreo->text();

    // Llamar a la función mostrarUsuario del árbol AVL
    std::string info = arbol->mostrarUsuario(correo.toStdString());

    // Mostrar la información del usuario en el QTextEdit
    if (!info.empty()) {
        ui->UsuariTxt->setPlainText(QString::fromStdString(info));
    } else {
        ui->UsuariTxt->setPlainText("Usuario no encontrado.");
    }
}


void Admin::on_ButtonGrafo_clicked()
{
    // Llamar al método para generar la imagen del grafo
    grafo->mostrarGrafo();

    // Cargar la imagen generada en el QGraphicsView
    QPixmap pixmap("grafo.png");
    if (pixmap.isNull()) {
        qDebug() << "No se pudo cargar la imagen del grafo.";
        return;
    }

    // Limpiar cualquier imagen que se esté mostrando en el QGraphicsView
    if (ui->graphicsView->scene()) {
        ui->graphicsView->scene()->clear();
    }

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio); // Ajustar la imagen al tamaño del QGraphicsView
}

void Admin::on_ButtonLista_clicked()
{
    // Llamar al método para generar la imagen de la lista de adyacencia
    grafo->graficarListaAdyacencia("listaAdyacencia");

    // Cargar la imagen generada en el QGraphicsView
    QPixmap pixmap("listaAdyacencia.png");
    if (pixmap.isNull()) {
        qDebug() << "No se pudo cargar la imagen de la lista de adyacencia.";
        return;
    }

    // Limpiar cualquier imagen que se esté mostrando en el QGraphicsView
    if (ui->graphicsView->scene()) {
        ui->graphicsView->scene()->clear();
    }

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio); // Ajustar la imagen al tamaño del QGraphicsView
}

void Admin::on_pushButton1_clicked()
{

}

