#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "arbolavl.h"

// Forward declaration
class Registro;

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = nullptr);
    ~MainView();

private slots:
    void on_Registro_clicked();

private:
    Ui::MainView *ui;
    Registro *registro;
    ArbolAVL arbol;
};

#endif // MAINVIEW_H
