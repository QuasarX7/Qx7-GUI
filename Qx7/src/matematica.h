/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7.                                              *
 *                                                                          *
 * Qx7 è una libreria software gratuita: puoi ridistribuirlo e/o modificarlo*
 * sotto i termini della GNU Lesser General Public License come pubblicato  *
 * dalla Free Software Foundation, o la versione 3 della licenza, o         *
 * (a tua scelta) qualsiasi versione successiva.                            *
 *                                                                          *
 * Qx7 è distribuita nella speranza che sia utile,                          *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7. Altrimenti, vedi al sito                          *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7.                                                *
 *                                                                          *
 *   Qx7 is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7 is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7.  If not, see                                   *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/

/**
 * @file matematica.h
 * @author Dr. Domenico della Peruta
 * @date 04-01-2018
 * @version 1.0.2, 23-07-2018
 * 
 * @brief File contenente l'intestazione e l'implementazione di alcune classi utili
 * nel campo della matematica e giometria.
 * 
 * @namespace Utili
 * @class Posizione
 * @class Dimensione
 */
#ifndef matematica_h
#define matematica_h

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <limits>
#include "testo.h"
using namespace std;

namespace Utili {
    
    // costanti angolari
    
    const static auto π   = M_PI;        ///< pi greco
    const static auto π¼  = M_PI_4;      ///< pi greco quarti
    const static auto π½  = M_PI_2;      ///< pi greco mezzi
    const static auto π3½ = M_PI+M_PI_2; ///< tre pi greco mezzi
    const static auto π2  = M_PI;        ///< due pi greco
    
    const static auto NUMERO_REALE_INDEFINITO = std::numeric_limits<double>::quiet_NaN();
    
    /**
     * Metodo che restituisce un numero casuale tra 0 e 1.
     * @return
     */
    template<typename numero>
    numero casuale(){ return (numero)std::rand()/(numero)RAND_MAX; }
    
    /**
     * La classe modello Posizione rappersenta un vettore numerico 2D o 3D.
     * 
     */
    template<typename numero>
    class Posizione{
    public:
        /**
         * Costruttore a due o tre argomenti numerici.
         * @throw invalid_argument      se il parametro non è un tipo numerico
         * @param x
         * @param y
         * @param z
         */
        Posizione(numero x, numero y,numero z=0);
      
        /**
         * Costruttore per copia.
         * @param copia
         */
        Posizione(const Posizione<numero>& copia)
        {_x=copia._x;_y=copia._y;_z=copia._z;}
        /**
         * Operatore di assegnazione
         * @param copia
         */
        Posizione<numero>& operator = (const Posizione<numero>& copia)
        {_x=copia._x;_y=copia._y;_z=copia._z;return *this;}
        
        /**
         * @fn numero x()
         * @brief restituisce la coordinata x
         * 
         * @return 
         */
        /**
         * @fn numero y()
         * @brief Restituisce la coordinata y
         * 
         * @return 
         */
        /**
         * @fn numero z()
         * @brief Restituisce la coordinata z
         * 
         * @return 
         */
        numero x()const{return _x;}
        numero y()const{return _y;}
        numero z()const{return _z;}
        /**
         * @fn void x(numero v)
         * @brief Imposta la coordinata x
         * 
         * @param v
         */
        /**
         * @fn void y(numero v)
         * @brief Imposta la coordinata y
         * 
         * @param v
         */
        /**
         * @fn void z(numero v)
         * @brief Imposta la coordinata z
         * 
         * @param v
         */
        void x(numero v){ _x=v;}
        void y(numero v){ _y=v;}
        void z(numero v){ _z=v;}
        /**
         * Distanza dalla posizione l'origine degli assi di riferimento.
         * @return 
         */
        numero distanzaOrigine()const{return sqrt(_x*_x + _y*_y + _z*_z);}
        /**
         * Angolo del piano ZP che va dallo zenit alla posizione corrente (P).
         * @return 
         */
        numero distanzaZenitale()const{return acos(_z/distanzaOrigine());}
        /**
         * Angolo del piano XY che va dall'asse X al punto P con centro nell'origine.
         * @return 
         */
        numero azimutOrigine()const;
        /**
         * Distanza dalla posizione p2.
         * @param p2
         * @return 
         */
        numero distanza(const Posizione<numero>& p2)const;
        /**
         * Angolo di inclinazione del segmento formato con il punto p2, con riferimento 
         * al piano XY.
         * @param p2
         * @return 
         */
        numero azimut(const Posizione<numero>& p2)const;
        /**
         * Metodo operatore di flusso stream d'inserimento, implementato in linea.
         * @param os
         * @param p
         * @return 
         */
        friend ostream& operator<<(ostream& os, const Posizione& p)
        {os << "("<< p._x << ", " << p._y << ", " << p._z <<")"; return os;}
        
        
    private:
        numero _x,_y,_z;
    };
    
    typedef Posizione<double> Coordinate;
    typedef Posizione<double> Vettore;
    
    /**
     * La Classe modello Dimensione rappresenta l'area (quadrata) o il volume (cubico)
     * occupato da un oggetto.
     */
    template<typename numero>
    class Dimensione{
    public:
        Dimensione(numero altezza,numero lunghezza, numero profondita=0)
        : h{altezza},b{lunghezza},s{profondita}
        {}
        Dimensione(const Dimensione& copia)
        : h{copia.h},b{copia.b},s{copia.s}
        {}
        Dimensione& operator = (const Dimensione& copia)
        {h=copia.h;b=copia.b;s=copia.s;return *this;}
        
        numero altezza()const{return h;}
        numero lunghezza()const{return b;}
        numero profondita()const{return s;}


    private:
        numero h, b, s;
    };

    


        /* Imprementazione metodi classi*/

    template <typename numero> 
    Posizione<numero>::Posizione(numero x, numero y,numero z):_x{x},_y{y},_z{z}{
        if(!is_floating_point<numero>::value && !is_integral<numero>::value)
            throw std::invalid_argument{"argomento non numerico!"};
    }


    template <typename numero> 
    numero Posizione<numero>::azimutOrigine() const{
        if(_x == 0 && _y > 0) return π½;
        else if(_x == 0 && _y < 0) return π3½;
        else if(_x == 0 && _y == 0)return NAN;
        else if(_x > 0 && _y >= 0)return atan(_y/_x);
        else if( (_x > 0 && _y < 0) || (_x < 0 && _y > 0) )return atan(_y/_x) + π2;
        else if(_x < 0 && _y <= 0) return atan(_y/_x) + π;
    }

    template <typename numero> 
    numero Posizione<numero>::distanza(const Posizione<numero>& p2) const{
        numero dx = p2._x - _x;
        numero dy = p2._y - _y;
        numero dz = p2._z - _z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }

    template <typename numero> 
    numero Posizione<numero>::azimut(const Posizione<numero>& p2) const{
        numero dx = p2._x - _x;
        numero dy = p2._y - _y;
        if(dx == 0 && dy > 0) return π½;
        else if(dx == 0 && dy < 0) return π3½;
        else if(dx == 0 && dy == 0)return NAN;
        else if(dx > 0 && dy >= 0)return atan(dy/dx);
        else if( (dx > 0 && dy < 0) || (dx < 0 && dy > 0) )return atan(dy/dx) + π2;
        else if(dx < 0 && dy <= 0) return atan(dy/dx) +π;
    }
    



            
}


#endif 
