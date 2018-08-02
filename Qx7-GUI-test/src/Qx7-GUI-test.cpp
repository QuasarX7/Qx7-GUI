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
#include "campo_numerico.h"
#include "pulsante.h"
#include "area_testo.h"
#include "pannello.h"
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
const size_t ID_13 = 3012;
const size_t ID_14 = 3013;


int main(int argc, char* argv[]) {

    Applicazione app(argc,argv);

    /* test 1 */

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


    /* test 2 */

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

    pCampoNumerico campoNumero1  = Oggetto::crea<CampoNumerico>(
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

	pCampoNumerico campoNumero2 = Oggetto::crea<CampoNumerico>(
			vistaTest2,
			ID_10,
			OrigineArea{200,200},
			(size_t)15
	);

	pCampoNumerico campoNumero3 = Oggetto::crea<CampoNumerico>(
				vistaTest2,
				ID_13,
				OrigineArea{200,250},
				(size_t)15
		);
	app.aggiungiVista(vistaTest2);

	pPulsante pulsante = Oggetto::crea<Pulsante>(
			vistaTest2,
			ID_14,
			"Somma",
			OrigineArea{50,250}
    );

	CodiceAzione clic = [](pVista vista){
		pCampoNumerico operando1 = vista->componente<CampoNumerico>(ID_8);
		pCampoNumerico operando2 = vista->componente<CampoNumerico>(ID_10);

		pCampoNumerico risultato = vista->componente<CampoNumerico>(ID_13);
		double somma = operando1->valore() + operando2->valore();
		risultato->testo(std::to_string(somma));
	};

	pulsante->comportamentoClick(clic);

	/* test 3 */

	pVista vistaTest3 = Utili::crea<Vista>(
			"Test 3",
			Area{
				OrigineArea{250,150},
				DimensioneArea{500,800}
			},
			ARANCIONE,
			ROSSO
		);
	pEtichetta etichettaTitolo3  = Oggetto::crea<Etichetta>(
			vistaTest3,
			ID_11,
			"Vista Panello",
			OrigineArea{200,0},
			BLU,
			TipoCarattere::HELVETICA_18
	);


	pPannello pannello1 = Oggetto::crea<Pannello>(
			vistaTest3,
			"pannello test",
			Area{
				OrigineArea{90,150},
				DimensioneArea{100,150}
			}
	);

	pPannello pannello2 = Oggetto::crea<Pannello>(
				vistaTest3,
				"pannello test2",
				Area{
					OrigineArea{250,100},
					DimensioneArea{100,150}
				}
		);
// /*
	pEtichetta etichettaPannello  = Oggetto::crea<Etichetta>(
				pannello1,
				ID_12,
				"Pannello",
				OrigineArea{10,100},
				BLU,
				TipoCarattere::GENERICO_PICCOLO
		);
// */
    app.aggiungiVista(vistaTest3);

    app.esegui();


    return 0;
}

