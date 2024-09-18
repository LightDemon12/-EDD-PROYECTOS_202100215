#include "admin.h"
#include "ui_admin.h"
#include <QFileDialog>
#include <QDebug>
#include "mainview.h" // Incluir la declaración completa de MainView


Admin::Admin(QWidget *parent, ArbolAVL* arbol, MatrizDispersa* matriz, ListaRelaciones* listaRelaciones, ListaDoble* listaDoble, ArbolBinarioCompleto* arbolBinarioCompleto) :
    QDialog(parent),
    ui(new Ui::Admin),
    arbol(arbol),
    matriz(matriz),
    listaRelaciones(listaRelaciones),
    listaDoble(listaDoble),
    arbolBinarioCompleto(arbolBinarioCompleto) // Inicializa el árbol binario completo

{
    ui->setupUi(this);
    cargaMasivaUsuarios = new CargaMasivaUsuarios(arbol);
    cargaMasivaSolicitudes = new CargaMasivaSolicitudes(arbol, listaRelaciones);
    cargaMasivaPublicaciones = new CargaMasivaPublicaciones(listaDoble); // Inicializar cargaMasivaPublicaciones
}
Admin::~Admin()
{
    delete ui;
    delete cargaMasivaUsuarios;
    delete cargaMasivaSolicitudes;
    delete cargaMasivaPublicaciones; // Liberar memoria
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

