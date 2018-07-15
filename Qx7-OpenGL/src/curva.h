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
 * @file curva.h
 * @author Dr. Domenico della Peruta
 * @date 20-04-2018
 * @version 1.0.2, 15-07-2018
 * 
 * @brief File contenente la definizione e l'implementazione dei metodi della classe Curva.
 * 
 * @namespace Grafica
 * @class Curva
 */
#ifndef CURVA_H
#define CURVA_H

#include <string>
using namespace std;
#include "espressione.h"
#include "matematica.h"
#include "area.h"
using namespace Utili;

#include "figura.h"

namespace Grafica{
    /**
     * La classe curva identifica una linea descritta da una funzione matematica
     * nella variabile x.
     * <pre>
     * 
     * --+---+--------------------->
     *   |   | (punto origine "Area" regione [in pixel])
     *   |   | /
     *   +---o. . . . . . .
     *   |    .   ^      *.
     *   |    .   |     * .<--- (dimensione "Area" regione [in pixel])
     *   |    .*  |   *   .
     *   |    . * |*      .
     *   |    .---o------>.  ---
     *   |    .   |       .   |  y ("Punto" origine [in unità di misura])
     *   |    . . . . . . .  ---
     *   v    
     *        |---| 
     *          x ("Punto" origine [in unità di misura] )
     * 
     * </pre>
     */
    class Curva : public Figura{
    public:
        /**
         * Costruttore a 5 argomenti.
         * 
         * @param funzioneX     funzione nella variabile x, es.: "x^3+sen(x-1)+3"
         * @param regione       identifica l'area di disegno della funzione (@see class Area)
         * @param origine       punto, relativo all'area di disegno, dove è posizionato l'origine 
         *                      degli assi cartesiani
         * @param unitaPixel    dimensione in pixel dell'unità di riferimento
         * @param colore        colore della curva.
         */
        Curva(const string& funzioneX,const Area& regione, const Punto& origine,size_t unitaPixel,const Colore& colore);
        /**
         * Distruttore
         */
        virtual ~Curva(){}
        /**
         * Disegna la curva.
         * @throw std::invalid_argument     sollevato da una non corretta scrittura della param "funzioneX"
         */
        virtual void disegna() const override;
        
    private:
        string funzione;
        size_t unita;
        DimensioneArea dominio;
        Punto origineAssi;
    };

}

#endif /* CURVA_H */

