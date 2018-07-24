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
 * @file prospettiva.cpp
 * @author Dr. Domenico della Peruta
 * @date 26-02-2018
 * @version 1.0.2, 21-07-2018
 * 
 * @brief File contenente l'implementazione dei metodi della classe Proiezione 
 * e delle sue derivate.
 * 
 * @namespace Grafica
 * @class Prospettiva
 * @class ProiezioneOrtogonale
 * @class Proiezione2D;
 * @class ProiezioneProspettica
 */
#include "prospettiva.h"
using namespace Grafica;

Proiezione::Proiezione(const CampoVisivo& volumeVisivo, const Area& finestraVisiva)
: campoVisivo(volumeVisivo), areaVisibile(finestraVisiva)
{}

void Proiezione::inizializza(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Proiezione::finestra(){
    glViewport(
               areaVisibile.origine().x(), areaVisibile.origine().y(),
               areaVisibile.dimensione().lunghezza(), areaVisibile.dimensione().altezza()
    );
}
//--------------------------------------------------------------------------------------------------

ProiezioneOrtogonale::ProiezioneOrtogonale(const CampoVisivo& volumeVisivo, const Area& finestraVisiva)
: Proiezione(volumeVisivo,finestraVisiva)
{}

void ProiezioneOrtogonale::applica(){
    finestra();
    inizializza();
    glOrtho(
            campoVisivo.sinistra(),campoVisivo.destra(),
            campoVisivo.sotto(),campoVisivo.sopra(),
            campoVisivo.vicino(),campoVisivo.lontano()
    );
}
//--------------------------------------------------------------------------------------------------

ProiezioneProspettica::ProiezioneProspettica(const CampoVisivo& volumeVisivo, const Area& finestraVisiva)
: Proiezione(volumeVisivo,finestraVisiva)
{}

void ProiezioneProspettica::applica(){
    finestra();
    inizializza();
    glFrustum(
              campoVisivo.sinistra(),campoVisivo.destra(),
              campoVisivo.sotto(),campoVisivo.sopra(),
              campoVisivo.vicino(),campoVisivo.lontano()
    );
}


//--------------------------------------------------------------------------------------------------

Proiezione2D::Proiezione2D(const CampoVisivo& campoVisivo, const Area& finestraVisiva)
: Proiezione(campoVisivo,finestraVisiva)
{}

void Proiezione2D::applica(){
    finestra();
    inizializza();
    gluOrtho2D(
               campoVisivo.sinistra(),campoVisivo.destra(),
               campoVisivo.sotto(),campoVisivo.sopra()
    );
}
