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
 * @file OpenGL.h
 * @author Dr. Domenico della Peruta
 * @date 26-02-2018
 * @version 2.0.1, 29-04-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe OpenGL.
 * 
 * @namespace Grafica
 * @class OpenGL
 */
#ifndef OpenGL_h
#define OpenGL_h

#include <memory>
#include <vector>
using namespace std;

#include "finestra.h"

namespace Grafica {
    /**
     * Puntatore intelligente alla classe finestra
     */
    typedef shared_ptr<Finestra> pFinestra;
    
    /**
     * Classe che implementa le funzionalità della libreria GLUT, tramite un'approccio orientato ad
     * oggetti.
     * <pre>
     * Esempio:
     * 
     * <code>
     * OpenGL gl{argc,argv};
    
     * pFinestra finestra = Utili::crea<Finestra>(string{"ciao mondo"});
     * finestra->disegna([]{
     *      ...............  AREA DISEGNO ...........
     * });
     *
     * finestra->camera([](int w, int h){
     *      ....... IMPOSTAZIONI PROSPETTICHE ....
     * });
     *
     * gl.aggiungiFinestra(finestra);
     * gl.esegui();
     * </code>
     * </pre>
     * 
     */
    class OpenGL{
    public:
        /**
         * Costruttore senza inizializzazione GLUT
         */
        OpenGL(){}
        /**
         * Costruttore con inizializzazione GLUT con parametri "main"
         * @param argc
         * @param argv
         */
        OpenGL(int argc, char* argv[]);
        /**
         * Distruttore
         */
        virtual ~OpenGL(){}
        /**
         * Permette di inizializzare i metodi OpenGL della libreria GLUT.
         * @param argc
         * @param argv
         */
        void inizializza(int argc, char* argv[]);
        /**
         * Aggiunta di una finestra.
         * @param finestra
         * @throw invalid_argument in caso di finestra nulla
         * @throw logic_error in caso di finestra già associata
         */
        void aggiungiFinestra(pFinestra finestra);
        /**
         * Seleziona una finestra in base all'indice.
         * @param indice
         * @throw std::out_of_range
         * @return 
         */
        pFinestra finestra(size_t indice)const;
        
        /**
         * Numero di finestre associate.
         * @return 
         */
        size_t numeroFinestre()const{return finestre.size();}
        /**
         * Effettua il loop main di OpenGL su tutte le finestre create.
         * @throw logic_error  eccezione generata se non sono definite finestre
         *                     oppure già create
         */
        void esegui();
        /**
         * Elimina i riferimenti alle finestre.
         */
        void eliminaFinestre(){finestre.clear();}
    private:
        vector<weak_ptr<Finestra> >  finestre{};///< lista delle finestre GUI
        
    };
    
}
#endif /* OpenGL_h */
