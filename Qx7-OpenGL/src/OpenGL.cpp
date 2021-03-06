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
 * @file OpenGL.cpp
 * @author Dr. Domenico della Peruta
 * @date 26-02-2018
 * @version 1.0.1, 29-04-2018
 * 
 * @brief File contenente l'implementazione dei metodi della classe OpenGL.
 * 
 * @namespace Grafica
 * @class OpenGL
 */
#include "OpenGL.h"
using namespace Grafica;

OpenGL::OpenGL(int argc, char* argv[]){
    inizializza(argc, argv);
}


void OpenGL::inizializza(int argc, char* argv[]){
    glutInit(&argc, argv);
}

void OpenGL::aggiungiFinestra(pFinestra finestra){
    if(finestra != nullptr){
        for(auto f : finestre)
            if(f.lock() == finestra)
                throw invalid_argument{
                    "impossibile aggiungere una finestra già inserita." 
                }; 
        finestre.push_back(finestra);
    }else{
        throw invalid_argument{
           "impossibile aggiungere una finestra inesistente." 
        };
    }
}

pFinestra OpenGL::finestra(size_t indice) const{
    return indice < finestre.size() 
            ? finestre[indice].lock() 
            : throw std::out_of_range{"indice finestra fuori intervallo."};
}

void OpenGL::esegui(){
    if(finestre.size() > 0){
        for(auto finestra: finestre){
            if(finestra.lock() != nullptr)
                finestra.lock()->esegui();
            else
                throw logic_error{
                    "una finestra GUI è inesistente...."
                };
        }
        glutMainLoop(); //Start the main loop
    }else{
        throw logic_error{
            "impossibile avviare il main loop se nessuna finestra GUI è definita."
        };
    }
}



