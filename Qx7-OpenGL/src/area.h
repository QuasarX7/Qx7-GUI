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
 * @file area.h
 * @author Dr. Domenico della Peruta
 * @date 14-01-2018
 * @version 1.0.0, 
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Area.
 * 
 * @namespace Utili
 * @class Area
 */
#ifndef area_h
#define area_h

#include "matematica.h"

namespace Utili {
    
    /**
     * @var typedef Posizione<int> OrigineArea
     * @brief Alias della posizione espressa in valori interi (punti discreti)
     */ 
    /**
     * @var typedef Dimensione<int> DimensioneArea
     * @brief Alias delle dimensioni (lunghezza e altezza) in valori interi (punti discreti)
     *        di una superfice di tipo rettangolare
     */ 
    typedef Posizione<int> OrigineArea;
    typedef Dimensione<int> DimensioneArea;
    
    /**
     * La classe Area identifica una superfice di punti di forma rettangolare
     * di cui conosciamo le dimensioni e un punto di origine (baricentro o un 
     * vertice). Ideata per definire i componenti GUI.
     * <pre>
     *   ^
     *   |   .........
     *   |   .///////.--- DimensioneArea
     *   |   .///////.
     *   |---x........
     *   |   |\ 
     *       | OrigineArea   
     *   |   |
     * --+--------------->
     *   |  
     * </pre>
     */
    class Area{
    public:
        /**
         * Costruttore con due argomenti.
         * 
         * @param origine
         * @param dimensione
         */
        Area(const OrigineArea& origine,const DimensioneArea& dimensione)
        : dimensioneArea{dimensione}, origineArea{origine}
        {}
        /**
         * Costruttore con quattro argomenti.
         * 
         * @param x     ascisse origine area
         * @param y     ordinata origine area
         * @param h     altezza
         * @param l     lunghezza
         */
        Area(int x, int y, int h, int l):
        dimensioneArea{h,l}, origineArea{x,y}
        {}
        /**
         * Costruttore senza parametri.
         */
        Area():Area{0,0,0,0}{}
        
        Area(const Area& copia):
        dimensioneArea{copia.dimensioneArea}, origineArea{copia.origineArea}
        {}
        
        /**
         * Distruttore
         */
        virtual ~Area(){}
        /**
         * Operatore di assegnazione
         * @param copia
         * @return 
         */
        Area& operator = (const Area& copia)
        {dimensioneArea = copia.dimensioneArea;origineArea=copia.origineArea;return *this;}
        
        /**
         * Accesso alla dimensione.
         * @return 
         */
        DimensioneArea dimensione()const {return dimensioneArea;}
        /**
         * Accesso al punto di in cui è posizionata l'area rispetto al sistema di riferimento.
         * @return 
         */
        OrigineArea origine()const {return origineArea;}
        /**
         * Imposta le dimensioni dell'area
         * @param dim
         */
        void dimensione(const DimensioneArea& dim){dimensioneArea=dim;}
        /**
         * Imposta la posizione dell'area rispetto al sistema di riferimento.
         * @param coordinate
         */
        void origine(const OrigineArea& coordinate){origineArea=coordinate;}
        /**
         * Verifica che le coordinate di un punto (x, y) siano interne all'Area.
         * 
         * @param x
         * @param y
         * @return 
         */
        bool puntoInterno(int x,int y)const{
            return x >= origineArea.x() && x <= (origineArea.x()+dimensioneArea.lunghezza()) &&
                   y >= origineArea.y() && y <= (origineArea.y()+dimensioneArea.altezza());
        }
        
    private:
        DimensioneArea dimensioneArea;
        OrigineArea origineArea;
    };
    
        
}


#endif /* area_h */
