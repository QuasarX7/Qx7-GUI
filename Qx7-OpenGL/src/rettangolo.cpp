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

#include "rettangolo.h"
using namespace Grafica;

Rettangolo::Rettangolo(const Colore& sfondo, const Colore& bordo, const Punto& origine, double altezza, double lunghezza)
: Figura(origine,sfondo,bordo),_altezza(altezza),_lunghezza(lunghezza){}


Rettangolo::Rettangolo(const Colore& sfondo, const Colore& bordo, const Area& area)
: Figura(Punto(area.origine().x(),area.origine().y()),sfondo,bordo),
  _altezza(area.dimensione().altezza()),_lunghezza(area.dimensione().lunghezza()){}


void Rettangolo::disegna()const{
    if(texture != nullptr){
        texture->applicaImmagine();
        glEnable( GL_TEXTURE_2D ); //enable 2D texturing
        
    }
    glPushMatrix();
    trasforma(Vettore{posizione.x(),posizione.y()});
    
    //   [1]   bordo con effetto sfumatura 
    
    const int dx = spessoreBordo;
    Colore cEsterno = this->coloreBordo;
    Colore cInterno = this->coloreSfondo;
        
        
    glBegin(GL_POLYGON); // sx
        cEsterno.disegna();
        glVertex2f(-dx,-dx);
        glVertex2f(-dx,+_altezza+dx);
        cInterno.disegna();
        glVertex2f(0.0,_altezza);
        glVertex2f(0.0,0.0);
    glEnd();
    glBegin(GL_POLYGON); // sopra
        cEsterno.disegna();
        glVertex2f(-dx,-dx);
        glVertex2f(_lunghezza +dx,-dx);
        cInterno.disegna();
        glVertex2f(_lunghezza,0.0);
        glVertex2f(0.0,0.0);
    glEnd();
    glBegin(GL_POLYGON); // dx
        glVertex2f(_lunghezza,0.0);
        glVertex2f(_lunghezza,_altezza);
        cEsterno.disegna();
        glVertex2f(_lunghezza+dx,_altezza+dx);
        glVertex2f(_lunghezza +dx,-dx);
    glEnd();
    glBegin(GL_POLYGON); // sotto
        
        glVertex2f(_lunghezza+dx,_altezza+dx);
        glVertex2f(-dx,_altezza+dx);
        cInterno.disegna();
        glVertex2f(0.0,_altezza);
        glVertex2f(_lunghezza,_altezza);
       
    glEnd();
    // [1]
    
    glBegin(GL_QUADS);
    coloreSfondo.disegna();
    if(texture == nullptr){
        
    // [2]  colore sfondo
    
        glVertex2f(0.0,0.0);
        glVertex2f(_lunghezza,0.0);
        glVertex2f(_lunghezza,_altezza);
        glVertex2f(0.0,_altezza);
    // [2]
    }else{
    
    // [3] copertura immagine
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0,0.0);
        glTexCoord2f(1.0, 1.0); glVertex2f(_lunghezza,0.0);
        glTexCoord2f(1.0, 0.0); glVertex2f(_lunghezza,_altezza);
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0,_altezza);
    // [3]
    }
    glEnd();
    glPopMatrix();
    if(texture != nullptr){
        texture->chiudi();
    }
}


void Rettangolo::immagine(const string& file){
    if(texture != nullptr)
        delete texture;
    texture = new Texture{file};
}
