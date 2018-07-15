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
 * @file finestra.cpp
 * @author Dr. Domenico della Peruta
 * @date 10-07-2018
 * @version 1.3.2, 04-05-2018
 * 
 * @brief File contenente i metodi per l'implementazione della classe Finestra.
 */
#include "finestra.h"
using namespace Grafica;



Finestra::Finestra(const string& titolo, int altezza, int lunghezza, int x, int y){
    titoloFinestra = titolo;
    altezzaFinestra = altezza;
    lunghezzaFinestra = lunghezza;
    coordinataX = x;
    coordinataY = y; 
}

Finestra::~Finestra(){
    if(creata){
        glutDestroyWindow(id_finestra);
        finestre.erase(id_finestra);
    }
}

void Finestra::verificaCreazione(){
    if(creata == false)
        creata = true;
    else
        throw logic_error{"finestra già creata in un'istanza OpenGL."};
}


void Finestra::esegui(){
    verificaCreazione();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    // impostazione finestra
    glutInitWindowSize(lunghezzaFinestra, altezzaFinestra); // dimensione finestra
    glutInitWindowPosition(coordinataX, coordinataY);
    id_finestra = glutCreateWindow(titoloFinestra.c_str());
    finestre.insert(id_finestra);
    // crea menu
    if(creaMenu != nullptr)creaMenu();
    
    glEnable(GL_DEPTH_TEST);
    
    // aggiornamento ridimensionamento della finestra
    if(vista != nullptr) 
        glutReshapeFunc(vista);
    else
        throw logic_error{"nessuna impostazione del sistema di riferimento e del campo visivo."};
 
    if(disegnoScena != nullptr)
        glutDisplayFunc(disegnoScena);
    else
        throw logic_error{"scena finestra non disegnata."};
    
    if(tastiera != nullptr) glutKeyboardFunc(tastiera);
    if(tastieraTastiSpeciali != nullptr)glutSpecialFunc(tastieraTastiSpeciali);
        
    if(clic != nullptr) glutMouseFunc(clic);
    if(mousePassivo != nullptr) glutPassiveMotionFunc(mousePassivo);
    if(mouseAttivo != nullptr) glutMotionFunc(mouseAttivo);  
        
    
    glutWMCloseFunc([]{
        auto id = Finestra::idFinestraCorrente();
        glutDestroyWindow(id); //distrugge la finestra in evidenza 
        finestre.erase(id);
        if(finestre.empty()) // se chiudiamo l'ultima finestra il programma si chiude
            exit(0);
    });
    
    if(azioni == nullptr)
        // riaggiorna il disegno ogni decimo di secondo...
        glutIdleFunc([](){
            this_thread::sleep_for(INTERVALLO_DI_AGGIORNAMENTO_GRAFICO);
            glutPostRedisplay();
        });
    else
        glutIdleFunc(azioni);
}

void Finestra::posizione(int& x, int& y){
    x = glutGet((GLenum)GLUT_WINDOW_X);
    y = glutGet((GLenum)GLUT_WINDOW_Y);
}

set<int> Finestra::finestre{};
