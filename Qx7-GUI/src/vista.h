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
 * @file vista.h
 * @author Dr. Domenico della Peruta
 * @date 04-05-2018
 * @version 1.0.1, 15-07-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Vista.
 * 
 * @namespace GUI
 * @class Vista
 */
#ifndef vista_h
#define vista_h

#include <iostream>
#include <memory>
using namespace std;

#include "rettangolo.h"
using namespace Grafica;

#include "etichetta.h"
#include "menu.h"

#include <cmath>
using namespace std;


namespace GUI {
    
    class Vista;
    /**
     * @var shared_ptr<Vista> pVista
     * @brief puntatore "intelligente" ad un oggetto di tipo Vista
     */ 
    /**
     * @var shared_ptr<Rettangolo> pRettangolo
     * @brief puntatore "intelligente" ad un oggetto di tipo Rettangolo
     */
    typedef shared_ptr<Vista> pVista;
    typedef shared_ptr<Rettangolo> pRettangolo;
    /**
     * La classe Vista rappresenta la parte interna alla finestra, essa contiene
     * tutti i componenti di input/output della nostra GUI.
     */
    class Vista: public Componente{
    public:
        /**
         * Costruttore.
         * @param titoloFinestra
         * @param campo
         * @param colore
         * @param sfumatura
         */
        Vista(const string& titoloFinestra,const Area& campo,const Colore& colore=GRIGIO_SCURO, const Colore& sfumatura=NERO);
        /**
         * Distruttore
         */
        virtual ~Vista();
        /**
         * Disegna la finestra è i suoi componenti.
         */
        virtual void disegna()override;
        /**
         * Titolo della finestra.
         * @return 
         */
        string titoloFinestra()const{return titolo;}
        /**
         * Associa un menu di contesto al cursore mouse nell'area della finestra.
         * @param m
         */
        void aggiungi(pMenu m){menu = m;}
        /**
         * Disegna il menu di contesto.
         */
        void disegnaMenu();
        /**
         * Dimensione dell'area della finestra.
         * @return 
         */
        DimensioneArea dimensione()const{return area.dimensione();}
        /**
         * Ridimensiona l'area della finestra.
         * @param dim
         */
        void dimensione(const DimensioneArea& dim){area.dimensione(dim);}
        /**
         * Posizione del primo vertice (alto-sinistra) della finestra rispetto allo schermo.
         * @return 
         */
        OrigineArea posizione()const{return area.origine();}
        /**
         * Reimposta la posizione della finestra.
         * @param p
         */
        void posiziona(const OrigineArea& p){area.origine(p);}
        /**
         * Sposta il focus dell'elemento interno alla vista a quello successivo.
         * @return ID del nuovo elemento col focus
         */
        size_t passaFocusSuccessivo();
        /**
         * Sposta il focus dell'elemento interno alla vista a quello precedente.
         * @return 
         */
        size_t passaFocusPrecedente();
        
