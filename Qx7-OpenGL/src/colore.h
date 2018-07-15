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
 * @file colore.h
 * @author Dr. Domenico della Peruta
 * @date 01-01-2018
 * @version 1.0.0, 06-04-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Colore.
 * 
 * @namespace Grafica
 * @class Colore
 */
#ifndef colore_h
#define colore_h

#include "disegno.h"

namespace Grafica {
    /**
     * Classe che permette di impostare il colore di un oggetto grafico OpenGL
     */
    class Colore final: public Disegno{
    public:
        /**
         * Costruttore a 3 o 4 argomenti.
         * @param rosso
         * @param verde
         * @param blu
         * @param alfa
         */
        Colore(float rosso,float verde,float blu, float alfa=1.0f)
        : _rosso(rosso),_verde(verde),_blu(blu),_alfa(alfa){}
        
        /**
         * Applica colore.
         */
        void disegna()const override
        { _alfa == 1.0f ? glColor3f(_rosso,_verde,_blu) : glColor4f(_rosso,_verde,_blu,_alfa); }
        
        float rosso()const{return _rosso;}
        float verde()const{return _verde;}
        float blu()const{return _blu;}
        float alfa()const{return _alfa;}
        
        void rosso(float valore){_rosso = valore;}
        void verde(float valore){_verde = valore;}
        void blu(float valore){_blu = valore;}
        void alfa(float valore){_alfa = valore;}
        /**
         * Determina un colore intermedio.
         * @param c
         * @return 
         */
        Colore combina(const Colore& c)const
        {return Colore{mix(_rosso,c._rosso),mix(_verde,c._verde),mix(_blu,c._blu),mix(_alfa,c._alfa)};}
    private:
        /**
         * Effettua la media aritmetica tra due numeri reali
         * @param a
         * @param b
         * @return 
         */
        float mix(float a, float b)const{return (a+b)/2.0f;}
        
        /* componenti dei del colore (RGBA) */
        float _rosso,_verde,_blu,_alfa;
    };
    
    /*        COLORI PREDEFINITI       R      G       B     */
    static const Colore ROSSO        {1.0f,  0.0f,   0.0f};
    static const Colore VERDE        {0.0f,  1.0f,   0.0f};
    static const Colore BLU          {0.0f,  0.0f,   1.0f};
    
    static const Colore NERO         {0.0f,  0.0f,   0.0f};
    static const Colore BIANCO       {1.0f,  1.0f,   1.0f};
    
    static const Colore GIALLO       {1.0f,  1.0f,   0.0f};
    static const Colore MAGENTA      {1.0f,  0.0f,   1.0f};
    static const Colore CIANO        {0.0f,  1.0f,   1.0f};
    
    static const Colore GRIGIO       {0.5f,  0.5f,   0.5f};
    static const Colore GRIGIO_CHIARO{0.75f, 0.75f,  0.75f};
    static const Colore GRIGIO_SCURO {0.25f, 0.25f,  0.25f};
    
    static const Colore ARANCIONE    {0.98f, 0.625f, 0.12f};    
}

#endif /* colore_h */
