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
 * @file finestra.h
 * @author Dr. Domenico della Peruta
 * @date 20-02-2018
 * @version 1.5.0, 24-06-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione della classe Finestra.
 * 
 * @namespace Grafica
 * @class Finestra
 * @namespace TastiSpeciali
 * @namespace TastiMouse
 * @namespace AzioneTastoMouse
 */
#ifndef finestra_h
#define finestra_h

#include <thread>
#include <chrono>
#include <string>
using namespace std;

#include "prospettiva.h"
#include "azioni.h"

#include <iostream>
#include <set>
using namespace std;

#include "ciclo.h"
using namespace Utili;


namespace Grafica {
    /**
     * Definisce il valore dei tasti speciali della tastiera
     * @see <code>void inputTastieraTastiSpeciali(void (* input)(int pulsante, int x, int y))</code>
     */
    namespace TastiSpeciali{
        const int F1 = GLUT_KEY_F1;
        const int F2 = GLUT_KEY_F2;
        const int F3 = GLUT_KEY_F3;
        const int F4 = GLUT_KEY_F4;
        const int F5 = GLUT_KEY_F5;
        const int F6 = GLUT_KEY_F6;
        const int F7 = GLUT_KEY_F7;
        const int F8 = GLUT_KEY_F8;
        const int F9 = GLUT_KEY_F9;
        const int F10 = GLUT_KEY_F10;
        const int F11 = GLUT_KEY_F11;
        const int F12 = GLUT_KEY_F12;
        const int LEFT  = GLUT_KEY_LEFT;
        const int UP    = GLUT_KEY_UP;
        const int RIGHT = GLUT_KEY_RIGHT;
        const int DOWN  = GLUT_KEY_DOWN;
        const int PAGE_UP   = GLUT_KEY_PAGE_UP;
        const int PAGE_DOWN = GLUT_KEY_PAGE_DOWN;
        const int HOME   = GLUT_KEY_HOME;
        const int END    = GLUT_KEY_END;
        const int INSERT = GLUT_KEY_INSERT;
    };
    
    /**
     * Definisce il valore del pulsante del mouse.
     * @see <code>void inputClic(void (* input)(int , int , int, int))</code>
     */
    namespace TastiMouse{
        const int SINISTRO = GLUT_LEFT_BUTTON;
        const int MEZZO    = GLUT_MIDDLE_BUTTON;
        const int DESTRO   = GLUT_RIGHT_BUTTON;
    };
    
    enum class Stato{
       Attivo,Passivo 
    };
    
    /**
     * Definisce il valore del stato (o comportamento) del pulsante del mouse.
     * @see <code>void inputClic(void (* input)(int , int , int, int))</code>
     */
    namespace AzioneTastoMouse{
        const int PREMUTO  = GLUT_DOWN;
        const int RILASCIO = GLUT_UP;
    };
    
    /* definizione tipi 'puntatore a funzioni' */
    typedef void (* CodiceScena)(void);
    typedef void (* CodiceTastiera)(unsigned char , int, int);
    typedef void (* CodiceTastieraTastiSpeciali)(int , int, int);
    typedef void (* CodiceClicMouse)(int , int , int , int );
    typedef void (* CodiceMuoviMouse)(int x, int y);
    typedef void (* CodiceSistemaRiferimentoVisivo)(int, int);
    typedef void (* CodiceMenu)(void); 
    typedef void (* CodiceAzioni)(void);
        
        
    /*
     * Classe che implementa una singola finestra GUI della libreria GLUT
     */
    class Finestra{
    public:
        /**
         * Costruttore di una finestra GUI.
         * <pr>
         *          |<----lunghezza ---->|
         *                  400
         * (x,y) -> #+++++++++++++++++++++------------------->
         *          +////////////////////+    ^
         *          +////////////////////+    |
         *          +////////////////////+    |
         *          +////////////////////+    altezza = 400
         *          +////////////////////+    |
         *          +////////////////////+    |
         *          +////////////////////+    v
         *          ++++++++++++++++++++++  ----
         *          |
         *          |
         *          |
         *          v
         * </pr>
         * 
         * @param titolo
         * @param altezza   di default 400
         * @param lunghezza di default 400
         * @param x         di default 0
         * @param y         di defoult 0
         */
        Finestra(const string& titolo, int altezza=400, int lunghezza=400, int x=0, int y=0);
        