        /**
         * Metodo che restituisce il componente associato alla vista partendo dal suo ID.
         * <pre>
         * Esempio:
         * <code>
         *  const size_t ID_29 = 3011;
         *  .....
         *  pPulsante pulsante = vista->componente<Pulsante>(ID_29);
         * </code>
         * </pre>
         * 
         * @param ID
         * @return 
         */
        template<typename tipo>
        shared_ptr<tipo> componente(size_t ID)
        {return dynamic_pointer_cast<tipo>(componenteAssociato(ID));}
        /**
         * Colore dello sfondo.
         * @return 
         */
        Colore coloreDelloSfondo()const{return coloreSfondo;}
        /**
         * Colore del bordo
         * @return 
         */
        Colore coloreDelBordo()const{return coloreBordoInattivo;}
        /**
         * Definisce informazioni di debug
         * @return 
         */
        string debug()const override;

        
    protected:
        const double spessore = 8.0;///< spessore della sfumatura di colore dello sfondo
        const double spessoreBarra = 20.0;
        /**
         * Verifica se un componente interno è un'etichetta.
         * @param componente
         * @return 
         */
        bool etichetta(pOggetto componente)const
        {return dynamic_pointer_cast<Etichetta>(componente) != nullptr;}
        /**
         * Verifica se è visibile la barra scorrimento verticale.
         * @return 
         */
        bool barraVerticaleAttiva()
        {return areaComponenti.dimensione().altezza() > dimensione().altezza() || areaComponenti.origine().y() < 0.0 ;}
        /**
         * Verifica se è visibile la barra scorrimento orizzontale.
         * @return 
         */
        bool barraOrizzontaleAttiva()
        {return areaComponenti.dimensione().lunghezza() > dimensione().lunghezza() || areaComponenti.origine().x() < 0.0 ;}
        /**
         * Coordinate attuali interne al cursore.
         * @param cursore
         * @param x
         * @param y
         * @return 
         */
        bool zonaCursore(pRettangolo cursore,int x,int y);
        /**
         * Disegna sulla vista le informazioni di debug.
         */
        void infoDebug();
        /**
         * Rapporto tra l'altezza dell'area reale della finestra e quella dell'area estesa dei componenti.
         * @return 
         */
        double proporzioneVerticale()const;
        /**
         * Rapporto tra la lunghezza dell'area reale della finestra e quella dell'area estesa dei componenti.
         * @return 
         */
        double proporzioneOrizzontale()const; 
        /**
         * Impedisce ai componenti grafici di scorrere verticalmente oltre i limiti di estensione della vista.
         */
        void limiteCursoreVerticale();
        /**
         * Impedisce ai componenti grafici di scorrere orizzontalemente oltre i limiti di estensione della vista.
         */
        void limiteCursoreOrizzontale();
        
        /**
         * Limite della coord. "y" del punto più basso del cursore verticale di scorrimento
         * @see <code>void limiteCursoreVerticale()</code>
         */
        int yCursoreBassoMax = -1;
        /**
         * Limite della coord. "x" del punto più a sinistra del cursore orizzontale di scorrimento
         */
        int xCursoreSinistraMax = -1;
        
    
        /**
         * Calcola l'area virtuale della vista, cioè quell'area che permette di visualizzare tutti i 
         * suoi componenti compresi quelli esterni al campo visivo. Questo metodo è usato per definire
         * le barre di scorrimento laterali al campo della vista. 
         * @return 
         */
        Area estensioneAreaComponenti()const;
        /**
         * Disegna una barra verticale e il suo cursore, per lo scorrimento verticale della finestra 
         * quando gli elementi della vista sono fuori dal margine superiore o inferiore.
         */
        void disegnaBarraScorrimentoVerticale()const;
        /**
         * Disegna una barra orizzontale e il suo cursore, per lo scorrimento orizzontale della finestra
         * quando gli elementi della vista sono fuori dal margine destro o sinistro.
         */
        void disegnaBarraScorrimentoOrizzontale()const;
        
        void spostaComponenti(int dx, int dy);
        
        /* SLOT */
        virtual void passaggioMouse(const Cursore& mouse,Stato stato)override; // segnale 'coordinateMouse'
        virtual void azione(const Mouse& mouse)override;  // segnale 'click'
        virtual void inputTastiera(const Tastiera& tastiera)override; // segnale 'tasto'
        virtual void inputTastieraSpeciale(const Tastiera& tastieraSpeciale)override; // segnale 'tastoSpeciale'
        /**
         * Questo metodo differisce da <code>Componente::eventoLocale(..)</code>, 
         * perché le coordinate di origine dell'area sono riferite a quelle dello schermo e non al piano 
         * locale di disegno.
         * 
         * @param mouse
         * @return 
         */
        virtual bool eventoLocale(const Cursore &mouse) override;
        
        
        pMenu menu = nullptr;
        pRettangolo sfondo;
        
        pRettangolo barraScorrimentoVerticale,barraScorrimentoOrizzontale;
        pRettangolo cursoreScorrimentoVerticale,cursoreScorrimentoOrizzontale;
        int xClic = 0, yClic = 0;
        bool scorrimentoVerticale = false;
        bool scorrimentoOrizzontale = false;
        
        Area areaComponenti; ///< Area contenente tutti i componenti della vista (anche esterni ad essa)
        Area areaPredefinitaVista; ///< Area predefinita vista, contiene le coordinate locali alla finestra (e non allo schermo come Componente::area)
        
        
        string titolo;
    };
}

#endif /* vista_h */
