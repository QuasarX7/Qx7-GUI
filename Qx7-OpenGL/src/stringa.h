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
 * @file stringa.h
 * @author Dr. Domenico della Peruta
 * @date 14-03-2018
 * @version 1.0.4, 17-07-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Stringa.
 * 
 * @namespace Grafica
 * @class Stringa
 * @enum TipoCarattere
 */
#ifndef stringa_h
#define stringa_h

#include "testo.h"
using namespace Utili;

#include "figura.h"
#include <string>
#include <sstream>
using namespace std;

namespace Grafica {
    /**
     * Font e dimensioni standard libreria GLUT
     */
    enum  TipoCarattere{
        GENERICO_GRANDE,
        GENERICO_PICCOLO,
        TIMES_ROMAN_10,
        TIMES_ROMAN_24,
        HELVETICA_10,
        HELVETICA_12,
        HELVETICA_18
    };
    /**
     * La classe Stringa permette di scrivere un testo sullo schermo. Si fa presente che la rotazione della stringa 
     * influenza solo l'eventuale blocco e non l'orientamento del testo.
     */
    class Stringa final: public Figura{
    public:
        /**
         * Costruttore 
         * @param testo
         * @param origine
         * @param colore
         * @param lunghezzaRiga permette di creare un blocco di testo
         */
        Stringa(const string& testo,const Punto& origine, const Colore& colore,size_t lunghezzaRiga =std::numeric_limits<size_t>::max())
        : Figura{origine,colore,colore}, limite{lunghezzaRiga},font{GENERICO_PICCOLO},_testo{testo} {}
        /**
         * Costruttore di copia
         * @param copia
         */
        Stringa(const Stringa& copia)
        : Figura{copia.posizione,copia.coloreSfondo,copia.coloreBordo}{
            limite = copia.limite;
            _testo = copia._testo;
            font   = copia.font;
        }
        /**
         * Distruttore
         */
        virtual ~Stringa(){}
        /**
         * Disegna la stringa di testo.
         */
        virtual void disegna() const override;
        /**
         * Altezza dei caratteri della stringa
         * @return 
         */
        size_t altezzaCarattere()const;
        /**
         * Altezza dei caratteri di una stringa
         * @param fontOpenGL
         * @return
         */
        static size_t altezzaCarattere(TipoCarattere fontOpenGL);
        /**
         * Altezza testo in pixel.
         * @return
         */
        size_t altezza()const;
        /**
         * Lunghezza della stringa in pixel.
         * @return
         */
        size_t lunghezza()const;
        /**
         * Numero massimo di caratteri per riga, nel caso non ci fosse nessun limite
         * il valore sarà -1.
         * @param n
         */
        void numeroCaratteriRiga(size_t n){limite = n;}
        /**
         * Imposta il tipo di font e dimensioni dei caratteri.
         * @param tipo
         */
        void carattere(TipoCarattere tipo){font=tipo;}
        /**
         * Tipo di font e dimensioni dei caratteri.
         * @return 
         */
        TipoCarattere carattere()const{return font;}
        /**
         * Permette di accedere al testo in modalità modifica
         * @return 
         */
        Testo& testo(){return _testo;}
        
        
    private:
        /**
         * Font di default GLUT
         * @return
         */
        void* tipoDiFont()const;

        size_t limite;
        Testo _testo;
        TipoCarattere font;
        
    };
}

#endif /* stringa_h */
