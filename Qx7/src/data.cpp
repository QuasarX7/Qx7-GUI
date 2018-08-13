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
 * @file data.cpp
 * @author Dr. Domenico della Peruta
 * @date 11-08-2018
 * @version 1.0.1, 12-08-2018
 *
 * @brief File contenente l'implementazione dei metodi della classe Data.
 *
 * @namespace Utili
 * @class Data
 */
#include "data.h"
using namespace Utili;


Data::Data(int gg,int mm, int aaaa){
	if(gg > 0 && gg <= giorniMese(mm,aaaa) && mm > 0 && mm <= 12 && aaaa >= 0){
		_giorno = gg;
		_mese = mm;
		_anno = aaaa;
	}
}


int Data::giorniMese(int mm,int aaaa)const{
	switch(mm){
	case 1:case 3: case 5: case 7: case 8: case 10: case 12: return 31;
	case 2:
		return ((aaaa % 4 == 0 && aaaa % 100 != 0) || aaaa % 400 == 0) ? 29 : 28;// calcolo mese bisestile
	case 4: case 6: case 9: case 11: return 30;
	};
	return -1;
}


void Data::incrementa(UnitàTemporale tipo){
	switch(tipo){
	case UnitàTemporale::GIORNO :
		if(_giorno < giorniMese(_mese,_anno))
			_giorno++;
		else{
			_giorno = 1;
			incrementa(UnitàTemporale::MESE);
		}
		break;
	case UnitàTemporale::MESE :
		if(_mese < 12){
			_mese++;
		}else{
			_mese = 1;
			incrementa(UnitàTemporale::ANNO);
		}
		break;
	case UnitàTemporale::ANNO :
		_anno++;
		break;
	default:
			throw std::invalid_argument{"Errore input metodo 'Data::incrementa(UnitàTemporale tipo)' "};
	};

}


void Data::decrementa(UnitàTemporale tipo){
	switch(tipo){
	case UnitàTemporale::GIORNO:
		if(_giorno > 1)
			_giorno--;
		else{
			decrementa(UnitàTemporale::MESE);
			_giorno = giorniMese(_mese,_anno);
		}
		break;
	case UnitàTemporale::MESE:
		if(_mese > 1){
			_mese--;
		}else{
			decrementa(UnitàTemporale::ANNO);
			_mese = 12;
		}
		break;
	case UnitàTemporale::ANNO:
		_anno--;
		break;
	default:
			throw std::invalid_argument{"Errore input metodo 'Data::decrementa(UnitàTemporale tipo)' "};
	};

}


void Data::aggiungi(UnitàTemporale tipo, u_int valore){
	for(auto i=0; i < valore; i++){
		incrementa(tipo);
	}
}


void Data::sottrai(UnitàTemporale tipo, u_int valore){
	for(auto i=valore; i > 0; i--){
		decrementa(tipo);
	}
}

int Data::giornoSettimana(int gg,int mm,int aaaa)const{
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	aaaa -= mm < 3;
	return (aaaa + aaaa/4 - aaaa/100 + aaaa/400 + t[mm-1] + gg) % 7;
}

string Data::stampa(FormatoData tipo)const{
	stringstream ss;
	string separatore = "/";
	string spazio = " ";
	switch(tipo){
	case FormatoData::ESTESA:
		ss << giornoSettimana() << spazio;
	case FormatoData::NORMALE: ss << doppiaCifraNumero(_giorno)
	<< separatore << doppiaCifraNumero(_mese) << separatore  << _anno; break;

	case FormatoData::ESTESA_TESTUALE:
		ss << giornoSettimana() << spazio;
	case FormatoData::TESTUALE:
		ss << _giorno << spazio << Mese[_mese-1] << spazio  << _anno ; break;


	};

	return ss.str();
}


float Data::valore(UnitàTemporale tipo)const{
	int m = _mese;
	int y = _anno;
	int d = _giorno;


	switch(tipo){
	case UnitàTemporale::GIORNO:{
		if (m < 3){
			y--;
			m += 12;
		}
		return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
	}
	case UnitàTemporale::MESE:
		return valore() / 30.4375f;
	case UnitàTemporale::ANNO:
		return valore() / 365.25f;

	case UnitàTemporale::ORA:
		return valore() * 24.0f;

	case UnitàTemporale::MINUTO:
		return valore(UnitàTemporale::ORA) * 60.0f;

	case UnitàTemporale::SECONDO:
		return valore(UnitàTemporale::MINUTO) * 60.0f;

	case UnitàTemporale::MILLI_SECONDO:
		return valore(UnitàTemporale::SECONDO) * 1000.0f;

	};
	return std::numeric_limits<float>::quiet_NaN();

}



