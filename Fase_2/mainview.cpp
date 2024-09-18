#include "mainview.h"
#include "ui_mainview.h"
#include "registro.h"
#include "feed.h" // Incluir la cabecera de la nueva ventana Feed
#include "admin.h" // Incluir la cabecera de la ventana Admin
#include <QDebug>
#include "arbolavl.h"
#include "ArbolBinarioCompleto.h" // Incluye el archivo de cabecera del árbol binario completo

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
    , registro(nullptr)
    , feed(nullptr)
    , matriz(100, 100)
    , listaRelaciones()
    , listaDoble() // Inicializar listaDoble
    , adminWindow(nullptr),
    arbolBinarioCompleto() // Inicializa el árbol binario completo

{
    ui->setupUi(this);
    qDebug() << "MainView window created";

}

MainView::~MainView()
{
    delete ui;
}
void MainView::insertarUsuario(Usuario* usuario)
{
    arbol.insertar(usuario);
}
void MainView::on_Registro_clicked()
{
    qDebug() << "Registro button clicked";

    // Crear la ventana de registro si no existe
    if (!registro) {
        registro = new Registro(nullptr, &arbol, this, &matriz); // Pasar el puntero de MainView y la matriz
        qDebug() << "Registro window instantiated";
    }

    // Mostrar la ventana de registro
    registro->show();
    qDebug() << "Registro window shown";

    // Ocultar la ventana principal
    this->hide();
    qDebug() << "MainView window hidden";
}

void MainView::on_Inicio_clicked()
{
    qDebug() << "Inicio button clicked";

    QString correo = ui->LineCorreo->text();
    QString contrasena = ui->LineContra->text();

    if (correo.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
        return;
    }

    if (correo == "admin" && contrasena == "admin") {
        QMessageBox::information(this, "Inicio de Sesión", "Inicio de sesión de administrador exitoso.");

        if (!adminWindow) {
            adminWindow = new Admin(this, &arbol, &matriz, &listaRelaciones, &listaDoble, &arbolBinarioCompleto);
            qDebug() << "Admin window instantiated";
        }

        adminWindow->show();
        adminWindow->raise();
        adminWindow->activateWindow();
        qDebug() << "Admin window shown";

        this->hide();
        qDebug() << "MainView window hidden";

        return;
    }

    if (arbol.buscarUsuario(correo.toStdString(), contrasena.toStdString())) {
        QMessageBox::information(this, "Inicio de Sesión", "Inicio de sesión exitoso.");

        currentUserEmail = correo;

        if (!feed) {
            feed = new Feed(this, &arbol, currentUserEmail, &matriz, &listaRelaciones, &listaDoble, &arbolBinarioCompleto); // Pasar el puntero del árbol binario completo
            qDebug() << "Feed window instantiated";
        } else {
            feed->setCurrentUserEmail(currentUserEmail);
        }

        feed->show();
        feed->raise();
        feed->activateWindow();
        qDebug() << "Feed window shown";

        this->hide();
        qDebug() << "MainView window hidden";
    } else {
        QMessageBox::warning(this, "Inicio de Sesión", "Correo o contraseña incorrectos.");
    }
}
