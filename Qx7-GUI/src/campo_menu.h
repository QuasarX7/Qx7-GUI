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
 * @file  campo_menu.h
 * @author Dr. Domenico della Peruta
 * @date 16-08-2018
 * @version 1.0.0, 16-08-2018
 *
 * @brief File contenente l'intestazione e l'implementazione della classe CampoMenu.
 *
 * @namespace GUI
 * @class CampoMenu
 */
#ifndef SRC_CAMPO_MENU_H_
#define SRC_CAMPO_MENU_H_

#include <vector>
using namespace std;

#include "campo.h"
#include "pulsante.h"
#include "etichetta.h"

namespace GUI {


class CampoMenu;
typedef shared_ptr<CampoMenu> pCampoMenu;
/**
 * La classe CampoMenu è un campo di input con l'aggiunta di un menu a tendina con i possibili
 * valori da inserire.
 */
class CampoMenu: public Campo {
public:
	/**
	 * Costruttore
	 * @param ID
	 * @param posizione
	 * @param listaInput
	 */
	CampoMenu(size_t ID, const OrigineArea& posizione, const vector<string>& listaInput);
	/**
	 * Distruttore
	 */
	virtual ~CampoMenu() {}

	virtual void disegna()override;
private:
	/**
	 * La lunghezza della stringa più grande della lista.
	 *
	 * @param lista
	 * @return
	 */
	size_t lunghezza(const vector<string>& lista);
	/**
	 * Genera voci del menu di ugnali dimensioni.
	 *
	 * @param voce
	 * @param lunghezzaVoce
	 * @return
	 */
	string lunghezzaFissa(const string& voce,size_t lunghezzaVoce);
	/**
	 * Estrae la stringa scritta nella voce menu (a lunghezza fissa).
	 * @param voce
	 * @return
	 */
	string realeLunghezzaVoce(const string& voce);

protected:
	/**
	 * Inizializza struttura menu.
	 * @param lista
	 */
	void creaMenu(const vector<string>& lista);
	/**
	 * Disegna e posiziona menu.
	 */
	void disegnaMenu();



	/* SLOT */
	virtual void azione(const Mouse& mouse)override;  // segnale 'click'
	virtual void passaggioMouse(const Cursore& mouse,Stato stato)override;

	bool listaVisibile = false;

	vector<pEtichetta> listaMenu;

	pPulsante pulsante;

	string voceMenuCorrente = "";


};




} /* namespace GUI */

#endif /* SRC_CAMPO_MENU_H_ */
