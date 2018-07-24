/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7-OpenGL.                                       *
 *                                                                          *
 * Qx7-OpenGL è una libreria software gratuita: puoi ridistribuirla e/o     *
 * modificarla sotto i termini della GNU Lesser General Public License come *
 * pubblicato  dalla Free Software Foundation, o la versione 3 della licenza,
 *  o (a tua scelta) qualsiasi versione successiva.                         *
 *                                                                          *
 * Qx7-OpenGL è distribuita nella speranza che sia utile,                   *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7-OpenGL. Altrimenti, vedi al sito                   *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7-OpenGL.                                         *
 *                                                                          *
 *   Qx7-OpenGL is free software: you can redistribute it and/or modify it  *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7-OpenGL is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7-OpenGL.  If not, see                            *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/

/**
 * @file azioni.cpp
 * @author Dr. Domenico della Peruta
 * @date 23-03-2018
 * @version 1.0.2, 15-07-2018
 * 
 * @brief File contenente l'implementazione dei metodi della classe Figura.
 * 
 * @namespace Grafica
 * @class Figura
 */
#include <memory>
using namespace std;

#include "figura.h"
using namespace Grafica;



void Figura::ruota(double angolo,Asse asse){
    switch(asse){
        case Asse::X : angoloRotazioneX = angolo;   break;
        case Asse::Y : angoloRotazioneY = angolo;   break;
        case Asse::Z : angoloRotazioneZ = angolo;   break;
    };
}

void Figura::trasforma(const Vettore& baricentro)const{
    
	//trasla
    glTranslated(baricentro.x()+trasla.x(),baricentro.y()+trasla.y(),baricentro.z()+trasla.z());
    
    // ruota lungo asse Z
    if(angoloRotazioneZ != 0.0){
        glRotated(-angoloRotazioneZ,0.0,0.0,1.0);
    }
    // ruota lungo asse Y
    if(angoloRotazioneY != 0.0){
        glRotated(-angoloRotazioneY,0.0,1.0,0.0);
    }
    // ruota lungo asse X
    if(angoloRotazioneX != 0.0){
        glRotated(-angoloRotazioneX,1.0,0.0,0.0);
    }
    //scala
    if(scala != 1.0){
        glScaled(scala, scala, scala);
        glTranslated(-baricentro.x(),-baricentro.y(),-baricentro.z());
    }
    
}



void Figura::anima(const vector<pAzione>& azioni)
{
    vita += INTERVALLO_DI_AGGIORNAMENTO_GRAFICO;
    
    for(auto azione: azioni){
        if(azione != nullptr)
            if(vita >= azione->inizio() && vita <= azione->fine()){
                pMovimento spostamento;
                pMovimentoRettilineoUniforme movimento;
                pRotazioneCostante rotazione;
                pDimensiona zoom;
                pColoraSfondo sfondi;
                pColoraBordo bordi;
                if((spostamento = dynamic_pointer_cast<Movimento>(azione)) != nullptr){
                    static size_t i=0;
                    auto traiettoria = spostamento->traiettoria();
                    if(i < traiettoria.size()){
                        auto punto = traiettoria.at(i++);
                        trasla.x(punto.x());
                        trasla.y(punto.y());
                        trasla.z(punto.z());
                    }else{
                        i = 0;
                    }

                }else if((movimento = dynamic_pointer_cast<MovimentoRettilineoUniforme>(azione)) != nullptr){
                    trasla.x(trasla.x() + movimento->velocità().x());
                    trasla.y(trasla.y() + movimento->velocità().y());
                    trasla.z(trasla.z() + movimento->velocità().z());

                }else if((rotazione = dynamic_pointer_cast<RotazioneCostante>(azione)) != nullptr){
                    switch(rotazione->asse()){
                        case Asse::X: angoloRotazioneX += rotazione->velocità(); break;
                        case Asse::Y: angoloRotazioneY += rotazione->velocità(); break;
                        case Asse::Z: angoloRotazioneZ += rotazione->velocità(); break;
                    };
                }else if((zoom = dynamic_pointer_cast<Dimensiona>(azione)) != nullptr){
                    // dt va da 0 a 1 nell'intervallo d'azione
                    double dt = (((double)(vita.count() - zoom->inizio().count())) / ((double)(zoom->fine().count() - zoom->inizio().count())) );
                    // fattore ^ dt
                    // inizio  -> [ dt = 0 ]  -> scala = 1
                    // fine    -> [ dt = 1 ]  -> scala = fattore
                    scala = pow(zoom->fattore(),dt);

                }else if((sfondi = dynamic_pointer_cast<ColoraSfondo>(azione)) != nullptr){
                    auto colori = sfondi->colori();
                    if(indiceColori < colori.size()){
                        coloreSfondo = colori.at(indiceColori);
                        if(sfondi->aggiornamento() == SECONDI){
                            if((ritardo++ % 10) == 1)indiceColori++;
                        }else
                            indiceColori++;
                    }else{
                        indiceColori = 0;
                    }

                }else if((bordi = dynamic_pointer_cast<ColoraBordo>(azione)) != nullptr){
                    static size_t i=0;
                    auto colori = bordi->colori();
                    if(i < colori.size()){
                        coloreBordo = colori.at(i++);
                    }else{
                        i = 0;
                    }
                }else{
                    throw std::logic_error{"Azione da implementare in Figura::anima(...)"};
                }
            }
    }
}
