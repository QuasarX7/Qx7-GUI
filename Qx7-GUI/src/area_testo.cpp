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
 * @file area_testo.cpp
 * @author Dr. Domenico della Peruta
 * @date 
 * @version 1.0.0, 
 * 
 * @brief File contenente l'implementazione dei metodi della classe AreaTesto.
 * 
 * @namespace GUI
 * @class AreaTesto
 */
#include "area_testo.h"
using namespace GUI;


AreaTesto::AreaTesto(size_t ID, const OrigineArea& posizione, size_t numeroCaratteriRiga,size_t numeroRighe)
: GUI::Campo{ID,posizione},
  limiteRighe{numeroRighe},
  lunghezzaRiga{numeroCaratteriRiga}
{
    
    limite = numeroCaratteriRiga * numeroRighe;
    area.dimensione(DimensioneArea{
        static_cast<int>((ALTEZZA_CARATTERE+2)*numeroRighe),
        static_cast<int>(LUNGHEZZA_CARATTERE*(numeroCaratteriRiga+2))
    });
    
    inizializzaCampo();
    inizializzaTestoInput();
    inizializzaCursore();
    
}
  
void AreaTesto::inizializzaTestoInput(){
    input =Utili::crea<Stringa>(
        "",
        posizioneCorrenteTesto(),
        coloreTesto,
        lunghezzaRiga
    );
}



void AreaTesto::disegnaCampo(){
    campo->sfondo(coloreSfondo);
    campo->bordo(statoFocus() ? coloreFocus : coloreBordo);
    bordoFocus->sfondo(coloreFocus);
    
    campo->posiziona(Punto(area.origine().x(),area.origine().y()));
    
    campo->bordo(3.0);
    campo->disegna();
    
    pVista vista = nullptr;
    if((vista=dynamic_pointer_cast<Vista>(genitore())) != nullptr && statoFocus() ){
        bordoFocus->bordo(vista->coloreDelloSfondo(),10.0);
        bordoFocus->posiziona(Punto(area.origine().x(),area.origine().y()));
        bordoFocus->disegna();
    }
    
}

void AreaTesto::disegnaCursore(){
    size_t y = posizioneCursoreY();
    size_t x = posizioneCursoreX();
    if(indice > 0){
        cursore->posiziona(
            Punto{
                area.origine().x() + 7.0 + x * LUNGHEZZA_CARATTERE ,
                area.origine().y() + 4.0 + y * input->altezza()
            }             
        );
    }else{
        cursore->posiziona(
            Punto{
                area.origine().x()+5.0 ,
                area.origine().y()+4.0
            }
        );
    }
        
    if(statoFocus()){
        if(cursoreVisibile++ > 5) // lampeggia ogni secondo...
            cursore->disegna();
        if(cursoreVisibile > 10)
            cursoreVisibile = 0;
    }
}

size_t AreaTesto::posizioneCursoreX(){
    if(indice > 0){
        auto testo = input->testo().frammento(0,indice).incolonna(lunghezzaRiga);
        auto righe = testo.righe();
        if(righe.size() > 0){
            auto ultimaRiga = righe.at(righe.size()-1);
            if(ultimaRiga.numeroCaratteri() > 0){
                if(ultimoCarattereInvio(testo) && righe.size() < limiteRighe)
                    return 0;
                return ultimaRiga.numeroCaratteri();
            }
        }
    }
    return 0;
}

size_t AreaTesto::posizioneCursoreY(){
    if(indice > 0){
        auto testo = input->testo().frammento(0,indice).incolonna(lunghezzaRiga);
        auto righe = testo.righe();
        if(righe.size() > 0){
            if(ultimoCarattereInvio(testo) && righe.size() < limiteRighe)
                return righe.size();
            return righe.size() - 1;
        }
    }
    return 0;
}

bool AreaTesto::ultimoCarattereInvio(const Testo& testo)const{
    auto carattereFine = testo.vedi(testo.numeroCaratteri()-1);
    return carattereFine == '\n' || carattereFine == '\r';
    
}

void AreaTesto::inputTastiera(const Tastiera& tastiera){
    //if(posizioneCursoreY() < limiteRighe)
        Campo::inputTastiera(tastiera);
    
    
}

void AreaTesto::inputTastieraSpeciale(const Tastiera& tastiera){
    //if(posizioneCursoreY() < limiteRighe)
        Campo::inputTastieraSpeciale(tastiera);
}

void AreaTesto::limiteInput(){
    auto righe = input->testo().incolonna(lunghezzaRiga).righe();
    const int nrRigheCreate = righe.size();
    if(nrRigheCreate > limiteRighe){
        Testo t;
        for(int i=0; i < limiteRighe; i++){
            t += righe[i];
            t += "\n";
        }
        input->testo().elimina();
        input->testo().aggiungi(t);
        if(indice > input->testo().numeroCaratteri())
            indice = input->testo().numeroCaratteri();
    }
}

