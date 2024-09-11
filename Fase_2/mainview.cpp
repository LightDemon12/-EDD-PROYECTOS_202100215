#include "mainview.h"
#include "ui_mainview.h"
#include "registro.h"
#include "feed.h" // Incluir la cabecera de la nueva ventana Feed
#include <QDebug>
#include "arbolavl.h"

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
    , registro(nullptr)
    , feed(nullptr) // Inicializar el puntero a la ventana Feed
    , matriz(100, 100) // Inicializar la matriz con 100 filas y 100 columnas
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

    // Obtener los datos de los QLineEdit
    QString correo = ui->LineCorreo->text();
    QString contrasena = ui->LineContra->text();

    // Verificar si algún campo está vacío
    if (correo.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
        return;
    }

    // Verificar si el correo y la contraseña coinciden con "admin"
    if (correo == "admin" && contrasena == "admin") {
        QMessageBox::information(this, "Inicio de Sesión", "Inicio de sesión de administrador exitoso.");
        return;
    }

    // Verificar si el correo y la contraseña coinciden en el árbol AVL
    if (arbol.buscarUsuario(correo.toStdString(), contrasena.toStdString())) {
        QMessageBox::information(this, "Inicio de Sesión", "Inicio de sesión exitoso.");

        // Almacenar el correo electrónico del usuario actual
        currentUserEmail = correo;

        // Crear la ventana Feed si no existe
        if (!feed) {
            feed = new Feed(this, &arbol, currentUserEmail, &matriz); // Pasar el puntero de MainView, el árbol AVL, el correo electrónico y la matriz
            qDebug() << "Feed window instantiated";
        } else {
            feed->setCurrentUserEmail(currentUserEmail); // Actualizar el correo electrónico del usuario actual en la ventana Feed
        }

        // Mostrar la ventana Feed
        feed->show();
        feed->raise(); // Asegurarse de que la ventana esté en el frente
        feed->activateWindow(); // Asegurarse de que la ventana esté activa
        qDebug() << "Feed window shown";

        // Ocultar la ventana principal
        this->hide();
        qDebug() << "MainView window hidden";
    } else {
        QMessageBox::warning(this, "Inicio de Sesión", "Correo o contraseña incorrectos.");
    }
}
