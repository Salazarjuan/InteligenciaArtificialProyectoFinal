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
    profundidadStack.resize(0);
    expandido = false;
}

bool Nodo::esMeta(int valorCasilla){
    if(valorCasilla == 4){
        return true;
    }
    return false;
}

bool Nodo::esMeta(int pos, int mapa[12][12]){
    //cout<<nodo.posI<<" "<<nodo.posJ<<" ";
    //cout<<mapa[nodo.posI][nodo.posJ]<<endl;

    if(mapa[profundidadStack[pos].posI][profundidadStack[pos].posJ] == 4){
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
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1)){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Izquierda");
                amplitud.push_back(nodoIzquierda);
            }
            if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1)){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Abajo");
                amplitud.push_back(nodoAbajo);
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
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }else{
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }

    //amplitud.erase(amplitud.begin() + i);
    amplitud.at(i).expandido = true;
    for(int j = 0; j < amplitud.size(); j++){
        if(amplitud.at(j).expandido == false){
            if(amplitud.at(j).costo < menor){
                menor = amplitud.at(j).costo;
                i = j;

            }
        }
    }
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        //cout << mapa[amplitud.at(i).posI][amplitud.at(i).posJ] << endl;
        //cout << amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<< endl;
        if(amplitud.at(i).municion > 0){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI - 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI + 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }else{
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI - 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI + 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }

        //amplitud.erase(amplitud.begin() + i);
        menor = 99999999;
        amplitud.at(i).expandido = true;
        for(int j = 0; j < amplitud.size(); j++){
            if(amplitud.at(j).expandido == false){
                if(amplitud.at(j).costo < menor){
                    menor = amplitud.at(j).costo;
                    i = j;

                }
            }
        }

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

void Nodo::expandirPorCostoUniformeCD(int posI, int posJ, int municion, int mapa[12][12]){
    amplitud.clear();
    int i = 0;
    int menor = 9999999999;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);

    if(raiz.municion > 0){
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }else{
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }

    //amplitud.erase(amplitud.begin() + i);
    amplitud.at(i).expandido = true;
    for(int j = 0; j < amplitud.size(); j++){
        if(amplitud.at(j).expandido == false){
            if(amplitud.at(j).costo < menor){
                menor = amplitud.at(j).costo;
                i = j;

            }
        }
    }
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        //cout << mapa[amplitud.at(i).posI][amplitud.at(i).posJ] << endl;
        //cout << amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<< endl;
        if(amplitud.at(i).municion > 0){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }else{
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }

        //amplitud.erase(amplitud.begin() + i);
        menor = 99999999;
        amplitud.at(i).expandido = true;
        for(int j = 0; j < amplitud.size(); j++){
            if(amplitud.at(j).expandido == false){
                if(amplitud.at(j).costo < menor){
                    menor = amplitud.at(j).costo;
                    i = j;

                }
            }
        }

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

