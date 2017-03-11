#include "nodo.h"

Nodo::Nodo()
{

}

Nodo::Nodo(int posI, int posJ, int municion, Nodo* padre, int profundidad, int costo, std::string operacion){
    this->posI = posI;
    this->posJ = posJ;
    this->municion = municion;
    this->padre = padre;
    this->profundidad = profundidad;
    this->costo = costo;
    this->operacion = operacion;
    amplitud.resize(0);
}

bool Nodo::esMeta(int valorCasilla){
    if(valorCasilla == 4){
        return true;
    }
    return false;
}

void Nodo::expandirPorAmplitudSD(int posI, int posJ, int municion, int mapa[12][12]){
    amplitud.clear();
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);
    int i = 0;
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        //cout << mapa[amplitud.at(i).posI][amplitud.at(i).posJ] << endl;
        if(amplitud.at(i).padre == NULL){
            if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1)){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Arriba");
                amplitud.push_back(nodoArriba);
                //cout << nodoArriba.posI << nodoArriba.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1)){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Izquierda");
                amplitud.push_back(nodoIzquierda);
                //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1)){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Abajo");
                amplitud.push_back(nodoAbajo);
                //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1)){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }
        }else{
            if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1) && (amplitud.at(i).padre->posI != amplitud.at(i).posI - 1)){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Arriba");
                amplitud.push_back(nodoArriba);
                //cout << nodoArriba.posI << nodoArriba.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1)){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Izquierda");
                amplitud.push_back(nodoIzquierda);
                //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1) && (amplitud.at(i).padre->posI != amplitud.at(i).posI + 1)){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Abajo");
                amplitud.push_back(nodoAbajo);
                //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1)){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }
        }
        i++;
        //cout << profundidad << endl;
    }
    cout<<i<<" "<<amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<<" "<<amplitud.at(i).profundidad<<endl;

    Nodo solucion = amplitud.at(i);
    Nodo * padres = solucion.padre;
    while(padres->padre != NULL){
        cout << padres->posI << "\t" << padres->posJ << endl;
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            cout << padres->posI << "\t" << padres->posJ << endl;
        }

    }
    cout << padres->posI << "\t" << padres->posJ << endl;


}

void Nodo::expandirPorAmplitudCD(int posI, int posJ, int municion, int mapa[12][12]){
    amplitud.clear();
    int i = 0;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        //cout << mapa[amplitud.at(i).posI][amplitud.at(i).posJ] << endl;

        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Arriba");
            amplitud.push_back(nodoArriba);
            //cout << nodoArriba.posI << nodoArriba.posJ << endl;
        }
        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Izquierda");
            amplitud.push_back(nodoIzquierda);
            //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
        }
        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Abajo");
            amplitud.push_back(nodoAbajo);
            //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
        }
        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Derecha");
            amplitud.push_back(nodoDerecha);
            //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
        }
        i++;
        //cout << profundidad << endl;
    }
    cout<<i<<" "<<amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<<endl;

    Nodo solucion = amplitud.at(i);
    Nodo * padres = solucion.padre;
    while(padres->padre != NULL){
        //cout << solucion.posI << "\t" << solucion.posJ << endl;
        padres = padres->padre;
    }
}

