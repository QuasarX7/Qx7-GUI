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
 * @file azioni.h
 * @author Dr. Domenico della Peruta
 * @date 23-03-2018
 * @version 1.0.0, 25-03-2018
 * 
 * @brief File contenente la definizione e l'implementazione dei metodi della classe Figura.
 * 
 * @namespace Grafica
 * @class Figura
 */
#ifndef figura_h
#define figura_h

#include "azioni.h"
#include "colore.h" // include anche "disegno.h"

#include "ciclo.h"
using namespace Utili;


namespace Grafica {
    
    
    
    /**
     * La classe Figura rappresenta un disegno generico rappresentato da una posizione,
     * da un colore di fondo e un bordo; su cui è possibile effetturare delle manipolazioni
     * come: la traslazione, la rotazione o lo scalamento.
     */
    class Figura: public Disegno{
    public:
        /**
         * Costruttore
         * 
         * @param _posizione
         * @param sfondo
         * @param bordo
         */
        Figura(const Punto& _posizione,const Colore& sfondo,const Colore& bordo)
        : posizione(_posizione), coloreSfondo(sfondo), coloreBordo(bordo), spessoreBordo(1.0),
        angoloRotazioneX{0.0},angoloRotazioneY{0.0},angoloRotazioneZ{0.0},scala{1.0},trasla{0.0,0.0,0.0}
        {}
        /**
         * Distruttore
         */
        virtual ~Figura(){}
        /**
         * Metodo da implementare nelle classi derivate, contenente il codice per il disegno
         * della figura.
         */
        
        /* ---------- DISEGNA ------------- */
        
        virtual void disegna() const override =0;
        /**
         * Assegna colore e spessore al bordo.
         * @param colore
         * @param spessore      di default è 1.0
         */
        void bordo(const Colore& colore, double spessore=1.0)
        {coloreBordo=colore; spessoreBordo=spessore;}
        /**
         * Assegna spessore al bordo.
         * @param spessore
         */
        void bordo(double spessore=1.0)
        {spessoreBordo=spessore;}
        /**
         * Assegna il colore della figura.
         * 
         * @param colore
         */
        void sfondo(const Colore& colore){coloreSfondo=colore;}
        /**
         * Permette il riposizionamento della figura.
         * @param punto
         */
        virtual void posiziona(const Punto& punto){posizione=punto;}
        /**
         * Posizione corente della figura
         * @return 
         */
        Punto localizzazione()const{return posizione;}
        
        /* -------- TRASFORMAZIONI --------*/
        
        /**
         * Effettua la rotazione di una figura geometrica, sell'oggetto è 3D va indicato anche il secondo 
         * parametro 'asse' di rotazione che per le figure piane è di default "Z"
         * 
         * @param angolo    espresso in sessadesimali (Es.: "45.5°")
         * @param asse
         */
        void ruota(double angolo,Grafica::Asse asse = Asse::Z);
        
        /**
         * Ingrandisce o riduce una figura secondo un fattore di scala (in tutte le 
         * direzioni).
         * 
         * @param fattore
         */
        void ingrandisci(double fattore)
        {scala=fattore;}
        
        /**
         * Sposta una figura rispetto al punto di posizionamento.
         * @param spostamento
         */
        void sposta(const Vettore& spostamento)
        {trasla = spostamento;}
        
        /* ------------ AZIONI --------------*/
        
        /**
         * Metodo che permete di effetturare una lista di Azioni di movimento. Viene implementato all'interno
         * della funzione lambda passata al metodo <code>background(...)</code> della classe <code>Finestra</code>.
         * 
         * @param azioni
         */
        void anima(const vector<pAzione>& azioni);
        
        /**
         * Tempo trascorso dall'inizio delle "azioni".
         * 
         * @return std::chrono::milliseconds (millisecondi)
         */
        Tempo età()const{return vita;}
        
        /**
         * Permette di riattivare le "azioni" se definite.
         */
        void azzeraVita(){vita=0ms;}
       
    protected:
        /**
         * Metodo protetto che effettua le trasformazioni fordamentali di traslazione, 
         * rotazione e scalamento.
         * 
         * @param baricentro
         */
        virtual void trasforma(const Vettore& baricentro)const;
        
        
        Punto posizione;
        Colore coloreSfondo, coloreBordo;
        double spessoreBordo;
        
        double angoloRotazioneZ,angoloRotazioneY,angoloRotazioneX, scala;
        Vettore trasla;
        
        Tempo vita = 0ms;
     
    private:
        //variabili Azione (colori)
        size_t indiceColori=0;
        size_t ritardo=0;
                
    };
}

#endif /* figura_h */
