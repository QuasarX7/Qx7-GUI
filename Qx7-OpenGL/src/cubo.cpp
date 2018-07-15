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
 * @file cubo.cpp
 * @author Dr. Domenico della Peruta
 * @date 28-02-2018
 * @version 1.0.0,
 * 
 * @brief File contenente l'implementazione dei metodi della classe Cubo.
 */
#include "cubo.h"
using namespace Grafica;

Cubo::Cubo(const Colore& sfondo, const Colore& bordo, const Punto& baricentro, double lunghezza)
: Figura(baricentro,sfondo,bordo),lato(lunghezza){
    
}


void Cubo::disegna() const{
    glPushMatrix();
    trasforma(Vettore{posizione.x()+lato/2.0,posizione.y()+lato/2.0});
    glLineWidth(spessoreBordo);
    
    coloreBordo.disegna();
    // faccia avanti
    glBegin(GL_LINE_LOOP);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
    glEnd();
    // faccia dietro
    glBegin(GL_LINE_LOOP);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
    glEnd();
    // bordi laterali
    glBegin(GL_LINES);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
    glEnd();
    
    coloreSfondo.disegna();
    
    glBegin(GL_QUADS);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
    glEnd();
 
    glBegin(GL_QUADS);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
    glEnd();
   
    glBegin(GL_QUADS);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()-lato/2.0,posizione.z()+lato/2.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()-lato/2.0);
        glVertex3f(posizione.x()+lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
        glVertex3f(posizione.x()-lato/2.0,posizione.y()+lato/2.0,posizione.z()+lato/2.0);
    glEnd();
    
    glPopMatrix();
}
