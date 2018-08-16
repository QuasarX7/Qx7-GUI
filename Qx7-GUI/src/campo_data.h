/***************************************************************************
 * Copyright (C) 2017-2018 by Dott. Domenico della Peruta                   *
 *                                                                          *
 * (ITALIANO)                                                               *
 * Questo file è parte di Qx7-GUI.                                          *
 *                                                                          *
 * Qx7-GUI è una libreria software gratuita: puoi ridistribuirla e/o        *
 * modificarla sotto i termini della GNU Lesser General Public License come *
 * pubblicato  dalla Free Software Foundation, o la versione 3 della licenza,
 *  o (a tua scelta) qualsiasi versione successiva.                         *
 *                                                                          *
 * Qx7-GUI è distribuita nella speranza che sia utile,                      *
 * ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di         *
 * COMMERCIABILITÀ O IDONEITÀ PER UN PARTICOLARE SCOPO. Vedi il             *
 * GNU Lesser General Public License per maggiori dettagli.                 *
 *                                                                          *
 * Dovresti aver ricevuto una copia di GNU Lesser General Public            *
 * Licenza insieme a Qx7-GUI. Altrimenti, vedi al sito                      *
 * <http://www.gnu.org/licenses/>.                                          *
 *                                                                          *
 * (ENGLISH)                                                                *
 * This file is part of Qx7-GUI.                                            *
 *                                                                          *
 *   Qx7-GUI is free software: you can redistribute it and/or modify it     *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Qx7-GUI is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Qx7-GUI.  If not, see                               *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/
/**
 * @file  campo_data.h
 * @author Dr. Domenico della Peruta
 * @date 12-08-2018
 * @version 1.0.0, 13-08-2018
 *
 * @brief File contenente l'intestazione e l'implementazione della classe CampoData.
 *
 * @namespace GUI
 * @class CampoData
 */
#ifndef SRC_CAMPO_DATA_H_
#define SRC_CAMPO_DATA_H_

#include <memory>
using namespace std;

#include "data.h"
using namespace Utili;

#include "campo_numerico.h"


namespace GUI {

typedef shared_ptr<Data> pData;

class CampoData;
typedef shared_ptr<CampoData> pCampoData;

/**
 * La classe CampoData permette l'inserimento dell'input riferito a una data del calendario Gregoriano.
 */
class CampoData: public CampoNumerico {
public:
	/**
	 * Costruttore.
	 * @param ID
	 * @param posizione
	 */
	CampoData(size_t ID, const OrigineArea& posizione):
		CampoNumerico{ID,posizione,(size_t)10,'/',Maschera{"__/__/____",'_'}} {}
	/**
	 * Distruttore
	 */
	virtual ~CampoData(){}
	/**
	 * Numero di giorni dal 01/01/0001 alla data inserita. La data 01/01/0001 è pari a 1 gg, se
	 * la data è nulla o incompleta, il valore restituito è 0.
	 * @return
	 */
	virtual double valore()const override{return _data != nullptr ? _data->valore(UnitàTemporale::GIORNO) : 0.0;}
	/**
	 * Data inserita.
	 * @return
	 */
	pData data()const{return _data;}


protected:
		/* SLOT */
	virtual void inputTastiera(const Tastiera& tastiera)override; ///< segnale input tastiera (tasto)


	pData _data = nullptr;
};

} /* namespace GUI */

#endif /* SRC_CAMPO_DATA_H_ */
