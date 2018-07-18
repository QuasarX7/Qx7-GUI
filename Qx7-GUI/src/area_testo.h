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
 * @file area_testo.h
 * @author Dr. Domenico della Peruta
 * @date 
 * @version  1.0.2, 17/07/2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe AreaTesto.
 * 
 * @namespace GUI
 * @class AreaTesto
 */
#ifndef area_testo_h
#define area_testo_h

#include <memory>
using namespace std;

#include "campo.h"

namespace GUI {
    class AreaTesto;
    typedef shared_ptr<AreaTesto> pAreaTesto;
    
    class AreaTesto: public Campo{
    public:
    	/**
    	 * Costruttore
    	 * @param ID
    	 * @param posizione
    	 * @param numeroCaratteriRiga
    	 * @param numeroRighe
    	 */
        AreaTesto(size_t ID, const OrigineArea& posizione, size_t numeroCaratteriRiga,size_t numeroRighe);
        /**
         * Distruttore
         */
        virtual ~AreaTesto(){}
        
        //string testo()const;
    private:
        /**
         * Tronca il testo quando supera l'area delcampo.
         */
        virtual void limiteInput()override;
    protected:
        virtual void inizializzaTestoInput() override;
        
        bool ultimoCarattereInvio(const Testo& testo)const;
        
        size_t posizioneCursoreX()override;
        size_t posizioneCursoreY();
        virtual void disegnaCursore()override;
        virtual void disegnaCampo()override;
        virtual Punto posizioneCorrenteTesto()override
        {return Punto(area.origine().x()+5,area.origine().y()+ALTEZZA_CARATTERE);}
        
        
        virtual void inputTastiera(const Tastiera& tastiera)override; // segnale input tastiera (tasto)
        virtual void inputTastieraSpeciale(const Tastiera& tastiera)override;
        size_t limiteRighe,lunghezzaRiga;

        size_t indiceRiga =0;
    
    };
}

#endif /* area_testo_h */
