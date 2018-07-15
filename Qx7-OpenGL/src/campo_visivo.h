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
 * @file campo_visivo.h
 * @author Dr. Domenico della Peruta
 * @date 14-01-2018
 * @version 1.0.0, 13-03-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe CampoVisivo.
 * 
 * @namespace Grafica
 * @class CampoVisivo
 * 
 */
#ifndef campo_visivo_h
#define campo_visivo_h

#include "matematica.h"
using namespace Utili;

namespace Grafica {
    /**
     * @var typedef Posizione<double> OrigineCampo
     * @brief Alias della posizione espressa in valori virgola mobile
     */ 
    /**
     * @var typedef Dimensione<double> DimensioneCampo
     * @brief Alias delle dimensioni (lunghezza e altezza) in valori virgola mobile
     *        di una superfice di tipo rettangolare
     */ 
    typedef Posizione<double> OrigineCampo;
    typedef Dimensione<double> DimensioneCampo;
    
    /**
     * La classe CampoVisivo identifica il volume (o la superficie) dove sono posizionati
     * gli oggetti della scena rappresentati nella finestra.
     * <pre>
     * 
     *          Nel caso 3D
     *   ^
     *   |            
     *   |         +-------+
     *   |        /.      /|
     *   | sopra / .     / |
     *   |      +-------+..+     <-------- lontano (nel caso 3D)
     *   |   /  | /     | /
     *   |  /   |/      |/
     *   | /    +-------+    <-------- vicino  (nel caso 3D)
     *   |/  sotto
     * --*-------------------------->
     *  /|     ^       ^
     *        /       /
     *   sinistra    /
     *            destra  
     * 
     * 
     * </pre>
     */
    class CampoVisivo{
    public:
        /**
         * Costruttore
         * @param sinistra
         * @param destra
         * @param sotto
         * @param sopra
         * @param vicino
         * @param lontano
         */
        CampoVisivo(double sinistra,double destra,double sotto,double sopra,double vicino=0.0,double lontano=0.0)
        : origineCampo(sinistra,sotto,vicino),
        dimensioneCampo( sopra-sotto, destra-sinistra, lontano-vicino)
        {}
        
        /**
         * Posizione del lato sinitro del campo visivo rispetto al sistema di riferimento.
         * @return 
         */
        double sinistra()const{return origineCampo.x();}
        /**
         * Posizione del lato destro del campo visivo rispetto al sistema di riferimento.
         * @return 
         */
        double destra()const{return origineCampo.x()+dimensioneCampo.lunghezza();}
        /**
         * Posizione del lato superiore del campo visivo rispetto al sistema di riferimento.
         * @return 
         */
        double sotto()const{return origineCampo.y();}
        /**
         * Posizione del lato inferiore del campo visivo rispetto al sistema di riferimento.
         * @return 
         */
        double sopra()const{return origineCampo.y()+dimensioneCampo.altezza();}
        /**
         * Posizione del lato più vicino del campo visivo rispetto al sistema di riferimento, 
         * nel caso di rappresentazioni in 3D.
         * @return 
         */
        double vicino()const{return origineCampo.z();}
        /**
         * Posizione del lato più lontano del campo visivo rispetto al sistema di riferimento, 
         * nel caso di rappresentazioni in 3D.
         * @return 
         */
        double lontano()const{return origineCampo.z()+dimensioneCampo.profondita();}
        
        /**
         * Dimensioni del campo visivo.
         * @return 
         */
        DimensioneCampo dimensione()const{return dimensioneCampo;}
        /**
         * Coordinate del vertice del campo visivo posto in basso, a sinistra e più vicino 
         * rispetto al sistema di riferimento.
         * @return 
         */
        OrigineCampo origine()const{return origineCampo;}
        
        
    private:
        DimensioneCampo dimensioneCampo;
        OrigineCampo    origineCampo;
    };

}

#endif /* campo_visivo_h */
