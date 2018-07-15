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
 * @file osservatore.h
 * @author Dr. Domenico della Peruta
 * @date 14-01-2018
 * @version 1.0.1, 29-04-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Osservatore.
 * 
 * @namespace Grafica
 * @class Osservatore
 */
#ifndef osservatore_h
#define osservatore_h

#include <OpenGL/glu.h>

#include "matematica.h"
using namespace Utili;


namespace Grafica {
    
    /**
     * La classe Osservatore rappresenta la posizione, l'orientamento e la direzione
     * di osservazione dell'ipotetica camera visiva.
     */
    class Osservatore{
    public:
        /**
         * Costruttore
         * 
         * @param posizione
         * @param puntoVista
         * @param alto
         */
        Osservatore(const Coordinate& posizione, const Coordinate& puntoVista, const Vettore& alto)
        : puntoOsservatore{posizione}, puntoOsservazione{puntoVista}, altoOsservatore{alto}
        {}
        /**
         * Distruttore
         */
        virtual ~Osservatore(){}
        /**
         * Posizione dell'osservatore.
         * @return 
         */
        Coordinate posizione()const{return puntoOsservatore;}
        /**
         * Posizione del punto osservato.
         * @return 
         */
        Coordinate puntoOsservato()const{return puntoOsservazione;}
        /**
         * Direzione vettoriale dell'alto riferito all'oservatore.
         * @return 
         */
        Vettore alto()const{return altoOsservatore;}
        /**
         * Applica il metodo OpenGL "gluLookAt" che definisce le specifiche 
         * dell'osservatore.
         */
        void osserva();
        
    private:
        Coordinate puntoOsservatore;
        Coordinate puntoOsservazione;
        Vettore altoOsservatore;
    };
    
    typedef shared_ptr<Osservatore> pOsservatore;
}

#endif /* osservatore_h */
