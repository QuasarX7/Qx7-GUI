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
 * @file terminale.h
 * @author Dr. Domenico della Peruta
 * @date 31-08-2018
 * @version 1.0.0, 01-09-2018
 *
 * @brief File contenente l'intestazione e l'implementazione della classe Terminale.
 *
 * @namespace Sistema
 * @class Terminale
 */
#ifndef SRC_TERMINALE_H_
#define SRC_TERMINALE_H_

#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

#include "testo.h"
using namespace Utili;

namespace Sistema {

/**
 * La classe Terminale implementa i comandi da console.
 */
class Terminale {
public:
	/**
	 * Costruttore.
	 * @param comando
	 * @throw std::length_error 	sollevato se la lunghezza del comando è superiore a 128 caratteri
	 */
	Terminale(const string& comando);
	/**
	 * Distruttore.
	 */
	virtual ~Terminale() {}
	/**
	 * Metodo che permette di visualizzare (per la copia) la stringa memorizzato nel SO.
	 * @return
	 */
	static Testo valoreInMemoria();
	/**
	 * Metodo che permette di memorizzare una stringa di caratteri (numero <= 128)
	 * @param copia
	 */
	static void valoreDaMemorizzare(const Testo& copia);
	/**
	 * Esegue il comando
	 * @return
	 */
	string esegui()const;


protected:
	string cmd;
};


} /* namespace Sistema */

#endif /* SRC_TERMINALE_H_ */
