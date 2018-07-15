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
 * @file stringa.cpp
 * @author Dr. Domenico della Peruta
 * @date 14-03-2018
 * @version 1.0.1, 05-05-2018
 * 
 * @brief File contenente l'implementazione della classe Stringa.
 * 
 * @namespace Grafica
 * @class Stringa
 */
#include "stringa.h"
using namespace Grafica;

#include <iostream>
using namespace std;

void Stringa::disegna()const{
    auto formatoCarattere = GLUT_BITMAP_HELVETICA_12;
    switch (font) {
        case GENERICO_GRANDE:   formatoCarattere = GLUT_BITMAP_9_BY_15; break;
        case GENERICO_PICCOLO:  formatoCarattere = GLUT_BITMAP_8_BY_13; break;
        case TIMES_ROMAN_10:    formatoCarattere = GLUT_BITMAP_TIMES_ROMAN_10; break;
        case TIMES_ROMAN_24:    formatoCarattere = GLUT_BITMAP_TIMES_ROMAN_24; break;
        case HELVETICA_10:      formatoCarattere = GLUT_BITMAP_HELVETICA_10; break;
        case HELVETICA_12:      formatoCarattere = GLUT_BITMAP_HELVETICA_12; break;
        case HELVETICA_18:      formatoCarattere = GLUT_BITMAP_HELVETICA_18; break;
    };
    glPushMatrix();
    trasforma(Vettore{posizione.x(),posizione.y()});
   
    coloreSfondo.disegna();
    
    size_t i=0;
    for(Testo riga : _testo.incolonna(limite).righe()){
        glRasterPos2f(posizione.x(),  posizione.y()+(i++)*altezza());
        for(char carattere : riga.latino1())
            glutBitmapCharacter(formatoCarattere,static_cast<u_char>(carattere));
    }
    glPopMatrix();
}


size_t Stringa::altezza()const{
    switch (font) {
        case GENERICO_GRANDE:   return 16;
        case GENERICO_PICCOLO:  return 14;
        case TIMES_ROMAN_10:    return 11;
        case TIMES_ROMAN_24:    return 25;
        case HELVETICA_10:      return 12;
        case HELVETICA_12:      return 14;
        case HELVETICA_18:      return 20;
    };
}





