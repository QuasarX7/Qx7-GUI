/****************************************************************************
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
 * @file  campo_numerico.h
 * @author Dr. Domenico della Peruta
 * @date 02-08-2018
 * @version 1.0.0, 02-08-2018
 *
 * @brief File contenente l'intestazione e l'implementazione della classe CampoNulerico.
 *
 * @namespace GUI
 * @class CampoNumerico
 */
#ifndef SRC_CAMPO_NUMERICO_H_
#define SRC_CAMPO_NUMERICO_H_

#include "campo.h"

namespace GUI {
/**
 * La casse CampoNumerico è una classe derivata da Campo che permette un input di tipo numerico
 * (in virgola mobile).
 */
class CampoNumerico: public Campo {
	public:
		/**
		 * Costruttore.
		 * @param ID
		 * @param posizione
		 * @param numeroCaratteri
		 * @param maschera
		 */
		CampoNumerico(size_t ID, const OrigineArea& posizione, size_t numeroCaratteri,const Maschera& maschera=Maschera{"",'_'}):
			Campo{ID,posizione,numeroCaratteri,maschera}{}


		/**
		 * Distruttore.
		 */
		virtual ~CampoNumerico() {}
		/**
		 * Valore numerico in virgola moblile.
		 * @return
		 */
		virtual double valore()const;
	protected:
		virtual void inputTastiera(const Tastiera& tastiera)override; ///< segnale input tastiera (tasto)

	};

	typedef shared_ptr<CampoNumerico> pCampoNumerico;

} /* namespace GUI */

#endif /* SRC_CAMPO_NUMERICO_H_ */
