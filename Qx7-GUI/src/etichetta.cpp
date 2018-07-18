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
 * Licenza insieme a Qx7-GUI. Altrimenti, vedi al sito                   *
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
 * @file componente.h
 * @author Dr. Domenico della Peruta
 * @date 
 * @version 1.0.0, 
 * 
 * @brief File contenente l'implementazione dei metodi della classe Etichetta.
 * 
 * @namespace GUI
 * @class Etichetta
 */
#include "etichetta.h"
#include "vista.h"
using namespace GUI;


Etichetta::Etichetta(size_t ID, const string& testo, const OrigineArea& posizione, const Colore& colore, TipoCarattere font)
:  Componente{ID, Area{posizione, DimensioneArea{0,0} } }
{
	coloreTesto = colore;
    stringa = Utili::crea<Stringa>(
        testo,
        Punto(area.origine().x(),area.origine().y()+Stringa::altezzaCarattere(font)*0.75),
        colore
    );
    stringa->carattere(font);
}

void Etichetta::disegnaSfondo(const Colore& vista){
	if(abilitaSfondo || abilitaBordo){
    	pRettangolo sfondo = Utili::crea<Rettangolo>(
				abilitaSfondo == false ? vista : coloreSfondo,
				abilitaBordo  == false ? vista : coloreBordo,
				area
		);
    	sfondo->bordo(2.0);
    	sfondo->disegna();
	}
}

void Etichetta::abilita(ColoreComponente colore,bool applica){
	if(colore == ColoreComponente::BORDO)
		this->abilitaBordo = applica;
	else if(colore == ColoreComponente::SFONDO)
		this->abilitaSfondo = applica;
}

void Etichetta::disegna(){
    stringa->posiziona(
        Punto(
            area.origine().x(),
            area.origine().y()+stringa->altezzaCarattere()*0.75
        )
    );
    area.dimensione(
		DimensioneArea{
			(int)stringa->altezza(),
			(int)stringa->lunghezza()
		}
    );
    stringa->disegna();
    
    pVista vista = std::dynamic_pointer_cast<Vista>(genitore());

    if(vista != nullptr){
        
        pStringa riflesso = Utili::crea<Stringa>(*stringa.get());
        
        Colore c = vista->coloreDelloSfondo();
        Colore ombra{c.rosso()*0.5f,c.verde()*0.5f,c.blu()*0.5f};
        riflesso->sfondo(vista->coloreDelBordo());
        
        riflesso->posiziona(
            Punto{stringa->localizzazione().x()+1,stringa->localizzazione().y()+1}
        );
        riflesso->disegna();
        disegnaSfondo(c);
    }
    

}

void Etichetta::riscrivi(const string& testo){
    stringa->testo().aggiungi(testo);
}


