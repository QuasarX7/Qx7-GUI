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
 * @file applicazione.h
 * @author Dr. Domenico della Peruta
 * @date 04-05-2018
 * @version  1.1.1, 15-07-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Applicazione.
 * 
 * @namespace GUI
 * @class Applicazione
 */
#ifndef applicazione_h
#define applicazione_h

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include "vista.h"
//#include "pulsante.h"
#include "OpenGL.h"
#include "finestra.h"
#include "osservatore.h"
#include "menu.h"
using namespace Grafica;
#include "input.h"

/**
 * Lo spazio dei nomi GUI, racchiude tutte le classi e i metodi della libreria 
 * Qx7-GUI
 */
namespace GUI {
    
    
    typedef weak_ptr<Vista>   riferimentoVista;
    typedef size_t id_finestra;
    
    typedef shared_ptr<OpenGL> pOpenGL;
    /**
     * La classe Applicazione, è la classe principale che raccogle e gestisce
     * tutte le finestre e i componenti associati.
     *  <pre>
     * Esempio:
     * <code>
     *  int main(int argc, char** argv) {
     * 
     *      Applicazione app{argc,argv};
     * 
     *      pVista vista = Utili::crea<Vista>("ciao mondo",ARANCIONE,Area{100,70,300,800});
     *      app.aggiungiVista(vista); 
     * 
     *      app.esegui();
     * 
     *      return (EXIT_SUCCESS);
     *  }
     * </code>
     * </pre>
     */
    class Applicazione{
    public:
        /**
         * Costruttore con gli argomenti passati dalla funzione principale main.
         *
         * @param argc
         * @param argv
         */
        Applicazione(int argc, char* argv[]);
        /**
         * Distruttore.
         */
        virtual ~Applicazione(){finestre.clear();}
        /**
         * Metodo di classe che aggiunge le viste per la creazione delle finestre GLUT.
         * @param vista
         */
        static void aggiungiVista(pVista vista);
        /**
         * Metodo che cambia la vista corrente.
         * @param vista
         */
        static void cambiaVistaCorrente(pVista vista);
        
        /**
         * Metodo fondamentale che crea le finestre GLUT tramite le viste precedentemente
         * aggiunte.
         */
        void esegui();
        
    private:
        /**
         * Metodo di inizializzazione tramite i parametri della funzione principale main.
         * @param argc
         * @param argv
         */
        void inizializza(int argc, char* argv[]){gl.inizializza(argc,argv);}
        
        /**
         * Metodo usato per associare i dati delle viste acquisite nel codice eventi delle
         * finestre GLUT.
         * @return 
         */
        static pVista vistaCorrente();
        
        /* codice eventi della 'finestra' GLUT */
        static CodiceScena          disegnaVista;
        static CodiceSistemaRiferimentoVisivo impostaCameraVista;
        static CodiceTastiera       tastiera;
        static CodiceTastieraTastiSpeciali tastieraTastiSpeciali;
        static CodiceClicMouse      clic;
        static CodiceMuoviMouse     mousePassivo, mouseAttivo;
        static CodiceMenu           menu; 
        static CodiceAzioni         azioni;
    
        OpenGL gl{}; ///< oggetto della classe che implementa la libreria GLUT
        
        vector<pFinestra> finestre{}; ///< memorizza le finestre create impedendone la distruzione  
        
        static map<id_finestra,riferimentoVista> viste; ///< contenitore delle viste associate alle finestre
        
    };
}



#endif /* applicazione_h */
