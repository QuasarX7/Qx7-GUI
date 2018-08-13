#include "campo_data.h"
using namespace GUI;



void CampoData::inputTastiera(const Tastiera& tastiera){
	const bool cancella = tastiera.carattere() == 127;
	bool conferma = true;
	string stringa = input->testo().latino1();
	if(!cancella){
		if(indice == 0){
			if(tastiera.carattere() < '0' || tastiera.carattere() > '3'){
				conferma = false;
			}
		}else if(indice == 1){
			if(stringa[0] == '3'){
				if(tastiera.carattere() < '0' || tastiera.carattere() > '1'){
					conferma = false;
				}
			}
		}else if(indice == 3 || indice == 2){
			if(tastiera.carattere() < '0' || tastiera.carattere() > '1'){
				conferma = false;
			}
		}else if(indice == 4){
			if(stringa[3] == '1'){
				if(tastiera.carattere() < '0' || tastiera.carattere() > '2'){
					conferma = false;
				}
			}
		}
	}

	if(conferma)
		CampoNumerico::inputTastiera(tastiera);

	if(verificaInput()){

		stringa = input->testo().latino1();
		_data = Utili::crea<Data>(
				std::atoi(stringa.substr(0,2).c_str()),
				std::atoi(stringa.substr(3,2).c_str()),
				std::atoi(stringa.substr(6,4).c_str())
		);

	}else{
		_data = nullptr;
	}
}


