/****************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7.                                          *
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
 * @file oggetto.cpp
 * @author Dr. Domenico della Peruta
 * @date 05-01-2018
 * @version 2.0.3, 15-07-2018
 * 
 * @brief File contenente l'implementazione della classe Oggetto.
 * 
 * @namespace Utili
 * @class Oggetto
 */

#include "oggetto.h"
using namespace Utili;

Oggetto::Oggetto():_genitore{nullptr}
{
}

pOggetto Oggetto::figlio(size_t indice)const{
    if(indice < figli.size())
        return figli[indice].lock();
    else
        return nullptr;
}


void Oggetto::adotta(pOggetto figlio){
    figlio->_genitore = shared_from_this();
    figli.push_back(figlio);
}

void Oggetto::assegnaGenitore(pOggetto genitore){
    _genitore = genitore;
        if(genitore != nullptr){
        _genitore->figli.push_back(shared_from_this());
    }
}

pOggetto Oggetto::abbandona(size_t indice){
    auto figlio = figli[indice].lock();
    figlio->_genitore = nullptr;
    figli.erase(figli.begin()+indice);
    return figlio;
}


string Oggetto::debug()const{
    stringstream ss;
    ss << "Oggetto [" << this <<"]" ;
    if(_genitore != nullptr ) ss << " - > (Genitore) [" << this <<"]";
    ss << std::endl;
    return ss.str();
}
        
