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
 * Licenza insieme a Qx7-GUI. Altrimenti, vedi al sito                      *
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
 *   License along with Qx7-GUI.  If not, see                               *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/
/**
 * @file  campo_menu.cpp
 * @author Dr. Domenico della Peruta
 * @date 16-08-2018
 * @version 1.0.0, 16-08-2018
 *
 * @brief File contenente l'implementazione della classe CampoMenu.
 *
 * @namespace GUI
 * @class CampoMenu
 */
#include "campo_menu.h"
using namespace GUI;

CampoMenu::CampoMenu(size_t ID, const OrigineArea& posizione, const vector<string>& listaInput):
		Campo{ID,posizione,lunghezza(listaInput)}
{
	pulsante = Utili::crea<Pulsante>(
			NO_ID,
			"+",
			OrigineArea{
				posizione.x()+area.dimensione().lunghezza()+8,
				posizione.y()+2
			}
	);
	area.dimensione(
			DimensioneArea{
				area.dimensione().altezza(),
				area.dimensione().lunghezza()+pulsante->dimensione().lunghezza()+10
			}
	);
	bordoFocus->dimensiona(
			bordoFocus->altezza(),
			bordoFocus->lunghezza()+pulsante->dimensione().lunghezza()+10
	);
	creaMenu(listaInput);
}

size_t CampoMenu::lunghezza(const vector<string>& lista){
	size_t lung = 0;
	for(string s: lista){
		Testo t{s};
		if(t.numeroCaratteri() > lung)lung=t.numeroCaratteri();
	}
	return lung;
}

void CampoMenu::disegna(){
	glPushMatrix();
    if(pulsante != nullptr){
    	pulsante->sposta(
    			OrigineArea{
    				area.origine().x()+area.dimensione().lunghezza()-pulsante->dimensione().lunghezza()-2,
    				area.origine().y()+2
				}
    	);
    	pulsante->disegna();
    }
    if(listaVisibile)
    	disegnaMenu();
    Campo::disegna();
    glPopMatrix();

}

void CampoMenu::creaMenu(const vector<string>& lista){
	int i=1;
	size_t lunghezzaVoce = lunghezza(lista);
	for(string nomeVoce: lista){
		pEtichetta voceMenu = Utili::crea<Etichetta>(
				NO_ID,
				lunghezzaFissa(nomeVoce,lunghezzaVoce),
				OrigineArea{
					origine().x() ,
					origine().y()+(i++)*19 + 7
				}
		);
		voceMenu->decora(GRIGIO_CHIARO,GRIGIO_SCURO);
		listaMenu.push_back(voceMenu);
	}
}

void CampoMenu::disegnaMenu(){
	int i=1;
	for(pEtichetta voceMenu: listaMenu){
		if(voceMenu != nullptr){
			voceMenu->sposta(
				OrigineArea{
					origine().x(),
					origine().y()+(i++)*19 + 7
				}
			);
			voceMenu->disegna();
		}
	}
}

void CampoMenu::azione(const Mouse& mouse){
	if(eventoLocale(mouse.posizione())){ // campoMenu e pulsante
		assegnaFocus();
		if(pulsante != nullptr){
			if(pulsante->eventoLocale(mouse.posizione())){
				if(mouse.pulsante() == PulsanteMouse::SINISTRO){
					if(mouse.stato() == StatoPulsante::SU){
						listaVisibile = !listaVisibile;//commuta
						if(listaVisibile){
							pulsante->rinomina("-");
							pulsante->colora(ROSSO,ColoreComponente::TESTO);
							pulsante->colora(ROSSO,ColoreComponente::BORDO);
						}else{
							pulsante->rinomina("+");
							pulsante->colora(NERO,ColoreComponente::TESTO);
							pulsante->colora(NERO,ColoreComponente::BORDO);

						}
						glutPostRedisplay();
					}
				}
			}
		}
	}else if(listaVisibile){
		if(mouse.pulsante() == PulsanteMouse::SINISTRO){
			if(mouse.stato() == StatoPulsante::SU){
				for(pEtichetta voceMenu: listaMenu){
					if(voceMenu != nullptr){
						if(voceMenu->eventoLocale(mouse.posizione())){
							listaVisibile = !listaVisibile;//commuta
							if(listaVisibile){
								pulsante->rinomina("-");
								pulsante->colora(ROSSO,ColoreComponente::TESTO);
								pulsante->colora(ROSSO,ColoreComponente::BORDO);
							}else{
								pulsante->rinomina("+");
								pulsante->colora(NERO,ColoreComponente::TESTO);
								pulsante->colora(NERO,ColoreComponente::BORDO);
								testo(voceMenuCorrente);
								voceMenuCorrente = "";
							}
							glutPostRedisplay();
							break;
						}
					}
				}
			}
		}
	}
}

void CampoMenu::passaggioMouse(const Cursore& mouse,Stato stato){
	Campo::passaggioMouse(mouse,stato);
	if(listaVisibile){
		for(pEtichetta voceMenu: listaMenu){
			if(voceMenu != nullptr){
				if(voceMenu->eventoLocale(mouse)){
					voceMenu->decora(GRIGIO_SCURO,NERO);
					voceMenu->colora(BLU,ColoreComponente::TESTO);
					voceMenuCorrente = realeLunghezzaVoce(voceMenu->testo().stringa());
				}else{
					voceMenu->decora(GRIGIO_CHIARO,GRIGIO_SCURO);
				}
			}
		}
	}
}

string CampoMenu::lunghezzaFissa(const string& voce,size_t lunghezzaVoce){
	string stringa = " "+ voce;
	int diff = lunghezzaVoce - Testo{voce}.numeroCaratteri();
	for(auto i=0; i < diff; i++)
		stringa += " ";
	return stringa + " ";
}


string CampoMenu::realeLunghezzaVoce(const string& voce){
	string reale = voce;
	auto i = voce.length()-1;
	for(; i > 0; i--){
		if(voce[i] != ' ')break;
	}
	reale.substr(0,i+1);
	return reale.substr(1,i);
}




