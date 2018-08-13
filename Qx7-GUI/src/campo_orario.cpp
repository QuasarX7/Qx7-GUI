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
 * @file  campo_orario.cpp
 * @author Dr. Domenico della Peruta
 * @date 25-05-2018
 * @version 1.0.1, 15-07-2018
 *
 * @brief File contenente l'implementazione della classe CampoOrario.
 *
 * @namespace GUI
 * @class CampoOrario
 */
#include "campo_orario.h"
using namespace GUI;




void CampoOrario::inputTastiera(const Tastiera& tastiera){
	const bool cancella = tastiera.carattere() == 127;
	bool conferma = true;
	string stringa = input->testo().latino1();
	if(!cancella){
		if(indice == 0){
			if(tastiera.carattere() < '0' || tastiera.carattere() > '2'){
				conferma = false;
			}
		}else if(indice == 1){
			if(stringa[0] == '2')
				if(tastiera.carattere() < '0' || tastiera.carattere() > '3'){
					conferma = false;
				}
		}else if(indice == 3 || indice == 2){
			if(tastiera.carattere() < '0' || tastiera.carattere() > '5'){
				conferma = false;
			}
		}
	}

	if(conferma)
		CampoNumerico::inputTastiera(tastiera);

	if(verificaInput()){
		stringa = input->testo().latino1();
		_orario = Utili::crea<Orario>(
				std::atoi(stringa.substr(0,2).c_str()),
				std::atoi(stringa.substr(3,2).c_str())
		);
	}else{
		_orario = nullptr;
	}
}

