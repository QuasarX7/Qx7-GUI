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
 * @file menu.h
 * @author Dr. Domenico della Peruta
 * @date 04-05-2018
 * @version  1.1.1, 15-07-2018
 *
 * @brief File contenente l'intestazione e l'implementazione delle classi Menu e VoceMenu.
 *
 * @namespace GUI
 * @class VoceMenu
 * @class Menu
 */
#ifndef menu_h
#define menu_h

#include <GLUT/glut.h>

#include <vector>
#include <memory>
using namespace std;

#include "componente.h"
using namespace Utili;

namespace GUI {
    
    class VoceMenu;
    typedef shared_ptr<VoceMenu> pVoceMenu;
    

    class VoceMenu: public Oggetto{
    public:
        VoceMenu(int ID,const string& etichetta);
        virtual ~VoceMenu(){}
        /**
         * Implementa il metodo GLUT <code>glutAddMenuEntry("nome voce",ID)</code> che permette
         * di disegnale le singole voci.
         */
        void disegna();
    private:
        string titolo;
        int identificativo;
        
    };
    
    typedef void (* ComportamentoMenu)(int idVoceMenu);
    
    class Menu;
    typedef shared_ptr<Menu> pMenu;

    
    class Menu: public Oggetto{
    public:
        Menu(const string& etichetta):titolo{etichetta}{}
        Menu(ComportamentoMenu comportamento):titolo{""}{azione=comportamento;} // menu principale
        
        virtual ~Menu(){}
        
        
        virtual void disegna();
        void aggiungiVoce(int ID,const string& etichetta){voci.push_back(Oggetto::crea<VoceMenu>(shared_from_this(),ID,etichetta));}
        
        string nome()const{return titolo;}
    
        virtual void assegnaGenitore(pOggetto genitore)override;
        
        int ID()const{return identificativo;}
        
        
    private:
        void creaSottomenu();
        void creaMenu();
        
        string titolo;
        int identificativo = -1;
        ComportamentoMenu azione = nullptr;
        
        vector<pVoceMenu> voci{};
        
    };
    
    
    
        
        
        
}

#endif /* menu_h */