void Nodo::expandirPorCostoUniformeSD(int posI, int posJ, int municion, int mapa[12][12]){
    amplitud.clear();
    int i = 0;
    int menor = 9999999999;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);

    if(raiz.municion > 0){
        if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3)){
            Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
            amplitud.push_back(nodoArriba);
            //cout << nodoArriba.posI << nodoArriba.posJ << endl;
        }else if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
            amplitud.push_back(nodoArriba);
            //cout << nodoArriba.posI << nodoArriba.posJ << endl;
        }
        if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3)){
            Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
            amplitud.push_back(nodoDerecha);
            //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
        }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
            amplitud.push_back(nodoDerecha);
            //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
        }
        if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3)){
            Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
            amplitud.push_back(nodoAbajo);
            //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
        }else if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
            amplitud.push_back(nodoAbajo);
            //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
        }
        if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3)){
            Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
            amplitud.push_back(nodoIzquierda);
            //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
        }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
            amplitud.push_back(nodoIzquierda);
            //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
        }
    }else{
        if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3)){
            Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Arriba");
            amplitud.push_back(nodoArriba);
            //cout << nodoArriba.posI << nodoArriba.posJ << endl;
        }else if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
            amplitud.push_back(nodoArriba);
            //cout << nodoArriba.posI << nodoArriba.posJ << endl;
        }
        if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3)){
            Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Derecha");
            amplitud.push_back(nodoDerecha);
            //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
        }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
            amplitud.push_back(nodoDerecha);
            //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
        }
        if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3)){
            Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Abajo");
            amplitud.push_back(nodoAbajo);
            //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
        }else if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
            amplitud.push_back(nodoAbajo);
            //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
        }
        if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3)){
            Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Izquierda");
            amplitud.push_back(nodoIzquierda);
            //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
        }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
            amplitud.push_back(nodoIzquierda);
            //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
        }
    }


    amplitud.erase(amplitud.begin() + i);

    for(int j = 0; j < amplitud.size(); j++){
        if(amplitud.at(j).costo < menor){
            menor = amplitud.at(j).costo;
            i = j;
        }
    }


    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        //cout << mapa[amplitud.at(i).posI][amplitud.at(i).posJ] << endl;

        if(amplitud.at(i).municion > 0){
            if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ]  == 3) && (amplitud.at(i).padre->posI != amplitud.at(i).posI - 1)){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Arriba");
                amplitud.push_back(nodoArriba);
                //cout << nodoArriba.posI << nodoArriba.posJ << endl;
            }else if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Arriba");
                amplitud.push_back(nodoArriba);
                //cout << nodoArriba.posI << nodoArriba.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1]  == 3) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1)){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ]  == 3) && (amplitud.at(i).padre->posI != amplitud.at(i).posI + 1)){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Abajo");
                amplitud.push_back(nodoAbajo);
                //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
            }else if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Abajo");
                amplitud.push_back(nodoAbajo);
                //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1]  == 3) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1)){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Izquierda");
                amplitud.push_back(nodoIzquierda);
                //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
            }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Izquierda");
                amplitud.push_back(nodoIzquierda);
                //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
            }
        }else{
            if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3) && (amplitud.at(i).padre->posI != amplitud.at(i).posI - 1)){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 5, "Arriba");
                amplitud.push_back(nodoArriba);
                //cout << nodoArriba.posI << nodoArriba.posJ << endl;
            }else if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Arriba");
                amplitud.push_back(nodoArriba);
                //cout << nodoArriba.posI << nodoArriba.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1)){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 5, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3) && (amplitud.at(i).padre->posI != amplitud.at(i).posI + 1)){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 5, "Abajo");
                amplitud.push_back(nodoAbajo);
                //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
            }else if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Abajo");
                amplitud.push_back(nodoAbajo);
                //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1)){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 5, "Izquierda");
                amplitud.push_back(nodoIzquierda);
                //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
            }else if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).padre->costo + 1, "Izquierda");
                amplitud.push_back(nodoIzquierda);
                //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
            }
        }
        amplitud.erase(amplitud.begin() + i);

        for(int j = 0; j < amplitud.size(); j++){
            if(amplitud.at(j).costo < menor){
                menor = amplitud.at(j).costo;
                i = j;
            }
        }

    }
    cout<<i<<" "<<amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<<" "<<amplitud.at(i).profundidad<<endl;
    /*
    Nodo solucion = amplitud.at(i);
    Nodo * padres = solucion.padre;
    while(padres->padre != NULL){
        cout << padres->posI << "\t" << padres->posJ << endl;
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            cout << padres->posI << "\t" << padres->posJ << endl;
        }
    }
    cout << padres->posI << "\t" << padres->posJ << endl;*/

}

void Nodo::expandirPorCostoUniformeCD(int posI, int posJ, int municion, int mapa[12][12]){
    amplitud.clear();
}




