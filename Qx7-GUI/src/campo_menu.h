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
