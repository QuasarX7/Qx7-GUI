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
 * @file  campo.cpp
 * @author Dr. Domenico della Peruta
 * @date 25-05-2018
 * @version 1.0.3, 16-08-2018
 * 
 * @brief File contenente l'implementazione della classe Campo.
 * 
 * @namespace GUI
 * @class Campo
 */
#include "campo.h"
#include "vista.h"
using namespace GUI;



Campo::Campo(size_t ID, const OrigineArea& posizione, size_t numeroCaratteri, const Maschera& maschera)
:
Componente{
    ID,
    Area(posizione,DimensioneArea(ALTEZZA_CARATTERE+4,LUNGHEZZA_CARATTERE*(numeroCaratteri+2)))
},
input{nullptr},limite{numeroCaratteri},
mascheraInput{maschera}
{
    inizializzaCampo();
    inizializzaCursore();
    inizializzaTestoInput();
}

Campo::Campo(size_t ID, const OrigineArea& posizione)
:Componente{
    ID,
    Area(posizione,DimensioneArea(0,0))
},
input{nullptr},
limite{0},
mascheraInput{Maschera{"",'_'}}
{
}

void Campo::inizializzaCampo(){
    campo = Utili::crea<Rettangolo>(
        coloreSfondo,
        coloreBordo,
        Punto(area.origine().x(),area.origine().y()),
        static_cast<double>(area.dimensione().altezza()),
        static_cast<double>(area.dimensione().lunghezza())
    );
    bordoFocus = Utili::crea<Rettangolo>(*campo.get());
}

void Campo::inizializzaCursore(){
    cursore = Utili::crea<Linea>(//dimensiona cursore
        Punto(area.origine().x(),area.origine().y()),
        Punto(area.origine().x(),area.origine().y()+ALTEZZA_CARATTERE),
        coloreFocus,
        1.0
    );
}

void Campo::inizializzaTestoInput(){
    input = Utili::crea<Stringa>(
        mascheraInput.stringa(),
        posizioneCorrenteTesto(),
        coloreTesto
    );
}

void Campo::disegna(){
    limiteInput();
    disegnaCursore();
    input->posiziona(posizioneCorrenteTesto());
    input->disegna();
    disegnaCampo();
}

void Campo::disegnaCampo(){
    campo->sfondo(coloreSfondo);
    campo->bordo(statoFocus() ? coloreFocus : coloreBordo);
    bordoFocus->sfondo(coloreFocus);
    Punto posizioneCorrente(area.origine().x(),area.origine().y());
    
    campo->posiziona(posizioneCorrente);
    
    campo->bordo(3.0);
    campo->disegna();
    
    pVista vista = nullptr;
    if((vista=dynamic_pointer_cast<Vista>(genitore())) != nullptr && statoFocus() ){
        bordoFocus->bordo(vista->coloreDelloSfondo(),10.0);
        bordoFocus->posiziona(posizioneCorrente);
        bordoFocus->disegna();
    }
    
}

void Campo::limiteInput(){
    if(input->testo().numeroCaratteri() > limite){
        Testo t = input->testo().frammento(0,limite);
        
        input->testo().elimina();
        input->testo().aggiungi(t);
        if(indice > input->testo().numeroCaratteri())
            indice = input->testo().numeroCaratteri();
    }
}

void Campo::disegnaCursore(){
    cursore->posiziona(//posiziona cursore
        Punto{
            area.origine().x()+posizioneCursoreX()*LUNGHEZZA_CARATTERE+7.0,
            area.origine().y()+3.0
        }
    );
    if(statoFocus()){
        if(cursoreVisibile++ > 5) // lampeggia ogni secondo...
            cursore->disegna();
        if(cursoreVisibile > 10)
            cursoreVisibile = 0;
    }
}

size_t Campo::posizioneCursoreX(){
    return indice;
}

void Campo::passaggioMouse(const Cursore& mouse,Stato stato){
    Componente::passaggioMouse(mouse,stato);
}


void Campo::azione(const Mouse& mouse){
	Componente::azione(mouse);
	/*
    if(eventoLocale(mouse.posizione())){
        assegnaFocus();
    }
    */
}

void Campo::inputTastiera(const Tastiera& tastiera){
    static Testo ultimoCarattere{""};// permette di ricostruire i caratteri multi-byte
    static int nrByte = 0;
    if(statoFocus() && ID() == Componente::idUltimoFocus()){
        switch (tastiera.carattere()) {
            case 127: // tasto 'canc'
                if(indice > 0){
                    indice--;
                    input->testo().elimina(indice,Unità::CARATTERE);
                    if(mascheraInput.stringa().size() > 0)//se esiste una maschera
                        input->testo().aggiungi(mascheraInput.stringa()[indice],indice,Unità::CARATTERE);
                }
                break;
            case 9: // tasto 'tab'
                break;
            case 13: // tasto invio
                if(!abilitaInvio)break;// "abilitaInvio è false" esegue il 'case' default...
            default:{
                size_t maxInput = mascheraInput.stringa().size() > 0 ? mascheraInput.stringa().size() : limite;
                if(indice < maxInput){
                    Testo byte = tastiera.carattere();
                    int dim = byte.byteCarattere(0);
                    if(dim >= 1){
                        nrByte = dim;
                        ultimoCarattere = byte;
                        
                    }else if(dim == 0){
                        ultimoCarattere += byte;
                        nrByte--;
                    }else{
                        ultimoCarattere = "";
                        nrByte = 0;
                        throw logic_error{"Errore Campo::inputTastiera(..): carattere acquisito non UTF8."};
                    }
                    if(nrByte == 1){
                        if(indice < mascheraInput.stringa().size()){//se esiste una maschera
                            while(mascheraInput.stringa()[indice] != mascheraInput.carattere()){
                                indice++;//salta i caratteri non oscurati
                                if(indice == maxInput) return;
                            }
                            input->testo().elimina(indice,Unità::CARATTERE);
                        }
                        input->testo().aggiungi(ultimoCarattere,indice,Unità::CARATTERE);
                        indice++;
                    }
                }
            }break;
        }
    }
}


void Campo::inputTastieraSpeciale(const Tastiera& tastiera){
    if(statoFocus()){
        switch (tastiera.carattere()) {
            case GLUT_KEY_RIGHT: // tasto '->'
                if(indice < std::numeric_limits<size_t>::max() && indice < input->testo().numeroCaratteri()){
                    indice++;
                }
                break;
            case GLUT_KEY_LEFT: // tasto '<-'
                if(indice > 0){
                    indice--;
                }
                break;
            case GLUT_KEY_UP: // tasto '^'
                indice = 0;
                break;
            case GLUT_KEY_DOWN: // tasto 'v'
                indice = input->testo().numeroCaratteri();
                break;
            default:
                break;
        }
    }
}

void Campo::focusAcquisito(){
    if(codiceFocusAcquisito != nullptr && genitore() != nullptr){
        auto finestra = dynamic_pointer_cast<Vista>(genitore());
        if(finestra != nullptr){
            codiceFocusAcquisito(finestra);
        }
    }
}

void Campo::focusCeduto(){
    if(codiceFocusPerso != nullptr && genitore() != nullptr){
        auto finestra = dynamic_pointer_cast<Vista>(genitore());
        if(finestra != nullptr){
            codiceFocusPerso(finestra);
        }
    }
}

void Campo::testo(const string& stringa){
	input->testo().elimina();
	input->testo().aggiungi(stringa);
	indice = input->testo().numeroCaratteri();
}











        
