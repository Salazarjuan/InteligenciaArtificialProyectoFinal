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

    nodosCreados.resize(0);
    amplitud.resize(0);

}

Mapa::~Mapa()
{
    delete ui;
}

void Mapa::on_abrir_btn_clicked()
{
    int municion = 0;

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            mapa[i][j] = 1;
        }
    }

    std::string ruta = QFileDialog::getOpenFileName(this,tr("Open File"),"C:/Users/juanjose/Desktop/",
                                               tr("text (*.txt)")).toStdString();

    ifstream imputFile(ruta);
    imputFile >> municion;

    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            imputFile >> mapa[i][j];
        }
    }

    //cout << municion << endl;

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }
}

void Mapa::busquedaPorAmplitud(){

}

void Mapa::posicionActual()
{
    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            if(mapa[i][j] == 2){
                posI = i;
                posJ = j;
                break;
            }
        }
    }
}































