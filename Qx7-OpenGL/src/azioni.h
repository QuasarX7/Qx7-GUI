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
 * @version 0.0.2, 02-06-2018
 * 
 * @brief File contenente la definizione e l'implementazione dei metodi in linea della 
 * classe Azione e delle sue derivate.
 * 
 * @namespace Grafica
 * @class Azione
 * @enum Asse
 * @enum Ritardo
 */
#ifndef AZIONI_H
#define AZIONI_H

#include "matematica.h"
#include "ciclo.h"
using namespace Utili;
#include "colore.h"

namespace Grafica {
            
    enum class Asse{X,Y,Z};
    
    enum Ritardo{
        SECONDI,
        DECISECONDI
    };
    
    typedef Posizione<double> Punto;    
    
    
    /**
     * La classe Azione che implementa un evento generico che ha un inizio e una fine
     * temporale.
     */
    class Azione {
    public:
        Azione(const Tempo& inizio,const Tempo& fine)
        :inizioAzione{inizio},fineAzione{fine}
        {}
        virtual ~Azione(){}
        Tempo inizio()const{return inizioAzione;}
        Tempo fine()const{return fineAzione;}
    protected:
        Tempo inizioAzione,fineAzione;
    };
    
    /**
     * La classe Movimento permette di spostare un oggetto grafico, ad ogni intervallo temporare
     * di aggiornamento, lungo una traiettoria sequenziale di punti in modo ciclico.
     */
    class Movimento: public Azione{
    public:
        Movimento(const Tempo& inizio,const Tempo& fine, const vector<Punto>& traiettoria)
        :Azione{inizio,fine},posizioni{traiettoria}{}
        vector<Punto> traiettoria()const{return posizioni;}
    protected:
        vector<Punto> posizioni;
    };
    
    /**
     * La classe MovimentoRettilineoUniforme permette di muovere un oggetto in modo rettilineo e uniforme.
     */
    class MovimentoRettilineoUniforme: public Azione{
    public:
        MovimentoRettilineoUniforme(const Tempo& inizio,const Tempo& fine, const Vettore& velocità)
        :Azione{inizio,fine},movimento{velocità}{}
        Vettore velocità()const{return movimento;}
    protected:
        Vettore movimento;
    };
    
    
    /**
     * La classe RotazioneCostante fa ruotare un oggetto in modo costante lungo uno dei suoi assi.
     */
    class RotazioneCostante: public Azione{
    public:
        RotazioneCostante(const Tempo& inizio,const Tempo& fine, Asse asse, double velocità)
        :Azione{inizio,fine},velocitàDiRotazione{velocità},asseDiRotazione{asse}{}
        
        double velocità()const{return velocitàDiRotazione;}
        Asse asse()const{return asseDiRotazione;}
        
    protected:
        double velocitàDiRotazione;
        Asse asseDiRotazione;
    };
    
    /**
     * La classe Dimensiona ingrandisce o riduce le dimensioni.
     */
    class Dimensiona: public Azione{
    public:
        Dimensiona(const Tempo& inizio,const Tempo& fine,double fattore)
        :Azione{inizio,fine},fattoreZoom{fattore}{}
        
        double fattore()const{return fattoreZoom;}
        
    protected:
        double fattoreZoom;
    };
    
    /**
     * La classe ColoraSfondo permette di reimpostare il colore dello sfondo secondo una sequenza definitaa.
     */
    class ColoraSfondo: public Azione{
    public:
        ColoraSfondo(const Tempo& inizio,const Tempo& fine, const vector<Colore>& colori,Ritardo aggiornamento=SECONDI)
        :Azione{inizio,fine},sequenzaColiri{colori},ritardo{aggiornamento}
        {}
        vector<Colore> colori()const{return sequenzaColiri;}
        Ritardo aggiornamento()const{return ritardo;}
    protected:
        vector<Colore> sequenzaColiri;
        Ritardo ritardo;
    };
    /**
     * La classe ColoraBordo permette di reimpostare il colore dei bordi secondo una sequenza definita.
     */
    class ColoraBordo: public ColoraSfondo{
    public:
        ColoraBordo(const Tempo& inizio,const Tempo& fine, const vector<Colore>& colori,Ritardo aggiornamento=SECONDI)
        :ColoraSfondo{inizio,fine,colori,aggiornamento}{}
    };
    
    
    typedef shared_ptr<Azione>                      pAzione;                     ///< Puntatore inteligente ad Azione
    typedef shared_ptr<Movimento>                   pMovimento;                  ///< Puntatore inteligente ad Movimento
    typedef shared_ptr<MovimentoRettilineoUniforme> pMovimentoRettilineoUniforme;    ///< Puntatore inteligente a MovimentoRettilineoUniforme
    typedef shared_ptr<RotazioneCostante>           pRotazioneCostante;          ///< Puntatore inteligente a RotazioneCostante
    typedef shared_ptr<Dimensiona>                  pDimensiona;                ///< Puntatore inteligente a Dimensiona
    typedef shared_ptr<ColoraSfondo>               pColoraSfondo;    ///< Puntatore inteligente a ColoraSfondo
    typedef shared_ptr<ColoraBordo>                 pColoraBordo;    ///< Puntatore inteligente a ColoraBordo
    
    
}

#endif /* AZIONI_H */

