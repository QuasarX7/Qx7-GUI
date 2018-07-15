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

#ifndef rettangolo_h
#define rettangolo_h

#include "figura.h"
#include "texture.h"
#include "area.h"

namespace Grafica {
    /**
     * Classe che disegna un rettangolo in un piano 2D.
     */
    class Rettangolo: public Figura{
    public:
        /**
         * Costruttore standard.
         * 
         * @param sfondo
         * @param bordo
         * @param origine
         * @param altezza
         * @param lunghezza
         */
        Rettangolo(const Colore& sfondo, const Colore& bordo, const Punto& origine, double altezza, double lunghezza);
        /**
         * Costruttore tramite area assegnata.
         * 
         * @see <code>Rettangolo(const Colore&, const Colore&, const Punto&, double, double)</code>
         * @param sfondo
         * @param bordo
         * @param area
         */
        Rettangolo(const Colore& sfondo, const Colore& bordo, const Area& area);
        /**
         * Costruttore di copia
         * @param copia
         */
        Rettangolo(const Rettangolo& copia)
        : Figura(copia.posizione,copia.coloreSfondo,copia.coloreBordo),
        _altezza(copia._altezza),_lunghezza(copia._lunghezza){}
        /**
         * Distruttore
         */
        virtual ~Rettangolo(){if(texture != nullptr)delete texture;}
        /**
         * Disegna un rettangolo.
         */
        virtual void disegna()const override;
        /**
         * Altezza iniziale del rettangolo.
         * @return 
         */
        double altezza()const{return _altezza;}
        /**
         * Lunghezza iniziale del rettangolo.
         * @return 
         */
        double lunghezza()const{return _lunghezza;}
        /**
         * Reinposta l'altezza e la lunghezza iniziale del rettangolo.
         * @param altezza
         * @param lunghezza
         */
        void dimensiona(double altezza, double lunghezza)
        {_altezza=altezza; _lunghezza=lunghezza;}
        /**
         * Assegna un immagine di sfondo al rettangolo.
         * @param file
         */
        void immagine(const string& file);
        
    protected:
        
        double _altezza,_lunghezza;
        Texture* texture = nullptr;
        
    };
}

#endif /* rettangolo_h */
