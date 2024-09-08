#include "mainview.h"
#include "ui_mainview.h"
#include "registro.h"
#include <QDebug>

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
    , registro(nullptr)
{
    ui->setupUi(this);
    qDebug() << "MainView window created";
}

MainView::~MainView()
{
    delete ui;
}

void MainView::on_Registro_clicked()
{
    qDebug() << "Registro button clicked";

    // Crear la ventana de registro si no existe
    if (!registro) {
        registro = new Registro(nullptr, &arbol, this); // Pasar el puntero de MainView
        qDebug() << "Registro window instantiated";
    }

    // Mostrar la ventana de registro
    registro->show();
    qDebug() << "Registro window shown";

    // Cerrar la ventana principal
    this->close();
    qDebug() << "MainView window closed";
}
