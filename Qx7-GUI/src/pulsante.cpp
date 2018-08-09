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
 * @file  pulsante.cpp
 * @author Dr. Domenico della Peruta
 * @date 
 * @version 1.0.0, 03-06-2018
 * 
 * @brief File contenente l'implementazione dei metodi della classe Pulsante.
 * 
 * @namespace GUI
 * @class Pulsante
 */
#include "pulsante.h"
using namespace GUI;
Pulsante::Pulsante(size_t ID, const string& etichetta, const Area& area)
: Componente{ID,area},
codiceAzione{nullptr}
{
    coloreSfondo = GRIGIO_CHIARO;
    coloreBordoInattivo= coloreBordo  = NERO;
    coloreTesto = GRIGIO_SCURO;
    
    figura = Utili::crea<Rettangolo>(
        coloreSfondo,
        coloreBordo,
        Punto(area.origine().x(),area.origine().y()),
        static_cast<double>(area.dimensione().altezza()),
        static_cast<double>(area.dimensione().lunghezza())
    );
    
    bordoFocus = Utili::crea<Rettangolo>(*figura.get());
    
    testo = Utili::crea<Stringa>(
        etichetta,
        posizioneCorrenteTesto(etichetta),
        coloreTesto
    ); 
    
}


Pulsante::Pulsante(size_t ID, const string& etichetta,const OrigineArea& posizione)
: Pulsante{ID,etichetta,Area{posizione,DimensioneArea{15,15 + (int)etichetta.size()*8}} }
{}

Punto Pulsante::posizioneCorrenteTesto(const string& etichetta){
    size_t numeroCaratteri = etichetta.size();
    if(etichetta.size() == 0)
        numeroCaratteri = testo->testo().numeroCaratteri();
    double xTesto = area.origine().x() + area.dimensione().lunghezza()/2.0 - numeroCaratteri * 4.0;
    double yTesto = area.origine().y() + area.dimensione().altezza()/2.0 + 4.0;
    
    return Punto{xTesto,yTesto};
};
    
void Pulsante::disegna(){
    // reimposta specifiche della figura
    figura->sfondo(coloreSfondo);
    figura->bordo(statoFocus() ? coloreFocus : coloreBordo,5.0);
    figura->posiziona(Punto(area.origine().x(),area.origine().y()));
    bordoFocus->sfondo(coloreFocus);
    
    // disegna
    if(area.dimensione().altezza() >= 15 && area.dimensione().lunghezza() >= (testo->testo().numeroCaratteri()+1) * 8){
        testo->posiziona(posizioneCorrenteTesto());
        testo->sfondo(coloreTesto);
        testo->disegna();
    }
    figura->disegna();
    
    pVista vista = nullptr;
    if((vista=dynamic_pointer_cast<Vista>(genitore())) != nullptr && statoFocus() ){
        bordoFocus->bordo(vista->coloreDelloSfondo(),10.0);
        bordoFocus->posiziona(Punto(area.origine().x(),area.origine().y()));
        bordoFocus->disegna();
    }
    
}

void Pulsante::coloraPulsante(const Colore& sfondo,const Colore& testo, const Colore& bordo){
    coloreTesto  = testo;
    coloreBordoInattivo = coloreBordo  = bordo;
    coloreSfondo = sfondo;
}

void Pulsante::passaggioMouse(const Cursore& mouse,Stato stato){
     Componente::passaggioMouse(mouse,stato);
}


void Pulsante::azione(const Mouse& mouse){
    if(eventoLocale(mouse.posizione())){
        assegnaFocus();
        if(mouse.pulsante() == PulsanteMouse::SINISTRO){
            if(mouse.stato() == StatoPulsante::SU){
                if(codiceAzione != nullptr && genitore() != nullptr){
                    auto finestra = dynamic_pointer_cast<Vista>(genitore());
                    if(finestra != nullptr){
                        codiceAzione(finestra);
                    }
                }
                figura->ingrandisci(1);
                bordoFocus->ingrandisci(1);
                glutPostRedisplay();
            }else  if(mouse.stato() == StatoPulsante::GIU){
                figura->ingrandisci(1.10);
                bordoFocus->ingrandisci(1.10);
                glutPostRedisplay();
                
            }
        }
    }
}


void Pulsante::inputTastiera(const Tastiera& tastiera){
    if(statoFocus()){ 
        switch (tastiera.carattere()) {
            case 13: // tasto invio
                if(codiceAzione != nullptr && genitore() != nullptr){
                    auto finestra = dynamic_pointer_cast<Vista>(genitore());
                    if(finestra != nullptr){
                        codiceAzione(finestra);
                    }
                }
                break;
                
            default:
                break;
        }
    }
}
