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
 * @file momento.h
 * @author Dr. Domenico della Peruta
 * @date 11-08-2018
 * @version 1.0.0, 11-08-2018
 *
 * @brief File contenente l'intestazione della classe astratta Momento.
 *
 * @namespace Utili
 * @class Momento
 */
#ifndef SRC_MOMENTO_H_
#define SRC_MOMENTO_H_

#include <sstream>
#include <string>
using namespace std;

namespace Utili {

enum class UnitàTemporale{
	ANNO,MESE,GIORNO,ORA,MINUTO,SECONDO,MILLI_SECONDO
};

/**
 * La classe astratta Momento identifica una posizione temporale in cui si verifica
 * un evento generico. Da essa derivano la classe Data e Orario
 */
class Momento {
public:
	virtual ~Momento(){}

	virtual float valore(UnitàTemporale tipo)const =0;

	float differenza(const Momento& confronto, UnitàTemporale tipo)const{
		return valore(tipo) - confronto.valore(tipo);
	}

	friend bool operator==(const Momento& a, const Momento& b)
	{return a.valore(UnitàTemporale::SECONDO) == b.valore(UnitàTemporale::SECONDO);}

	friend bool operator!=(const Momento& a, const Momento& b)
	{return !(a == b);}

	friend bool operator<(const Momento& a, const Momento& b)
	{return a.valore(UnitàTemporale::SECONDO) < b.valore(UnitàTemporale::SECONDO);}


	friend bool operator>(const Momento& a, const Momento& b)
	{return b < a;}

	friend bool operator<=(const Momento& a, const Momento& b)
	{return (a == b) && (a < b);}

	friend bool operator>=(const Momento& a, const Momento& b)
	{return (a == b) && (a > b);}
protected:
	Momento(){}

	string doppiaCifraNumero(int numero)const;
	string triplaCifraNumero(int numero)const;
};



} /* namespace Utili */

#endif /* SRC_MOMENTO_H_ */
