#ifndef MAPA_H
#define MAPA_H


#ifdef WIN32
#include <windows.h>
#endif

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include "nodo.h"
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
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
    void posicionActual();
    std::vector<int> rutaSolucion;

private slots:
    void on_abrir_btn_clicked();
    void on_buscarSolucion_btn_clicked();

    void on_pushButton_clicked();

    void on_informada_clicked();

    void on_no_informada_clicked();

private:
    Ui::Mapa *ui;
    void pintarRuta();
    void pintarMapa();
    void leerMatriz(std::string ruta);
    int randomPlayer;
    QLabel * labels[12][12];
    double tiempo;
    double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b){
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
    }
};

#endif // MAPA_H
