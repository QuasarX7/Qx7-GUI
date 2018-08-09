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
 * @file componente.cpp
 * @author Dr. Domenico della Peruta
 * @date 
 * @version 1.0.2, 15/07/2018
 * 
 * @brief File contenente l'implementazione dei metodi della classe Componente.
 * 
 * @namespace GUI
 * @class Componente
 */
#include "componente.h"
using namespace GUI;


vector<int> Componente::id_componenti{};

Componente::Componente(size_t ID, const Area& superficie):
area{superficie},
focus{false}
{
    if(controlloID(ID)){
        identificativo = ID;
        id_componenti.push_back(identificativo);
    }else{
        stringstream ss;
        ss << "Errore input componente: ID = '" << ID << "' già presente!" << endl;
        throw invalid_argument{ss.str()};
    }
}

bool Componente::controlloID(size_t ID)const{
    if(ID > 0 && id_componenti.size() > 0){
        for(auto id : id_componenti){
            if(id == ID){
                return false;
            }
        }
    }
    return true;
}

void Componente::ID(int n){
    if(controlloID(n)){
        identificativo = n;
    }else{
        stringstream ss;
        ss << "Errore input componente: ID = '" << n << "' già presente!" << endl;
        throw invalid_argument{ss.str()};
    }
        
}
        

pComponente Componente::componenteAssociato(size_t ID){
    for(size_t i=0; i < numeroFigli(); i++){
        auto componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){
            if(componente->identificativo == ID){
                return componente;
            }
        }
    }
    return nullptr;
}

        
pComponente Componente::primoComponenteAssociato(){
    for(size_t i=0; i < numeroFigli(); i++){
        auto componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){
            return componente;
        }
    }
    return nullptr;
}
   
pComponente Componente::ultimoComponenteAssociato(){
    for(size_t i=numeroFigli()-1; i < std::numeric_limits<size_t>::max(); i--){ // [i] = 0 -> [i--] = SIZE_T_MAX
        auto componente = dynamic_pointer_cast<Componente>(figlio(i));
        if(componente != nullptr){
            return componente;
        }
    }
    return nullptr;
}

void Componente::passaggioMouse(const Cursore& mouse,Stato stato){
    bool passaggio = eventoLocale(mouse);
    
    // trasferisci l'evento a tutti i componenti associati
    if(passaggio)
        for(size_t i=0; i < this->numeroFigli(); i++){
            auto nodo = figlio(i);
            if(nodo != nullptr){
                auto componente = dynamic_pointer_cast<Componente>(nodo);
                if(componente != nullptr)
                    componente->passaggioMouse(mouse,stato);
            }
        }
    // disegna il bordo in evidenza al passaggio del mouse
    if(evidenzaBordo != passaggio){
        coloreBordo = (passaggio == true) ? coloreEvidenza : coloreBordoInattivo;
        glutPostRedisplay();
        evidenzaBordo = passaggio;
    }
}

void Componente::azione(const Mouse& mouse){
    if(eventoLocale(mouse.posizione())){
        assegnaFocus();
        // trasmetti l'evento azione a tutti i componenti associati
        for(size_t i=0; i < numeroFigli(); i++){
            auto nodo = figlio(i);
            if(nodo != nullptr){
                auto componente = dynamic_pointer_cast<Componente>(nodo);
                if(componente != nullptr){
                    componente->azione(mouse);
                }
            }
        }
    }
}
        
void Componente::inputTastiera(const Tastiera& tastiera){
    // trasmetti l'evento azione a tutti i componenti associati
    for(size_t i=0; i < numeroFigli(); i++){
        auto nodo = figlio(i);
        if(nodo != nullptr){
            auto componente = dynamic_pointer_cast<Componente>(nodo);
            if(componente != nullptr){
                componente->inputTastiera(tastiera);
            }
        }
    }
}
   
        
void Componente::inputTastieraSpeciale(const Tastiera& tastieraSpeciale){
    // trasmetti l'evento azione a tutti i componenti associati
    for(size_t i=0; i < numeroFigli(); i++){
        auto nodo = figlio(i);
        if(nodo != nullptr){
            auto componente = dynamic_pointer_cast<Componente>(nodo);
            if(componente != nullptr){
                componente->inputTastieraSpeciale(tastieraSpeciale);
            }
        }
    }
}
        
void Componente::assegnaFocus(){
    if(genitore() != nullptr){
        //cerca vecchio focus e richiama il metodo 'focusCeduto'
        for(size_t i=0; i < genitore()->numeroFigli(); i++){
            auto componente = dynamic_pointer_cast<Componente>(genitore()->figlio(i));
            if(componente != nullptr){
                if(componente->focus){
                    componente->focusCeduto();
                    break;
                }
            }
        }
        //aggiorna focus e richiama il metodo 'focusAcquisito'
        for(size_t i=0; i < genitore()->numeroFigli(); i++){
            auto componente = dynamic_pointer_cast<Componente>(genitore()->figlio(i));
            if(componente != nullptr){
                /* assegna 'true' solo a questo elemento e 'false' a gli altri elementi
                   associati al genitore */
                componente->focus = ( this->ID() == componente->ID() );
                if(this->ID() == componente->ID())
                    componente->focusAcquisito();
                
            }
        }
    }
}
        
        
bool Componente::eventoLocale(const Cursore &mouse){
    int Xmin = area.origine().x();
    int Xmax = Xmin + area.dimensione().lunghezza();
    int Ymin = area.origine().y();
    int Ymax = Ymin + area.dimensione().altezza();
    
    return mouse.x() > Xmin && mouse.x() < Xmax && mouse.y() > Ymin && mouse.y() < Ymax;
    
}

void Componente::colora(const Colore& colore, ColoreComponente componente){
    switch(componente){
        case SFONDO: coloreSfondo = colore; break;
        case BORDO:  coloreBordo  = colore; break;
        case TESTO:  coloreTesto  = colore; break;
        case FOCUS:  coloreFocus  = colore; break;
        case MOUSE:    coloreEvidenza   = colore; break;
        case INATTIVO: coloreDisattivo  = colore; break;   
    };
}

Colore Componente::colore(ColoreComponente componente)const{
    switch(componente){
        case SFONDO: return coloreSfondo;
        case BORDO:  return coloreBordo;
        case TESTO:  return coloreTesto;
        case FOCUS:  return coloreFocus;
        case MOUSE:    return coloreEvidenza;
        case INATTIVO: return coloreDisattivo;   
    };
    return NERO;
}
