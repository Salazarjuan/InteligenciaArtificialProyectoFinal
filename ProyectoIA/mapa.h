#ifndef MAPA_H
#define MAPA_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include "nodo.h"

namespace Ui {
class Mapa;
}

class Mapa : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mapa(QWidget *parent = 0);
    ~Mapa();
    int mapa[12][12];
    int posI;
    int posJ;
    std::vector<Nodo> nodosCreados;
    std::vector<Nodo> amplitud;
    void busquedaPorAmplitud();
    void posicionActual();

private slots:
    void on_abrir_btn_clicked();

private:
    Ui::Mapa *ui;
};

#endif // MAPA_H
