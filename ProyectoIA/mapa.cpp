#include "mapa.h"
#include "ui_mapa.h"


Mapa::Mapa(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mapa)
{
    ui->setupUi(this);

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            mapa[i][j] = 1;
        }
    }
    municion = 0;
    posI = 0;
    posJ = 0;
    ui->no_informada_cb->setEnabled(false);
    ui->informada_cb->setEnabled(false);
}

Mapa::~Mapa()
{
    delete ui;
}

void Mapa::on_abrir_btn_clicked()
{
    std::string ruta = QFileDialog::getOpenFileName(this,tr("Open File"),"C:/Users/juanjose/Desktop/",
                                               tr("text (*.txt)")).toStdString();


    leerMatriz(ruta);
    posicionActual();
    pintarMapa();
}

void Mapa::pintarMapa(){
    srand (time(NULL));
    randomPlayer = randomPlayer = rand() % 3;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            QPixmap imagen;
            if(mapa[i][j] == 0){
                imagen.load("floor.jpg");
            }else if(mapa[i][j] == 1){
                imagen.load("blocks.png");
            }else if(mapa[i][j] == 2){
                if(randomPlayer == 0){
                    imagen.load("jujo.png");
                }else if(randomPlayer == 1){
                    imagen.load("juan_jose.png");
                }else if(randomPlayer == 2){
                    imagen.load("juan_david.png");
                }
            }else if(mapa[i][j] == 3){
                imagen.load("parcial.png");
            }else if(mapa[i][j] == 4){
                imagen.load("5.png");
            }

            QLabel * label = new QLabel();
            label->setPixmap(imagen);
            labels[i][j] = label;

            ui->gridLayout->addWidget(label, i, j, 0);
            ui->gridLayout->update();
        }
    }
}

void Mapa::leerMatriz(std::string ruta){
    ifstream imputFile(ruta);
    imputFile >> municion;

    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            imputFile >> mapa[i][j];
        }
    }
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
    int id = -1;
    LARGE_INTEGER t_ini, t_fin;
    if(ui->informada->isChecked()){
        cout<<"Avara"<<endl;
        id = ui->informada_cb->currentIndex();
        switch (id) {
        case 0:
            cout<<"Avara"<<endl;

            QueryPerformanceCounter(&t_ini); //Inicio del contador de tiempo

            rutaSolucion = nodo->expandirPorBusquedaAvaraSD(posI, posJ, municion, mapa, ui->profundidad, ui->nodos_expandidos);

            QueryPerformanceCounter(&t_fin);//Final del contador de tiempo

            this->tiempo = performancecounter_diff(&t_fin, &t_ini);
            ui->tiempo_ejecucion->setText("Tiempo: " + QString::number(tiempo*1000.0,'g',15) + " ms\n");
            delete nodo;
            nodo = 0;
            break;
        case 1:
            cout<<"A*"<<endl;

            QueryPerformanceCounter(&t_ini); //Inicio del contador de tiempo

            rutaSolucion = nodo->expandirPorAEstrellaSD(posI, posJ, municion, mapa, ui->profundidad, ui->nodos_expandidos);
            QueryPerformanceCounter(&t_fin);//Final del contador de tiempo

            this->tiempo = performancecounter_diff(&t_fin, &t_ini);
            ui->tiempo_ejecucion->setText("Tiempo: " + QString::number(tiempo*1000.0,'g',15) + " ms\n");
            delete nodo;
            nodo = 0;
            break;
        default:
            break;
        }
    }else{
        id = ui->no_informada_cb->currentIndex();
        switch(id){
        case 0:
            cout<<"Amplitud"<<endl;

            QueryPerformanceCounter(&t_ini); //Inicio del contador de tiempo

            rutaSolucion = nodo->expandirPorAmplitudSD(posI, posJ, municion, mapa, ui->profundidad, ui->nodos_expandidos);
            QueryPerformanceCounter(&t_fin);//Final del contador de tiempo

            this->tiempo = performancecounter_diff(&t_fin, &t_ini);
            ui->tiempo_ejecucion->setText("Tiempo: " + QString::number(tiempo*1000.0,'g',15) + " ms\n");
            delete nodo;
            nodo = 0;
            break;
        case 1:
            cout<<"Costo"<<endl;

            QueryPerformanceCounter(&t_ini); //Inicio del contador de tiempo

            rutaSolucion = nodo->expandirPorCostoUniformeSD(posI, posJ, municion, mapa, ui->profundidad, ui->nodos_expandidos);
            QueryPerformanceCounter(&t_fin);//Final del contador de tiempo

            this->tiempo = performancecounter_diff(&t_fin, &t_ini);
            ui->tiempo_ejecucion->setText("Tiempo: " + QString::number(tiempo*1000.0,'g',15) + " ms\n");
            delete nodo;
            nodo = 0;
            break;
        case 2:
            cout<<"Proundidad Sin C"<<endl;

            QueryPerformanceCounter(&t_ini); //Inicio del contador de tiempo

            rutaSolucion = nodo->expandirPorPreferenteProfundidadSC(posI, posJ, municion, mapa, ui->profundidad, ui->nodos_expandidos);
            QueryPerformanceCounter(&t_fin);//Final del contador de tiempo

            this->tiempo = performancecounter_diff(&t_fin, &t_ini);
            ui->tiempo_ejecucion->setText("Tiempo: " + QString::number(tiempo*1000.0,'g',15) + " ms\n");
            delete nodo;
            nodo = 0;
            break;
        }
    }

    pintarRuta();
}

