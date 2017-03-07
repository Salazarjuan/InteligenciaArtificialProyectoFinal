#ifndef MAPA_H
#define MAPA_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include "nodo.h"
#include <QFileDialog>
#include <fstream>
#include <iostream>

using namespace std;

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
    int municion;
    void busquedaPorAmplitud();
    void posicionActual();

private slots:
    void on_abrir_btn_clicked();

    void on_buscarSolucion_btn_clicked();

private:
    Ui::Mapa *ui;
};

#endif // MAPA_H
