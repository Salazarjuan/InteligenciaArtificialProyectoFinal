#include "mapa.h"
#include "ui_mapa.h"


Mapa::Mapa(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mapa)
{
    ui->setupUi(this);
    for (int i = 0; i < 12; i++) {
        QPixmap imagen("floor.jpg");
        imagen = imagen.scaled(60,60);
        for (int j = 0; j < 12; j++) {

            QLabel * label = new QLabel();
            label->setPixmap(imagen);
            ui->gridLayout->addWidget(label, i, j, 0);
        }
    }

    municion = 0;
    posI = 0;
    posJ = 0;

}

Mapa::~Mapa()
{
    delete ui;
}

void Mapa::on_abrir_btn_clicked()
{

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

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }

    posicionActual();
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

void Mapa::on_buscarSolucion_btn_clicked()
{
    Nodo * nodo = new Nodo();
    //nodo->expandirPorAmplitudSD(posI, posJ, municion, mapa);


    int id = ui->busquedas_cb->currentIndex();

    switch(id){
    case 0:
        cout<<"Amplitud SD"<<endl;
        nodo->expandirPorAmplitudSD(posI, posJ, municion, mapa);
        delete nodo;
        nodo = 0;
        break;
    case 1:
        cout<<"Amplitud CD"<<endl;
        nodo->expandirPorAmplitudCD(posI, posJ, municion, mapa);
        delete nodo;
        nodo = 0;
        break;
    case 2:
        cout<<"Costo SD"<<endl;
        nodo->expandirPorCostoUniformeSD(posI, posJ, municion, mapa);
        delete nodo;
        nodo = 0;
        break;
    case 3:
        cout<<"Costo CD"<<endl;
        nodo->expandirPorCostoUniformeCD(posI, posJ, municion, mapa);
        delete nodo;
        nodo = 0;
        break;
    case 4:
        cout<<"Profundidad Con C"<<endl;
        nodo->expandirPorPreferenteProfundidadSD(posI, posJ, municion, mapa);
        delete nodo;
        nodo = 0;
        break;
    case 5:
        cout<<"Proundidad Sin C"<<endl;
        nodo->expandirPorPreferenteProfundidadCD(posI, posJ, municion, mapa);
        break;
    case 6:
        cout<<"Buen intento"<<"Avara SD"<<endl;
        nodo->expandirPorBusquedaAvaraSD(posI, posJ, municion, mapa);
        break;
    case 7:
        cout<<"Buen intento"<<"A* SD"<<endl;
        nodo->expandirPorAEstrellaSD(posI, posJ, municion, mapa);
        break;
    case 8:
        cout<<"Buen intento"<<"A* CD"<<endl;
        nodo->expandirPorAEstrellaCD(posI, posJ, municion, mapa);
        break;
    }


}
