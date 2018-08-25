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
 * @file pannello.h
 * @author Dr. Domenico della Peruta
 * @date 02-08-2018
 * @version 1.0.0, 02-08-2018
 *
 * @brief File contenente l'intestazione e l'implementazione delle metodi della classe Pannello.
 *
 * @namespace GUI
 * @class Pannello
 */
#ifndef PANNELLO_H
#define PANNELLO_H

#include "vista.h"

namespace GUI{

	class Pannello;
	typedef shared_ptr<Pannello> pPannello;
	/**
	 * La classe Pannello è una "sotto-vista", permette di raggruppare gli elementi
	 * di una vista.
	 */
	class Pannello: public Vista{
	public:

		Pannello(const string& titoloPannello,const Area& campo,const Colore& colore=GRIGIO_SCURO, const Colore& bordoPannello=NERO);
		/**
		 * Distruttore
		 */
		virtual ~Pannello(){}
		/**
		 * Disegna il pannello
		 * @throw logic_error		quando la vista a cui appartiene la vista non è definita correttamente.
		 */
		virtual void disegna()override;
	protected:
		/**
		 * Posiziona lo sfondo del pannello in base alle coordinate assegnate del primo vertice.
		 */
		virtual void riposizionaSfondo()override;
		virtual void disegnaBarraScorrimentoVerticale(const OrigineArea& trasla = OrigineArea{0,0})const override;
		virtual void disegnaBarraScorrimentoOrizzontale(const OrigineArea& trasla = OrigineArea{0,0})const override;
		virtual void infoDebug()override;
		virtual Area estensioneAreaComponenti()const override;
		virtual void limiteCursoreVerticale(int estremoSup = 0)override;
		virtual void limiteCursoreOrizzontale(int estremoSX = 0)override;

		virtual bool eventoLocale(const Cursore& mouse)override;

	private:

	};
}
#endif /* PANNELLO_H */

