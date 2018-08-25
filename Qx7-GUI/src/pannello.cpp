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
 * @file pannello.cpp
 * @author Dr. Domenico della Peruta
 * @date 02-08-2018
 * @version 1.0.0, 02-08-2018
 *
 * @brief File contenente l'implementazione delle metodi della classe Pannello.
 *
 * @namespace GUI
 * @class Pannello
 */
#include "pannello.h"
using namespace GUI;

Pannello::Pannello(const string& titoloFinestra,const Area& campo,const Colore& colore, const Colore& bordoPannello)
:Vista{titoloFinestra,campo,colore,bordoPannello}{
	areaPredefinitaVista.origine(campo.origine());
}

void Pannello::riposizionaSfondo(){
	sfondo->posiziona(Punto{area.origine().x()+spessore,area.origine().y()+spessore});
}

void Pannello::disegnaBarraScorrimentoVerticale(const OrigineArea& trasla)const{
	Vista::disegnaBarraScorrimentoVerticale(area.origine());
}

void Pannello::disegnaBarraScorrimentoOrizzontale(const OrigineArea& trasla)const{
	Vista::disegnaBarraScorrimentoOrizzontale(area.origine());
}

void Pannello::disegna(){
//	/*
	auto vista = genitore();
	if(vista != nullptr){
		auto _vista = std::dynamic_pointer_cast<Vista>(vista);
		if(_vista != nullptr){
			glEnable(GL_SCISSOR_TEST);
			glScissor(
					area.origine().x(),
					_vista->dimensione().altezza() - area.origine().y() - area.dimensione().altezza(),
					area.dimensione().lunghezza(),
					area.dimensione().altezza()
			);
			Vista::disegna();

			glDisable(GL_SCISSOR_TEST);

			return;
		}
	}
	throw logic_error{"Errore in Pannello::disegna(): vista genitore non definita correttamente..."};
}

void Pannello::infoDebug(){
    pStringa s = Utili::crea<Stringa>(debug(),Punto{area.origine().x()+10.0,area.origine().y()+10.0},BIANCO);
    s->disegna();
    //Rettangolo r{BLU,ROSSO,areaComponenti};r.disegna();
}

Area Pannello::estensioneAreaComponenti()const{
    int xMax = area.origine().x();
    int xMin = area.origine().x();
    int yMax = area.origine().y();
    int yMin = area.origine().y();

    for(size_t i=0; i < numeroFigli(); i++){
        pComponente componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){
            Area zona = componente->zonaOccupata();

            int x = zona.origine().x();
            if(x < xMin)
                xMin = x;

            int y = zona.origine().y();
            if(y < yMin)
                yMin = y;

            x += zona.dimensione().lunghezza();
            if(x > xMax)
                xMax = x;

            y += zona.dimensione().altezza();
            if(y > yMax)
                yMax = y;
        }
    }
    // aggiunta della stessa area della vista predefinita
    int x = areaPredefinitaVista.origine().x();
    if(x < xMin)
        xMin = x;

    int y = areaPredefinitaVista.origine().y();
    if(y < yMin)
        yMin = y;

    x += areaPredefinitaVista.dimensione().lunghezza();
    if(x > xMax)
        xMax = x;

    y += areaPredefinitaVista.dimensione().altezza();
    if(y > yMax)
        yMax = y;

    // aggiungi lo spessore della barra
    if(yMax > areaPredefinitaVista.origine().y() + areaPredefinitaVista.dimensione().altezza())
    	yMax += (int)(spessoreBarra)+ 5;
    if(xMax > areaPredefinitaVista.origine().x() + areaPredefinitaVista.dimensione().lunghezza())
        xMax += (int)(spessoreBarra)+ 5;


    return Area{xMin, yMin, yMax-yMin, xMax-xMin};

}

void Pannello::limiteCursoreVerticale(int estremoSup){
	Vista::limiteCursoreVerticale(area.origine().y());
}

void Pannello::limiteCursoreOrizzontale(int estremoSX){
	Vista::limiteCursoreOrizzontale(area.origine().x());
}

bool Pannello::eventoLocale(const Cursore& mouse){
	return Componente::eventoLocale(mouse);//non eredita "Vista::eventoLocale(mouse)"
}

