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
 * @file  pulsante.h
 * @author Dr. Domenico della Peruta
 * @date 
 * @version 1.0.0, 03-06-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Pulsante.
 * 
 * @namespace GUI
 * @class Pulsante
 */
#ifndef Pulsante_h
#define Pulsante_h

#include <iostream>
#include <memory>
using namespace std;

#include "vista.h"
#include "rettangolo.h"
#include "stringa.h"
using namespace Grafica;

namespace GUI {
    
    typedef void (* CodiceAzione)(pVista finestra);
    
    typedef shared_ptr<Rettangolo> pRettangolo;
    typedef shared_ptr<Stringa> pStringa;
    
    class Pulsante;
    typedef shared_ptr<Pulsante> pPulsante;
    
    class Pulsante: public Componente{
    public:
        Pulsante(size_t ID, const string& etichetta, const Area& area);
        Pulsante(size_t ID, const string& etichetta,const OrigineArea& posizione);
        
        virtual ~Pulsante(){}
        void colora(const Colore& sfondo,const Colore& testo, const Colore& bordo);
        
        void disegna()override;
        
        void comportamentoClick(CodiceAzione codice)
        {codiceAzione=codice;}
        
        
    private:
        Punto posizioneCorrenteTesto(const string& etichetta="");
        
    protected:
        /* SLOT */
        virtual void passaggioMouse(const Cursore& mouse,Stato stato)override; // movimento (passivo) cursore mouse
        virtual void azione(const Mouse& mouse)override; // segnale click mouse
        virtual void inputTastiera(const Tastiera& tastiera)override; ///< segnale input tastiera (tasto invio)
        
        
        pRettangolo figura, bordoFocus;
        pStringa testo;
        
        CodiceAzione codiceAzione;
    
        
        
    };
}

#endif /* Pulsante_h */
