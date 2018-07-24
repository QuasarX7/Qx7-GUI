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
 * @file prospettiva.h
 * @author Dr. Domenico della Peruta
 * @date 26-02-2018
 * @version 1.0.2, 21-07-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Proiezione 
 * e delle sue derivate.
 * 
 * @namespace Grafica
 * @class Prospettiva
 * @class ProiezioneOrtogonale
 * @class Proiezione2D;
 * @class ProiezioneProspettica
 */
#ifndef prospettiva_h
#define prospettiva_h

#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "area.h"
#include "campo_visivo.h"

namespace Grafica {

    /**
     * Classe astratta che generalizza la visualizzazione prospettica OpenGL.
     */
    class Proiezione{
    public:
    	/**
    	 * Costruttore
    	 * @param volumeVisivo
    	 * @param finestraVisiva
    	 */
        Proiezione(const CampoVisivo& volumeVisivo, const Area& finestraVisiva);
        /**
         * Implementa la prospettiva.
         */
        virtual void applica()=0;
        /**
         * Distruttore
         */
        virtual ~Proiezione(){}
    protected:
        void inizializza();
        void finestra();
        
        CampoVisivo campoVisivo;
        Area areaVisibile;
    };
    
    /**
     * Classe che implementa una visione 3D Ortogonale.
     * <pre>
     * Esempio
     * <code>
     * finestra->camera([](int w, int h){
     *       
     *      ProiezioneOrtogonale vista{
     *          CampoVisivo{-0.005*w,0.005*w,0.005*h,-0.005*h,0.5,7.0},
     *          Area{
     *               OrigineArea{0,0},
     *               DimensioneArea{h,w}
     *          }
     *      };
     *      vista.applica();
     * });
     * </code>
     * </pre>
     */
    class ProiezioneOrtogonale: public Proiezione{
    public:
    	/**
    	 * Costruttore
    	 * @param volumeVisivo
    	 * @param finestraVisiva
    	 */
        ProiezioneOrtogonale(const CampoVisivo& volumeVisivo, const Area& finestraVisiva);
        /**
         * Distruttore
         */
        virtual ~ProiezioneOrtogonale(){}
        /**
         * Applica la proiezione ortogonale
         */
        void applica();
    };
    

    /**
     * Classe che impementa una visione di tipo prospettica
     * <pre>
     * Esempio
     * <code>
     * finestra->camera([](int w, int h){
     *       
     *      ProiezioneProspettica vista{
     *          CampoVisivo{-0.001*w,0.001*w,0.001*h,-0.001*h,0.5,7.0},
     *          Area{
     *               OrigineArea{0,0},
     *               DimensioneArea{h,w}
     *          }
     *      };
     *      vista.applica();
     * });
     * </code>
     * </pre>
     */
    class ProiezioneProspettica: public Proiezione{
    public:
    	/**
    	 * Costruttore
    	 * @param volumeVisivo
    	 * @param finestraVisiva
    	 */
        ProiezioneProspettica(const CampoVisivo& volumeVisivo, const Area& finestraVisiva);
        /**
         * Distruttore
         */
        virtual ~ProiezioneProspettica(){}
        /**
         * Applica la visualizzazione proprettica
         */
        void applica();
    };
    
    /**
     * Classe per implementare una visione 2D.
     * <pre>
     * Esempio
     * <code>
     * finestra->camera([](int w, int h){
     *       
     *      Proiezione2D vista{
     *          CampoVisivo{0.0,(double)w,(double)h,0.0)},
     *          Area{
     *               OrigineArea{0,0},
     *               DimensioneArea{h,w}
     *          }
     *      };
     *      vista.applica();
     * });
     * </code>
     * 
     */
    class Proiezione2D: public Proiezione{
    public:
        Proiezione2D(const CampoVisivo& campoVisivo, const Area& finestraVisiva);
        
        void applica();
    };
    
    typedef shared_ptr<Proiezione2D> pProiezione2D;
    typedef shared_ptr<ProiezioneProspettica> pProiezioneProspettica;
    typedef shared_ptr<ProiezioneOrtogonale> pProiezioneOrtogonale;
}

#endif /* prospettiva_h */
