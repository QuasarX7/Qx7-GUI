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
const size_t ID_5 = 1003;
const size_t ID_4 = 1004;
const size_t ID_6 = 1005;
const size_t ID_7 = 1006;
const size_t ID_8 = 1007;
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
			"Questa è una bellissima vista",
			OrigineArea{200,0},
			ARANCIONE,
			TipoCarattere::TIMES_ROMAN_24
	);
    etichettaTitolo1->colora(ROSSO,ColoreComponente::BORDO);
    etichettaTitolo1->abilita(ColoreComponente::BORDO, true);

    etichettaTitolo1->colora(NERO,ColoreComponente::SFONDO);
    etichettaTitolo1->abilita(ColoreComponente::SFONDO,true);


    pEtichetta etichettaDescrizione1  = Oggetto::crea<Etichetta>(
        	vistaTest1,
    		ID_2,
    		"Teste sulla vista:\n "
    		"verifica la corretta implementazione delle barre laterali di scorrimento,\n"
    		"quando i componenti aggiunti sono fuori dal campo visivo predefinito della\n"
    		"finestra.",
    		OrigineArea{200,80},
    		ROSSO,
    		TipoCarattere::GENERICO_GRANDE,
			(size_t)15

    );

    etichettaDescrizione1->colora(BLU,ColoreComponente::SFONDO);
    etichettaDescrizione1->abilita(ColoreComponente::SFONDO,true);

    pCampo campo1  = Oggetto::crea<Campo>(vistaTest1,ID_3,OrigineArea{-100,-140},(size_t)15,Maschera{"**/**/****",'*'});
    pCampo campo2  = Oggetto::crea<Campo>(vistaTest1,ID_4,OrigineArea{600,700},(size_t)15);


    pAreaTesto area1 = Oggetto::crea<AreaTesto>(vistaTest1,ID_5,OrigineArea{-200,700},(size_t)30,(size_t)6);
    app.aggiungiVista(vistaTest1);

    pVista vistaTest2 = Utili::crea<Vista>(
		"Test 2",
		Area{
			OrigineArea{150,50},
			DimensioneArea{500,800}
		},
		NERO,
		BIANCO
	);
    pEtichetta etichettaTitolo2  = Oggetto::crea<Etichetta>(
			vistaTest2,
			ID_6,
			"SOMMA 2 NUMERI",
			OrigineArea{200,0},
			BIANCO,
			TipoCarattere::TIMES_ROMAN_24
	);


    pEtichetta etichettaCampoNumero1 = Oggetto::crea<Etichetta>(
			vistaTest2,
			ID_7,
			"A = ",
			OrigineArea{50,150},
			BLU,
			TipoCarattere::TIMES_ROMAN_24
	);

    pCampo campoNumero1  = Oggetto::crea<Campo>(
    		vistaTest2,
			ID_8,
			OrigineArea{200,150},
			(size_t)15
	);

    pEtichetta etichettaCampoNumero2 = Oggetto::crea<Etichetta>(
			vistaTest2,
			ID_9,
			"B = ",
			OrigineArea{50,200},
			BLU,
			TipoCarattere::TIMES_ROMAN_24
	);

	pCampo campoNumero2  = Oggetto::crea<Campo>(
			vistaTest2,
			ID_10,
			OrigineArea{200,200},
			(size_t)15
	);


    app.aggiungiVista(vistaTest2);

    app.esegui();


    return 0;
}

