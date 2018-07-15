/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7-GUI.                                          *
 *                                                                          *
 * Qx7-GUI è una libreria software gratuita: puoi ridistribuirla e/o        *
 * modificarla sotto i termini della GNU Lesser General Public License come *
 * pubblicato  dalla Free Software Foundation, o la versione 3 della licenza,
 *  o (a tua scelta) qualsiasi versione successiva.                         *
 *                                                                          *
 * Qx7-GUI è distribuita nella speranza che sia utile,                      *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7-OpenGL. Altrimenti, vedi al sito                   *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7-GUI.                                            *
 *                                                                          *
 *   Qx7-GUI is free software: you can redistribute it and/or modify it     *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7-GUI is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7-GUI.  If not, see                            *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/
/**
 * @file applicazione.cpp
 * @author Dr. Domenico della Peruta
 * @date 04-05-2018
 * @version 1.1.1, 15-07-2018
 * 
 * @brief File contenente l'implementazione della classe Applicazione.
 * 
 * @namespace GUI
 * @class Applicazione
 */
#include "applicazione.h"
using namespace GUI;

Applicazione::Applicazione(int argc, char* argv[]){
    gl.inizializza(argc,argv);
}

map<id_finestra,riferimentoVista> Applicazione::viste{};

pVista Applicazione::vistaCorrente(){
    auto id = Finestra::idFinestraCorrente();
    if(id > 0 && id <= viste.size())
        return viste[id].lock();
    return nullptr;
     
 }
 
CodiceScena Applicazione::disegnaVista = []{
    // cancella le informazioni dell'ultimo disegno
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //passaggio al disegno prospettico

    glLoadIdentity(); // rinizializza il disegno

    /* coordinate dell'osservazione */
    Osservatore osservatore{
        Coordinate{0.0,0.0,0.0}, // punto osservatore
        Coordinate{0.0,0.0,-1.0},// punto osservato
        Vettore{0.0,1.0,0.0}     // asse Y = zenit
    };
    osservatore.osserva();

    /* AREA DISEGNO */
    auto vista = vistaCorrente();
    if(vista != nullptr)
    	vista->disegna();

    glutSwapBuffers(); //Inviare la scena 3D allo schermo

};

CodiceSistemaRiferimentoVisivo Applicazione::impostaCameraVista =[](int w, int h){
    // aggiornamento dimensione finestra
    //altezzaApplicazione = h;
    ////lunghezzaApplicazione = w;

    Proiezione2D campo{
        CampoVisivo(0.0,(double)w,(double)h,0.0),
        Area( // finestra visiva
                OrigineArea(0,0),
                DimensioneArea(h,w)
        )
    };
    campo.applica();
    auto vista = vistaCorrente();
    if(vista != nullptr){
    	vista->dimensione(DimensioneArea(h,w));
    	int x,y;
    	Finestra::posizione(x,y);//aggiorna le coordinate correnti
    	vista->posiziona(OrigineArea(x,y));
    }
};

CodiceMuoviMouse Applicazione::mousePassivo = [](int x,int y){
	auto vista = vistaCorrente();
	if(vista != nullptr)
		vista->coordinateMouse.emetti(Cursore(x,y),Stato::Passivo);
};

CodiceMuoviMouse Applicazione::mouseAttivo = [](int x,int y){
	auto vista = vistaCorrente();
	if(vista != nullptr)
		vista->coordinateMouse.emetti(Cursore(x,y),Stato::Attivo);
};

CodiceClicMouse  Applicazione::clic = [](int pulsante, int stato, int x, int y){
    PulsanteMouse pulsanteMouse =
            pulsante == GLUT_LEFT_BUTTON   ? PulsanteMouse::SINISTRO :
            pulsante == GLUT_RIGHT_BUTTON  ? PulsanteMouse::DESTRO :
            pulsante == GLUT_MIDDLE_BUTTON ? PulsanteMouse::CENTRO :
            pulsante == 3                  ? PulsanteMouse::SCORRI_SU :
            pulsante == 4                  ? PulsanteMouse::SCORRI_GIU :
                                           PulsanteMouse::NON_DEFINITO;
    //cout << "->" << pulsante << endl;
    StatoPulsante statoPulsante =
            stato == GLUT_UP ? StatoPulsante::SU : StatoPulsante::GIU;

    auto vista = vistaCorrente();
    if(vista != nullptr)
    	vista->click.emetti(Mouse(pulsanteMouse,statoPulsante, Cursore(x,y)));

};
        
CodiceTastiera Applicazione::tastiera= [](unsigned char tasto, int x, int y){
	auto vista = vistaCorrente();
	if(vista != nullptr)
		vista->tasto.emetti(Tastiera(tasto,Cursore(x,y)));
};
     
CodiceTastieraTastiSpeciali Applicazione::tastieraTastiSpeciali = [](int tasto, int x, int y){
	auto vista = vistaCorrente();
	if(vista != nullptr)
		vista->tastoSpeciale.emetti(Tastiera(tasto,Cursore(x,y)));
};

CodiceMenu Applicazione::menu = []{
	auto vista = vistaCorrente();
	if(vista != nullptr)
		vista->disegnaMenu();
}; 

void Applicazione::aggiungiVista(pVista vista){
    // L' id della "vista" viene generato come l' id delle finestre GLUT
    // cioè come un numero intero che parte da 1.
    // Quiondi la chiave per accedere alla vista della mappa, è l'id della finestra associata.
    // E' il compromesso per inserire i dati della 'vista' all'interno del codice eventi della
    // 'finestra' GLUT. Vedi uso del metodo "vistaCorrente()"
    static size_t id =1; //id prima finestra GLUT
    viste[id++] = vista;
}

void Applicazione::cambiaVistaCorrente(pVista vista){
    viste[Finestra::idFinestraCorrente()] = vista;
}
        
void Applicazione::esegui(){
    gl.eliminaFinestre();
    // creazione delle finestre  GLUT a partire dai dati della vista associata
    for(auto i = viste.begin(); i != viste.end(); ++i){
        auto vista = i->second;
        auto finestra = Utili::crea<Finestra>(
            vista.lock()->titoloFinestra(),
            vista.lock()->dimensione().altezza(),
            vista.lock()->dimensione().lunghezza(),
            vista.lock()->origine().x(),
            vista.lock()->origine().y()
        );
        // associazione del codice eventi GLUT
        finestra->disegna(disegnaVista);
        finestra->camera(impostaCameraVista);
        finestra->inputMouse(mousePassivo,Stato::Passivo);
        finestra->inputMouse(mouseAttivo,Stato::Attivo);
        finestra->inputClic(clic);
        finestra->inputTastiera(tastiera);
        finestra->inputTastieraTastiSpeciali(tastieraTastiSpeciali);
        finestra->aggiungiMenu(menu);
        
        finestre.push_back(finestra);
        gl.aggiungiFinestra(finestra);
    }
    gl.esegui();
}
