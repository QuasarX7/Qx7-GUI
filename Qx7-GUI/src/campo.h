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
 * @file  campo.h
 * @author Dr. Domenico della Peruta
 * @date 25-05-2018
 * @version 1.0.2, 16-07-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Campo.
 * 
 * @namespace GUI
 * @class Campo
 */
#ifndef campo_h
#define campo_h

#include <memory>
using namespace std;

#include "ciclo.h"
using namespace Utili;

#include "etichetta.h"
#include "rettangolo.h"
#include "linea.h"
#include "maschera.h"
#include "stringa.h"
using namespace Grafica;

#include "vista.h"

namespace GUI {
    
    typedef shared_ptr<Linea>       pLinea;
    typedef shared_ptr<Rettangolo>  pRettangolo;
    typedef shared_ptr<Stringa>     pStringa;
    
    typedef void (* CodiceFocusAcquisito)(pVista finestra);
    typedef void (* CodiceFocusPerso)(pVista finestra);

    
    class Campo;
    typedef shared_ptr<Campo> pCampo;
    
    enum MovimentoCursore{
        SINISTRA,DESTRA
    };
    /**
     * La classe Campo rappresenta quel componente grafico di input che acquisisce da tastiera
     * una semplice stringa lineare di caratteri.
     */
    class Campo: public Componente{
    public:
        /* Costanti grafiche della classe */
        constexpr static double LUNGHEZZA_CARATTERE = 8.0; 
        constexpr static double ALTEZZA_CARATTERE   = 16.0;
        
        /**
         * Costruttore
         * 
         * @param ID                numero identificativo
         * @param posizione         coordinate del punto alto a sinistra del campo rispetto alle sistema di riferimento della Vista
         * @param numeroCaratteri   numero massimo dei caratteri che determina la lunghezza del campo
         * @param maschera          se definita, imposta il tipo di formattazione del campo
         */
        Campo(size_t ID, const OrigineArea& posizione, size_t numeroCaratteri,const Maschera& maschera=Maschera{"",'_'});
        /**
         * Distruttore
         */
        virtual ~Campo(){}
        /**
         * Metodo che disegna il campo di testo.
         */
        virtual void disegna()override;
        /**
         * Testo di caratteri inserito nel campo.
         * @return 
         */
        string testo()const{return input->testo().stringa();}
        /**
         * Imposta il testo da visualizzare nel campo.
         * @param stringa
         */
        void testo(const string& stringa){input->testo().elimina();input->testo().aggiungi(stringa);}
        /**
         * Assegna il codice da eseguiri quando il campo acquisisce il focus
         * @param codice
         */
        void comportamentoFocusAcquisito(CodiceFocusAcquisito codice)
        {codiceFocusAcquisito = codice;}
        /**
         * Assegna il codice da eseguire quando il campo perde il focus
         * @param codice
         */
        void comportamentoFocusPerso(CodiceFocusPerso codice)
        {codiceFocusPerso = codice;}
    
    protected:
        
        
    
        /**
         * Costruttore parziale usato da eventuali classi derivate.
         * @param ID
         * @param posizione
         */
        Campo(size_t ID, const OrigineArea& posizione);
        /**
         * Inizializza l'aspetto grafico del campo.
         */
        virtual void inizializzaCampo();
        /**
         * Inizializza l'aspetto grafico del cursore di testo.
         */
        virtual void inizializzaCursore();
        /**
         * Inizializza input di testo
         */
        virtual void inizializzaTestoInput();
        /**
         * Tronca la lunghezza dell'input immesso quando supera il limite di caratteri predefinito.
         */
        virtual void limiteInput();
        /**
         * Posizione orizzontale del carattere da sinistra.
         * @return 
         */
        virtual size_t posizioneCursoreX();
        /**
         * Disegna il cursore.
         */
        virtual void disegnaCursore();
        /**
         * Disegna il campo.
         */
        virtual void disegnaCampo();
        /**
         * Definisce la posizione del testo dopo un aggiornamento
         * @return 
         */
        virtual Punto posizioneCorrenteTesto()
        {return Punto(area.origine().x()+5,area.origine().y()+area.dimensione().altezza()-6);};
        
        int cursoreVisibile = 0;///< variabile usata per implementare la pulsazione del cursore
        
        
        
        /* SLOT */
        virtual void passaggioMouse(const Cursore& mouse,Stato stato)override; ///< movimento (passivo) cursore mouse
        virtual void azione(const Mouse& mouse)override; ///< segnale click mouse
        virtual void inputTastiera(const Tastiera& tastiera)override; ///< segnale input tastiera (tasto)
        virtual void inputTastieraSpeciale(const Tastiera& tastieraSpeciale)override; ///< segnale 'tastoSpeciale'
        
        virtual void focusAcquisito()override; ///< acquisizione focus
        virtual void focusCeduto()override;    ///< perdita focus
        
        bool abilitaInvio = false;///< permette di acquisire l'input di invio ("\n") da tastiera
        
        pStringa    input;
        pRettangolo campo,bordoFocus;
        pLinea      cursore;
        
        size_t indice = 0; ///< posizione cursore (riferita ai caratteri in codifica UTF8)
        
        size_t limite;
        
        Maschera mascheraInput; ///< definisce la formatazione dell'input
        
        CodiceFocusAcquisito codiceFocusAcquisito = nullptr;
        CodiceFocusPerso     codiceFocusPerso = nullptr;
        
    };
}

#endif /* campo_h */
