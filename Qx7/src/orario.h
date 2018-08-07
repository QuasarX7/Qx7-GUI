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
 * @file orario.h
 * @author Dr. Domenico della Peruta
 * @date 07-08-2018
 * @version 1.0.0, 07-08-2018
 *
 * @brief File contenente l'intestazione della classe Orario.
 *
 * @namespace Utili
 * @class Orario
 */
#ifndef SRC_ORARIO_H_
#define SRC_ORARIO_H_

#include <sys/time.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

namespace Utili {

enum class UnitàTemporale{
	ANNO,MESE,GIORNO,ORA,MINUTO,SECONDO,MILLI_SECONDO
};

enum class FormatoOrario{
	SI_SECONDI,			// 12:25:05
	NO_SECONDI,			// 12:25
	ESTESO_MILLISECONDI // 12:25:05.012
};
/**
 * La classe Orario gestisce e spemplifica i calcoli temporali sugli orari.
 */
class Orario {
public:
	Orario(int h,int min, float sec=0.0f);
	Orario(const Orario& copia):_ore{copia._ore},_minuti{copia._minuti},_secondi{copia._secondi}{}
	virtual ~Orario() {}

	int ore()const{return _ore;}
	int minuti()const{return _minuti;}
	int secondi()const{return static_cast<int>(_secondi);}
	int millisecondi()const;

	void incrementa(UnitàTemporale tipo, bool* domani = nullptr);
	void decrementa(UnitàTemporale tipo, bool* ieri = nullptr);

	void aggiungi(UnitàTemporale tipo, u_int valore, int* giorniIncrementati = nullptr);
	void sottrai(UnitàTemporale tipo, u_int valore, int* giorniDecrementati = nullptr);

	string stampa(FormatoOrario formato = FormatoOrario::NO_SECONDI);

	friend ostream& operator<<(ostream& out, const Orario& orario)
	{out << orario.ore() << ":" << orario.minuti() <<":"<< orario.secondi() <<" ["<< orario.millisecondi()<<"ms]"; return out;}

	static Orario oraAttuale();

	float valore(UnitàTemporale tipo=UnitàTemporale::SECONDO)const;

	friend bool operator==(const Orario& a, const Orario& b)
	{return a.valore() == b.valore();}

	friend bool operator!=(const Orario& a, const Orario& b)
	{return !(a == b);}

	friend bool operator<(const Orario& a, const Orario& b)
	{return a.valore() < b.valore();}


	friend bool operator>(const Orario& a, const Orario& b)
	{return b < a;}

	friend bool operator<=(const Orario& a, const Orario& b)
	{return (a == b) && (a < b);}

	friend bool operator>=(const Orario& a, const Orario& b)
	{return (a == b) && (a > b);}

	float differenza(const Orario& confronto,UnitàTemporale tipo=UnitàTemporale::SECONDO)const
	{return valore(tipo) - confronto.valore(tipo);}



private:
	string doppiaCifraNumero(int numero)const;
	string triplaCifraNumero(int numero)const;

	int _ore,_minuti;
	float _secondi;

};

} /* namespace Utili */

#endif /* SRC_ORARIO_H_ */
