#include "feed.h"
#include "ui_feed.h"
#include <QDebug>
#include <QMessageBox> // Incluir QMessageBox

Feed::Feed(QWidget *parent, ArbolAVL* arbol) :
    QDialog(parent), // Cambiar a QDialog
    ui(new Ui::Feed),
    arbol(arbol) // Inicializar el puntero al árbol AVL
{
    ui->setupUi(this);
    qDebug() << "Feed window setup completed";
}

Feed::~Feed()
{
    delete ui;
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
