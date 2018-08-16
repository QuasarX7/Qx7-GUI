#include "campo_menu.h"
using namespace GUI;

CampoMenu::CampoMenu(size_t ID, const OrigineArea& posizione, const vector<string>& listaInput):
		Campo{ID,posizione,lunghezza(listaInput)}
{
	pulsante = Utili::crea<Pulsante>(
			NO_ID,
			"+",
			OrigineArea{
				posizione.x()+area.dimensione().lunghezza()+8,
				posizione.y()+2
			}
	);
	area.dimensione(
			DimensioneArea{
				area.dimensione().altezza(),
				area.dimensione().lunghezza()+pulsante->dimensione().lunghezza()+10
			}
	);
	bordoFocus->dimensiona(
			bordoFocus->altezza(),
			bordoFocus->lunghezza()+pulsante->dimensione().lunghezza()+10
	);
	creaMenu(listaInput);
}

size_t CampoMenu::lunghezza(const vector<string>& lista){
	size_t lung = 0;
	for(string s: lista){
		Testo t{s};
		if(t.numeroCaratteri() > lung)lung=t.numeroCaratteri();
	}
	return lung;
}

void CampoMenu::disegna(){
	glPushMatrix();
    if(pulsante != nullptr){
    	pulsante->sposta(
    			OrigineArea{
    				area.origine().x()+area.dimensione().lunghezza()-pulsante->dimensione().lunghezza()-2,
    				area.origine().y()+2
				}
    	);
    	pulsante->disegna();
    }
    if(listaVisibile)
    	disegnaMenu();
    Campo::disegna();
    glPopMatrix();

}

void CampoMenu::creaMenu(const vector<string>& lista){
	int i=1;
	size_t lunghezzaVoce = lunghezza(lista);
	for(string nomeVoce: lista){
		pEtichetta voceMenu = Utili::crea<Etichetta>(
				NO_ID,
				lunghezzaFissa(nomeVoce,lunghezzaVoce),
				OrigineArea{
					origine().x() ,
					origine().y()+(i++)*19 + 7
				}
		);
		voceMenu->decora(GRIGIO_CHIARO,GRIGIO_SCURO);
		listaMenu.push_back(voceMenu);
	}
}

void CampoMenu::disegnaMenu(){
	int i=1;
	for(pEtichetta voceMenu: listaMenu){
		if(voceMenu != nullptr){
			voceMenu->sposta(
				OrigineArea{
					origine().x(),
					origine().y()+(i++)*19 + 7
				}
			);
			voceMenu->disegna();
		}
	}
}

void CampoMenu::azione(const Mouse& mouse){
	if(eventoLocale(mouse.posizione())){ // campoMenu e pulsante
		assegnaFocus();
		if(pulsante != nullptr){
			if(pulsante->eventoLocale(mouse.posizione())){
				if(mouse.pulsante() == PulsanteMouse::SINISTRO){
					if(mouse.stato() == StatoPulsante::SU){
						listaVisibile = !listaVisibile;//commuta
						if(listaVisibile){
							pulsante->rinomina("-");
							pulsante->colora(ROSSO,ColoreComponente::TESTO);
							pulsante->colora(ROSSO,ColoreComponente::BORDO);
						}else{
							pulsante->rinomina("+");
							pulsante->colora(NERO,ColoreComponente::TESTO);
							pulsante->colora(NERO,ColoreComponente::BORDO);

						}
						glutPostRedisplay();
					}
				}
			}
		}
	}else if(listaVisibile){
		if(mouse.pulsante() == PulsanteMouse::SINISTRO){
			if(mouse.stato() == StatoPulsante::SU){
				for(pEtichetta voceMenu: listaMenu){
					if(voceMenu != nullptr){
						if(voceMenu->eventoLocale(mouse.posizione())){
							listaVisibile = !listaVisibile;//commuta
							if(listaVisibile){
								pulsante->rinomina("-");
								pulsante->colora(ROSSO,ColoreComponente::TESTO);
								pulsante->colora(ROSSO,ColoreComponente::BORDO);
							}else{
								pulsante->rinomina("+");
								pulsante->colora(NERO,ColoreComponente::TESTO);
								pulsante->colora(NERO,ColoreComponente::BORDO);
								testo(voceMenuCorrente);
								voceMenuCorrente = "";
							}
							glutPostRedisplay();
							break;
						}
					}
				}
			}
		}
	}
}

void CampoMenu::passaggioMouse(const Cursore& mouse,Stato stato){
	Campo::passaggioMouse(mouse,stato);
	if(listaVisibile){
		for(pEtichetta voceMenu: listaMenu){
			if(voceMenu != nullptr){
				if(voceMenu->eventoLocale(mouse)){
					voceMenu->decora(GRIGIO_SCURO,NERO);
					voceMenu->colora(BLU,ColoreComponente::TESTO);
					voceMenuCorrente = realeLunghezzaVoce(voceMenu->testo().stringa());
				}else{
					voceMenu->decora(GRIGIO_CHIARO,GRIGIO_SCURO);
				}
			}
		}
	}
}

string CampoMenu::lunghezzaFissa(const string& voce,size_t lunghezzaVoce){
	string stringa = " "+ voce;
	int diff = lunghezzaVoce - Testo{voce}.numeroCaratteri();
	for(auto i=0; i < diff; i++)
		stringa += " ";
	return stringa + " ";
}


string CampoMenu::realeLunghezzaVoce(const string& voce){
	string reale = voce;
	auto i = voce.length()-1;
	for(; i > 0; i--){
		if(voce[i] != ' ')break;
	}
	reale.substr(0,i+1);
	return reale.substr(1,i);
}