        /**
         * Distruttore, implementa il metodo GLUT 'glutDestroyWindow' che chiude la finestra.
         */
        virtual ~Finestra();
        /**
         * Imposta il sistema di riferimento visivo al variare delle dimensioni della finestra.
         * <br>Esempio:<br>
         * <pre><code>
         * Finestra* finestra = new Finestra{"ciao mondo"};
         * finestra->disegna([]{
         *     ........
         * });
         * finestra->camera([](int w, int h){
         *      Proiezione2D vista(
         *          CampoVisivo(0.0,(double)w,(double)h,0.0),
         *          Area( // finestra visiva
         *              OrigineArea(0,0),
         *              DimensioneArea(h,w)
         *          )
         *      );
         *      vista.applica();
         * });
         * ......
         * </code></pre>
         * @param campoVisivo    puntatore alla funzione <code>void f(int, int)</code> dove gli argomenti sono le
         *                       nuove dimenzioni della finestra (lunghezza e altezza)
         */
        void camera(CodiceSistemaRiferimentoVisivo campoVisivo){vista=campoVisivo;}
        
        /**
         * Permette di disegnare gli oggetti della scena.
         * <br>Esempio:<br>
         * <pre><code>
         * Finestra* finestra = new Finestra{"ciao mondo"};
         * finestra->disegna([]{
         *      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         *      glMatrixMode(GL_MODELVIEW);
         *      glLoadIdentity();
         *      
         *      Osservatore osservatore{
         *          Coordinate{0.0,0.0,0.0},
         *          Coordinate{0.0,0.0,-1.0},
         *          Vettore{0.0,1.0,0.0}
         *      };
         *      osservatore.osserva();
         * 
         *      // AREA DISEGNO 
         *   ..........................
         *   ..........................
         *      glutSwapBuffers(); 
         * });
         * finestra->camera([](int w, int h){
         *      .........
         * });
         * ......
         * </code></pre>
         * 
         * @param scena         puntatore a funzione <code> void f(void)</code> contenente la scena da disegnare e i
         *                      parametri di formattazione GLUT.
         */
        void disegna(CodiceScena scena){disegnoScena = scena;}
        /**
         * Permette di implementare dei comandi dall'input di tastiera. 
         * 
         * @param input        puntatore a funzione <code> void f(unsigned char pulsante, int x, int y)</code>
         *                     contenente il codice che implementa le azioni da tastiera; il parametro 'pulsante'
         *                     rapresenta il testo premuto, mentre i successivi parametri x e y, sono le coordinate
         *                     sullo schermo del mouse.
         */
        void inputTastiera(CodiceTastiera input){tastiera = input;}
        /**
         * Permette di implementare dei comandi dall'input di tastiera usando anche i tasti speciali. 
         * 
         * 
         * @param input        puntatore a funzione <code> void f(int pulsante, int x, int y)</code>
         *                     contenente il codice che implementa le azioni da tastiera; il parametro 'pulsante'
         *                     rapresenta il testo (speciale) premuto, i cui valori sono definiti nel namespace 'TastiSpeciali';
         *                     mentre i successivi parametri x e y, sono le coordinate sullo schermo del mouse.
         */
        void inputTastieraTastiSpeciali(CodiceTastieraTastiSpeciali input)
        {tastieraTastiSpeciali = input;}
        /**
         * Permette di implementare dei comandi tramite il clic del mouse.
         * 
         * @param input         puntatore a funzione <code>void f(int pulsante, int stato, int x, int y)</code>
         *                      contenente il codice che implementa le azioni da clic mouse; il parametro 'puntante' individua 
         *                      l'origine del clic, i cui valori sono definiti nel namespace 'TastiMouse'; il parametro stato
         *                      identifica se l'evento dovra avvenire prima o dopo il clic; infine, i successivi parametri x e y, 
         *                      sono le coordinate sullo schermo del mouse.
         */
        void inputClic(CodiceClicMouse input){clic = input;}
        /**
         * Permette di implementare delle azioni allo scorrere del mouse.
         * 
         * @param input         puntatore a funzione <code>void f(int x, int y)</code> dove i parametri x e y
         *                      sono le coordinate sullo schermo del mouse
         * @param stato         attivo quando è premuto un pulsante del mouse
         */
        void inputMouse(CodiceMuoviMouse input, Stato stato)
        {if(stato == Stato::Passivo)mousePassivo = input;else mouseAttivo=input;}
        /**
         * Aggiunge ulteriore codice da eseguire (ciclicamente) in background. 
         * Se non viene specificato nessun codice da eseguire, verrà eseguito di default solo il ridisegnamento della finestra 
         * ogni 100 millisecondi (0,1 sec)
         * 
         * @param codice        puntatrore a funzione <code>void f(void)</code>
         */
        void background(CodiceAzioni codice){azioni = codice;}
        /**
         * Permette di aggiungere un menu a comparsa tramite mouse.
         * 
         * @param menu          puntatore a funzione <code>void f(void)</code> viene implementata 
         *                      tramite i metodi previsti dalla libreria GLUT.
         */
        void aggiungiMenu(CodiceMenu menu){creaMenu=menu;}
        /**
         * Implementa la finestra GUI tramite la libreria GLUT.
         * 
         * @throw logic_error eccezione che si verifica o quando non è stata disegnata una scena 
         *        o quando la finestra è stata già implementata da un'altra istanza OpenGL.
         */
        void esegui();
        /**
         * Altezza iniziale della finestra
         * @return 
         */
        int altezza()const{return altezzaFinestra;}
        /**
         * Lunghezza iniziale della finestra
         * @return 
         */
        int lunghezza()const{return lunghezzaFinestra;}
        /**
         * Posizione iniziale del vertice alto-sinitro della finestra sullo schermo.
         * @return <code>Posizione<int></code>
         */
        OrigineArea posizioneFinestra()const{return OrigineArea{coordinataX, coordinataY};}
        /**
         * ID della finestra assegnato all'atto della chiamata di <code>void esegui()</code>
         * @return 
         */
        int ID()const{return id_finestra;}
        /**
         * ID della finestra in evidenza.
         * @return 
         */
        static int idFinestraCorrente(){return glutGetWindow();};
        /**
         * Restituisce le coordinate della finestra corrente. 
         * Gli argomenti x e y sono valori in output.
         * 
         * @param x
         * @param y
         */
        static void posizione(int& x,int& y);
        
