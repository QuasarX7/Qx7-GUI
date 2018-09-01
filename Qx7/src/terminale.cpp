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
 * @file terminale.cpp
 * @author Dr. Domenico della Peruta
 * @date 31-08-2018
 * @version 1.0.0, 01-09-2018
 *
 * @brief File contenente l'implementazione dei metodi della classe Terminale.
 *
 * @namespace Sistema
 * @class Terminale
 */
#include "terminale.h"
using namespace Sistema;

Terminale::Terminale(const string& comando):cmd{comando}{
	if(cmd.length() > 128)
	throw std::length_error{"Lunghezza caratteri comando da terminale maggiore di 128..."};
}

string Terminale::esegui()const{
	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe)
		return "ERRORE";
	char buffer[128];
	string result = "";
	while(!feof(pipe)){
		if(fgets(buffer, 128, pipe) != 0){
		  result += buffer;
		}
	}
	pclose(pipe);
	return result;
}


Testo Terminale::valoreInMemoria(){
	Terminale cmd{"pbpaste"};
	Testo incolla{cmd.esegui()};
	return incolla.frammento(0,incolla.numeroCaratteri()-1);
}

void Terminale::valoreDaMemorizzare(const Testo& copia){
	stringstream cmd;
	cmd << "echo \"" << copia.stringa() << "\" | pbcopy";
	Terminale terminale{cmd.str()};
	terminale.esegui();
}
