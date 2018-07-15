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
 * Licenza insieme a Qx7-GUI. Altrimenti, vedi al sito                   *
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
 *   License along with Qx7-GUI.  If not, see                            *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/
/**
 * @file componente.h
 * @author Dr. Domenico della Peruta
 * @date 
 * @version 1.0.0, 03-06-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Componente.
 * 
 * @namespace GUI
 * @class Componente
 */
#ifndef componente_h
#define componente_h

#include <stdexcept>
#include <iostream>
#include <memory>
using namespace std;

#include "colore.h"
#include "finestra.h"
using namespace Grafica;

#include "area.h"
#include "oggetto.h"
using namespace Utili;

#include "segnale.h"
#include "input.h"


namespace GUI {
    
    class Componente;
    typedef shared_ptr<Componente> pComponente;
    
    enum ColoreComponente{
        SFONDO,BORDO,TESTO,FOCUS,MOUSE,INATTIVO
    };
    
    class Componente: public Oggetto{
    public:
        Componente(size_t ID, const Area& superficie);
        
        virtual ~Componente(){}
        
        size_t ID()const{return identificativo;}
        void ID(int n);
        /**
         * Zona occupata dal componente.
         * @return 
         */
        Area zonaOccupata()const{return area;}
        
        void colora(Colore colore, ColoreComponente componente);
        Colore colore(ColoreComponente componente)const;
        
        
        virtual void disegna()=0;
        
        pComponente componenteAssociato(size_t ID);
        pComponente primoComponenteAssociato();
        pComponente ultimoComponenteAssociato();
        
        
        //
        
        OrigineArea origine()const{return area.origine();}
        void sposta(const OrigineArea& coordinate){area.origine(coordinate);}
        
        virtual void assegnaFocus();
        bool statoFocus()const{return focus;}
        
        
        /* SEGNALI */ 
        /* I segnali vengono emessi dall' "Applicazione" e trasmessi a tutti i "Componenti della 
         * "Vista" associata */
        Segnale<const Cursore&, Stato >  coordinateMouse;
        Segnale<const Mouse& >    click;
        Segnale<const Tastiera& > tasto;
        Segnale<const Tastiera& > tastoSpeciale;
        
        
    protected:
        virtual bool eventoLocale(const Cursore& mouse);
        bool controlloID(size_t ID)const;
        
        /* SLOT */
        virtual void passaggioMouse(const Cursore& mouse,Stato stato); // segnale 'coordinateMouse'
        virtual void azione(const Mouse& mouse);  // segnale 'click'
        virtual void inputTastiera(const Tastiera& tastiera); // segnale 'tasto'
        virtual void inputTastieraSpeciale(const Tastiera& tastieraSpeciale); // segnale 'tastoSpeciale'
       
        virtual void focusAcquisito(){}
        virtual void focusCeduto(){}
        
        Area area;
        size_t identificativo;
        bool focus;
        
        Colore coloreSfondo = NERO;
        Colore coloreBordo  = GRIGIO_CHIARO;
        Colore coloreTesto  = BIANCO;
        
        Colore coloreDisattivo = GRIGIO;
        Colore coloreEvidenza = BLU;
        Colore coloreFocus = VERDE;
       
        Colore coloreBordoInattivo=coloreBordo; ///< colore del bordo quando non evidenziato
        bool evidenzaBordo = true; ///< usato per gestire il cambio del colore del bordo (con il focus)
        
    private:
        static vector<int> id_componenti;
        
    };
    
}

#endif /* componente_h */
