#ifndef FEED_H
#define FEED_H

#include <QDialog>
#include "arbolavl.h" // Incluir la cabecera del árbol AVL

namespace Ui {
class Feed;
}

class Feed : public QDialog
{
    Q_OBJECT

public:
    explicit Feed(QWidget *parent = nullptr, ArbolAVL* arbol = nullptr); // Pasar el puntero del árbol AVL
    ~Feed();

private slots:
    void on_ButtonBuscar_clicked();

private:
    Ui::Feed *ui;
    ArbolAVL* arbol; // Puntero al árbol AVL
};

#endif // FEED_H