void Nodo::expandirPorPreferenteProfundidadSD(int posI, int posJ, int municion, int mapa[12][12]){
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");

    raiz.expandido = true;
    int i = 0, ultimaPos = 0;

    if((mapa[raiz.posI + 1][raiz.posJ] != 1)){
        Nodo nodoAbajo(raiz.posI + 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Abajo");
        profundidadStack.push_back(nodoAbajo);
    }
    if((mapa[raiz.posI][raiz.posJ - 1] != 1)){
        Nodo nodoIzquierda(raiz.posI, raiz.posJ - 1, municion, &raiz, raiz.profundidad + 1, 0, "Izquierda");
        profundidadStack.push_back(nodoIzquierda);
    }
    if(mapa[raiz.posI][raiz.posJ] != 1){
        Nodo nodoArriba(raiz.posI - 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Arriba");
        profundidadStack.push_back(nodoArriba);
    }
    if((mapa[raiz.posI][raiz.posJ + 1] != 1)){
        Nodo nodoDerecha(raiz.posI, raiz.posJ + 1, municion, &raiz, raiz.profundidad + 1, 0, "Derecha");
        profundidadStack.push_back(nodoDerecha);
    }

    for(int j = 0; j < profundidadStack.size(); j++){
        (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
    }

    while(!esMeta(ultimaPos, mapa)){
        for(int j = 0; j < profundidadStack.size(); j++){
            (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
        }

        profundidadStack[ultimaPos].expandido = true;

        if((mapa[profundidadStack[ultimaPos].posI + 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI + 1)){
            Nodo nodoAbajo(profundidadStack[ultimaPos].posI + 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Abajo");
            profundidadStack.push_back(nodoAbajo);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ - 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ - 1)){
            Nodo nodoIzquierda(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ - 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Izquierda");
            profundidadStack.push_back(nodoIzquierda);
        }
        if((mapa[profundidadStack[ultimaPos].posI - 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI - 1)){
            Nodo nodoArriba(profundidadStack[ultimaPos].posI - 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Arriba");
            profundidadStack.push_back(nodoArriba);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ + 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ + 1)){
            Nodo nodoDerecha(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ + 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Derecha");
            profundidadStack.push_back(nodoDerecha);

        }

        i++;
        if(i > 10000){
            cout<<"demasiadas iteraciones";
            break;
        }
    }

    cout<<"Meta encontrada: "<<profundidadStack[ultimaPos].posI<<" "<<profundidadStack[ultimaPos].posJ<<" "<<profundidadStack[ultimaPos].profundidad<<endl;

    Nodo solucion = profundidadStack[ultimaPos];
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

void Nodo::expandirPorPreferenteProfundidadCD(int posI, int posJ, int municion, int mapa[12][12]){
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");

    raiz.expandido = true;
    int i = 0, ultimaPos = 0;

    if((mapa[raiz.posI + 1][raiz.posJ] != 1)){
        Nodo nodoAbajo(raiz.posI + 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Abajo");
        profundidadStack.push_back(nodoAbajo);
    }
    if((mapa[raiz.posI][raiz.posJ - 1] != 1)){
        Nodo nodoIzquierda(raiz.posI, raiz.posJ - 1, municion, &raiz, raiz.profundidad + 1, 0, "Izquierda");
        profundidadStack.push_back(nodoIzquierda);
    }
    if(mapa[raiz.posI][raiz.posJ] != 1){
        Nodo nodoArriba(raiz.posI - 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Arriba");
        profundidadStack.push_back(nodoArriba);
    }
    if((mapa[raiz.posI][raiz.posJ + 1] != 1)){
        Nodo nodoDerecha(raiz.posI, raiz.posJ + 1, municion, &raiz, raiz.profundidad + 1, 0, "Derecha");
        profundidadStack.push_back(nodoDerecha);
    }

    for(int j = 0; j < profundidadStack.size(); j++){
        (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
    }

    while(!esMeta(ultimaPos, mapa)){
        for(int j = 0; j < profundidadStack.size(); j++){
            (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
        }

        profundidadStack[ultimaPos].expandido = true;

        if((mapa[profundidadStack[ultimaPos].posI + 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI + 1)){
            Nodo nodoAbajo(profundidadStack[ultimaPos].posI + 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Abajo");
            profundidadStack.push_back(nodoAbajo);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ - 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ - 1)){
            Nodo nodoIzquierda(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ - 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Izquierda");
            profundidadStack.push_back(nodoIzquierda);
        }
        if((mapa[profundidadStack[ultimaPos].posI - 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI - 1)){
            Nodo nodoArriba(profundidadStack[ultimaPos].posI - 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Arriba");
            profundidadStack.push_back(nodoArriba);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ + 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ + 1)){
            Nodo nodoDerecha(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ + 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Derecha");
            profundidadStack.push_back(nodoDerecha);

        }

        i++;
        if(i > 10000){
            cout<<"demasiadas iteraciones";
            break;
        }
    }

    cout<<"Meta encontrada: "<<profundidadStack[ultimaPos].posI<<" "<<profundidadStack[ultimaPos].posJ<<" "<<profundidadStack[ultimaPos].profundidad<<endl;

    Nodo solucion = profundidadStack[ultimaPos];
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


bool Nodo::yaVisitado(Nodo nodo){
    Nodo unNodo = nodo;
    while(unNodo.padre != NULL){
        unNodo = * unNodo.padre;
        if(unNodo.posI == nodo.posI && unNodo.posJ == nodo.posJ){
            return true;
        }
    }
    return false;
}