void Mapa::pintarRuta(){
    int rutaPosI[rutaSolucion.size()/2];
    int rutaPosJ[rutaSolucion.size()/2];
    int iterI = rutaSolucion.size()/2 - 1, iterJ = rutaSolucion.size()/2 - 1;
    for (int i = 0; i < rutaSolucion.size(); i++) {
        if(i%2 == 0){
            rutaPosI[iterI] = rutaSolucion[i];
            iterI--;
        }else{
            rutaPosJ[iterJ] = rutaSolucion[i];
            iterJ--;
        }
    }
    for (int i = 0; i < rutaSolucion.size()/2; i++) {
        cout<<rutaPosI[i]<<"\t"<<rutaPosJ[i]<<endl;
    }
    QPixmap imagen, imagenPasto, imagenParcial;

    imagenPasto.load("floor.jpg");
    imagenParcial.load("parcial.png");
    if(randomPlayer == 0){
        imagen.load("jujo.png");
    }else if(randomPlayer == 1){
        imagen.load("juan_jose.png");
    }else if(randomPlayer == 2){
        imagen.load("juan_david.png");
   }
    int k = 0;
    for (int i = 1; i < rutaSolucion.size()/2; i++) {
        labels[rutaPosI[i]][rutaPosJ[i]]->setPixmap(imagen);
        if(mapa[rutaPosI[i-1]][rutaPosJ[i-1]] == 0 || mapa[rutaPosI[i-1]][rutaPosJ[i-1]] == 2){
            labels[rutaPosI[i-1]][rutaPosJ[i-1]]->setPixmap(imagenPasto);
        }else{
            labels[rutaPosI[i-1]][rutaPosJ[i-1]]->setPixmap(imagenParcial);
        }
        ui->gridLayout->update();
        this->repaint();
        for(k = 0; k <30000000;k++);

    }

}

void Mapa::on_pushButton_clicked()
{
    pintarMapa();
    ui->profundidad->setText("Profundidad:");
    ui->nodos_expandidos->setText("Nodos expandidos:");
    ui->tiempo_ejecucion->setText("Tiempo:");
}

void Mapa::on_informada_clicked()
{
    ui->no_informada_cb->setEnabled(false);
    ui->informada_cb->setEnabled(true);

}

void Mapa::on_no_informada_clicked()
{
    ui->informada_cb->setEnabled(false);
    ui->no_informada_cb->setEnabled(true);
}
