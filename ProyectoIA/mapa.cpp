#include "mapa.h"
#include "ui_mapa.h"

Mapa::Mapa(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mapa)
{
    ui->setupUi(this);
    for (int i = 0; i < 12; i++) {
        QPixmap imagen("Imagenes/floor.jpg");
        imagen = imagen.scaled(60,60);
        for (int j = 0; j < 12; j++) {

            QLabel * label = new QLabel();
            label->setPixmap(imagen);
            ui->gridLayout->addWidget(label, i, j, 0);
        }
    }

}

Mapa::~Mapa()
{
    delete ui;
}
