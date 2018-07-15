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
:  Componente{ID,Area{posizione, DimensioneArea{20,10*(int)testo.size()}}}
{
    stringa = Utili::crea<Stringa>(
        testo,
        Punto(area.origine().x(),area.origine().y()+area.dimensione().altezza()),
        colore
    );
    stringa->carattere(font);
}

void Etichetta::disegna(){
    stringa->posiziona(
        Punto(
            area.origine().x(),
            area.origine().y()+area.dimensione().altezza()
        )
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
    }
    
    
}

void Etichetta::riscrivi(const string& testo){
    stringa->testo().aggiungi(testo);
}


