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
 * @file  campo_numerico.cpp
 * @author Dr. Domenico della Peruta
 * @date 02-08-2018
 * @version 1.0.1, 01-09-2018
 *
 * @brief File contenente l'implementazione dei metodi della classe CampoNulerico.
 *
 * @namespace GUI
 * @class CampoNumerico
 */
#include "campo_numerico.h"
using namespace GUI;

void CampoNumerico::inputTastiera(const Tastiera& tastiera){
	const bool numero = tastiera.carattere() >= '0' && tastiera.carattere() <= '9';
	const bool separatoreDecimale = tastiera.carattere() == separatore;
	const bool segno = tastiera.carattere() == '-';
	const bool cancella = tastiera.carattere() == 127;
	bool conferma = numero || cancella;

	if(input->testo().numeroCaratteri() == 0)//primo carattere
		conferma = conferma || segno;
	//controllo presenza del punto di separazione
	bool separatoreNonInserito = true;
	for(auto carattere : input->testo().stringa())
		if(carattere == separatore)
			separatoreNonInserito = false;
	if(separatoreNonInserito)
		conferma = conferma || separatoreDecimale;

	if(conferma)
		Campo::inputTastiera(tastiera);
}

double CampoNumerico::valore()const{
	char *scarto;
	auto stringa = input->testo().stringa();
	if(stringa.find(',') >= 0 && stringa.find(',') < stringa.length())
		stringa.replace(stringa.find(','),1,".");
	return std::strtod(stringa.c_str(),&scarto);

}

bool CampoNumerico::verificaInput()const{
	string stringa = input->testo().latino1();
	if(mascheraInput.stringa().length() > 0){//se c'è la maschera attiva
		if(stringa.length() != mascheraInput.stringa().length()) return false;
		if(stringa.compare(mascheraInput.stringa())==0)return false;
	}
	for(auto i=0; i < stringa.length(); i++){
		if((stringa[i] < '0' || stringa[i] > '9') && stringa[i] != separatore ) return false;
	}
	return true;

}

void CampoNumerico::testo(const string& stringa){
	Campo::testo(stringa);//tronca se lunga...
	if(!verificaInput()){//input errato
		input->testo().elimina();
		input->testo().aggiungi(mascheraInput.stringa());
		indice = 0;
	}
}
