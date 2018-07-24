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
#include "linea.h"
using namespace Grafica;

Linea::Linea(const Punto& p1,const Punto& p2,const Colore& colore,double spessore)
:Figura(p1,colore,colore),estremo{p2}
{
    spessoreBordo = spessore;
    dx = estremo.x() - posizione.x();
    dy = estremo.y() - posizione.y();
    
}

void Linea::disegna() const{
    glPushMatrix();
    trasforma(Vettore{posizione.x(),posizione.y()});
    glLineWidth(spessoreBordo);
    glBegin(GL_LINE_LOOP);
    coloreBordo.disegna();
    glVertex2f(0.0,0.0);
    glVertex2f(dx,dy);
    glEnd();
    glPopMatrix();
}


void Linea::posiziona(const Punto& punto){
    posizione.x(punto.x());
    posizione.y(punto.y());
    
    estremo.x(punto.x()+dx);
    estremo.y(punto.y()+dy);
}
