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
 * @file data.h
 * @author Dr. Domenico della Peruta
 * @date 11-08-2018
 * @version 1.0.2, 16-08-2018
 *
 * @brief File contenente l'intestazione della classe Data.
 *
 * @namespace Utili
 * @class Data
 * @enum FormatoData
 */
#ifndef SRC_DATA_H_
#define SRC_DATA_H_

#include <cmath>
#include <sstream>
using namespace std;

#include <ctime>
using namespace std;

#include "momento.h"


namespace Utili {

enum class FormatoData{
	NORMALE,			//         12/03/2014
	TESTUALE,			//         02 gennaio 2015
	ESTESA,    			// mercoledi 08/08/2018
	ESTESA_TESTUALE		// giovedì 09 agosto 2018
};

const string GiornoSettimana[]{
		"domenica",
		"lunedì",
		"martedì",
		"mercoledì",
		"giovedì",
		"venerdì",
		"sabato"
};

const string Mese[]{
		"gennaio",
		"febbraio",
		"marzo",
		"aprile",
		"maggio",
		"giugno",
		"luglio",
		"agosto",
		"settembre",
		"ottobre",
		"novembre",
		"dicembre"
};
/**
 * La classe Data implementa la rappresentazione di un giorno del calendario Gregoriano.
 */
class Data : public Momento{
public:
	/**
	 * Costruttore di data.
	 *
	 * @param gg
	 * @param mm
	 * @param aaaa
	 * @throw std::invalid_argument 	data non formattata correttamente
	 */
	Data(int gg,int mm, int aaaa);
	virtual ~Data() {}

	int giorno()const{return _giorno;}
	int mese()const{return _mese;}
	int anno()const{return _anno;}

	void incrementa(UnitàTemporale tipo);
	void decrementa(UnitàTemporale tipo);

	void aggiungi(UnitàTemporale tipo, u_int valore);
	void sottrai(UnitàTemporale tipo, u_int valore);

	string stampa(FormatoData tipo=FormatoData::NORMALE)const;

	virtual float valore(UnitàTemporale tipo=UnitàTemporale::GIORNO)const;

	string giornoSettimana()const{return GiornoSettimana[giornoSettimana(_giorno,_mese,_anno)];}
protected:
	int giorniMese(int mm,int aaaa)const;
	int giornoSettimana(int gg,int mm,int aaaa)const;

	int _giorno,_mese,_anno;
};

} /* namespace Utili */

#endif /* SRC_DATA_H_ */
