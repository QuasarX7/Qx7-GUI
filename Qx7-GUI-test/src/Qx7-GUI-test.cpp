/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Ninja
 *
 * Created on 14 gennaio 2018, 9.09
 */
#include <memory>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "applicazione.h"
#include "etichetta.h"
#include "campo.h"
#include "pulsante.h"
#include "area_testo.h"
using namespace GUI;

using namespace Grafica;

const size_t ID_1 = 1000;
const size_t ID_2 = 1001;
const size_t ID_3 = 1002;
const size_t ID_5 = 1005;
const size_t ID_4 = 1008;
const size_t ID_6 = 1009;
const size_t ID_9 = 1019;
const size_t ID_10 = 3000;
const size_t ID_11 = 3001;
const size_t ID_12 = 3011;



int main(int argc, char* argv[]) {

    Applicazione app(argc,argv);
    pVista vista = Utili::crea<Vista>(
        "O.o",
        Area{
            OrigineArea{25,25},
            DimensioneArea{500,500}
        }
    );
    pVista vista2 = Utili::crea<Vista>(
        "^_^",
        Area{
            OrigineArea{100,100},
            DimensioneArea{400,800}
        }
        ,BLU

    );

    pVista vista3 = Utili::crea<Vista>(
        ".....",
        Area{
            OrigineArea{200,200},
            DimensioneArea{500,500}
        },
        GIALLO,
         ROSSO
    );
    pEtichetta etichetta  = Oggetto::crea<Etichetta>(vista2,ID_1,"Prima Etichetta",OrigineArea{-100,200},ROSSO,TipoCarattere::TIMES_ROMAN_24);
    pEtichetta etichetta2 = Oggetto::crea<Etichetta>(vista2,ID_2,"Prima Etichetta",OrigineArea{250,100},ROSSO,TipoCarattere::TIMES_ROMAN_24);
    pEtichetta etichetta3 = Oggetto::crea<Etichetta>(vista3,ID_3,"Prima Etichetta",OrigineArea{100,200},ROSSO,TipoCarattere::TIMES_ROMAN_24);

    pCampo campo  = Oggetto::crea<Campo>(vista,ID_4,OrigineArea{-100,-140},(size_t)15,Maschera{"**/**/****",'*'});
    pCampo campo2 = Oggetto::crea<Campo>(vista2,ID_5,OrigineArea{100,100},(size_t)15);
    pCampo campo3 = Oggetto::crea<Campo>(vista2,ID_6,OrigineArea{100,200},(size_t)15);
    pCampo campo4 = Oggetto::crea<Campo>(vista2,ID_12,OrigineArea{-100,-400},(size_t)15);

    pAreaTesto area = Oggetto::crea<AreaTesto>(vista2,ID_11,OrigineArea{100,270},(size_t)10,(size_t)5);
    campo3->comportamentoFocusAcquisito(
        [](pVista vista){
            pCampo campo3 = vista->componente<Campo>(ID_6);
            pCampo campo2 = vista->componente<Campo>(ID_5);
            campo3->testo(campo2->testo());
        }
    );

    pPulsante pulsante = Oggetto::crea<Pulsante>(vista2,ID_10,"ciao mond",Area{300,270,15,80});
    //pulsante->colora(NERO,BIANCO,ROSSO);
    pulsante->comportamentoClick(
        [](pVista vista){
            pCampo campo2 = vista->componente<Campo>(ID_5);
            pCampo campo3 = vista->componente<Campo>(ID_6);

            campo2->testo(campo3->testo());
        }
    );




    auto xxx = [](int x){
        switch (x) {
            case 100:
                cout << "ciao mondo"<< endl;
                break;
            case 101:
                cout << "pippoooo"<< endl;
                break;
            case 200:
                cout << "maria"<< endl;
                break;

            case 201:
                cout << "gigginooooo"<< endl;
                break;
            case 300:
                cout << "ok"<< endl;
                break;
            case 600:
                cout << ":'("<< endl;

                break;
            case 601:
                cout << "xxxxxxxxxxx"<< endl;
                break;
            default:
                break;
        }
    };

    pMenu menu = crea<Menu>(xxx);
    menu->aggiungiVoce(100, "ciao mondo");
    menu->aggiungiVoce(101, "pippo");
    menu->aggiungiVoce(0, "_____");

    pMenu sm = Oggetto::crea<Menu>(menu,"maria");
    sm->aggiungiVoce(200, "mariaaa");
    sm->aggiungiVoce(201, "luigi");

    menu->aggiungiVoce(600, ":'(");


    pMenu sx = Oggetto::crea<Menu>(menu,"xxxxx");
    sx->aggiungiVoce(601,"ciaoooo mondo X");


    vista->aggiungi(menu);


    app.aggiungiVista(vista);
    app.aggiungiVista(vista2);
    app.aggiungiVista(vista3);


    app.esegui();


    return 0;
}

