#ifndef MAPA_H
#define MAPA_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class Mapa;
}

class Mapa : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mapa(QWidget *parent = 0);
    ~Mapa();

private slots:
    void on_abrir_btn_clicked();

private:
    Ui::Mapa *ui;
};

#endif // MAPA_H
