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
 * @file oggetto.h
 * @author Dr. Domenico della Peruta
 * @date 05-01-2018
 * @version 2.0.3, 15-07-2018
 * 
 * @brief File contenente l'intestazione della classe Oggetto.
 * 
 * @namespace Utili
 * @class Oggetto
 */

#ifndef oggetto_h
#define oggetto_h

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;


namespace Utili {
    /**
     * La classe Oggetto oltre ad identificare un oggetto generico da cui derivano
     * altri oggetti, permette di generare una struttura ad albero nidificata: 
     * ogni oggetto può essere legato tramite puntatore "intelligenti" ad un altro
     * oggetto genitore. 
     * L'uso di puntatori "intelligenti" di tipo shared_ptr (C++11)
     * permette di distruggere in modo automatico l'oggetto dall'area heap
     * quando quest'ultimo non è più utilizzato nel programma.
     */
    class Oggetto;
    
    /**
     * Puntatore "intelligente" ad un Oggetto, di tipo shared_ptr (C++11), permette la 
     * distruzione automatica nell'area heap dell'oggetto.
     */
    typedef shared_ptr<Oggetto> pOggetto;
    
    /**
     * Metodo che permette di allocare la memoria dinamica riferita al puntatore 'shared_ptr'.
     * <pre>
     * Esempio:
     * <code>
     * pOggetto p = Utili::crea<Oggetto>();
     * </code>
     * </pre>
     * 
     * @param in
     * @return 
     */
    template<typename TipoOggetto,typename... Input>
    shared_ptr<TipoOggetto> crea(Input&&... in){
        return shared_ptr<TipoOggetto>{new TipoOggetto{std::forward<Input>(in)...}};
    }
    
    
    
    /**
     * Definizione della classe generica Oggetto
     */
    class Oggetto : public std::enable_shared_from_this<Oggetto>{
    public:
        /**
         * Costruttore
         */
        Oggetto();
        /**
         * Distruttore
         */
        virtual ~Oggetto(){}
        /**
         * Oggetto padre se esiste.
         * @return 
         */
        pOggetto genitore()const{return _genitore;}
        
        /**
         * Permette di accedere in modo sequenziale agli oggetti figli.
         * @param indice
         * @return 
         */
        pOggetto figlio(size_t indice)const;
        /**
         * Numero degli oggetti figli, cioè degli oggetti associati.
         * @return 
         */
        size_t numeroFigli()const{return figli.size();}
        /**
         * Informazioni di debug, da implementare delle classi derivate.
         * @return 
         */
        virtual string debug()const;
        
        /**
         * Permette ad un oggetto di cambiare oggetto da cui dipende.
         * @param genitore
         */
        virtual void assegnaGenitore(pOggetto genitore);
        
        /**
         * Metodo di classe che permette di costruire in modo completa un oggetto
         * ed assegnargli un oggetto genitore.
         * <pre>
         * <code>
         * class X: public Oggetto{
         *      public:
         *          X(int a, char b){......}
         *      ......
         * };
         * typedef shared_ptr<X> pX; 
         * 
         * pOggetto padre = Utili::crea<Oggetto>();  // genitore nullptr
         * pX figlio = Oggetto::crea<X>(padre, 123, 'k'); // genitore 'padre' , arg.1 (int), arg.2 (char)
         * </code>
         * </pre>
         * @param genitore
         * @param in
         * @return 
         */
        template<typename Tipo,typename... Input>
        static shared_ptr<Tipo> crea(pOggetto genitore, Input&&... in){
            shared_ptr<Tipo> oggetto{new Tipo{std::forward<Input>(in)...}};
            oggetto->assegnaGenitore(genitore);
            return oggetto;
        }
        
    protected:
        /**
         * Permette di legare un oggetto ad un altro da cui dipenderà.
         * @param figlio
         */
        void adotta(pOggetto figlio);
        /**
         * Elimina la dipendenza di un oggetto "figlio".
         * 
         * @param indice
         * @return 
         */
        pOggetto abbandona(size_t indice);
        
        
    private:
        
        vector<weak_ptr<Oggetto> > figli{};
        pOggetto _genitore;
        
        
    };
    
    
}
#endif /* oggetto_h */
