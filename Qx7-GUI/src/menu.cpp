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
 * @file menu.cpp
 * @author Dr. Domenico della Peruta
 * @date
 * @version 1.0.1, 15/07/2018
 *
 * @brief File contenente l'implementazione dei metodi delle classi Menu e VoceMenu.
 *
 * @namespace GUI
 * @class VoceMenu
 * @class Menu
 */
#include "menu.h"
using namespace GUI;

VoceMenu::VoceMenu(int ID,const string& etichetta)
:titolo{etichetta},identificativo{ID}
{
}

void VoceMenu::disegna(){
    glutAddMenuEntry(titolo.c_str(), identificativo);
}




void Menu::assegnaGenitore(pOggetto genitore){
    Oggetto::assegnaGenitore(genitore);
    pMenu menuPrincipale;
    if( ( menuPrincipale = dynamic_pointer_cast<Menu>(genitore) ) != nullptr){
        azione = menuPrincipale->azione;
    }
}  

void Menu::disegna(){
    if(azione != nullptr){
        creaSottomenu();
        creaMenu();
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        
    }else{
        throw logic_error{"Errore Menu::disegna(): azione non definita."};
    }
}

void Menu::creaSottomenu(){
    pMenu sottoMenu;
    for(size_t i=0; i < numeroFigli(); i++){
        if(( sottoMenu = dynamic_pointer_cast<Menu>(figlio(i)) ) != nullptr){
            sottoMenu->creaMenu();
        }
    }
}

void Menu::creaMenu(){
    //crea menu principale
    identificativo = glutCreateMenu(azione);
        
    pMenu sottoMenu;
    pVoceMenu voceMenu;
    for(size_t i=0; i < numeroFigli(); i++){
        if(( voceMenu = dynamic_pointer_cast<VoceMenu>(figlio(i)) ) != nullptr){
            //aggiungi voce del menu principale
            voceMenu->disegna();
        }else if(( sottoMenu = dynamic_pointer_cast<Menu>(figlio(i)) ) != nullptr){
            //aggiungi sottomenu creato dal metodo (precedente) Menu::creaSottomenu()
            glutAddSubMenu(sottoMenu->nome().c_str(),sottoMenu->identificativo);
        }
    }
}
        
