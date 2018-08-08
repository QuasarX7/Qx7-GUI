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

	if(indice > 4){
		stringa = input->testo().latino1();
		_orario = Utili::crea<Orario>(
				std::atoi(stringa.substr(0,2).c_str()),
				std::atoi(stringa.substr(3,2).c_str())
		);
	}else{
		_orario = nullptr;
	}
}



