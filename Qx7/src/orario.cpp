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
 * @file orario.cpp
 * @author Dr. Domenico della Peruta
 * @date 07-08-2018
 * @version 1.0.0, 07-08-2018
 *
 * @brief File contenente l'implementazione dei metodi della classe Orario.
 *
 * @namespace Utili
 * @class Orario
 */
#include "orario.h"
using namespace Utili;

Orario::Orario(int h,int min,float sec) {
	if(h >= 0 && h < 24 && min >= 0 && min < 60 && sec >= 0.0f && sec < 60.0f){
		_ore = h;
		_minuti = min;
		_secondi = sec;
	}else{
		stringstream ss;
		ss << "Errore costruzione orario \"" << h << ":"<<min<<":"<< sec<< "\"..."<<endl;
		throw std::invalid_argument{ss.str()};
	}

}

int Orario::millisecondi()const{
	float millisec = _secondi - secondi();
	return std::floor(static_cast<int>(millisec * 1000.0f));
}


void Orario::incrementa(UnitàTemporale tipo, bool* domani){
	switch(tipo){
	case UnitàTemporale::MILLI_SECONDO:
		if(_secondi < 59.999f)
			_secondi += 0.001f;
		else{
			_secondi = 0.0f;
			incrementa(UnitàTemporale::MINUTO,domani);
		}
		break;
	case UnitàTemporale::SECONDO:
		if(_secondi < 59.0f){
			_secondi += 1.0f;
		}else{
			_secondi = 0.0f;
			incrementa(UnitàTemporale::MINUTO,domani);
		}
		break;
	case UnitàTemporale::MINUTO:
		if(_minuti < 59){
			_minuti++;
		}else{
			_minuti = 0;
			incrementa(UnitàTemporale::ORA,domani);
		}
		break;
	case UnitàTemporale::ORA:
		if(_ore < 23){
			_ore++;
		}else{
			_ore = 0;
			if(domani != nullptr)
				*domani = true;
		}
		break;
	default:
			throw std::invalid_argument{"Errore input metodo 'Orario::incrementa(UnitàTemporale tipo)' "};
	};

}


void Orario::decrementa(UnitàTemporale tipo, bool* ieri){
	switch(tipo){
	case UnitàTemporale::MILLI_SECONDO:
		if(_secondi > 0.0f)
			_secondi -= 0.001f;
		else{
			_secondi = 59.999f;
			decrementa(UnitàTemporale::MINUTO,ieri);
		}
		break;
	case UnitàTemporale::SECONDO:
		if(_secondi > 0.0f){
			_secondi -= 1.0f;
		}else{
			_secondi = 59.0f;
			decrementa(UnitàTemporale::MINUTO,ieri);
		}
		break;
	case UnitàTemporale::MINUTO:
		if(_minuti > 0){
			_minuti--;
		}else{
			_minuti = 59;
			decrementa(UnitàTemporale::ORA,ieri);
		}
		break;
	case UnitàTemporale::ORA:
		if(_ore > 0){
			_ore--;
		}else{
			_ore = 23;
			if(ieri != nullptr)
				*ieri = true;
		}
		break;
	default:
			throw std::invalid_argument{"Errore input metodo 'Orario::decrementa(UnitàTemporale tipo)' "};
	};

}


void Orario::aggiungi(UnitàTemporale tipo, u_int valore, int* giorniIncrementati){

	bool domani = false;

	for(auto i=0; i < valore; i++){
		incrementa(tipo,&domani);
		if(domani && giorniIncrementati != nullptr)
			(*giorniIncrementati)++;
		domani = false;
	}

}


void Orario::sottrai(UnitàTemporale tipo, u_int valore, int* giorniDecrementati){

	bool ieri = false;

	for(auto i=valore; i > 0; i--){
		decrementa(tipo,&ieri);
		if(ieri && giorniDecrementati != nullptr)
			(*giorniDecrementati)++;
		ieri = false;
	}

}


string Orario::stampa(FormatoOrario formato){
	stringstream ss;
	ss << doppiaCifraNumero(_ore)<< ":"<< doppiaCifraNumero(_minuti);
	if(formato == FormatoOrario::NO_SECONDI || formato == FormatoOrario::ESTESO_MILLISECONDI)
		ss << ":" << doppiaCifraNumero(secondi());
	if(formato == FormatoOrario::ESTESO_MILLISECONDI)
			ss << "," << triplaCifraNumero(millisecondi());

	return ss.str();
}

string Orario::doppiaCifraNumero(int numero)const{
	stringstream ss;
	if(numero < 10)
		ss <<  "0";
	ss << numero;
	return ss.str();
}

string Orario::triplaCifraNumero(int numero)const{
	stringstream ss;
	if(numero < 10)
		ss <<  "00";
	else if(numero < 100)
		ss <<  "0";
	ss << numero;
	return ss.str();
}


Orario Orario::oraAttuale(){
	timeval tempo; // struttura contenente i secondi e i microsecondi
	gettimeofday(&tempo, 0);
	time_t t = tempo.tv_sec;
	auto adesso = localtime(&t);
	return Orario{
				adesso->tm_hour,
				adesso->tm_min,
				adesso->tm_sec + static_cast<float>(tempo.tv_usec/1000000.0f)
			};

}

float Orario::valore(UnitàTemporale tipo)const{
	switch(tipo){
	case UnitàTemporale::MILLI_SECONDO: return valore()*1000;
	case UnitàTemporale::SECONDO: 		return _secondi + _minuti*60 + _ore*3600;
	case UnitàTemporale::MINUTO:		return valore()/60;
	case UnitàTemporale::ORA:			return valore()/3600;
	default:
			throw std::invalid_argument{"Errore input metodo 'Orario::valore(UnitàTemporale tipo)' "};
	};
}