    private:
        /**
         * La finestra può essere creata, cioè resa visibile, solo una volta da 
         * una sola istanza OpenGL.
         * 
         * @throw logic_error  si verifica se la finestra già è visibile
         */
        void verificaCreazione();
        
        /* puntatori a funzioni*/
        CodiceScena                     disegnoScena    = nullptr;
        CodiceTastiera                  tastiera        = nullptr;
        CodiceTastieraTastiSpeciali     tastieraTastiSpeciali = nullptr;
        CodiceClicMouse                 clic            = nullptr; ///< definisce il comportamento legate al clic da mouse
        CodiceMuoviMouse                mousePassivo    = nullptr; ///< definisce il comportamento legato al movimento del mouse quando passivo
        CodiceMuoviMouse                mouseAttivo     = nullptr; ///< definisce il comportamento legato al movimento del mouse quando attivo
        CodiceSistemaRiferimentoVisivo  vista           = nullptr; ///< definisce il sistema di riferimento nella finestra
        CodiceMenu                      creaMenu        = nullptr; ///< aggiunge menu contesto
        CodiceAzioni                    azioni          = nullptr; ///< aggiungi ulteriore codice da eseguire in background
        
        string titoloFinestra; ///< titolo finestra
        
        int altezzaFinestra, lunghezzaFinestra;
        int coordinataX, coordinataY;
        int id_finestra;
        
        bool creata=false; ///< determina se una finestra è associata ad un'istanza OpenGL
    
        static set<int> finestre; ///< finestre create
        
    };
}

#endif /* finestra_h */
