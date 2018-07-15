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
 * @file curva.cpp
 * @author Dr. Domenico della Peruta
 * @date 20-04-2018
 * @version 1.0.1, 28-04-2018
 * 
 * @brief File contenente l'implementazione dei metodi della classe Curva.
 * 
 * @namespace Grafica
 * @class Curva
 */
#include "curva.h"
#include "area.h"
using namespace Grafica;


Curva::Curva(const string& funzioneX,const Area& regione, const Punto& origine, size_t unitaPixel,const Colore& colore)
:Figura{Punto(regione.origine().x(),regione.origine().y()),colore,colore},
    unita{unitaPixel},
    funzione{funzioneX},
    dominio{regione.dimensione()}, origineAssi{origine}
{
}


void Curva::disegna() const{
    glPushMatrix();
    trasforma(Vettore{posizione.x(),posizione.y()});
    glLineWidth(spessoreBordo);
    
    glBegin(GL_LINE_STRIP);
    try{
        coloreBordo.disegna();
        Espressione f{funzione};
        for(double x = 0.0; x <= (double)dominio.lunghezza()/(double)unita; x += 1.0/unita){
            f.assegna("x", x - origineAssi.x());
            auto y = f.esegui()  + origineAssi.y();
            if( y > 0.0 && y <= (double)dominio.altezza()/(double)unita ){
                glVertex2f(x*unita + posizione.x(),(double)dominio.lunghezza() - y*unita + posizione.y());
            }
         }
    }catch(std::invalid_argument e){
        glEnd();
        glPopMatrix();
        throw e;
    }
    glEnd();
    
    glPopMatrix();
}
