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
    pVista vistaTest1 = Utili::crea<Vista>(
        "Test 1",
        Area{
            OrigineArea{25,25},
            DimensioneArea{500,500}
        }
    );

    pEtichetta etichettaTitolo1  = Oggetto::crea<Etichetta>(
    		vistaTest1,
			ID_1,
			"Test Vista",
			OrigineArea{200,0},
			ARANCIONE,
			TipoCarattere::TIMES_ROMAN_24
	);
    etichettaTitolo1->colora(ROSSO,ColoreComponente::BORDO);
    etichettaTitolo1->abilita(ColoreComponente::BORDO, true);

    etichettaTitolo1->colora(NERO,ColoreComponente::SFONDO);
    etichettaTitolo1->abilita(ColoreComponente::SFONDO,true);
/*
 *
    pEtichetta etichettaDescrizione1  = Oggetto::crea<Etichetta>(
        	vistaTest1,
    		ID_2,
    		"Teste sulla vista:\n "
    		"verifica la corretta implementazione delle barre laterali di scorrimento,\n"
    		"quando i componenti aggiunti sono fuori dal campo visivo predefinito della\n"
    		"finestra.",
    		OrigineArea{200,80},
    		ROSSO,
    		TipoCarattere::GENERICO_GRANDE
    );
*/
    pCampo campo1  = Oggetto::crea<Campo>(vistaTest1,ID_3,OrigineArea{-100,-140},(size_t)15,Maschera{"**/**/****",'*'});
    pCampo campo2  = Oggetto::crea<Campo>(vistaTest1,ID_4,OrigineArea{600,700},(size_t)15);


    pAreaTesto area1 = Oggetto::crea<AreaTesto>(vistaTest1,ID_5,OrigineArea{-200,700},(size_t)30,(size_t)6);
    app.aggiungiVista(vistaTest1);


    app.esegui();


    return 0;
}

