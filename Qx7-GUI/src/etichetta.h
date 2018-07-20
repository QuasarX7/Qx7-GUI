/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7-GUI.                                          *
 *                                                                          *
 * Qx7-GUI è una libreria software gratuita: puoi ridistribuirla e/o        *
 * modificarla sotto i termini della GNU Lesser General Public License come *
 * pubblicato  dalla Free Software Foundation, o la versione 3 della licenza,
 *  o (a tua scelta) qualsiasi versione successiva.                         *
 *                                                                          *
 * Qx7-GUI è distribuita nella speranza che sia utile,                      *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7-GUI. Altrimenti, vedi al sito                      *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7-GUI.                                            *
 *                                                                          *
 *   Qx7-GUI is free software: you can redistribute it and/or modify it     *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7-GUI is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7-GUI.  If not, see                               *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/
/**
 * @file componente.h
 * @author Dr. Domenico della Peruta
 * @date 
 * @version 1.0.0, 
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Etichetta.
 * 
 * @namespace GUI
 * @class Etichetta
 */
#ifndef etichetta_h
#define etichetta_h

#include <memory>
using namespace std;

#include "componente.h"

#include "stringa.h"
#include "rettangolo.h"
using namespace Grafica;


namespace GUI {
    typedef shared_ptr<Stringa> pStringa;
    
    typedef shared_ptr<Rettangolo> pRettangolo;

    class Etichetta;
    typedef shared_ptr<Etichetta> pEtichetta;
    /**
     * La classe Etichetta rappresenta un semplice componente visivo di output.
     */
    class Etichetta: public Componente{
    public:
    	/**
    	 * Costruttore, ci permetti di definire il testo e la posizione di un componente, eventualmente anche il
    	 * colore del testo, il tipo di font e la lunghezza limite di caratteri per riga.
    	 *
    	 * @param ID				numero di identificazione del componente
    	 * @param testo				testo espesso con codifica latina 1 (europa occidentale)
    	 * @param posizione    		coordinate locali riferite al vertice alto-sinistra
    	 * @param colore			colore testo, di default NERO
    	 * @param font				font standard GLUT, definiti nel tipo enumerativo 'TipoCarattere'
    	 * @param lunghezzaRiga		di default è pari al valore massimo del tipo size_t
    	 */
        Etichetta(size_t ID,const string& testo, const OrigineArea& posizione, const Colore& colore = NERO,
        		TipoCarattere font = GENERICO_PICCOLO, size_t lunghezzaRiga = std::numeric_limits<size_t>::max() );
        /**
         * Distruttore.
         */
        virtual ~Etichetta(){}
        /**
         * Abilita la colorazione decorativa dell'etichetta.
         *
         * @param colore 	tipo elemento decorativo: ColoreComponente::BORDO o ColoreComponente::SFONDO
         * @param applica	true (di default) abilita la decorazione; false la disabilita.
         */
        void abilita(ColoreComponente colore,bool applica=true);
        /**
         * Disegna l'etichetta.
         */
        virtual void disegna()override;
        
        /* SLOT */
        virtual void passaggioMouse(const Cursore& mouse,Stato stato) override{/* nessun effetto */}
        /**
         * Rinizializza testo.
         * @param testo
         */
        void riscrivi(const string& testo);
        /**
         * Testo dell'etichetta.
         * @return
         */
        Testo testo()const{return stringa->testo();}
    private:
        /**
         * Se impostato un colore di fondo o uno di bordo, lo applica al disegno.
         * @param vista
         */
        void disegnaSfondo(const Colore& vista);
    protected:
        pStringa stringa;            ///< testo dell'etichetta
        bool abilitaSfondo = false;  ///< abilita la visualizzazione dello sfondo rettangolare
        bool abilitaBordo  = false;  ///< abilita la visualizzazione del margine  rettangolare
    };
}

#endif /* etichetta_h */
