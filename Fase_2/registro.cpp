#include "registro.h"
#include "ui_registro.h"
#include "mainview.h"
#include <QMessageBox>
#include <QDebug>

Registro::Registro(QWidget *parent, ArbolAVL* arbol, MainView* mainView, MatrizDispersa* matriz)
    : QWidget(parent)
    , ui(new Ui::Registro)
    , arbol(arbol)
    , mainView(mainView)
    , matriz(matriz)
    , contadorNodos(0) // Inicializar el contador de nodos
{
    ui->setupUi(this);
    qDebug() << "Registro window created";
}

Registro::~Registro()
{
    delete ui;
}

void Registro::on_ButtonRegistro_clicked()
{
    qDebug() << "ButtonRegistro clicked";

    QString nombre = ui->lineNombre->text();
    QString apellido = ui->lineApellido->text();
    QString correo = ui->lineCorreo->text();
    QString contrasena = ui->lineContra->text();
    QString fechaNacimiento = ui->dateFecha->date().toString("dd/MM/yyyy");

    if (nombre.isEmpty() || apellido.isEmpty() || correo.isEmpty() || contrasena.isEmpty() || fechaNacimiento.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
        return;
    }

    if (arbol->buscar(correo.toStdString())) {
        QMessageBox::warning(this, "Error", "El correo ya está registrado.");
        return;
    }

    Usuario* nuevoUsuario = new Usuario(nombre.toStdString(), apellido.toStdString(), fechaNacimiento.toStdString(), correo.toStdString(), contrasena.toStdString());

    arbol->insertar(nuevoUsuario);

    // Asegurarse de que los índices no son 0
    int fila = contadorNodos > 0 ? contadorNodos : 1; // Empezar en 1 si el contador es 0
    int columna = contadorNodos > 0 ? contadorNodos : 1; // Empezar en 1 si el contador es 0

    matriz->setValor(fila, columna, correo.toStdString());
    contadorNodos++;

    qDebug() << "Usuarios en el árbol AVL (enOrden):";
    arbol->enOrden(arbol->getRaiz());
}

void Registro::on_ButtonSalir_clicked()
{
    // Mostrar la ventana principal
    if (mainView) {
        mainView->show();
    }

    // Cerrar la ventana de registro
    this->close();
}
